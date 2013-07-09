AC_PREREQ([2.65])
AC_INIT([easycurl], [0.1], [noreply@dev.null])
AM_INIT_AUTOMAKE
AC_CONFIG_MACRO_DIR([m4])

#
# Checks for programs.
#

AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL

m4_include([m4/boost.m4])

BOOST_REQUIRE(1.40)
BOOST_REGEX()

LIBCURL_CHECK_CONFIG([yes], [], [], [
    AC_MSG_ERROR([easycurl requires libcurl (http://curl.haxx.se/).])
])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

AC_CONFIG_HEADER([src/config.h])

AC_OUTPUT
