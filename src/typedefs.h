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
#ifndef __typedefs_h__
#define __typedefs_h__
#include "samplecat/typedefs.h"

#define OVERVIEW_WIDTH (200)
#define OVERVIEW_HEIGHT (20)

#ifndef __PRI64_PREFIX
#if (defined __X86_64__ || defined __LP64__)
# define __PRI64_PREFIX  "l"
#else
# define __PRI64_PREFIX  "ll"
#endif
#endif

#ifndef PRIu64
# define PRIu64   __PRI64_PREFIX "u"
#endif
#ifndef PRIi64
# define PRIi64   __PRI64_PREFIX "i"
#endif

#ifndef PATH_MAX
#define PATH_MAX (1024)
#endif

typedef enum {
	BACKEND_NONE = 0,
	BACKEND_MYSQL,
	BACKEND_SQLITE,
	BACKEND_TRACKER,
} BackendType;

typedef struct _menu_def          MenuDef;
typedef struct _libraryview       LibraryView;
typedef struct _inspector         Inspector;
typedef struct _inspector_priv    InspectorPriv;
typedef struct _PlayCtrl          PlayCtrl;
typedef struct _auditioner        Auditioner;
typedef struct _view_option       ViewOption;
typedef struct _SamplecatModel    SamplecatModel;
typedef struct _backend           SamplecatBackend;
typedef struct _palette           Palette;
typedef struct _config            Config;
typedef struct _accel             Accel;
typedef struct _db_config         DbConfig;
typedef struct _ScanResults       ScanResults;

#ifndef __file_manager_h__
typedef struct _GimpActionGroup   GimpActionGroup;
#endif

#endif
