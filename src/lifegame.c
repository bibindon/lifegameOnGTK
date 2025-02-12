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
	int i;
	i++;
}

void btnReset_click_cb(GtkButton *button, gpointer user_data)
{
}

gboolean on_test_draw(GtkWidget *widget, cairo_t *cr)
{

    GdkRGBA color;
    gdouble dashes[]    =   {50.0, 10.0, 10.0, 10.0};
    guchar  num         =   sizeof(dashes) / sizeof(dashes[0]);
    
    cairo_move_to   (cr,  20,  20   );
    cairo_line_to   (cr, 280,  20   );
    cairo_stroke    (cr);
    
    cairo_move_to   (cr,  20,  50   );
    cairo_line_to   (cr, 280,  50   );
    gdk_rgba_parse  (&color, "#f00" );
    gdk_cairo_set_source_rgba
                    (cr,    &color  );
    cairo_set_dash  (cr, dashes, num, 0.0   );
    cairo_set_line_width
                    (cr,        1.0 );
    cairo_stroke    (cr);
    
    cairo_move_to   (cr,  20,  80   );
    cairo_line_to   (cr, 280,  80   );
    cairo_set_dash  (cr, dashes, num, 25.0  );
    gdk_rgba_parse  (&color, "#0f0" );
    gdk_cairo_set_source_rgba
                    (cr,    &color  );
    cairo_stroke    (cr);
    
    cairo_move_to   (cr,  30, 110   );
    cairo_line_to   (cr, 270, 110   );
    cairo_set_dash  (cr, dashes, 0, 25.0    );
    gdk_rgba_parse  (&color, "#00f" );
    gdk_cairo_set_source_rgba
                    (cr,    &color  );
    cairo_set_line_cap
                    (cr, CAIRO_LINE_CAP_BUTT    );
    cairo_set_line_width
                    (cr,    20.0    );
    cairo_stroke    (cr);
    
    cairo_move_to   (cr,  30, 140   );
    cairo_line_to   (cr, 270, 140   );
    gdk_rgba_parse  (&color, "#0ff" );
    gdk_cairo_set_source_rgba
                    (cr,    &color  );
    cairo_set_line_cap
                    (cr, CAIRO_LINE_CAP_ROUND   );
    cairo_stroke    (cr);
    
    cairo_move_to   (cr,  30, 170   );
    cairo_line_to   (cr, 270, 170   );
    gdk_rgba_parse  (&color, "#f0f" );
    gdk_cairo_set_source_rgba
                    (cr,    &color  );
    cairo_set_line_cap
                    (cr, CAIRO_LINE_CAP_SQUARE  );
    cairo_stroke    (cr);
}



