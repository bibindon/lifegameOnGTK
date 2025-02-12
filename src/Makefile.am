## Process this file with automake to produce Makefile.in

## Created by Anjuta


uidir = $(pkgdatadir)/ui
ui_DATA = lifegame.ui


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(LIFEGAME_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = lifegame

lifegame_SOURCES = \
	main.c \
	lifegame.h \
	lifegame.c	


lifegame_LDFLAGS = \
	-Wl,--export-dynamic

lifegame_LDADD = $(LIFEGAME_LIBS)




EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)

