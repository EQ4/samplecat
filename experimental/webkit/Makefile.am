
bin_PROGRAMS = samplecat_webkit

AUDIOANALYSERS_SRC = \
	$(FFT_ANANALYSERS_SRC) \
	$(top_srcdir)/src/audio_analysis/meter/peak.c $(top_srcdir)/src/audio_analysis/meter/peak.h \
	$(top_srcdir)/src/audio_analysis/waveform/waveform.c $(top_srcdir)/src/audio_analysis/waveform/waveform.h \
	$(top_srcdir)/src/audio_analysis/ebumeter/ebur128.cc $(top_srcdir)/src/audio_analysis/ebumeter/ebur128.h \
	$(top_srcdir)/src/audio_analysis/ebumeter/ebu_r128_proc.cc $(top_srcdir)/src/audio_analysis/ebumeter/ebu_r128_proc.h

AD_SRC = ../../src/audio_decoder/ad.h \
	../../src/audio_decoder/ad_plugin.h ../../src/audio_decoder/ad_plugin.c \
	../../src/audio_decoder/ad_soundfile.c \
	../../src/audio_decoder/ad_flac.c \
	../../src/audio_decoder/ad_ffmpeg.c \
	../../src/audio_decoder/ffcompat.h

samplecat_webkit_SOURCES = \
	webkit.c \
	util.c util.h \
	table.c table.h \
	$(top_srcdir)/src/sample.c $(top_srcdir)/src/sample.h \
	$(top_srcdir)/src/model.c $(top_srcdir)/src/model.h \
	$(top_srcdir)/src/worker.c $(top_srcdir)/src/worker.h \
	$(AUDIOANALYSERS_SRC) \
	$(AD_SRC)

AM_CFLAGS = \
	-g -Wall -O2 \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DIMAGES_DIR=\"$(imagesdir)\" \
	-I$(top_srcdir)/lib \
	-I$(top_srcdir)/xdgmime \
	-I$(top_srcdir) \
	-I$(top_srcdir)/src \
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
	$(MYSQL_CFLAGS) \
	$(WEBKIT_CFLAGS)

AM_CXXFLAGS = $(AM_CFLAGS)

samplecat_webkit_LDADD = \
	$(top_srcdir)/lib/utils/libutils.a \
	$(top_srcdir)/lib/file_manager/libfilemanager.a \
	$(top_srcdir)/lib/xdgmime/libxdgmime.a \
	$(top_srcdir)/lib/dir_tree/libdirtree.a \
	$(top_srcdir)/lib/samplecat/libsamplecat.a \
	$(top_srcdir)/src/db/libsamplecatdb.a \
	$(top_srcdir)/lib/debug/libdebug.a \
	$(top_srcdir)/lib/utils/libutils.a \
	$(SAMPLECAT_LIBS) \
	$(AYYI_LIBS) \
	$(TRACKER_LIBS) \
	$(SQLITE_LIBS) \
	$(GTK_LIBS) $(MYSQL_LDFLAGS) \
	$(JACK_LIBS) $(SNDFILE_LIBS) ${SAMPLERATE_LIBS} \
	$(GTHREAD_LIBS) \
	$(FFTW3_LIBS) \
	$(OPENGL_LIBS) \
	$(ZLIB_LIBS) \
	$(FFMPEG_LIBS) \
	$(WEBKIT_LIBS)

