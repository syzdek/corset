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
#define _LIB_LIBOTPUTIL_LARGS_C 1
#include "largs.h"

///////////////
//           //
//  Headers  //
//           //
///////////////
// MARK: - Headers

#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <assert.h>
#include <getopt.h>
#include <sys/stat.h>

#include "ldaemon.h"


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
// MARK: - Prototypes

static void
corset_version(
         corset_t *                    ch );


/////////////////
//             //
//  Functions  //
//             //
/////////////////
// MARK: - Functions

int
corset_getopt(
         corset_t *                    ch,
         int                           argc,
         char * const *                argv,
         const char *                  optstring )
{
   int            c;
   int            rc;
   int            opt_index;

   static struct option long_opt[] =
   {
      {"help",             no_argument,       NULL, 'h' },
      {"quiet",            no_argument,       NULL, 'q' },
      {"silent",           no_argument,       NULL, 'q' },
      {"version",          no_argument,       NULL, 'V' },
      {"verbose",          no_argument,       NULL, 'v' },
      { NULL, 0, NULL, 0 }
   };

   assert(ch   != NULL);
   assert(argc != 0);
   assert(argv != NULL);

   optstring = ((optstring)) ? optstring : "fhL:qVv";
   opt_index = 0;

   while((c = getopt_long(argc, argv, optstring, long_opt, &opt_index)) != -1)
   {
      switch(c)
      {
         case -1:       /* no more arguments */
         case 0:        /* long options toggles */
         break;

         case 'f':
         ch->cor_flags |= CORSET_FLG_FOREGROUND;
         break;

         case 'h':
         corset_usage(optstring);
         return(2);

         case 'L':
         if ((rc = corset_set_param(ch, CORSET_OPT_MODDIR, optarg)) != 0)
         {
            fprintf(stderr, "%s: %s\n", corset_prog_name_ptr, "out of virtual memory");
            return(1);
         };
         break;

         case 'q':
         ch->cor_flags |= CORSET_FLG_QUIET;
         break;

         case 'V':
         corset_version(ch);
         return(2);

         case 'v':
         ch->cor_verbose++;
         break;

         case '?':
         fprintf(stderr, "Try `%s --help' for more information.\n", corset_prog_name_ptr);
         return(1);

         default:
         fprintf(stderr, "%s: unrecognized option `--%c'\n", corset_prog_name_ptr, c);
         fprintf(stderr, "Try `%s --help' for more information.\n", corset_prog_name_ptr);
         return(1);
      };
   };

   if ( ((ch->cor_flags & CORSET_FLG_QUIET)) && ((ch->cor_verbose)) )
   {
      fprintf(stderr, "%s: incompatible options `-q' and `-v'\n", corset_prog_name_ptr);
      fprintf(stderr, "Try `%s --help' for more information.\n", corset_prog_name_ptr);
      return(1);
   };

   return(0);
}


void
corset_usage_options(
         const char *                  optstring )
{
   printf("OPTIONS:\n");
   if ((strchr(optstring, 'h'))) printf("  -h, --help                print this help and exit\n");
   if ((strchr(optstring, 'q'))) printf("  -q, --quiet, --silent     do not print messages\n");
   if ((strchr(optstring, 'V'))) printf("  -V, --version             print version number and exit\n");
   if ((strchr(optstring, 'v'))) printf("  -v, --verbose             print verbose messages\n");

   return;
}


void
corset_version(
         corset_t *                    ch )
{
   assert(ch  != NULL);
   printf("%s (%s) %s\n", corset_prog_name_ptr, PACKAGE_NAME, PACKAGE_VERSION);
   printf("Written by David M. Syzdek.\n");
   return;
}

/* end of source file */
