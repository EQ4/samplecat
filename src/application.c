#include <glib.h>
#include <glib-object.h>
#include <config.h>
#include <sample.h>


#define TYPE_APPLICATION (application_get_type ())
#define APPLICATION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_APPLICATION, Application))
#define APPLICATION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_APPLICATION, ApplicationClass))
#define IS_APPLICATION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_APPLICATION))
#define IS_APPLICATION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_APPLICATION))
#define APPLICATION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_APPLICATION, ApplicationClass))

typedef struct _Application Application;
typedef struct _ApplicationClass ApplicationClass;
typedef struct _ApplicationPrivate ApplicationPrivate;

struct _Application {
	GObject parent_instance;
	ApplicationPrivate * priv;
	gint state;
	gchar* cache_dir;
};

struct _ApplicationClass {
	GObjectClass parent_class;
};


static gpointer application_parent_class = NULL;

GType application_get_type (void) G_GNUC_CONST;
enum  {
	APPLICATION_DUMMY_PROPERTY
};
Application* application_new (void);
Application* application_construct (GType object_type);
void application_emit_icon_theme_changed (Application* self, const gchar* s);
static GObject * application_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void application_finalize (GObject* obj);


Application* application_construct (GType object_type) {
	Application * self = NULL;
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	self = (Application*) g_object_new (object_type, NULL);
	self->state = 1;
	_tmp0_ = g_get_home_dir ();
	_tmp1_ = g_build_filename (_tmp0_, ".config", PACKAGE, "cache", NULL, NULL);
	self->cache_dir = _tmp1_;
	return self;
}


Application* application_new (void) {
	return application_construct (TYPE_APPLICATION);
}


void application_emit_icon_theme_changed (Application* self, const gchar* s) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (s != NULL);
	g_signal_emit_by_name (self, "icon-theme", s);
}


static GObject * application_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	parent_class = G_OBJECT_CLASS (application_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	return obj;
}


static void application_class_init (ApplicationClass * klass) {
	application_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->constructor = application_constructor;
	G_OBJECT_CLASS (klass)->finalize = application_finalize;
	g_signal_new ("icon_theme", TYPE_APPLICATION, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__STRING, G_TYPE_NONE, 1, G_TYPE_STRING);
	g_signal_new ("selection_changed", TYPE_APPLICATION, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__POINTER, G_TYPE_NONE, 1, G_TYPE_POINTER);
}


static void application_instance_init (Application * self) {
	self->state = 0;
}


static void application_finalize (GObject* obj) {
	G_OBJECT_CLASS (application_parent_class)->finalize (obj);
}


GType application_get_type (void) {
	static volatile gsize application_type_id__volatile = 0;
	if (g_once_init_enter (&application_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (ApplicationClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) application_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (Application), 0, (GInstanceInitFunc) application_instance_init, NULL };
		GType application_type_id;
		application_type_id = g_type_register_static (G_TYPE_OBJECT, "Application", &g_define_type_info, 0);
		g_once_init_leave (&application_type_id__volatile, application_type_id);
	}
	return application_type_id__volatile;
}



