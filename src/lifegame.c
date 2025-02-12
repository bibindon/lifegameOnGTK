/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * lifegame.c
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
#include "lifegame.h"

#include <glib/gi18n.h>

bool lifeXY[100][100];

/* For testing propose use the local (not installed) ui file */
/* #define UI_FILE PACKAGE_DATA_DIR"/ui/lifegame.ui" */
#define UI_FILE "src/lifegame.ui"
#define TOP_WINDOW "window"


G_DEFINE_TYPE (Lifegame, lifegame, GTK_TYPE_APPLICATION);

/* ANJUTA: Macro LIFEGAME_APPLICATION gets Lifegame - DO NOT REMOVE */
struct _LifegamePrivate
{
	/* ANJUTA: Widgets declaration for lifegame.ui - DO NOT REMOVE */
};

/* Create a new window loading a file */
static void
lifegame_new_window (GApplication *app,
                           GFile        *file)
{
	GtkWidget *window;

	GtkBuilder *builder;
	GError* error = NULL;

	LifegamePrivate *priv = LIFEGAME_APPLICATION(app)->priv;

	/* Load UI from file */
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_FILE, &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (builder, app);

	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (builder, TOP_WINDOW));
        if (!window)
        {
		g_critical ("Widget \"%s\" is missing in file %s.",
				TOP_WINDOW,
				UI_FILE);
        }

	
	/* ANJUTA: Widgets initialization for lifegame.ui - DO NOT REMOVE */

	g_object_unref (builder);
	
	
	gtk_window_set_application (GTK_WINDOW (window), GTK_APPLICATION (app));
	if (file != NULL)
	{
		/* TODO: Add code here to open the file in the new window */
	}

	gtk_widget_show_all (GTK_WIDGET (window));

	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			lifeXY[i][j] = false;
		}
	}
}


/* GApplication implementation */
static void
lifegame_activate (GApplication *application)
{
	lifegame_new_window (application, NULL);
}

static void
lifegame_open (GApplication  *application,
                     GFile        **files,
                     gint           n_files,
                     const gchar   *hint)
{
	gint i;

	for (i = 0; i < n_files; i++)
		lifegame_new_window (application, files[i]);
}

static void
lifegame_init (Lifegame *object)
{
	object->priv = G_TYPE_INSTANCE_GET_PRIVATE (object, LIFEGAME_TYPE_APPLICATION, LifegamePrivate);
}

static void
lifegame_finalize (GObject *object)
{
	G_OBJECT_CLASS (lifegame_parent_class)->finalize (object);
}

static void
lifegame_class_init (LifegameClass *klass)
{
	G_APPLICATION_CLASS (klass)->activate = lifegame_activate;
	G_APPLICATION_CLASS (klass)->open = lifegame_open;

	g_type_class_add_private (klass, sizeof (LifegamePrivate));

	G_OBJECT_CLASS (klass)->finalize = lifegame_finalize;
}

Lifegame *
lifegame_new (void)
{
	return g_object_new (lifegame_get_type (),
	                     "application-id", "org.gnome.lifegame",
	                     "flags", G_APPLICATION_HANDLES_OPEN,
	                     NULL);
}

void btnStart_click_cb(GtkButton *button, gpointer user_data)
{
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			int rnd = rand() % 100;
			if (rnd < 50)
			{
				lifeXY[i][j] = true;
			}
			else
			{
				lifeXY[i][j] = false;
			}
		}
	}
}

void btnReset_click_cb(GtkButton *button, gpointer user_data)
{
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			lifeXY[i][j] = false;
		}
	}
}

void drawRectangle(cairo_t *cr, int x, int y)
{
	cairo_set_source_rgb (cr, 0, 1, 0);
	cairo_rectangle (cr, x * 5, y * 5, 5, 5);
	cairo_fill(cr);
}

GtkWidget* drawingArea = NULL;

// Not called. i dont know why.
void on_test_show(GtkWidget *widget, gpointer user_data)
{
	if (drawingArea == NULL)
	{
		drawingArea = widget;

		g_timeout_add(100, on_timeout, drawingArea);
	}
}

void updateLifeCycle()
{
	bool workXY[100][100];
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			workXY[i][j] = lifeXY[i][j];
		}
	}
	
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			int aliveCount = 0;

			// UP
			if (j >= 1)
			{
				if (i >= 1)
				{
					if (workXY[i-1][j-1])
					{
						++aliveCount;
					}
				}
				
				if (workXY[i][j-1])
				{
					++aliveCount;
				}

				if (i <= 98)
				{
					if (workXY[i+1][j-1])
					{
						++aliveCount;
					}
				}
			}


			// MIDDLE
			
			if (i >= 1)
			{
				if (workXY[i-1][j])
				{
					++aliveCount;
				}
			}
			
			if (i <= 98)
			{
				if (workXY[i+1][j])
				{
					++aliveCount;
				}
			}

			// LOW
			if (j <= 98)
			{
				if (i >= 1)
				{
					if (workXY[i-1][j+1])
					{
						++aliveCount;
					}
				}

				if (workXY[i][j+1])
				{
					++aliveCount;
				}

				if (i <= 98)
				{
					if (workXY[i+1][j+1])
					{
						++aliveCount;
					}
				}
			}

			// 誕生...死んでいるセルに隣接する生きたセルがちょうど3つあれば、次の世代が誕生する。
			if (!workXY[i][j])
			{
				if (aliveCount == 3)
				{
					lifeXY[i][j] = true;
				}
				else
				{
					lifeXY[i][j] = false;
				}
			}
			else if (workXY[i][j])
			{
				// 生存...生きているセルに隣接する生きたセルが2つか3つならば、次の世代でも生存する。
				if (aliveCount == 2 || aliveCount == 3)
				{
					lifeXY[i][j] = true;
				}
				// 過疎...生きているセルに隣接する生きたセルが1つ以下ならば、過疎により死滅する。
				else if (aliveCount == 0 || aliveCount == 1)
				{
					lifeXY[i][j] = false;
				}
				// 過密...生きているセルに隣接する生きたセルが4つ以上ならば、過密により死滅する。
				else if (aliveCount >= 4)
				{
					lifeXY[i][j] = false;
				}
			}
		}
	}
}

gboolean on_test_draw(GtkWidget *widget, cairo_t *cr)
{
	if (drawingArea == NULL)
	{
		drawingArea = widget;
		g_timeout_add(17, on_timeout, drawingArea);
	}
	else
	{
		updateLifeCycle();
	}
	
	// draw background
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_rectangle (cr, 0, 0, 500, 500);
	cairo_fill(cr);
	
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			if (lifeXY[i][j])
			{
				drawRectangle (cr, i, j);
			}
		}
	}
	return FALSE;
}

gboolean on_timeout(gpointer user_data)
{
    // DrawingAreaを取得
    GtkWidget *drawing_area = GTK_WIDGET(user_data);
    gtk_widget_queue_draw(drawing_area); // DrawingAreaを再描画する
    return TRUE;
}



