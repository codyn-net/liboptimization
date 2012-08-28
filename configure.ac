AC_INIT(liboptimization, 2.3)

AM_INIT_AUTOMAKE([-Wno-portability])

AC_CONFIG_MACRO_DIR([m4])
AC_PROG_LIBTOOL

AC_ISC_POSIX
AC_STDC_HEADERS
AC_PROG_CXX
AC_HEADER_STDC

AC_PROG_INSTALL
AC_PROG_MAKE_SET

PKG_PROG_PKG_CONFIG

AC_CONFIG_HEADERS(optimization/config.hh)
AM_MAINTAINER_MODE
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

LIBOPTIMIZATION_API_VERSION=2.0
AC_SUBST(LIBOPTIMIZATION_API_VERSION)

pkgincludedir="$includedir/liboptimization-$LIBOPTIMIZATION_API_VERSION"
AC_SUBST(pkgincludedir)

PKG_CHECK_MODULES(PACKAGE_LIBOPTIMIZATION, [
	libjessevdk-1.0 >= 1.0
	glibmm-2.4
	protobuf >= 2.2.0a
])

LDFLAGS=$SAVED_LDFLAGS

if test "x$USE_MAINTAINER_MODE" = "xyes"; then
PACKAGE_LIBOPTIMIZATION_CFLAGS="$PACKAGE_LIBOPTIMIZATION_CFLAGS -Wall -Werror -Wuninitialized -Wmissing-declarations"
fi

AC_SUBST(PACKAGE_LIBOPTIMIZATION_CFLAGS)
AC_SUBST(PACKAGE_LIBOPTIMIZATION_LIBS)

AC_ARG_ENABLE([docs],
	AS_HELP_STRING([--enable-docs],[Enable documentation building (default: disabled)]),
	[enable_docs=$enableval],
	[enable_docs=no])

if test "x$enable_docs" != "xno"; then
	AC_CHECK_PROG(DOXYGEN, doxygen, doxygen, no)
	
	if test x"$DOXYGEN" == "xno"; then
		AC_MSG_ERROR([you need to have doxygen installed for generating documentation])
	fi
fi

AM_CONDITIONAL(ENABLE_DOCS, test x"$enable_docs" = "xyes")

AC_OUTPUT(
Makefile
optimization/Makefile
liboptimization.pc
docs/Makefile
docs/doxygen.cfg
)

echo "

Configuration:

        Source code location:   ${srcdir}
        Compiler:               ${CC}
        Documentation enabled:  $enable_docs
"
