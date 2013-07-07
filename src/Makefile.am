lib_LTLIBRARIES=libeasycurl.la
libeasycurl_la_SOURCES=easycurl.cpp \
                       stripper.cpp \
                       entities.c
libeasycurl_la_CPPFLAGS=@LIBCURL_CPPFLAGS@ $(BOOST_CPPFLAGS)
libeasycurl_la_LDFLAGS=@LIBCURL@ $(BOOST_REGEX_LDFLAGS)

include_HEADERS=easycurl.h

noinst_PROGRAMS=test
test_SOURCES=test.cpp
test_LDADD=libeasycurl.la $(BOOST_REGEX_LIBS) @LIBCURL@
test_CPPFLAGS=@LIBCURL_CPPFLAGS@
