lib_LTLIBRARIES=libeasycurl.la
libeasycurl_la_SOURCES=easycurl.cpp \
					   stripper.cpp
libeasycurl_la_CPPFLAGS=@LIBCURL_CPPFLAGS@ $(BOOST_CPPFLAGS)
libeasycurl_la_LDFLAGS=@LIBCURL@ $(BOOST_REGEX_LDFLAGS)
libeasycurl_la_LIBS=$(BOOST_REGEX_LIBS)
libeasycurl_la_LIBADD=libentities.a

include_HEADERS=easycurl.h

noinst_LIBRARIES=libentities.a
libentities_a_SOURCES=entities.c
libentities_a_CFLAGS=-std=c99

noinst_PROGRAMS=test
#bin_PROGRAMS=test
test_SOURCES=test.cpp
test_LDADD=libeasycurl.la $(BOOST_REGEX_LIBS) @LIBCURL@
test_CPPFLAGS=@LIBCURL_CPPFLAGS@
