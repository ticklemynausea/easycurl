#!/bin/sh

aclocal --force
libtoolize --force
autoconf --force
automake -a
