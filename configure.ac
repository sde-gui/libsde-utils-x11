AC_PREREQ(2.53)
AC_INIT(sde-utils-x11-0, 0.1.0-alpha, http://make-linux.org/)
AM_INIT_AUTOMAKE
AM_MAINTAINER_MODE([enable])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES])
AC_CONFIG_SRCDIR([src/atoms.c])
AC_CONFIG_HEADER([config.h])

AC_DISABLE_STATIC

AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_LIBTOOL
AM_PROG_CC_C_O


dnl ================================================================
dnl Gettext stuff.
dnl ================================================================

#IT_PROG_INTLTOOL([0.50.1])

#AM_GNU_GETTEXT_VERSION([0.19])
#AM_GNU_GETTEXT([external])

#AC_SUBST([GETTEXT_PACKAGE], [libsde-utils])
#AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], "$GETTEXT_PACKAGE", [Define to the gettext package name.])

dnl ================================================================
dnl Checks for libraries.
dnl ================================================================

pkg_modules="sde-utils-0 >= 0.1 x11"
PKG_CHECK_MODULES(PACKAGE, [$pkg_modules])
AC_SUBST(PACKAGE_CFLAGS)
AC_SUBST(PACKAGE_LIBS)

dnl ================================================================
dnl Dev. Options
dnl ================================================================

AC_ARG_ENABLE([debug],
    AS_HELP_STRING([--enable-debug],
               [enable debug build (default: disable)]),
               debug=$enableval, debug="no")
if test x"$debug" = "xyes"; then
    CFLAGS="$CFLAGS -DDEBUG -Og -g"
fi

dnl ================================================================
dnl Dev. Options
dnl ================================================================

_save_cflags="$CFLAGS"
CFLAGS="-Werror-implicit-function-declaration"
AC_MSG_CHECKING([whether $CC accepts $CFLAGS])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([])],
    [AC_MSG_RESULT([yes])]
    CFLAGS="$_save_cflags $CFLAGS",
    [AC_MSG_RESULT([no])]
    CFLAGS="$_save_cflags"
)

dnl ================================================================

dnl linker tweaking
# The function of the link flag --as-needed is to prevent unnecesary linking.
# Example: A -> B -> C
# Normally, A would link to B and also depend on C, this is of cource
# unnecesary. In this situation, however we do need to link to C, so this
# must be done explicitly. This flag comes in handy when a library ABI
# is changed, minimizing the amount of recompilations needed.
AC_MSG_CHECKING([whether $LD accepts --as-needed])
case `$LD --as-needed -v 2>&1 </dev/null` in
*GNU* | *'with BFD'*)
    LDFLAGS="$LDFLAGS -Wl,--as-needed"
    AC_MSG_RESULT([yes])
    ;;
*)
    AC_MSG_RESULT([no])
    ;;
esac

dnl linker optimizations
AC_MSG_CHECKING([whether $LD accepts -O1])
case `$LD -O1 -v 2>&1 </dev/null` in
*GNU* | *'with BFD'*)
  LDFLAGS="$LDFLAGS -Wl,-O1"
  AC_MSG_RESULT([yes])
  ;;
*)
  AC_MSG_RESULT([no])
  ;;
esac
AC_MSG_CHECKING([whether $LD accepts -Bsymbolic-functions])
case `$LD -Bsymbolic-functions -v 2>&1 </dev/null` in
*GNU* | *'with BFD'*)
  LDFLAGS="$LDFLAGS -Wl,-Bsymbolic-functions"
  AC_MSG_RESULT([yes])
  ;;
*)
  AC_MSG_RESULT([no])
  ;;
esac
AC_MSG_CHECKING([whether $LD accepts --sort-common])
case `$LD --sort-common -v 2>&1 </dev/null` in
*GNU* | *'with BFD'*)
  LDFLAGS="$LDFLAGS -Wl,--sort-common"
  AC_MSG_RESULT([yes])
  ;;
*)
  AC_MSG_RESULT([no])
  ;;
esac

AC_CONFIG_FILES([
    sde-utils-x11-0.pc
    Makefile
    src/Makefile
    include/Makefile
])
AC_OUTPUT


echo
echo "$PACKAGE $VERSION"
echo
echo "prefix $prefix"
echo
echo "PACKAGE_CFLAGS     =  $PACKAGE_CFLAGS"
echo "PACKAGE_LIBS       =  $PACKAGE_LIBS"
echo "LDFLAGS            =  $LDFLAGS"
echo "CFLAGS             =  $CFLAGS"
echo "CC                 =  $CC"
echo "LD                 =  $LD"
echo "AR                 =  $AR"
echo
