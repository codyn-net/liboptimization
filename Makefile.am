
include Makefile.am.inc
	
# pkg-config stuff
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = \
	liboptimization-@LIBOPTIMIZATION_API_VERSION@.pc

liboptimization-@LIBOPTIMIZATION_API_VERSION@.pc: liboptimization.pc
	cp liboptimization.pc liboptimization-@LIBOPTIMIZATION_API_VERSION@.pc

EXTRA_DIST += \
	liboptimization.pc.in

CLEANFILES = 	\
	$(pkgconfig_DATA)
