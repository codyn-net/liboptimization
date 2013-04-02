if ENABLE_DOCS

DOCDIR = $(DESTDIR)$(datadir)/doc/liboptimization-@LIBOPTIMIZATION_API_VERSION@
PAGES = $(wildcard pages/*.md)

all: html/index.html

SCAN_FILES = \
	../optimization/taskreader.cc \
	../optimization/taskreader.hh \
	../optimization/dispatcher.cc \
	../optimization/dispatcher.hh \
	../optimization/webots.cc \
	../optimization/webots.hh \
	../optimization/constants.cc \
	../optimization/constants.hh \
	../optimization/messages.cc \
	../optimization/messages.hh \
	../optimization/messages/task.pb.h \
	../optimization/messages/task.pb.cc \
	../optimization/messages/discovery.pb.h \
	../optimization/messages/discovery.pb.cc

html/index.html: $(PAGES) $(SCAN_FILES)
	$(AM_V_GEN) $(CLDOC) $(PACKAGE_LIBOPTIMIZATION_CFLAGS) -I$(top_srcdir) -I$(top_builddir) -- \
		--output html \
		--quiet \
		--report \
		$(foreach i,$(PAGES),--merge $(i)) \
		$(SCAN_FILES)

install-data-hook: html/index.html
	test -z "$(DOCDIR)" || mkdir -p "$(DOCDIR)" && \
	cp -r html $(DOCDIR)/

uninstall-hook:
	test -z "$(DOCDIR)" || rm -rf "$(DOCDIR)/html"

clean-local:
	rm -rf html

endif

EXTRA_DIST = \
	$(PAGES)
