INCLUDES = \
	-I$(top_srcdir)\
	-I$(top_builddir)\
	-I$(top_srcdir) \
	-I$(top_builddir) \
	$(PACKAGE_LIBOPTIMIZATION_CFLAGS) \
	-DDATADIR=\""$(datadir)"\" \
	-DLIBDIR=\""$(libdir)"\" \
	-DCONFDIR=\""$(sysconfdir)"\" \
	-DPREFIXDIR=\""$(prefix)"\" \
	-DPKGDATADIR=\""$(pkgdatadir)"\" \
	-DPKGLIBDIR=\""$(pkglibdir)"\"

BUILT_SOURCES = 	\
	_task.pb.cc 	\
	_discovery.pb.cc

BUILT_HDRS = 		\
	task.pb.h 	\
	discovery.pb.h

_task.pb.cc: task.proto task.pb.h
	protoc --cpp_out=/tmp/ -I$(srcdir) $(srcdir)/task.proto && mv /tmp/task.pb.cc $@

task.pb.h: task.proto
	protoc --cpp_out=/tmp/ -I$(srcdir) $< && mv /tmp/$@ $@	

_discovery.pb.cc: discovery.proto discovery.pb.h
	protoc --cpp_out=/tmp/ -I$(srcdir) $(srcdir)/discovery.proto && mv /tmp/discovery.pb.cc $@

discovery.pb.h: discovery.proto
	protoc --cpp_out=/tmp/ -I$(srcdir) $< && mv /tmp/$@ $@

protodir = $(pkgincludedir)/optimization
proto_DATA = 		\
	task.proto	\
	discovery.proto

INSTHEADERS = \
	optimization.hh \
	constants.hh \
	debug.hh \
	discovery.hh \
	dispatcher.hh \
	messages.hh \
	processes.hh \
	taskreader.hh \
	webots.hh
	
headerdir = $(pkgincludedir)/optimization
header_DATA = 	\
	$(INSTHEADERS) \
	$(BUILT_HDRS)

lib_LTLIBRARIES = liboptimization-1.0.la
liboptimization_1_0_la_SOURCES = \
	messages.cc \
	constants.cc \
	discovery.cc \
	dispatcher.cc \
	processes.cc \
	taskreader.cc \
	webots.cc \
	$(BUILT_SOURCES)

liboptimization_1_0_la_CFLAGS = -g $(PACKAGE_LIBOPTIMIZATION_CFLAGS)
liboptimization_1_0_la_LDFLAGS = -export-dynamic -no-undefined $(PACKAGE_LIBOPTIMIZATION_LIBS)

EXTRA_DIST = \
	$(INSTHEADERS) \
	$(proto_DATA)

CLEANFILES = \
	$(BUILT_SOURCES) \
	$(BUILT_HDRS)
