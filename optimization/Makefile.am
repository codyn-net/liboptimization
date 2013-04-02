AM_CPPFLAGS = \
	-I$(top_srcdir)\
	-I$(top_builddir)\
	-I$(top_srcdir) \
	-I$(top_builddir) \
	$(PACKAGE_LIBOPTIMIZATION_CFLAGS)

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
	dispatcher.hh \
	messages.hh \
	taskreader.hh \
	webots.hh

headerdir = $(pkgincludedir)/optimization
header_HEADERS = 	\
	$(INSTHEADERS)

messagesdir = $(pkgincludedir)/optimization/messages
messages_HEADERS = $(BUILT_HDRS)

lib_LTLIBRARIES = liboptimization-3.0.la

liboptimization_3_0_la_SOURCES = \
	messages.cc \
	constants.cc \
	dispatcher.cc \
	taskreader.cc \
	socketbuffer.cc \
	webots.cc \
	$(BUILT_SOURCES)

liboptimization_3_0_la_CXXFLAGS = -g $(PACKAGE_LIBOPTIMIZATION_CFLAGS)
liboptimization_3_0_la_LDFLAGS = -export-dynamic -no-undefined $(PACKAGE_LIBOPTIMIZATION_LIBS)

if PLATFORM_WINDOWS
liboptimization_3_0_la_SOURCES += webots_windows.cc
liboptimization_3_0_la_LDFLAGS += -lws2_32
else
liboptimization_3_0_la_SOURCES += webots_unix.cc
endif

EXTRA_DIST = \
	$(INSTHEADERS) \
	$(proto_DATA)

CLEANFILES = \
	$(BUILT_SOURCES) \
	$(BUILT_HDRS)
