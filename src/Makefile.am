AUTOMAKE_OPTIONS = subdir-objects

noinst_LTLIBRARIES=libentities.la
libentities_la_SOURCES=entities/entities.c
libentities_la_CFLAGS=-std=c99

lib_LTLIBRARIES=libeasycurl.la

libeasycurl_la_SOURCES=easycurl.cpp \
                       stripper.cpp

libeasycurl_la_CPPFLAGS=$(BOOST_CPPFLAGS) \
			@LIBCURL_CPPFLAGS@

libeasycurl_la_LDFLAGS=$(BOOST_SYSTEM_LDFLAGS) \
		       $(BOOST_REGEX_LDFLAGS) \
		       $(BOOST_REGEX_LIBS) \
		       @LIBCURL@

libeasycurl_la_LIBADD=libentities.la

include_HEADERS=easycurl.h

pkgconfigdir = $(libdir)/pkgconfig
nodist_pkgconfig_DATA = libeasycurl.pc

libeasycurl.pc: libeasycurl.pc.in
	sed -e 's![@]prefix[@]!$(prefix)!g' \
		-e 's![@]exec_prefix[@]!$(exec_prefix)!g' \
		-e 's![@]includedir[@]!$(includedir)!g' \
		-e 's![@]libdir[@]!$(libdir)!g' \
		-e 's![@]PACKAGE_VERSION[@]!$(PACKAGE_VERSION)!g' \
		libeasycurl.pc.in > $@

noinst_PROGRAMS=test

test_SOURCES=test.cpp

test_LDADD=libeasycurl.la

test_CPPFLAGS=$(BOOST_CPPFLAGS) \
	     @LIBCURL_CPPFLAGS@

test_LDFLAGS=$(BOOST_SYSTEM_LDFLAGS) \
	     $(BOOST_REGEX_LDFLAGS) \
	     $(BOOST_REGEX_LIBS) \
	     @LIBCURL@
