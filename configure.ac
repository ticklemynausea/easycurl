#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([easycurl], [0.1], [noreply@dev.null])
AC_CONFIG_SRCDIR([src/easycurl.cpp])
AC_CONFIG_HEADERS([src/config.h])

AM_INIT_AUTOMAKE
AC_CANONICAL_HOST

AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AM_PROG_CC_C_O

AC_PROG_LIBTOOL
AC_SUBST([LIBTOOL_DEPS])

AC_PROG_GREP
AC_PROG_EGREP

# Checks for libraries.
m4_include([m4/libcurl.m4])
m4_include([m4/boost.m4])

LIBCURL_CHECK_CONFIG([yes], [], [], [
    AC_MSG_ERROR([easycurl requires libcurl (http://curl.haxx.se/).])
])

BOOST_REQUIRE
BOOST_REGEX

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strchr strtoul])

AC_OUTPUT(Makefile src/Makefile)

AC_OUTPUT
