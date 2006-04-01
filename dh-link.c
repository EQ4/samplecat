/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * Copyright (C) 2001-2002 CodeFactory AB
 * Copyright (C) 2001-2002 Mikael Hallendal <micke@imendio.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

//#include <config.h>
#include "string.h"
#include "dh-link.h"

static void link_free (DhLink *link);

static void 
link_free (DhLink *link)
{
	g_free (link->name);
	g_free (link->uri);

	g_free (link);
}

DhLink *
dh_link_new (DhLinkType type, const gchar *name, const gchar *uri)
{
	DhLink *link;

	g_return_val_if_fail (name != NULL, NULL);
	g_return_val_if_fail (uri != NULL, NULL);

	link = g_new0 (DhLink, 1);

	link->type = type;

	link->name = g_strdup (name);
	link->uri  = g_strdup (uri);
	
	return link;
}

DhLink *
dh_link_copy (const DhLink *link)
{
	return dh_link_new (link->type, link->name, link->uri);
}

gint
dh_link_compare  (gconstpointer a, gconstpointer b)
{
	return strcmp (((DhLink *)a)->name, ((DhLink *)b)->name);
}

DhLink *
dh_link_ref (DhLink *link)
{
	g_return_val_if_fail (link != NULL, NULL);

	link->ref_count++;
	
	return link;
}

void
dh_link_unref (DhLink *link)
{
	g_return_if_fail (link != NULL);
	
	link->ref_count--;

	if (link->ref_count == 0) {
		link_free (link);
	}
}
