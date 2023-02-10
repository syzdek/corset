#
#   Corset Firewall
#   Copyright (C) 2023 David M. Syzdek <david@syzdek.net>.
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

# AC_CORSET_DAEMON()
# ______________________________________________________________________________
AC_DEFUN([AC_CORSET_DAEMON],[dnl
   enableval=""
   AC_ARG_ENABLE(
      daemon,
      [AS_HELP_STRING([--disable-daemon], [install corsetd])],
      [ EDAEMON=$enableval ],
      [ EDAEMON=$enableval ]
   )

   if test "x${EDAEMON}" == "xno";then
      ENABLE_DAEMON="no"
   else
      ENABLE_DAEMON="yes"
   fi

   AM_CONDITIONAL([ENABLE_DAEMON],  [test "$ENABLE_DAEMON" = "yes"])
   AM_CONDITIONAL([DISABLE_DAEMON], [test "$ENABLE_DAEMON" = "no"])
])dnl


# AC_CORSET_DOCS()
# ______________________________________________________________________________
AC_DEFUN([AC_CORSET_DOCS],[dnl
   enableval=""
   AC_ARG_ENABLE(
      extra-docs,
      [AS_HELP_STRING([--enable-extra-docs], [install extra documentation])],
      [ EDOCUMENATION=$enableval ],
      [ EDOCUMENATION=$enableval ]
   )

   if test "x${EDOCUMENATION}" == "xyes";then
      ENABLE_DOCUMENATION="yes"
   else
      ENABLE_DOCUMENATION="no"
   fi

   AM_CONDITIONAL([ENABLE_DOCUMENATION],  [test "$ENABLE_DOCUMENATION" = "yes"])
   AM_CONDITIONAL([DISABLE_DOCUMENATION], [test "$ENABLE_DOCUMENATION" = "no"])
])dnl


# AC_CORSET_EXAMPLES()
# ______________________________________________________________________________
AC_DEFUN([AC_CORSET_EXAMPLES],[dnl
   enableval=""
   AC_ARG_ENABLE(
      examples,
      [AS_HELP_STRING([--enable-examples], [build examples])],
      [ EEXAMPLES=$enableval ],
      [ EEXAMPLES=$enableval ]
   )

   if test "x${EEXAMPLES}" == "xyes";then
      ENABLE_EXAMPLES="yes"
   else
      ENABLE_EXAMPLES="no"
   fi

   AM_CONDITIONAL([ENABLE_EXAMPLES],  [test "$ENABLE_EXAMPLES" = "yes"])
   AM_CONDITIONAL([DISABLE_EXAMPLES], [test "$ENABLE_EXAMPLES" = "no"])
])dnl


# AC_CORSET_MODULE_DEV()
# ______________________________________________________________________________
AC_DEFUN([AC_CORSET_MODULE_DEV],[dnl
   enableval=""
   AC_ARG_ENABLE(
      module-dev,
      [AS_HELP_STRING([--enable-module-dev], [install module development files])],
      [ EMODULEDEV=$enableval ],
      [ EMODULEDEV=$enableval ]
   )

   if test "x${EMODULEDEV}" == "xyes";then
      ENABLE_MODULE_DEV="yes"
   else
      ENABLE_MODULE_DEV="no"
   fi

   AM_CONDITIONAL([ENABLE_MODULE_DEV],  [test "$ENABLE_MODULE_DEV" = "yes"])
   AM_CONDITIONAL([DISABLE_MODULE_DEV], [test "$ENABLE_MODULE_DEV" = "no"])
])dnl

# end of m4 file
