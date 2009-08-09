AC_INIT(liboptimization, 0.1)

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)

AC_CONFIG_MACRO_DIR([m4])
AC_PROG_LIBTOOL

AC_ISC_POSIX
AC_STDC_HEADERS
AC_PROG_CXX
AC_HEADER_STDC

AC_PROG_INSTALL
AC_PROG_MAKE_SET

AM_MAINTAINER_MODE

LIBOPTIMIZATION_API_VERSION=0.1
AC_SUBST(LIBOPTIMIZATION_API_VERSION)

pkgincludedir="$includedir/liboptimization-$LIBOPTIMIZATION_API_VERSION"
AC_SUBST(pkgincludedir)

pkgbasedir=""
AC_SUBST(pkgbasedir)

PKG_CHECK_MODULES(PACKAGE_OPTIMIZATION, [
	libjessevdk-base-0.1
	libjessevdk-os-0.1
	libjessevdk-math-0.1
	libjessevdk-db-0.1
	libjessevdk-network-0.1
	cpg-network-1.0
	glibmm-2.4
])

AC_SUBST(PACKAGE_OPTIMIZATION_CFLAGS)
AC_SUBST(PACKAGE_OPTIMIZATION_LIBS)

AC_OUTPUT(
Makefile
optimization/Boundaries/Makefile
optimization/Constants/Makefile
optimization/Container/Makefile
optimization/Discovery/Makefile
optimization/Dispatcher/Makefile
optimization/Fitness/Makefile
optimization/Messages/Makefile
optimization/Optimizer/Extension/Makefile
optimization/Optimizer/Makefile
optimization/Parameters/Makefile
optimization/Settings/Makefile
optimization/Solution/Makefile
optimization/Webots/Makefile
optimization/Makefile

liboptimization.pc
)
