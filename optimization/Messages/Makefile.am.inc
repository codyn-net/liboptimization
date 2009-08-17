BUILT_SOURCES = 	\
	_worker.pb.cc 	\
	_discovery.pb.cc \
	_command.pb.cc

BUILT_HDRS = 		\
	worker.pb.h 	\
	discovery.pb.h 	\
	command.pb.h

_worker.pb.cc: worker.proto worker.pb.h
	protoc --cpp_out=/tmp/ -I$(srcdir) $(srcdir)/worker.proto && mv /tmp/worker.pb.cc $@

worker.pb.h: worker.proto
	protoc --cpp_out=/tmp/ -I$(srcdir) $< && mv /tmp/$@ $@	

_discovery.pb.cc: discovery.proto discovery.pb.h
	protoc --cpp_out=/tmp/ -I$(srcdir) $(srcdir)/discovery.proto && mv /tmp/discovery.pb.cc $@

discovery.pb.h: discovery.proto
	protoc --cpp_out=/tmp/ -I$(srcdir) $< && mv /tmp/$@ $@

_command.pb.cc: command.proto command.pb.h
	protoc --cpp_out=/tmp/ -I$(srcdir) $(srcdir)/command.proto && mv /tmp/command.pb.cc $@

command.pb.h: command.proto
	protoc --cpp_out=/tmp/ -I$(srcdir) $< && mv /tmp/$@ $@

nodist_liboptimizationoptimizationmessages_la_SOURCES = $(BUILT_SOURCES)
nodist_header_DATA = $(BUILT_HDRS)

protodir = $(pkgincludedir)/optimization/Messages
proto_DATA = 		\
	worker.proto	\
	discovery.proto	\
	command.proto

EXTRA_DIST += $(proto_DATA)
CLEANFILES = $(BUILT_SOURCES) $(BUILT_HDRS)
