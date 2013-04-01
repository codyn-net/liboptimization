if ENABLE_DOCS

DOCDIR = $(DESTDIR)$(datadir)/doc/liboptimization-@LIBOPTIMIZATION_API_VERSION@
PAGES = $(wildcard pages/*.md)

all: html/index.html

SCAN_FILES = \
	../optimization/taskreader.cc \
	../optimization/taskreader.hh

html/index.html: $(PAGES) $(SCAN_FILES)
	@echo [CLDOC] $(SCAN_FILES); \
	$(CLDOC) $(PACKAGE_LIBOPTIMIZATION_CFLAGS) -I$(top_srcdir) -I$(top_builddir) -- \
		--output html \
		--static \
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
