#
#   Corset Firewall
#   Copyright (C) 2017 David M. Syzdek <david@syzdek.net>.
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions are
#   met:
#
#      * Redistributions of source code must retain the above copyright
#        notice, this list of conditions and the following disclaimer.
#      * Redistributions in binary form must reproduce the above copyright
#        notice, this list of conditions and the following disclaimer in the
#        documentation and/or other materials provided with the distribution.
#      * Neither the name of David M. Syzdek nor the
#        names of its contributors may be used to endorse or promote products
#        derived from this software without specific prior written permission.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
#   IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#   PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL DAVID M SYZDEK BE LIABLE FOR
#   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
#   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
#   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
#   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
#   SUCH DAMAGE.
#
#   acinclude.m4 - custom m4 macros used by configure.ac
#


# AC_CFW_YAJL
# ______________________________________________________________________________
AC_DEFUN([AC_CFW_YAJL],[dnl

   withval=""
   AC_ARG_WITH(
      yajl-includedir,
      [AS_HELP_STRING([--with-yajl-includedir=DIR], [Search for yajl headers in DIR.])],
      [ WITH_YAJL_INCLUDEDIR=$withval ],
      [ WITH_YAJL_INCLUDEDIR=$withval ]
   )
   withval=""
   AC_ARG_WITH(
      yajl-libdir,
      [AS_HELP_STRING([--with-yajl-libdir=DIR], [Search for yajl library in DIR.])],
      [ WITH_YAJL_LIBDIR=$withval ],
      [ WITH_YAJL_LIBDIR=$withval ]
   )

   # modifies CPPFLAGS and LDFLAGS
   if test "x${WITH_YAJL_INCLUDEDIR}" != "x" && \
      test "x${WITH_YAJL_INCLUDEDIR}" != "xno" && \
      test "x${WITH_YAJL_INCLUDEDIR}" != "xyes";then
      CPPFLAGS="${CPPFLAGS} -I${WITH_YAJL_INCLUDEDIR}"
   fi
   if test "x${WITH_YAJL_LIBDIR}" != "x" && \
      test "x${WITH_YAJL_LIBDIR}" != "xno" && \
      test "x${WITH_YAJL_LIBDIR}" != "xyes";then
      LDFLAGS="${LDFLAGS} -L${WITH_YAJL_LIBDIR} -lyajl"
   else
      LDFLAGS="${LDFLAGS} -lyajl"
   fi

   HAVE_YAJL=yes
   AC_CHECK_HEADERS([yajl/yajl_parse.h],  [], [HAVE_YAJL=no])
   AC_CHECK_HEADERS([yajl/yajl_gen.h],    [], [HAVE_YAJL=no])
   AC_CHECK_TYPES([yajl_gen],             [], [HAVE_YAJL=no], [[#include <yajl/yajl_gen.h>]])
   AC_CHECK_TYPES([yajl_handle],          [], [HAVE_YAJL=no], [[#include <yajl/yajl_parse.h>]])
   AC_CHECK_TYPES([yajl_status],          [], [HAVE_YAJL=no], [[#include <yajl/yajl_parse.h>]])
   AC_CHECK_TYPES([yajl_callbacks],       [], [HAVE_YAJL=no], [[#include <yajl/yajl_parse.h>]])
   AC_SEARCH_LIBS([yajl_gen_null],        [yajl], [], [HAVE_YAJL=no])
   AC_SEARCH_LIBS([yajl_gen_bool],        [yajl], [], [HAVE_YAJL=no])
   AC_SEARCH_LIBS([yajl_gen_number],      [yajl], [], [HAVE_YAJL=no])
   AC_SEARCH_LIBS([yajl_gen_string],      [yajl], [], [HAVE_YAJL=no])
   AC_SEARCH_LIBS([yajl_gen_map_open],    [yajl], [], [HAVE_YAJL=no])
   AC_SEARCH_LIBS([yajl_gen_map_close],   [yajl], [], [HAVE_YAJL=no])
   AC_SEARCH_LIBS([yajl_gen_array_open],  [yajl], [], [HAVE_YAJL=no])
   AC_SEARCH_LIBS([yajl_gen_array_close], [yajl], [], [HAVE_YAJL=no])
   AC_SEARCH_LIBS([yajl_gen_alloc],       [yajl], [], [HAVE_YAJL=no])
   AC_SEARCH_LIBS([yajl_gen_config],      [yajl], [], [HAVE_YAJL=no])
   AC_SEARCH_LIBS([yajl_alloc],           [yajl], [], [HAVE_YAJL=no])
   AC_SEARCH_LIBS([yajl_config],          [yajl], [], [HAVE_YAJL=no])
   AC_SEARCH_LIBS([yajl_parse],           [yajl], [], [HAVE_YAJL=no])

   if test "x${HAVE_YAJL}" == "xno";then
      AC_MSG_ERROR([Unable to find yajl prerequists])
   fi

])dnl


# end of m4 file
