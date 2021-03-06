/**
* +----------------------------------------------------------------------+
* | This file is part of Samplecat. http://ayyi.github.io/samplecat/     |
* | copyright (C) 2007-2015 Tim Orford <tim@orford.org>                  |
* +----------------------------------------------------------------------+
* | This program is free software; you can redistribute it and/or modify |
* | it under the terms of the GNU General Public License version 3       |
* | as published by the Free Software Foundation.                        |
* +----------------------------------------------------------------------+
*
*/
#include "config.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <gtk/gtk.h>

#include "debug/debug.h"
#ifdef USE_AYYI
#include "ayyi/ayyi.h"
#endif

#include "typedefs.h"
#include "utils/pixmaps.h"
#include "file_manager/mimetype.h"
#include "db/db.h"
#include "support.h"
#include "model.h"
#include "application.h"
#include "sample.h"
#include "list_store.h"
#include "listmodel.h"



