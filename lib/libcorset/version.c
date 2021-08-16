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

#include "version.h"

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

void cfw_usage_options(const char * short_opt)
{
   int i;

   short_opt = ((short_opt)) ? short_opt : "hqVv";

   printf("OPTIONS:\n");
   for (i = 0; ((short_opt[i])); i++)
   {
      switch (short_opt[i])
      {
         case 'd':
         printf("  -d level                  debug level\n");
         break;

         case 'h':
         printf("  -h, --help                print this help and exit\n");
         break;

         case 'q':
         printf("  -q, --quiet, --silent     do not print messages\n");
         break;

         case 'V':
         printf("  -V, --version             print version number and exit\n");
         break;

         case 'v':
         printf("  -v, --verbose             print verbose messages\n");
         break;

         default:
         break;
      };
   };

   return;
}

void cfw_version(const corsetfw * cfw)
{
   assert(cfw != NULL);
   assert(cfw->prog_name != NULL);
   printf(( "%s (%s) %s\n"
            "%s\n"),
            cfw->prog_name, PACKAGE_NAME, PACKAGE_VERSION,
            PACKAGE_URL
   );
   return;
}


/* end of source */
