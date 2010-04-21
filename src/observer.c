#include "../config.h"
#include <gtk/gtk.h>
#include "file_manager/file_manager.h"
#include "gqview_view_dir_tree.h"
#include "typedefs.h"
#include "listview.h"
#include "dh-link.h"
#include "support.h"
#include "main.h"

void file_manager__update_all();

extern struct _app app;
extern int debug;


void
observer__files_moved(GList* file_list, const char* dest)
{
	PF;
	GList* l = file_list;
	for(;l;l=l->next){
		dbg(0, "%s", l->data);
	}

	char msg[256];
	if(g_list_length(file_list) > 1){
		snprintf(msg, 255, "%i files moved.", g_list_length(file_list));
	}else{
		snprintf(msg, 255, "file: '%s' moved.", (char*)file_list->data);
	}
	statusbar_print(1, msg);

	//FIXME
	//db_update_path(const char* old_path, const char* new_path);
}


void
observer__icon_theme()
{
	listmodel__update();
	vdtree_on_icon_theme_changed((ViewDirTree*)app.dir_treeview2);
	file_manager__update_all();
}

