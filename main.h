char err [32];
char warn[32];

#define EXPAND_TRUE 1
#define EXPAND_FALSE 0
#define FILL_TRUE 1
#define FILL_FALSE 0

//dnd:
enum {
  TARGET_APP_COLLECTION_MEMBER,
  TARGET_URI_LIST,
  TARGET_TEXT_PLAIN
};


struct _app
{
	char      search_phrase[256];
	char*     search_dir;
	gchar*    search_category;

	int       playing_id; //database index of the file that is currently playing, or zero if none playing.

	GtkListStore *store;
	
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *toolbar;
	GtkWidget *toolbar2;
	GtkWidget *scroll;
	GtkWidget *view;
	GtkWidget *statusbar;
	GtkWidget *statusbar2;
	GtkWidget *search;
	GtkWidget *category;
	GtkWidget *view_category;
	GtkWidget *context_menu;

	GtkCellRenderer*   cell1;     //sample name.
	GtkCellRenderer*   cell_tags;
	GtkTreeViewColumn* col_pixbuf;
	GtkTreeViewColumn* col_tags;

	GtkTreeRowReference* mouseover_row_ref;

	GNode*   dir_tree;

	GdkColor fg_colour;
	GdkColor bg_colour;

	MYSQL mysql;

	//nasty!
	gint     mouse_x;
	gint     mouse_y;
};

typedef struct _sample
{
	int         id;			//database index.
	GtkTreeRowReference* row_ref;
	char        filename[256]; //full path.
	char        filetype;   //see enum.
	int         sample_rate;
	int         length;     // milliseconds
	int         channels;
	int         bitdepth;
	GdkPixbuf*  pixbuf;

} sample;

enum {
	TYPE_SNDFILE=1,
	TYPE_FLAC,
};

gboolean	window_new();
GtkWidget*  left_pane();
void        window_on_realise(GtkWidget *win, gpointer user_data);
gboolean	filter_new();
gboolean    tag_selector_new();
gboolean    tagshow_selector_new();
void        on_view_category_changed(GtkComboBox *widget, gpointer user_data);
void        on_category_changed(GtkComboBox *widget, gpointer user_data);
void        on_set_clicked(GtkComboBox *widget, gpointer user_data);

gboolean	db_connect();
void        do_search(char *search, char *dir);

gboolean    new_search(GtkWidget *widget, gpointer userdata);

void        scan_dir();

void        dnd_setup();
gint        drag_received(GtkWidget *widget, GdkDragContext *drag_context, gint x, gint y,
                          GtkSelectionData *data, guint info, guint time, gpointer user_data);

sample*     sample_new();
void        sample_free(sample* sample);

void        add_file(char *uri);
gboolean    get_file_info(sample* sample);
gboolean    get_file_info_sndfile(sample* sample);
gboolean    on_overview_done(gpointer sample);

void        db_update_pixbuf(sample *sample);
int         db_insert(char *qry);
void        db_get_dirs();

void        keywords_on_edited(GtkCellRendererText *cell, gchar *path_string, gchar *new_text, gpointer user_data);
void        delete_row(GtkWidget *widget, gpointer user_data);
void        update_row(GtkWidget *widget, gpointer user_data);
void        edit_row  (GtkWidget *widget, gpointer user_data);
GtkWidget*  make_context_menu();
gboolean    on_row_clicked(GtkWidget *widget, GdkEventButton *event, gpointer user_data);
gboolean    treeview_on_motion(GtkWidget *widget, GdkEventMotion *event, gpointer user_data);
gboolean    treeview_get_cell(GtkTreeView *view, guint x, guint y, GtkCellRenderer **cell);
gboolean    treeview_get_tags_cell(GtkTreeView *view, guint x, guint y, GtkCellRenderer **cell);

gint        get_mouseover_row();
void        tag_cell_data(GtkTreeViewColumn *tree_column, GtkCellRenderer *cell, GtkTreeModel *tree_model, GtkTreeIter *iter, gpointer data);
gboolean    tree_on_link_selected(GObject *ignored, DhLink *link, gpointer data);
