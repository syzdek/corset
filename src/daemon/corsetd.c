/*
 *  Corset Firewall
 *  Copyright (C) 2017 David M. Syzdek <david@syzdek.net>.
 *  All rights reserved.
 *
 *  @SYZDEK_BSD_LICENSE_START@
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
 *
 *  @SYZDEK_BSD_LICENSE_END@
 */

///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef __CORSET_PMARK
#pragma mark - Headers
#endif

#include "corsetd.h"

#include <stdio.h>


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

void corsetd_usage(corsetfw * cfw);
int main(int argc, char * argv[]);


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
void corsetd_usage(corsetfw * cfw)
{
   printf("Usage: %s [OPTIONS]\n", cfw->prog_name);
   printf("\n");

   cfw_usage_options(CFW_COMMON_GETOPT);
   printf("\n");

   return;
}


int main(int argc, char * argv[])
{
   int              rc;
   int              c;
   int              opt_index;
   corsetfw       * cfw;

   static char   short_opt[] = "+" CFW_COMMON_GETOPT;

   if ((rc = cfw_initialize(&cfw, argv[0])) == -1)
   {
      perror("cfw_initialize()");
      return(1);
   };

   while((c = cfw_getopt(cfw, argc, argv, short_opt, &opt_index)) != -1)
   {
      switch(c)
      {
         case -1:   /* no more arguments */
         case 0:    /* long options toggles */
         break;

         case 'h':
         corsetd_usage(cfw);
         cfw_destroy(&cfw);
         return(0);

         case 'V':
         cfw_version(cfw);
         cfw_destroy(&cfw);
         return(0);

         case 1:
         cfw_destroy(&cfw);
         cfw_destroy(&cfw);
         return(1);

         case '?':
         fprintf(stderr, "Try `%s --help' for more information.\n", cfw->prog_name);
         cfw_destroy(&cfw);
         return(1);

         default:
         fprintf(stderr, "%s: unrecognized option `--%c'\n", cfw->prog_name, c);
         fprintf(stderr, "Try `%s --help' for more information.\n", cfw->prog_name);
         cfw_destroy(&cfw);
         return(1);
      };
   };

   cfw_destroy(&cfw);

   return(0);
}

/* end of source */
