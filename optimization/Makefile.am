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
	messages/command.pb.cc	\
	messages/task.pb.cc 	\
	messages/discovery.pb.cc \
	messages/monitor.pb.cc

BUILT_HDRS = $(BUILT_SOURCES:.cc=.h)

messages/%.pb.cc messages/%.pb.h: messages/%.proto
	$(AM_V_GEN) protoc --cpp_out=$(top_srcdir) -I$(top_srcdir) $(top_srcdir)/optimization/$<

protodir = $(pkgincludedir)/optimization/messages
proto_DATA =				\
	messages/command.proto		\
	messages/task.proto		\
	messages/discovery.proto	\
	messages/monitor.proto

INSTHEADERS = \
	optimization.hh \
	constants.hh \
	debug.hh \
	discovery.hh \
	dispatcher.hh \
	messages.hh \
	taskreader.hh \
	webots.hh

headerdir = $(pkgincludedir)/optimization
header_DATA = 	\
	$(INSTHEADERS)

messagesdir = $(pkgincludedir)/optimization/messages
messages_DATA = $(BUILT_HDRS)

lib_LTLIBRARIES = liboptimization-2.0.la
liboptimization_2_0_la_SOURCES = \
	messages.cc \
	constants.cc \
	discovery.cc \
	dispatcher.cc \
	taskreader.cc \
	webots.cc \
	$(BUILT_SOURCES)

liboptimization_2_0_la_CFLAGS = -g $(PACKAGE_LIBOPTIMIZATION_CFLAGS)
liboptimization_2_0_la_LDFLAGS = -export-dynamic -no-undefined $(PACKAGE_LIBOPTIMIZATION_LIBS)

EXTRA_DIST = \
	$(INSTHEADERS) \
	$(proto_DATA)

CLEANFILES = \
	$(BUILT_SOURCES) \
	$(BUILT_HDRS)