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
#define _LIB_LIBOTPUTIL_LMEMORY_C 1
#include "lmemory.h"

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
#include <stdio.h>
#include <sys/stat.h>

#include "ldaemon.h"


///////////////////
//               //
//  Definitions  //
//               //
///////////////////
// MARK: - Definitions

#define CORSET_DFLT_CONFFILE        (PKGCONFDIR    "/corsetd.conf")
#define CORSET_DFLT_FOREGROUND      CORSET_NO
#define CORSET_DFLT_MODDIR          (PKGLIBDIR     "/modules")
#define CORSET_DFLT_PIDFILE         (RUNSTATEDIR   "/corsetd.pid")
#define CORSET_DFLT_SOCKET          (RUNSTATEDIR   "/corsetd.sock")
#define CORSET_DFLT_VERBOSE         0
#define CORSET_DFLT_QUIET           CORSET_NO


/////////////////
//             //
//  Variables  //
//             //
/////////////////
// MARK: - Variables


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
// MARK: - Prototypes

static int
corset_defaults(
         corset_t *                    ch );


static void
corset_set_param_flag(
         corset_t *                    ch,
         unsigned                      flag,
         int                           dflt,
         const int *                   valp );


/////////////////
//             //
//  Functions  //
//             //
/////////////////
// MARK: - Functions

int
corset_defaults(
         corset_t *                    ch )
{
   int rc;
   if ((rc = corset_set_param(ch, CORSET_OPT_CONFFILE,      NULL))) return(rc);
   if ((rc = corset_set_param(ch, CORSET_OPT_FOREGROUND,    NULL))) return(rc);
   if ((rc = corset_set_param(ch, CORSET_OPT_MODDIR,        NULL))) return(rc);
   if ((rc = corset_set_param(ch, CORSET_OPT_PIDFILE,       NULL))) return(rc);
   if ((rc = corset_set_param(ch, CORSET_OPT_SOCKET,        NULL))) return(rc);
   if ((rc = corset_set_param(ch, CORSET_OPT_VERBOSE,       NULL))) return(rc);
   if ((rc = corset_set_param(ch, CORSET_OPT_QUIET,         NULL))) return(rc);
   return(0);
}


void
corset_destroy(
         corset_t *                    cnf )
{
   if (!(cnf))
      return;

   if ((cnf->cnf_pidfile))
      free(cnf->cnf_pidfile);
   free(cnf);

   return;
}


int
corset_get_param(
         corset_t *                    cnf,
         int                           option,
         void *                        outvalue )
{
   char *         str;

   switch(option)
   {
      case CORSET_OPT_CONFFILE:
      if ((str = bindle_strdup(cnf->cnf_conffile)) == NULL)
         return(-1);
      *((char **)outvalue) = str;
      return(0);

      case CORSET_OPT_FOREGROUND:
      *((int *)outvalue) = ((cnf->cnf_flags & CORSET_FLG_FOREGROUND)) ? 1 : 0;
      return(0);

      case CORSET_OPT_MODDIR:
      if ((str = bindle_strdup(cnf->cnf_moddir)) == NULL)
         return(-1);
      *((char **)outvalue) = str;
      return(0);

      case CORSET_OPT_PIDFILE:
      if ((str = bindle_strdup(cnf->cnf_pidfile)) == NULL)
         return(-1);
      *((char **)outvalue) = str;
      return(0);

      case CORSET_OPT_QUIET:
      *((int *)outvalue) = ((cnf->cnf_flags & CORSET_FLG_QUIET)) ? 1 : 0;
      return(0);

      case CORSET_OPT_SOCKET:
      if ((str = bindle_strdup(cnf->cnf_sockfile)) == NULL)
         return(-1);
      *((char **)outvalue) = str;
      return(0);

      case CORSET_OPT_VERBOSE:
      *((int *)outvalue) = cnf->cnf_verbose;
      return(0);

      default:
      return(-1);
   };

   return(0);
}


corset_t *
corset_init(
         void )
{
   corset_t *        cnf;

   // initialize memory
   if ((cnf = malloc(sizeof(corset_t))) == NULL)
      return(NULL);
   memset(cnf, 0, sizeof(corset_t));

   if ((corset_defaults(cnf)))
   {
      corset_destroy(cnf);
      return(NULL);
   };

   return(cnf);
}


int
corset_set_param(
         corset_t *                    cnf,
         int                           option,
         const void *                  invalue )
{
   char *         str;

   switch(option)
   {
      case CORSET_OPT_CONFFILE:
      invalue = ((invalue)) ? invalue : CORSET_DFLT_CONFFILE;
      if ((str = bindle_strdup(invalue)) == NULL)
         return(-1);
      if ((cnf->cnf_conffile))
         free(cnf->cnf_conffile);
      cnf->cnf_conffile = str;
      return(0);

      case CORSET_OPT_FOREGROUND:
      corset_set_param_flag(cnf, CORSET_FLG_FOREGROUND, CORSET_DFLT_FOREGROUND, invalue);
      return(0);

      case CORSET_OPT_MODDIR:
      invalue = ((invalue)) ? invalue : CORSET_DFLT_MODDIR;
      if ((str = bindle_strdup(invalue)) == NULL)
         return(-1);
      if ((cnf->cnf_moddir))
         free(cnf->cnf_moddir);
      cnf->cnf_moddir = str;
      return(0);

      case CORSET_OPT_PIDFILE:
      invalue = ((invalue)) ? invalue : CORSET_DFLT_PIDFILE;
      if ((str = bindle_strdup(invalue)) == NULL)
         return(-1);
      if ((cnf->cnf_pidfile))
         free(cnf->cnf_pidfile);
      cnf->cnf_pidfile = str;
      return(0);

      case CORSET_OPT_QUIET:
      corset_set_param_flag(cnf, CORSET_FLG_QUIET, CORSET_DFLT_QUIET, invalue);
      return(0);

      case CORSET_OPT_SOCKET:
      invalue = ((invalue)) ? invalue : CORSET_DFLT_SOCKET;
      if ((str = bindle_strdup(invalue)) == NULL)
         return(-1);
      if ((cnf->cnf_sockfile))
         free(cnf->cnf_sockfile);
      cnf->cnf_sockfile = str;
      return(0);

      case CORSET_OPT_VERBOSE:
      cnf->cnf_verbose = ((invalue)) ? *((const int *)invalue) : CORSET_DFLT_VERBOSE;
      return(0);

      default:
      break;
   };

   return(-1);
}


void
corset_set_param_flag(
         corset_t *                    ch,
         unsigned                      flag,
         int                           dflt,
         const int *                   valp )
{
   int ival;

   assert(ch != NULL);

   if (!(valp))
   {
      ival  = dflt;
      valp  = &ival;
   };

   if ((*valp))
      ch->cnf_flags |= flag;
   else
      ch->cnf_flags &= ~flag;

   return;
}

/* end of source file */
