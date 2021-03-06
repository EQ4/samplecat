## Process this file with automake to produce Makefile.in

VALA_DIR =
SUBDIRS = gimp db $(VALA_DIR)

AM_CFLAGS = \
	-g -Wall -O2 \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DIMAGES_DIR=\"$(imagesdir)\" \
	-I$(top_srcdir)/lib \
	-I$(top_srcdir)/lib/file_manager \
	-I$(top_srcdir)/lib/waveform \
	-I$(top_srcdir)/xdgmime \
	-I./dir_tree \
	-I./gimp \
	$(SAMPLECAT_CFLAGS) \
	$(FFTW3_CFLAGS) \
	$(OPENGL_CFLAGS) \
	$(JACK_CFLAGS) \
	$(SAMPLERATE_CFLAGS) \
	$(SNDFILE_CFLAGS) \
	$(FFMPEG_CFLAGS) \
	$(ZLIB_CFLAGS) \
	$(GTK_CFLAGS) \
	$(GMODULE_LIBS) \
	$(DBUS_CFLAGS) $(MYSQL_CFLAGS) $(TRACKER_CFLAGS)

AM_CXXFLAGS = $(AM_CFLAGS)

bin_PROGRAMS = samplecat

if ENABLE_AYYI
AYYI_SRC = ayyi.c ayyi.h ayyi_model.c ayyi_model.h
endif

AD_SRC = audio_decoder/ad.h audio_decoder/ad_plugin.h audio_decoder/ad_plugin.c \
	audio_decoder/ad_soundfile.c \
	audio_decoder/ad_flac.c \
	audio_decoder/ad_ffmpeg.c \
	audio_decoder/ffcompat.h

if ENABLE_FFTW3
FFT_SRC = spectrogram_widget.c spectrogram_widget.h
FFT_ANANALYSERS_SRC = \
	audio_analysis/spectrogram/spectrogram.c audio_analysis/spectrogram/spectrogram.h \
	audio_analysis/spectrogram/sndfile_window.c audio_analysis/spectrogram/sndfile_window.h
endif

if ENABLE_OPENGL
if ENABLE_FFTW3
OPENGL_FFTW_SRC = gl_spectrogram_view.c gl_spectrogram_view.h
endif
OPENGL_SRC = \
	$(OPENGL_FFTW_SRC) \
	rotator.c rotator.h
OPENGL_LDFLAGS = \
	$(top_srcdir)/lib/waveform/agl/.libs/libagl.a \
	$(top_srcdir)/lib/waveform/transition/.libs/libtransition.a \
	$(OPENGL_LIBS)
endif

if ENABLE_GDL
GDL_LDFLAGS=$(top_srcdir)/lib/gdl/libgdl.a $(XML_LIBS)
endif

if ENABLE_AYYIDBUS
AUDITIONER_AYYI = auditioner.c
endif

if ENABLE_GPLAYER
AUDITIONER_GPLAYER = gplayer.c
endif

if ENABLE_JACK
AUDITIONER_JACK = jack_player.c jack_player.h ladspa_proc.c ladspa_proc.h
endif

AUDIOANALYSERS_SRC = \
	$(FFT_ANANALYSERS_SRC) \
	audio_analysis/meter/peak.c audio_analysis/meter/peak.h \
	audio_analysis/waveform/waveform.c audio_analysis/waveform/waveform.h \
	audio_analysis/ebumeter/ebur128.cc audio_analysis/ebumeter/ebur128.h \
	audio_analysis/ebumeter/ebu_r128_proc.cc audio_analysis/ebumeter/ebu_r128_proc.h

samplecat_SOURCES = \
	typedefs.h types.h \
	main.c \
	application.c application.h \
	model.c model.h \
	list_store.c list_store.h \
	window.c window.h \
	progress_dialog.c progress_dialog.h \
	listview.c listview.h \
	inspector.c inspector.h \
	player_control.c player_control.h \
	sample.c sample.h \
	worker.c worker.h \
	directories.c directories.h \
	dh_link.c dh_link.h \
	dh_tree.c dh_tree.h \
	cellrenderer_hypertext.c cellrenderer_hypertext.h \
	colour_box.c colour_box.h \
	dnd.c dnd.h \
	support.c support.h \
	console_view.c console_view.h \
	icon_theme.c icon_theme.h \
	table.c table.h \
	$(AUDIOANALYSERS_SRC) \
	$(AD_SRC) \
	$(FFT_SRC) \
	$(OPENGL_SRC) \
	$(AYYI_SRC) \
	$(AUDITIONER_AYYI) $(AUDITIONER_GPLAYER) $(AUDITIONER_JACK)

samplecat_LDADD = \
	$(top_srcdir)/lib/utils/libutils.a \
	$(top_srcdir)/lib/file_manager/libfilemanager.a \
	$(top_srcdir)/lib/xdgmime/libxdgmime.a \
	$(top_srcdir)/lib/dir_tree/libdirtree.a \
	$(top_srcdir)/lib/debug/libdebug.a \
	$(top_srcdir)/lib/samplecat/libsamplecat.a \
	$(GDL_LDFLAGS) \
	gimp/libgimpwidgets.a \
	db/libsamplecatdb.a \
	$(top_srcdir)/lib/waveform/waveform/.libs/libwaveform.a \
	$(SAMPLECAT_LIBS) \
	$(AYYI_LIBS) \
	$(DBUS_LIBS) \
	$(TRACKER_LIBS) \
	$(SQLITE_LIBS) \
	$(GTK_LIBS) $(MYSQL_LDFLAGS) \
	$(JACK_LIBS) $(SNDFILE_LIBS) ${SAMPLERATE_LIBS} \
	$(GTHREAD_LIBS) \
	$(FFTW3_LIBS) \
	$(OPENGL_LDFLAGS) \
	$(LIBASS_LDFLAGS) \
	$(ZLIB_LIBS) \
	$(FFMPEG_LIBS) \
	-ldl
