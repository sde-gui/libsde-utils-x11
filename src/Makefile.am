
ABI_VERSION=1:0:0

NULL=

AM_CPPFLAGS = \
	-I$(top_srcdir) \
	-I$(top_srcdir)/include \
	-DPACKAGE_DATA_DIR=\""$(datadir)/$(PACKAGE)"\" \
	-DPACKAGE_LIB_DIR=\""$(libdir)/$(PACKAGE)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	$(NULL)

lib_LTLIBRARIES = libsde-utils-x11-0.la
libsde_utils_x11_0_la_SOURCES = atoms.c utils.c

libsde_utils_x11_0_la_CFLAGS = \
	$(PACKAGE_CFLAGS) \
	$(NULL)

libsde_utils_x11_0_la_LIBADD = \
	$(PACKAGE_LIBS) \
	$(NULL)

libsde_utils_x11_0_la_LDFLAGS = \
	-no-undefined \
	-export-symbols-regex '^(su|a)' \
	-version-info $(ABI_VERSION) \
	$(NULL)

