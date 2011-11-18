#ifndef __AD_PLUGIN_H__
#define __AD_PLUGIN_H__
#include <stdint.h>
#include "audio_decoder/ad.h"

typedef struct {
	void *  (*open)(const char *, struct adinfo *);
	int     (*close)(void *);
	int     (*info)(void *, struct adinfo *);
	int64_t (*seek)(void *, int64_t);
	ssize_t (*read_dbl)(void *, double *, size_t);
} ad_plugin;

void *  ad_open_null(const char *, struct adinfo *);
int     ad_close_null(void *);
int     ad_info_null(void *, struct adinfo *);
int64_t ad_seek_null(void *, int64_t);
ssize_t ad_read_null(void *, double*, size_t);

/* hardcoded backends */
const ad_plugin * get_sndfile();
const ad_plugin * get_libflac();
const ad_plugin * get_ffmpeg();
#endif
