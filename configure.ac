#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([libbeato],[1.0])
AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE
LT_INIT([shared,static])
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_SRCDIR([beato/metaBig.c])

# Checks for programs.
AC_PROG_CC
AC_LANG([C])
AM_PROG_CC_C_O
AM_MAINTAINER_MODE([disable])

# Stuff for the -DCOLOR32 define. This is library-independent so just having the define
# is enough
AC_ARG_ENABLE([color-32],
	[AS_HELP_STRING([--disable-color-32],[disable 32-bit color in PNG etc (default enabled)])], 
	[color32=${enableval}], 
	[color32=yes])

   # to catch that one scenario where some does --disable-color-32=no which makes no sense
   if test "x${color32}" = xno; then
      color32=yes
   fi
   # finally define the variable to put in config.h
   if test "x${color32}" = xyes; then 
      AC_DEFINE([COLOR32],[1],[Use 32-bit color in PNG etc])
   fi

# Stuff for MACHTYPE_ 
case $host in
     *x86_64*)  AC_DEFINE([MACHTYPE_x86_64],[],[Used in some rare cases.]) ;;
     *i386*)    AC_DEFINE([MACHTYPE_i386],[],[Used in some rare cases.]) ;;
     *ppc*)     AC_DEFINE([MACHTYPE_ppc],[],[Used in some rare cases.]) ;;
     *alpha*)   AC_DEFINE([MACHTYPE_alpha],[],[Used in some rare cases.]) ;;
     *sparc*)   AC_DEFINE([MACHTYPE_sparc],[],[Used in some rare cases.]) ;;
     *)         AC_DEFINE([MACHTYPE_unknown],[],[Used in some rare cases.]) ;;
esac

# Stuff for warnings
case $host in
     *ppc*)	AC_SUBST([MACHTYPE_WARN],["-Wall -Wno-unused-variable"]) ;;
     *)         AC_SUBST([MACHTYPE_WARN],["-Wall -Wformat -Wimplicit -Wreturn-type -Wuninitialized"]) ;;
esac

# Checks for header files.
AC_CHECK_HEADERS([assert.h float.h limits.h math.h stdio.h],[],[AC_MSG_ERROR([
   ---------------------------------------------
   One of the basic headers is missing.  Check your 
   C compiler installation.
   ---------------------------------------------])])

AC_SEARCH_LIBS([pthread_create], [pthread], [], [AC_MSG_ERROR([
   ---------------------------------------------
   Unable to find libpthread required for compiling
   libkent. Install this and run ./configure
   with the appropriate LDFLAGS. See the INSTALL
   for examples.
   ---------------------------------------------])])

AC_SEARCH_LIBS([zlibVersion], [z], [], [AC_MSG_ERROR([
   ---------------------------------------------
   Unable to find zlib required for compiling
   libkent. Install this and run ./configure with
   the appropriate LDFLAGS. See the INSTALL for 
   examples.
   ---------------------------------------------])])

AC_CHECK_HEADERS([png.h],[
    AC_SEARCH_LIBS([png_init_io],[png],[
        AC_DEFINE([USE_PNG],[1],[Turn on PNG support.])
    ])
])

has_ssl=yes
AC_SEARCH_LIBS([SHA1], [crypto], [], [has_ssl=no])
AC_SEARCH_LIBS([SSL_connect], [ssl], [], [has_ssl=no])
if test "x${has_ssl}" = xyes; then
    AC_DEFINE([USE_SSL],[1],[Turn on SSL support in https.c])
else
    AC_MSG_ERROR([
    ---------------------------------------------
    Unable to find libssl/libcrypto required for 
    compiling libbeato. Install this and run
    ./configure with the appropriate LDFLAGS. See
    the INSTALL for examples.
    ---------------------------------------------])
fi

AC_CHECK_HEADERS([kent/common.h],[
    has_kent=yes
    AC_SEARCH_LIBS([slSort], [kent], [], [has_kent=no])
    AC_SEARCH_LIBS([bam_hdr_init], [jkhts], [], [has_kent=no])
    if test "x${has_kent}" = xno; then
       AC_MSG_ERROR([
        ---------------------------------------------
        Unable to find libkent/libjkhts required for 
        compiling libbeato. Install this and run ./configure
        with the appropriate LDFLAGS. See the INSTALL
        for examples.
        ---------------------------------------------])
    fi],[AC_MSG_ERROR([
        ---------------------------------------------
        Unable to find libkent headers required for compiling
        libbeato. Install this and run ./configure with 
        the appropriate CFLAGS. See the INSTALL for
        examples.
        ---------------------------------------------])])

# Integrated htslib-specific defines
AC_DEFINE([USE_HTSLIB],[1],[Integrated UCSC htslib option])
AC_DEFINE([UCSC_CRAM],[1],[Integrated UCSC htslib option])
AC_DEFINE([KNETFILE_HOOKS],[1],[Integrated UCSC htslib option])

# Large file support
AC_SYS_LARGEFILE

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UID_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_FSEEKO
AC_FUNC_MKTIME
AC_FUNC_MMAP
AC_FUNC_STRTOD
AC_CHECK_FUNCS([bzero dup2 floor getcwd gettimeofday memmove memset mkdir munmap pow putenv regcomp rint select setenv socket sqrt strcasecmp strchr strcspn strdup strerror strrchr strspn strstr strtol tzset uname utime])

AC_CONFIG_FILES([Makefile beato/Makefile])

AC_OUTPUT
