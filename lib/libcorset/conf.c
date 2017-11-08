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

#include "conf.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <strings.h>


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

int cfw_destroy(corsetfw ** cfwp)
{
   assert(cfwp != NULL);

   // exit if there is nothing to do
   if (!(*cfwp))
      return(0);

   // free strings
   if ((*cfwp)->prog_name != NULL)     free((*cfwp)->prog_name);

   // zero and free configuration struct
   bzero(*cfwp, sizeof(struct corset_firewall));
   free(*cfwp);
   *cfwp = NULL;

   return(0);
}

int cfw_getopt(corsetfw * cfw, int argc, char * const * argv,
      const char * optstring, int *longindex)
{
   int c;

   static struct option long_opt[] =
   {
      {"help",             no_argument,       NULL, 'h' },
      {"quiet",            no_argument,       NULL, 'q' },
      {"silent",           no_argument,       NULL, 'q' },
      {"version",          no_argument,       NULL, 'V' },
      {"verbose",          no_argument,       NULL, 'v' },
      { NULL, 0, NULL, 0 }
   };

   assert(cfw != NULL);

   switch(c = getopt_long(argc, argv, optstring, long_opt, longindex))
   {
      // -d level, debug level
      case 'd':
      cfw->debug = (uint64_t) strtoumax(optarg, NULL, 0);
      return(0);


      // -q, --quiet, --silent, do not print messages
      case 'q':
      cfw->silent = 1;
      if ((cfw->verbose))
      {
         fprintf(stderr, "%s: incompatible options: `-q' and `-v'\n", cfw->prog_name);
         fprintf(stderr, "Try `%s --help' for more information.\n", cfw->prog_name);
         return(1);
      };
      return(0);


      // -v, --verbose, print verbose messages
      case 'v':
      cfw->verbose++;
      if ((cfw->silent))
      {
         fprintf(stderr, "%s: incompatible options: `-q' and `-v'\n", cfw->prog_name);
         fprintf(stderr, "Try `%s --help' for more information.\n", cfw->prog_name);
         return(1);
      };
      return(0);


      default:
      break;
   };

   return(c);
}


int cfw_initialize(corsetfw ** cfwp, const char * prog_name)
{
   const char * ptr;

   assert(cfwp       != NULL);
   assert(prog_name  != NULL);

   // allocation configuration struct
   if ((*cfwp = malloc(sizeof(corsetfw))) == NULL)
      return(-1);
   bzero(*cfwp, sizeof(sizeof(struct corset_firewall)));

   // save program name (used for help messages, logging, etc)
   if ((ptr = rindex(prog_name, '/')) != NULL)
      prog_name = &ptr[1];
   if (prog_name[0] == '\0')
   {
      cfw_destroy(cfwp);
      return(-1);
   };
   if (((*cfwp)->prog_name = strdup(prog_name)) == NULL)
   {
      cfw_destroy(cfwp);
      return(-1);
   };

   return(0);
}

/* end of source */
