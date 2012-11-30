if ENABLE_DOCS
all: .html-stamp

.html-stamp: doxygen.cfg
	$(DOXYGEN) doxygen.cfg && \
	touch .html-stamp

DOCDIR = $(DESTDIR)$(datadir)/doc/liboptimization-@LIBOPTIMIZATION_API_VERSION@

install-data-hook: .html-stamp
	test -z "$(DOCDIR)" || mkdir -p "$(DOCDIR)" && \
	cp -r html $(DOCDIR)/

uninstall-hook:
	test -z "$(DOCDIR)" || rm -rf "$(DOCDIR)/html"

clean-local:
	rm -rf html

CLEANFILES = .html-stamp

endif

EXTRA_DIST = \
	doxygen.cfg \
	templates \
	mainpage.hh \
	messages.hh \
	optimization.hh
