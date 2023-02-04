/*
 *  Corset Firewall
 *  Copyright (C) 2020, 2023 David M. Syzdek <david@syzdek.net>.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *     1. Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *
 *     2. Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *
 *     3. Neither the name of the copyright holder nor the names of its
 *        contributors may be used to endorse or promote products derived from
 *        this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 *  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 *  @file src/examples/example-ipset.c example ipset program
 */
/*
 *  Simple Build:
 *     CFLAGS='-DPROGRAM_NAME="example-ipset" -Wall -Werror'
 *     LDFLAGS='-lipset'
 *     gcc ${CFLAGS}  -c -o example-ipset.o example-ipset.c
 *     gcc ${LDFLAGS}    -o example-ipset   example-ipset.o
 *
 *  Simple Clean:
 *     rm -f example-ipset.lo example-ipset
 *
 *  Libtool Build:
 *     CFLAGS='-DPROGRAM_NAME="example-ipset" -Wall -Werror'
 *     LDFLAGS='-lnetfilter_queue'
 *     libtool --mode=compile --tag=CC gcc ${CFLAGS}  -c example-ipset.c
 *     libtool --mode=link    --tag=CC gcc ${LDFLAGS} -o example-ipset \
 *             example-ipset.lo
 *
 *  Libtool Clean:
 *     libtool --mode=clean rm -f example-ipset.lo example-ipset
 */
#define _CORSET_EXAMPLES_EXAMPLE_IPSET_C 1


///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark - Headers

#include <corset_compat.h>

#ifdef HAVE_CONFIG_H
#   include <config.h>
#endif

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>
#include <assert.h>
#include <signal.h>
#include <stdarg.h>
#include <arpa/inet.h>
#include <libipset/ipset.h>


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#pragma mark - Prototypes

extern int
main(
         int                           argc,
         char *                        argv[] );


static int
my_custom_errorfn(
         struct ipset *                ipset,
         void *                        p,
         int                           status,
         const char *                  msg,
         ... );


static int
my_standard_errorfn(
         struct ipset *                ipset,
         void *                        p );


static int
my_print_outfn(
         struct ipset_session *        session,
         void *                        p,
         const char *                  fmt,
         ... );


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#pragma mark - Functions

int
main(
         int                           argc,
         char *                        argv[] )
{
   char *                  prog_name;
   struct ipset *          ipset;
   int                     rc;
   char                    line[1024];
   char                    errmsg[IPSET_ERRORBUFLEN];


   // determine program name for error messages
   if ((prog_name = rindex(argv[0], '/')) == NULL)
   {
      prog_name = argv[0];
   } else {
      prog_name = &prog_name[1];
   };


   // process user supplied parameters
   if ( (argc < 3) || (argc > 4) )
   {
      fprintf(stderr, "Usage: %s <set> [ <entry> [ <comment> ] ]\n", prog_name);
      fprintf(stderr, "Create sets with:\n");
      fprintf(stderr, "   ipset create TEST1 hash:net family inet hashsize 1024 maxelem 65536 comment\n");
      fprintf(stderr, "   ipset create TEST2 hash:net family inet hashsize 1024 maxelem 65536 comment\n");
      fprintf(stderr, "   ipset create TEST3 hash:net family inet hashsize 1024 maxelem 65536\n");
      fprintf(stderr, "   ipset create TEST4 hash:net family inet hashsize 1024 maxelem 65536\n");
      fprintf(stderr, "\n");
      return(1);
   };


   // checks user
   if (getuid() != 0)
   {
      fprintf(stderr, "%s: must run as root\n", prog_name);
      return(1);
   };


   // initialize ipset library
   ipset_load_types();
   if ((ipset = ipset_init()) == NULL)
   {
      fprintf(stderr, "%s: unable to initialize ipset\n", prog_name);
      return(1);
   };
   ipset_custom_printf(ipset, my_custom_errorfn, my_standard_errorfn, my_print_outfn, errmsg);


   // verifies set exists
   snprintf(line, sizeof(line), "list %s", argv[1]);
   if ((rc = ipset_parse_line(ipset, line)) == -1)
   {
      fprintf(stderr, "%s: set does not exist\n", prog_name);
      ipset_fini(ipset);
      return(1);
   };


   // adds entry to set
   if (argc == 3)
      snprintf(line, sizeof(line), "add %s %s", argv[1], argv[2]);
   else
      snprintf(line, sizeof(line), "add %s %s comment \"%s\"", argv[1], argv[2], argv[3]);
   if ((rc = ipset_parse_line(ipset, line)) == -1)
   {
      fprintf(stderr, "%s: %s\n", prog_name, errmsg);
      ipset_fini(ipset);
      return(1);
   };


   // clean up resources
   ipset_fini(ipset);


   return(0);
}


int
my_custom_errorfn(
         struct ipset *                ipset,
         void *                        p,
         int                           status,
         const char *                  msg,
         ... )
{
   strncpy(p, msg, IPSET_ERRORBUFLEN);
   return(-1);
}


int
my_standard_errorfn(
         struct ipset *                ipset,
         void *                        p )
{
   char *      errmsg;
   size_t      len;

   errmsg = p;
   strncpy(errmsg, ipset_session_report_msg(ipset_session(ipset)), IPSET_ERRORBUFLEN);
   if ((len = strlen(errmsg)) > 0)
      len--;
   errmsg[len] = '\0';
   
   return(-1);
}


int
my_print_outfn(
         struct ipset_session *        session,
         void *                        p,
         const char *                  fmt,
         ... )
{
   return(0);
}


/* end of source */
