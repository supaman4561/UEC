#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([tndhmc],[0.01],[daihinmin@inf.uec.ac.jp])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/client.c])
AC_CONFIG_HEADER([src/config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_DEFUN([LIB_SOCKET_NSL],
[
        AC_SEARCH_LIBS([gethostbyname], [nsl])
        AC_SEARCH_LIBS([socket], [socket], [], [
                AC_CHECK_LIB([socket], [socket], [LIBS="-lsocket -lnsl $LIBS"],
                [], [-lnsl])])
])
LIB_SOCKET_NSL

LDFLAGS="$LDFLAGS"

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([arpa/inet.h inttypes.h netdb.h netinet/in.h stdlib.h string.h strings.h sys/param.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CHECK_FUNCS([bzero inet_ntoa memset socket],,AC_MSG_ERROR(not found.))

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
