/*
 *  Corset Firewall
 *  Copyright (C) 2023 David M. Syzdek <david@syzdek.net>.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of David M. Syzdek nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 *  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL DAVID M SYZDEK BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 */
#define _LIB_LIBOTPUTIL_LDEBUG_C 1
#include "ldebug.h"

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark - Headers

#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#pragma mark - Prototypes

static void
corset_debug_print_section(
         FILE *                        fs,
         int                           tabs,
         const char *                  title );


static void
corset_debug_print_str(
         FILE *                        fs,
         int                           tabs,
         const char *                  field,
         const char *                  value );


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#pragma mark - Functions

void
corset_debug_config(
         corset_cnf_t *                cnf,
         FILE *                        fs )
{
   if (!(cnf))
      return;

   fs = ((fs)) ? fs : stdout;

   corset_debug_print_section(fs, 0, "Package Information:");
   corset_debug_print_str(fs, 0, "Package Name:",           PACKAGE_NAME);
   corset_debug_print_str(fs, 0, "Package Version:",        PACKAGE_VERSION);
   corset_debug_print_section(fs, 0, NULL);

   corset_debug_print_section(fs, 0, "General Options:");
   corset_debug_print_str(fs, 0, "Quiet Mode:",             (((cnf->cnf_flags & CORSET_FLG_QUIET)) ? "yes" : "no"));
   corset_debug_print_str(fs, 0, "Verbose Mode:",           (((cnf->cnf_verbose)) ? "yes" : "no"));
   corset_debug_print_str(fs, 0, "Run in Foreground:",      (((cnf->cnf_flags & CORSET_FLG_FOREGROUND)) ? "yes" : "no"));
   corset_debug_print_str(fs, 0, "Configuration File:",     cnf->cnf_conffile);
   corset_debug_print_str(fs, 0, "PID File:",               cnf->cnf_pidfile);
   corset_debug_print_str(fs, 0, "Control Socket:",         cnf->cnf_sockfile);
   corset_debug_print_str(fs, 0, "Module Directory:",       cnf->cnf_moddir);
   corset_debug_print_section(fs, 0, NULL);

   return;
}


void
corset_debug_print_section(
         FILE *                        fs,
         int                           tabs,
         const char *                  title )
{
   fs    = ((fs))    ? fs    : stdout;
   tabs *= 3;
   if (!(title))
   {
      fprintf(fs, "\n");
      return;
   };
   fprintf(fs, "%*s%s\n", tabs, "", title);
   return;
}


void
corset_debug_print_str(
         FILE *                        fs,
         int                           tabs,
         const char *                  field,
         const char *                  value )
{
   tabs++;
   tabs *= 3;
   fs    = ((fs))    ? fs    : stdout;
   value = ((value)) ? value : "n/a";
   fprintf(fs, "%*s%-24s %s\n", tabs, "", field, value);
   return;
}


/* end of source file */
