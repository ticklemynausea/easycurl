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

noinst_PROGRAMS=test
test_SOURCES=test.cpp
test_LDADD=libeasycurl.la
