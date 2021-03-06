/* gl_spectrogram_view.c generated by valac 0.12.1, the Vala compiler
 * generated from gl_spectrogram_view.vala, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <gdk-pixbuf/gdk-pixdata.h>
#include <gtk/gtk.h>
#include <float.h>
#include <math.h>
#include <gdk/gdk.h>
#include <gtkglext-1.0/gdk/gdkgl.h>
#include <gtkglext-1.0/gtk/gtkgl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <string.h>
#include "agl/utils.h"
#include "agl/shader.h"


#define TYPE_GL_SPECTROGRAM (gl_spectrogram_get_type ())
#define GL_SPECTROGRAM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_GL_SPECTROGRAM, GlSpectrogram))
#define GL_SPECTROGRAM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_GL_SPECTROGRAM, GlSpectrogramClass))
#define IS_GL_SPECTROGRAM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_GL_SPECTROGRAM))
#define IS_GL_SPECTROGRAM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_GL_SPECTROGRAM))
#define GL_SPECTROGRAM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_GL_SPECTROGRAM, GlSpectrogramClass))

typedef struct _GlSpectrogram GlSpectrogram;
typedef struct _GlSpectrogramClass GlSpectrogramClass;
typedef struct _GlSpectrogramPrivate GlSpectrogramPrivate;
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

typedef void (*SpectrogramReady) (gchar* filename, GdkPixbuf* a, void* user_data_, void* user_data);
struct _GlSpectrogram {
	GtkDrawingArea parent_instance;
	GlSpectrogramPrivate * priv;
};

struct _GlSpectrogramClass {
	GtkDrawingAreaClass parent_class;
};

struct _GlSpectrogramPrivate {
	struct _agl* agl;
	gchar* _filename;
	GdkPixbuf* pixbuf;
	gboolean gl_init_done;
	GLuint Textures[2];
};


static gpointer gl_spectrogram_parent_class = NULL;
extern GlSpectrogram* gl_spectrogram_instance;
GlSpectrogram* gl_spectrogram_instance = NULL;
static GdkGLContext* gl_spectrogram_glcontext = NULL;

void get_spectrogram_with_target (gchar* path, SpectrogramReady on_ready, void* on_ready_target, void* user_data);
void cancel_spectrogram (gchar* path);
GType gl_spectrogram_get_type (void) G_GNUC_CONST;
#define GL_SPECTROGRAM_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_GL_SPECTROGRAM, GlSpectrogramPrivate))
enum  {
	GL_SPECTROGRAM_DUMMY_PROPERTY
};
#define GL_SPECTROGRAM_near 10.0
#define GL_SPECTROGRAM_far (-100.0)
GlSpectrogram* gl_spectrogram_new (void);
GlSpectrogram* gl_spectrogram_construct (GType object_type);
void gl_spectrogram_set_gl_context (GdkGLContext* _glcontext);
static void gl_spectrogram_load_texture (GlSpectrogram* self);
static gboolean gl_spectrogram_real_configure_event (GtkWidget* base, GdkEventConfigure* event);
static gboolean gl_spectrogram_real_expose_event (GtkWidget* base, GdkEventExpose* event);
static void gl_spectrogram_set_projection (GlSpectrogram* self);
void gl_spectrogram_set_file (GlSpectrogram* self, gchar* filename);
static void _lambda0_ (gchar* filename, GdkPixbuf* _pixbuf, void* b, GlSpectrogram* self);
static void __lambda0__spectrogram_ready (gchar* filename, GdkPixbuf* a, void* user_data_, gpointer self);
static void gl_spectrogram_real_unrealize (GtkWidget* base);
static void gl_spectrogram_finalize (GObject* obj);


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


GlSpectrogram* gl_spectrogram_construct (GType object_type) {
	GlSpectrogram * self = NULL;
	GdkGLConfig* _tmp0_ = NULL;
	GdkGLConfig* glconfig;
	GlSpectrogram* _tmp1_;
	self = (GlSpectrogram*) g_object_new (object_type, NULL);
	gtk_widget_add_events ((GtkWidget*) self, (gint) ((GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK) | GDK_POINTER_MOTION_MASK));
	gtk_widget_set_size_request ((GtkWidget*) self, 200, 100);
	_tmp0_ = gdk_gl_config_new_by_mode (GDK_GL_MODE_RGB | GDK_GL_MODE_DOUBLE);
	glconfig = _tmp0_;
	gtk_widget_set_gl_capability ((GtkWidget*) self, glconfig, gl_spectrogram_glcontext, TRUE, (gint) GDK_GL_RGBA_TYPE);
	_tmp1_ = _g_object_ref0 (self);
	_g_object_unref0 (gl_spectrogram_instance);
	gl_spectrogram_instance = _tmp1_;
	_g_object_unref0 (glconfig);
	return self;
}


GlSpectrogram* gl_spectrogram_new (void) {
	return gl_spectrogram_construct (TYPE_GL_SPECTROGRAM);
}


void gl_spectrogram_set_gl_context (GdkGLContext* _glcontext) {
	GdkGLContext* _tmp0_;
	g_return_if_fail (_glcontext != NULL);
	_tmp0_ = _g_object_ref0 (_glcontext);
	_g_object_unref0 (gl_spectrogram_glcontext);
	gl_spectrogram_glcontext = _tmp0_;
}


static void gl_spectrogram_load_texture (GlSpectrogram* self) {
	GdkGLDrawable* _tmp0_ = NULL;
	GdkGLDrawable* _tmp1_;
	GdkGLDrawable* gldrawable;
	gboolean _tmp2_;
	gboolean _tmp3_;
	GdkPixbuf* _tmp4_ = NULL;
	GdkPixbuf* scaled;
	gint _tmp5_;
	GLint n_colour_components;
	GLenum _tmp6_ = 0U;
	gint _tmp7_;
	GLenum format;
	gint _tmp8_;
	gint _tmp9_;
	guint8* _tmp10_ = NULL;
	GLint _tmp11_;
	g_return_if_fail (self != NULL);
	_tmp0_ = gtk_widget_get_gl_drawable ((GtkWidget*) self);
	_tmp1_ = _g_object_ref0 (_tmp0_);
	gldrawable = _tmp1_;
	_tmp2_ = gdk_gl_drawable_gl_begin (gldrawable, gtk_widget_get_gl_context((GtkWidget*)self));
	if (!_tmp2_) {
		g_print ("gl context error!\n");
	}
	_tmp3_ = gdk_gl_drawable_gl_begin (gldrawable, gtk_widget_get_gl_context((GtkWidget*)self));
	if (!_tmp3_) {
		_g_object_unref0 (gldrawable);
		return;
	}
	glBindTexture (GL_TEXTURE_2D, self->priv->Textures[0]);
	_tmp4_ = gdk_pixbuf_scale_simple (self->priv->pixbuf, 256, 256, GDK_INTERP_BILINEAR);
	scaled = _tmp4_;
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat) GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint) GL_LINEAR);
	_tmp5_ = gdk_pixbuf_get_n_channels (scaled);
	n_colour_components = (GLint) _tmp5_;
	_tmp7_ = gdk_pixbuf_get_n_channels (scaled);
	if (_tmp7_ == 4) {
		_tmp6_ = GL_RGBA;
	} else {
		_tmp6_ = GL_RGB;
	}
	format = _tmp6_;
	_tmp8_ = gdk_pixbuf_get_width (scaled);
	_tmp9_ = gdk_pixbuf_get_height (scaled);
	_tmp10_ = gdk_pixbuf_get_pixels (scaled);
	_tmp11_ = gluBuild2DMipmaps (GL_TEXTURE_2D, n_colour_components, (GLsizei) _tmp8_, (GLsizei) _tmp9_, format, GL_UNSIGNED_BYTE, _tmp10_);
	if ((gboolean) _tmp11_) {
		g_print ("mipmap generation failed!\n");
	}
	g_object_unref ((GObject*) scaled);
	gdk_gl_drawable_gl_end (gldrawable);
	_g_object_unref0 (gldrawable);
}


static gboolean gl_spectrogram_real_configure_event (GtkWidget* base, GdkEventConfigure* event) {
	GlSpectrogram * self;
	gboolean result = FALSE;
	GdkGLDrawable* _tmp0_ = NULL;
	GdkGLDrawable* _tmp1_;
	GdkGLDrawable* gldrawable;
	gboolean _tmp2_;
	struct _agl* _tmp12_ = NULL;
	self = (GlSpectrogram*) base;
	_tmp0_ = gtk_widget_get_gl_drawable ((GtkWidget*) self);
	_tmp1_ = _g_object_ref0 (_tmp0_);
	gldrawable = _tmp1_;
	_tmp2_ = gdk_gl_drawable_gl_begin (gldrawable, gtk_widget_get_gl_context((GtkWidget*)self));
	if (!_tmp2_) {
		result = FALSE;
		_g_object_unref0 (gldrawable);
		return result;
	}
	glViewport ((GLint) 0, (GLint) 0, (GLsizei) ((GtkWidget*) self)->allocation.width, (GLsizei) ((GtkWidget*) self)->allocation.height);
	if (!self->priv->gl_init_done) {
		glGenTextures ((GLsizei) 1, self->priv->Textures);
		glEnable (GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, self->priv->Textures[0]);
		self->priv->gl_init_done = TRUE;
	}
	gdk_gl_drawable_gl_end (gldrawable);
	result = TRUE;
	_g_object_unref0 (gldrawable);
	_tmp12_ = agl_get_instance ();
	self->priv->agl = _tmp12_;
	return result;
}


static gboolean gl_spectrogram_real_expose_event (GtkWidget* base, GdkEventExpose* event) {
	GlSpectrogram * self;
	gboolean result = FALSE;
	GdkGLDrawable* _tmp0_ = NULL;
	GdkGLDrawable* _tmp1_;
	GdkGLDrawable* gldrawable;
	gboolean _tmp2_;
	gdouble x;
	gdouble w;
	gdouble top;
	gdouble botm;
	gboolean _tmp3_;
	self = (GlSpectrogram*) base;
	_tmp0_ = gtk_widget_get_gl_drawable ((GtkWidget*) self);
	_tmp1_ = _g_object_ref0 (_tmp0_);
	gldrawable = _tmp1_;
	_tmp2_ = gdk_gl_drawable_gl_begin (gldrawable, gtk_widget_get_gl_context((GtkWidget*)self));
	if (!_tmp2_) {
		result = FALSE;
		_g_object_unref0 (gldrawable);
		return result;
	}
	gl_spectrogram_set_projection (self);
	glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
	glClear ((GLbitfield) GL_COLOR_BUFFER_BIT);
	x = 0.0;
	w = (gdouble) ((GtkWidget*) self)->allocation.width;
	top = (gdouble) ((GtkWidget*) self)->allocation.height;
	botm = 0.0;
	if(self->priv->agl->use_shaders){
		self->priv->agl->shaders.texture->uniform.fg_colour = 0xffffffff;
		agl_use_program((AGlShader*)self->priv->agl->shaders.texture);
	}
	glEnable (GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, self->priv->Textures[0]);
	glBegin (GL_QUADS);
	glTexCoord2d (0.0, 0.0);
	glVertex2d (x, top);
	glTexCoord2d (1.0, 0.0);
	glVertex2d (x + w, top);
	glTexCoord2d (1.0, 1.0);
	glVertex2d (x + w, botm);
	glTexCoord2d (0.0, 1.0);
	glVertex2d (x, botm);
	glEnd ();
	_tmp3_ = gdk_gl_drawable_is_double_buffered (gldrawable);
	if (_tmp3_) {
		gdk_gl_drawable_swap_buffers (gldrawable);
	} else {
		glFlush ();
	}
	gdk_gl_drawable_gl_end (gldrawable);
	result = TRUE;
	_g_object_unref0 (gldrawable);
	return result;
}


static void gl_spectrogram_set_projection (GlSpectrogram* self) {
	gdouble left;
	gdouble right;
	gdouble top;
	gdouble bottom;
	g_return_if_fail (self != NULL);
	glViewport ((GLint) 0, (GLint) 0, (GLsizei) ((GtkWidget*) self)->allocation.width, (GLsizei) ((GtkWidget*) self)->allocation.height);
	glMatrixMode ((GLenum) GL_PROJECTION);
	glLoadIdentity ();
	left = 0.0;
	right = (gdouble) ((GtkWidget*) self)->allocation.width;
	top = (gdouble) ((GtkWidget*) self)->allocation.height;
	bottom = 0.0;
	glOrtho (left, right, bottom, top, GL_SPECTROGRAM_near, GL_SPECTROGRAM_far);
}


static void _lambda0_ (gchar* filename, GdkPixbuf* _pixbuf, void* b, GlSpectrogram* self) {
	if ((gboolean) _pixbuf) {
		if ((gboolean) self->priv->pixbuf) {
			g_object_unref ((GObject*) self->priv->pixbuf);
		}
		self->priv->pixbuf = _pixbuf;
		gl_spectrogram_load_texture (self);
		gtk_widget_queue_draw ((GtkWidget*) self);
	}
}


static void __lambda0__spectrogram_ready (gchar* filename, GdkPixbuf* a, void* user_data_, gpointer self) {
	_lambda0_ (filename, a, user_data_, self);
}


void gl_spectrogram_set_file (GlSpectrogram* self, gchar* filename) {
	gchar* _tmp0_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = g_strdup ((const gchar*) filename);
	_g_free0 (self->priv->_filename);
	self->priv->_filename = _tmp0_;
	cancel_spectrogram (NULL);
	get_spectrogram_with_target (filename, __lambda0__spectrogram_ready, self, NULL);
}


static void gl_spectrogram_real_unrealize (GtkWidget* base) {
	GlSpectrogram * self;
	self = (GlSpectrogram*) base;
	cancel_spectrogram (NULL);
	GTK_WIDGET_CLASS (gl_spectrogram_parent_class)->unrealize ((GtkWidget*) G_TYPE_CHECK_INSTANCE_CAST (self, GTK_TYPE_DRAWING_AREA, GtkDrawingArea));
}


static void gl_spectrogram_class_init (GlSpectrogramClass * klass) {
	gl_spectrogram_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GlSpectrogramPrivate));
	GTK_WIDGET_CLASS (klass)->configure_event = gl_spectrogram_real_configure_event;
	GTK_WIDGET_CLASS (klass)->expose_event = gl_spectrogram_real_expose_event;
	GTK_WIDGET_CLASS (klass)->unrealize = gl_spectrogram_real_unrealize;
	G_OBJECT_CLASS (klass)->finalize = gl_spectrogram_finalize;
}


static void gl_spectrogram_instance_init (GlSpectrogram * self) {
	self->priv = GL_SPECTROGRAM_GET_PRIVATE (self);
	self->priv->pixbuf = NULL;
	self->priv->gl_init_done = FALSE;
}


static void gl_spectrogram_finalize (GObject* obj) {
	GlSpectrogram * self;
	self = GL_SPECTROGRAM (obj);
	cancel_spectrogram (NULL);
	_g_free0 (self->priv->_filename);
	G_OBJECT_CLASS (gl_spectrogram_parent_class)->finalize (obj);
}


GType gl_spectrogram_get_type (void) {
	static volatile gsize gl_spectrogram_type_id__volatile = 0;
	if (g_once_init_enter (&gl_spectrogram_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (GlSpectrogramClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gl_spectrogram_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GlSpectrogram), 0, (GInstanceInitFunc) gl_spectrogram_instance_init, NULL };
		GType gl_spectrogram_type_id;
		gl_spectrogram_type_id = g_type_register_static (GTK_TYPE_DRAWING_AREA, "GlSpectrogram", &g_define_type_info, 0);
		g_once_init_leave (&gl_spectrogram_type_id__volatile, gl_spectrogram_type_id);
	}
	return gl_spectrogram_type_id__volatile;
}



