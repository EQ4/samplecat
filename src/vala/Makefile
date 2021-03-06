packages=--pkg config --pkg posix --pkg gdk-2.0 --pkg gtk+-2.0 --pkg gmodule-2.0  --pkg debug
vapidir=--vapidir=. --vapidir=../../lib/debug model.vala

all:
	valac -C -H spectrogram_widget.h --pkg gtk+-2.0 --pkg gmodule-2.0 spectrogram_widget.vala

application.c: application.vala
	valac -C -H application.h $(packages) --pkg samplecat $(vapidir) application.vala

Xmodel.c: model.vala
	valac -C -H model.h $(packages) --pkg samplecat $(vapidir)
	@sed -i -e "/\#include <gobject\/gvaluecollector.h>/a#include <model.h>" model.c # append
	@sed -i -e "/\#include <gobject\/gvaluecollector.h>/a#include <application.h>" model.c # append
	@sed -i -e "/typedef struct _SamplecatModel SamplecatModel/d" model.h
	@sed -i -e "/^typedef struct _SamplecatModel/d" model.c
	@sed -i -e "s/^struct _/struct x_/" model.c
	@sed -i -e "s/^struct x_SamplecatParamSpecFilter/struct SamplecatParamSpecFilter/" model.c
	@sed -i -e "s/^struct x_SamplecatModelPrivate/struct SamplecatModelPrivate/" model.c
	mv model.c model.h ..

model.c: model.vala
	valac -C -H model.h $(packages) --pkg samplecat $(vapidir)
	@sed -i -e "/\#include <gobject\/gvaluecollector.h>/a#include <application.h>" model.c # append

list_store.c: list_store.vala
	valac -C -H list_store.h $(packages) --pkg samplecat $(vapidir) list_store.vala
	@sed -i -e "/^typedef struct _SamplecatListStore /d" list_store.c
	@sed -i -e "/^typedef struct _SamplecatListStoreClass/d" list_store.c
	@sed -i -e "/^typedef struct _SamplecatListStorePrivate/d" list_store.c
	@sed -i -e "s/^struct _SamplecatListStore /struct _SamplecatListStoreX /" list_store.c
	@sed -i -e "s/^struct _SamplecatListStoreClass /struct _SamplecatListStoreClassX /" list_store.c
	@sed -i -e "s/^struct _SamplecatFilter /struct _SamplecatFilterX /" list_store.h
	@sed -i -e "s/^struct _SamplecatFilterClass /struct _SamplecatFilterClassX /" list_store.h
	@sed -i -e "s/^struct _SamplecatFilters /struct _SamplecatFiltersX /" list_store.h
	@sed -i -e "s/^struct _SamplecatModel /struct _SamplecatModelX /" list_store.h
	@sed -i -e "s/^struct _SamplecatModelClass /struct _SamplecatModelClassX /" list_store.h

#check vala does not add an unneccesary include for glew.h
gl_spectrogram_view.c: gl_spectrogram_view.vala
	valac -C -H gl_spectrogram_view.h --vapidir=../../lib/waveform/agl --pkg gtk+-2.0 --pkg gl --pkg glu --pkg gtkglext-1.0 --pkg gmodule-2.0 --pkg agl gl_spectrogram_view.vala
