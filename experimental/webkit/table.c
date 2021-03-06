/* table.c generated by valac 0.16.0, the Vala compiler
 * generated from table.vala, do not modify */

/*
  This file is part of Samplecat. http://samplecat.orford.org
  copyright (C) 2007-2012 Tim Orford and others.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License version 3
  as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#include <glib.h>
#include <glib-object.h>
#include <webkit/webkit.h>
#include <stdlib.h>
#include <string.h>


#define TYPE_TABLE (table_get_type ())
#define TABLE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TABLE, Table))
#define TABLE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TABLE, TableClass))
#define IS_TABLE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TABLE))
#define IS_TABLE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TABLE))
#define TABLE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TABLE, TableClass))

typedef struct _Table Table;
typedef struct _TableClass TableClass;
typedef struct _TablePrivate TablePrivate;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

struct _Table {
	GObject parent_instance;
	TablePrivate * priv;
	WebKitDOMElement* el;
	WebKitDOMElement* tbody;
	WebKitDOMElement* thead;
};

struct _TableClass {
	GObjectClass parent_class;
};


static gpointer table_parent_class = NULL;
extern WebKitDOMDocument* table_document;
WebKitDOMDocument* table_document = NULL;

GType table_get_type (void) G_GNUC_CONST;
enum  {
	TABLE_DUMMY_PROPERTY
};
Table* table_new (WebKitDOMElement* parent, const gchar* id);
Table* table_construct (GType object_type, WebKitDOMElement* parent, const gchar* id);
static GObject * table_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void table_finalize (GObject* obj);


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


Table* table_construct (GType object_type, WebKitDOMElement* parent, const gchar* id) {
	Table * self = NULL;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (parent != NULL, NULL);
	g_return_val_if_fail (id != NULL, NULL);
	self = (Table*) g_object_new (object_type, NULL);
	{
		WebKitDOMElement* _tmp0_;
		const gchar* _tmp1_;
		WebKitDOMElement* _tmp2_;
		WebKitDOMElement* _tmp3_;
		WebKitDOMDocument* _tmp4_;
		WebKitDOMElement* _tmp5_ = NULL;
		WebKitDOMElement* _tmp6_;
		WebKitDOMElement* _tmp7_;
		WebKitDOMElement* _tmp8_;
		WebKitDOMElement* _tmp9_;
		WebKitDOMDocument* _tmp10_;
		WebKitDOMElement* _tmp11_ = NULL;
		WebKitDOMElement* _tmp12_;
		WebKitDOMElement* _tmp13_;
		WebKitDOMElement* _tmp14_;
		WebKitDOMElement* _tmp15_;
		_tmp0_ = self->el;
		_tmp1_ = id;
		webkit_dom_element_set_attribute (_tmp0_, "id", _tmp1_, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch0_g_error;
		}
		_tmp2_ = parent;
		_tmp3_ = self->el;
		webkit_dom_node_append_child ((WebKitDOMNode*) _tmp2_, WEBKIT_DOM_NODE (_tmp3_), &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch0_g_error;
		}
		_tmp4_ = table_document;
		_tmp5_ = webkit_dom_document_create_element (_tmp4_, "thead", &_inner_error_);
		_tmp6_ = _tmp5_;
		if (_inner_error_ != NULL) {
			goto __catch0_g_error;
		}
		_tmp7_ = self->el;
		_tmp8_ = _g_object_ref0 (_tmp6_);
		_g_object_unref0 (self->thead);
		self->thead = _tmp8_;
		_tmp9_ = self->thead;
		webkit_dom_node_append_child ((WebKitDOMNode*) _tmp7_, (WebKitDOMNode*) _tmp9_, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch0_g_error;
		}
		_tmp10_ = table_document;
		_tmp11_ = webkit_dom_document_create_element (_tmp10_, "tbody", &_inner_error_);
		_tmp12_ = _tmp11_;
		if (_inner_error_ != NULL) {
			goto __catch0_g_error;
		}
		_tmp13_ = self->el;
		_tmp14_ = _g_object_ref0 (_tmp12_);
		_g_object_unref0 (self->tbody);
		self->tbody = _tmp14_;
		_tmp15_ = self->tbody;
		webkit_dom_node_append_child ((WebKitDOMNode*) _tmp13_, (WebKitDOMNode*) _tmp15_, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch0_g_error;
		}
	}
	goto __finally0;
	__catch0_g_error:
	{
		g_clear_error (&_inner_error_);
		_inner_error_ = NULL;
	}
	__finally0:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	return self;
}


Table* table_new (WebKitDOMElement* parent, const gchar* id) {
	return table_construct (TYPE_TABLE, parent, id);
}


static GObject * table_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	Table * self;
	GError * _inner_error_ = NULL;
	parent_class = G_OBJECT_CLASS (table_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = TABLE (obj);
	{
		WebKitDOMDocument* _tmp0_;
		WebKitDOMElement* _tmp1_ = NULL;
		WebKitDOMElement* _tmp2_;
		WebKitDOMElement* _tmp3_;
		_tmp0_ = table_document;
		_tmp1_ = webkit_dom_document_create_element (_tmp0_, "table", &_inner_error_);
		_tmp2_ = _tmp1_;
		if (_inner_error_ != NULL) {
			goto __catch1_g_error;
		}
		_tmp3_ = _g_object_ref0 (_tmp2_);
		_g_object_unref0 (self->el);
		self->el = _tmp3_;
	}
	goto __finally1;
	__catch1_g_error:
	{
		g_clear_error (&_inner_error_);
		_inner_error_ = NULL;
	}
	__finally1:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
	}
	return obj;
}


static void table_class_init (TableClass * klass) {
	table_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->constructor = table_constructor;
	G_OBJECT_CLASS (klass)->finalize = table_finalize;
}


static void table_instance_init (Table * self) {
}


static void table_finalize (GObject* obj) {
	Table * self;
	self = TABLE (obj);
	_g_object_unref0 (self->el);
	_g_object_unref0 (self->tbody);
	_g_object_unref0 (self->thead);
	G_OBJECT_CLASS (table_parent_class)->finalize (obj);
}


GType table_get_type (void) {
	static volatile gsize table_type_id__volatile = 0;
	if (g_once_init_enter (&table_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (TableClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) table_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (Table), 0, (GInstanceInitFunc) table_instance_init, NULL };
		GType table_type_id;
		table_type_id = g_type_register_static (G_TYPE_OBJECT, "Table", &g_define_type_info, 0);
		g_once_init_leave (&table_type_id__volatile, table_type_id);
	}
	return table_type_id__volatile;
}



