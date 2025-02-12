/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * lifegame.h
 * Copyright (C) 2025 bibindon <bibindon@bibindon-VirtualBox>
 * 
 * lifegame is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * lifegame is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _LIFEGAME_
#define _LIFEGAME_

#include <gtk/gtk.h>
#include <stdbool.h>

G_BEGIN_DECLS

#define LIFEGAME_TYPE_APPLICATION             (lifegame_get_type ())
#define LIFEGAME_APPLICATION(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), LIFEGAME_TYPE_APPLICATION, Lifegame))
#define LIFEGAME_APPLICATION_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), LIFEGAME_TYPE_APPLICATION, LifegameClass))
#define LIFEGAME_IS_APPLICATION(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LIFEGAME_TYPE_APPLICATION))
#define LIFEGAME_IS_APPLICATION_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), LIFEGAME_TYPE_APPLICATION))
#define LIFEGAME_APPLICATION_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), LIFEGAME_TYPE_APPLICATION, LifegameClass))

typedef struct _LifegameClass LifegameClass;
typedef struct _Lifegame Lifegame;
typedef struct _LifegamePrivate LifegamePrivate;

struct _LifegameClass
{
	GtkApplicationClass parent_class;
};

struct _Lifegame
{
	GtkApplication parent_instance;

	LifegamePrivate *priv;

};

GType lifegame_get_type (void) G_GNUC_CONST;
Lifegame *lifegame_new (void);

extern bool lifeXY[100][100];

/* Callbacks */

gboolean on_timeout(gpointer user_data);
	
G_END_DECLS

#endif /* _APPLICATION_H_ */

