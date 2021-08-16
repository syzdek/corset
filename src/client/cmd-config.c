/*
 *  Corset Firewall
 *  Copyright (C) 2017 David M. Syzdek <david@syzdek.net>.
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

///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef __CORSET_PMARK
#pragma mark - Headers
#endif

#include "cmd-config.h"

#include <stdio.h>
#include <assert.h>


///////////////////
//               //
//  Definitions  //
//               //
///////////////////
#ifdef __CORSET_PMARK
#pragma mark - Definitions
#endif


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#ifdef __CORSET_PMARK
#pragma mark - Prototypes
#endif

void cfwc_cmd_config_usage(corsetfw * cfw);


/////////////////
//             //
//  Variables  //
//             //
/////////////////
#ifdef __CORSET_PMARK
#pragma mark - Variables
#endif


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#ifdef __CORSET_PMARK
#pragma mark - Functions
#endif

int cfwc_cmd_config(corsetfw * cfw, int argc, char ** argv)
{
   int                  c;
   int                  opt_index;

   static char   short_opt[] = "+" CFW_COMMON_GETOPT;

   assert(cfw != NULL);

   while((c = cfw_getopt(cfw, argc, argv, short_opt, &opt_index)) != -1)
   {
      switch(c)
      {
         case -1:   /* no more arguments */
         case 0:    /* long options toggles */
         break;

         case 'h':
         cfwc_cmd_config_usage(cfw);
         return(0);

         case 'V':
         cfw_version(cfw);
         return(0);

         case 1:
         return(1);

         case '?':
         fprintf(stderr, "Try `%s --help' for more information.\n", cfw->prog_name);
         return(1);

         default:
         fprintf(stderr, "%s: unrecognized option `--%c'\n", cfw->prog_name, c);
         fprintf(stderr, "Try `%s --help' for more information.\n", cfw->prog_name);
         return(1);
      };
   };

   printf("debug:    %" PRIu64 "\n", cfw->debug);
   printf("verbose:  %" PRIu8 "\n", cfw->verbose);
   printf("silent:   %" PRIu8 "\n", cfw->silent);

   return(0);
}


void cfwc_cmd_config_usage(corsetfw * cfw)
{
   printf("Usage: %s config [OPTIONS]\n", cfw->prog_name);
   printf("\n");

   cfw_usage_options(CFW_COMMON_GETOPT);
   printf("\n");
}


/* end of source */
