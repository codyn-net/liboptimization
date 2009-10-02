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

nodist_liboptimizationoptimizationmessages_la_SOURCES = $(BUILT_SOURCES)
nodist_header_DATA = $(BUILT_HDRS)

protodir = $(pkgincludedir)/optimization/Messages
proto_DATA = 		\
	task.proto	\
	discovery.proto

EXTRA_DIST += $(proto_DATA)
CLEANFILES = $(BUILT_SOURCES) $(BUILT_HDRS)
