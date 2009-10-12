all: doxygen.cfg
	$(DOXYGEN) doxygen.cfg

install-data-hook: all
	cp -r html $(datadir)/doc/liboptimization-@LIBOPTIMIZATION_API_VERSION@

EXTRA_DIST = doxygen.cfg
