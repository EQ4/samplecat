/**
* +----------------------------------------------------------------------+
* | This file is part of Samplecat. http://ayyi.github.io/samplecat/     |
* | copyright (C) 2007-2015 Tim Orford <tim@orford.org>                  |
* +----------------------------------------------------------------------+
* | This program is free software; you can redistribute it and/or modify |
* | it under the terms of the GNU General Public License version 3       |
* | as published by the Free Software Foundation.                        |
* +----------------------------------------------------------------------+
*
*/
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <gtk/gtk.h>

#include "debug/debug.h"
#include "utils/pixmaps.h"
#include "file_manager/file_manager.h"
#include "file_manager/mimetype.h"
#include "typedefs.h"
#include "support.h"
#include "sample.h"
#include "model.h"
#include "listmodel.h"
#include "audio_decoder/ad.h"
#include "audio_analysis/waveform/waveform.h"
#include "worker.h"

typedef struct
{
	enum MsgType type;
	Sample*      sample;
} Message;

typedef struct
{
   Sample* sample;
   bool    success;
} WorkResult;

static GList*          msg_list = NULL;
static GAsyncQueue*    msg_queue = NULL;
static SamplecatModel* model = NULL;

static gpointer worker_thread (gpointer data);

static bool   on_overview_done  (gpointer);
static bool   on_peaklevel_done (gpointer);
static bool   on_ebur128_done   (gpointer);

// TODO move to audio_analysis/analyzers.c ?!
#include "audio_analysis/meter/peak.h"
static double calc_signal_max (Sample* sample) {
	return ad_maxsignal(sample->full_path);
}

#include "audio_analysis/ebumeter/ebur128.h"
static bool
calc_ebur128(Sample* sample)
{
	struct ebur128 ebur;
	if (!ebur128analyse(sample->full_path, &ebur)){
		if (sample->ebur) free(sample->ebur);
		sample->ebur = g_strdup_printf(ebur.err
			?	"-"
			:	"intgd loudness:%.1lf LU%s\n"
				"loudness range:%.1lf LU\n"
				"intgd threshold:%.1lf LU%s\n"
				"range threshold:%.1lf LU%s\n"
				"range min:%.1lf LU%s\n"
				"range max:%.1lf LU%s\n"
				"momentary max:%.1lf LU%s\n"
				"short term max:%.1lf LU%s\n"
				, ebur.integrated , ebur.lufs?"FS":""
				, ebur.range
				, ebur.integ_thr  , ebur.lufs?"FS":""
				, ebur.range_thr  , ebur.lufs?"FS":""
				, ebur.range_min  , ebur.lufs?"FS":""
				, ebur.range_max  , ebur.lufs?"FS":""
				, ebur.maxloudn_M , ebur.lufs?"FS":""
				, ebur.maxloudn_S , ebur.lufs?"FS":""
		);
		return true;
	}
	return false;
}


void
worker_thread_init(SamplecatModel* _model)
{
	dbg(3, "creating overview thread...");
	model = _model;

	msg_queue = g_async_queue_new();

	if(!g_thread_new("worker", worker_thread, NULL)){
		perr("failed to create worker thread");
	}
}


static bool
print_progress(gpointer user_data)
{
	int n = GPOINTER_TO_INT(user_data);
	if(n) statusbar_print(2, "updating %i items...", n);
	else statusbar_print(2, "");

	return G_SOURCE_REMOVE;
}


static gpointer
worker_thread(gpointer data)
{
	//TODO consider replacing the main loop with a blocking call on the async queue,
	//(g_async_queue_pop) waiting for messages.

	dbg(1, "new worker thread.");

	g_async_queue_ref(msg_queue);

	bool worker_timeout(gpointer data)
	{

		//check for new work
		while(g_async_queue_length(msg_queue)){
			Message* message = g_async_queue_pop(msg_queue); // blocks
			msg_list = g_list_append(msg_list, message);
			dbg(2, "new message! %p", message);
		}

		while(msg_list != NULL){
			Message* message = g_list_first(msg_list)->data;
			msg_list = g_list_remove(msg_list, message);

			Sample* sample = message->sample;
			if(message->type == MSG_TYPE_OVERVIEW){
				dbg(1, "queuing for overview: filename=%s.", sample->full_path);
				make_overview(sample);
				g_idle_add(on_overview_done, sample);
			}
			else if(message->type == MSG_TYPE_PEAKLEVEL){
				sample->peaklevel = calc_signal_max(message->sample);
				g_idle_add(on_peaklevel_done, sample);
			}
			else if(message->type == MSG_TYPE_EBUR128){
				WorkResult* result = g_new0(WorkResult, 1);
				result->sample = sample;
				result->success = calc_ebur128(message->sample);
				g_idle_add(on_ebur128_done, result);
			}

			g_idle_add(print_progress, GINT_TO_POINTER(g_list_length(msg_list)));

			g_free(message);
		}

		return TIMER_CONTINUE;
	}

	GMainContext* context = g_main_context_new();
	GSource* source = g_timeout_source_new(1000);
	gpointer _data = NULL;
	g_source_set_callback(source, worker_timeout, _data, NULL);
	g_source_attach(source, context);

	g_main_loop_run (g_main_loop_new (context, 0));

	return NULL;
}


static Message*
new_message(enum MsgType type, Sample* sample)
{
	Message* message = g_new0(Message, 1);
	message->type = type;
	message->sample = sample_ref(sample);
	return message;
}


void
request_overview(Sample* sample)
{
	if(!msg_queue) return;

	Message* message = g_new0(Message, 1);
	message->type = MSG_TYPE_OVERVIEW;
	message->sample = sample;

	dbg(2, "sample=%p filename=%s", sample, sample->full_path);
	sample_ref(sample);
	g_async_queue_push(msg_queue, message);
}


void
request_peaklevel(Sample* sample)
{
	if(!msg_queue) return;

	Message* message = g_new0(Message, 1);
	message->type = MSG_TYPE_PEAKLEVEL;
	message->sample = sample;

	dbg(2, "sample=%p filename=%s", sample, sample->full_path);
	sample_ref(sample);
	g_async_queue_push(msg_queue, message);
}


void
request_ebur128(Sample* sample)
{
	if(!msg_queue) return;

	dbg(2, "sample=%p filename=%s", sample, sample->full_path);

	g_async_queue_push(msg_queue, new_message(MSG_TYPE_EBUR128, sample));
}


static bool
on_overview_done(gpointer _sample)
{
	PF;
	Sample* sample = _sample;
	g_return_val_if_fail(sample, false);
	if(sample->overview){
		samplecat_model_update_sample (model, sample, COL_OVERVIEW, NULL);
	}else{
		dbg(1, "overview creation failed (no pixbuf).");
	}
	sample_unref(sample);

	return G_SOURCE_REMOVE;
}


static bool
on_peaklevel_done(gpointer _sample)
{
	Sample* sample = _sample;
	dbg(1, "peaklevel=%.2f id=%i", sample->peaklevel, sample->id);
	samplecat_model_update_sample (model, sample, COL_PEAKLEVEL, NULL);
	sample_unref(sample);
	return G_SOURCE_REMOVE;
}


static bool
on_ebur128_done(gpointer _result)
{
	WorkResult* result = _result;
	if(result->success) samplecat_model_update_sample (model, result->sample, COL_X_EBUR, NULL);
	sample_unref(result->sample);
	g_free(result);
	return G_SOURCE_REMOVE;
}


