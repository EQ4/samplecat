
struct _sample
{
	int          id;            //database index.
	GtkTreeRowReference* row_ref;
	char         filename[256]; //full path.
	char         filetype;      //see enum.
	unsigned int sample_rate;
	unsigned int length;        //milliseconds
	unsigned int frames;        //total number of frames (eg a frame for 16bit stereo is 4 bytes).
	unsigned int channels;
	int          bitdepth;
	short        minmax[OVERVIEW_WIDTH]; //peak data before it is copied onto the pixbuf.
	GdkPixbuf*   pixbuf;
	GdkColor     bg_colour;
};

sample*     sample_new               ();
sample*     sample_new_from_model    (GtkTreePath*);
sample*     sample_new_from_fileview (GtkTreeModel*, GtkTreeIter*);
sample*     sample_new_from_result   (SamplecatResult*);
void        sample_free              (sample*);

gboolean    sample_get_file_sndfile_info(sample*);
void        sample_set_type_from_mime_string(sample*, char*);
