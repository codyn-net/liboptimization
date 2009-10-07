#!/bin/sh
# Run this to generate all the initial makefiles, etc.

if which ccbuild-autotools;
then
	ccbuild-autotools --version 1.0 generate
fi

autoreconf --install
