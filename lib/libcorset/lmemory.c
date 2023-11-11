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


/////////////////
//             //
//  Variables  //
//             //
/////////////////
// MARK: - Variables

static int default_cnf_init = 0;
static corset_cnf_t default_cnf =
{
   .cnf_conffile           = NULL,
   .cnf_flags              = 0,
   .cnf_moddir             = NULL,
   .cnf_pidfile            = NULL,
   .cnf_sockfile           = NULL,
   .cnf_verbose            = 0,
};


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
// MARK: - Prototypes

static int
corset_defaults(
         corset_cnf_t *                cnf );


/////////////////
//             //
//  Functions  //
//             //
/////////////////
// MARK: - Functions

int
corset_defaults(
         corset_cnf_t *                cnf )
{
   int               rc;
   int               ival;
   const char *      str;
   char              buff[128];

   default_cnf_init  = 1;
   cnf               = ((cnf)) ? cnf : &default_cnf;

   // copy flags
   cnf->cnf_flags = default_cnf.cnf_flags;

   // CORSET_OPT_CONFFILE
   str = ((default_cnf.cnf_conffile)) ? default_cnf.cnf_conffile : buff;
   if (str == buff)
      snprintf(buff, sizeof(buff), "%s/%s.conf", PKGCONFDIR, corset_prog_name_ptr);
   if ((rc = corset_set_param(cnf, CORSET_OPT_CONFFILE, str)) != 0)
      return(rc);

   // CORSET_OPT_MODDIR
   str = ((default_cnf.cnf_moddir)) ? default_cnf.cnf_moddir : buff;
   if (str == buff)
      snprintf(buff, sizeof(buff), "%s/modules", PKGLIBDIR);
   if ((rc = corset_set_param(cnf, CORSET_OPT_MODDIR, str)) != 0)
      return(rc);

   // CORSET_OPT_PIDFILE
   str = ((default_cnf.cnf_pidfile)) ? default_cnf.cnf_pidfile : buff;
   if (str == buff)
      snprintf(buff, sizeof(buff), "%s/%s.pid", RUNSTATEDIR, corset_prog_name_ptr);
   if ((rc = corset_set_param(cnf, CORSET_OPT_PIDFILE, str)) != 0)
      return(rc);

   // CORSET_OPT_SOCKET
   str = ((default_cnf.cnf_sockfile)) ? default_cnf.cnf_sockfile : buff;
   if (str == buff)
      snprintf(buff, sizeof(buff), "%s/%s.sock", RUNSTATEDIR, corset_prog_name_ptr);
   if ((rc = corset_set_param(cnf, CORSET_OPT_SOCKET, str)) != 0)
      return(rc);

   // CORSET_OPT_VERBOSE
   ival = default_cnf.cnf_verbose;
   if ((rc = corset_set_param(cnf, CORSET_OPT_VERBOSE, &ival)) != 0)
      return(rc);

   return(0);
}


void
corset_destroy(
         corset_cnf_t *                cnf )
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
         corset_cnf_t *                cnf,
         int                           option,
         void *                        outvalue )
{
   int            rc;
   char *         str;

   cnf = ((cnf)) ? cnf : &default_cnf;

   // initialize defaults
   if (!(default_cnf_init))
      if ((rc = corset_defaults(NULL)) != 0)
         return(rc);

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


corset_cnf_t *
corset_init(
         void )
{
   int               rc;
   corset_cnf_t *    cnf;

   // initialize defaults
   if (!(default_cnf_init))
      if ((rc = corset_defaults(NULL)) != 0)
         return(NULL);

   // initialize memory
   if ((cnf = malloc(sizeof(corset_cnf_t))) == NULL)
      return(NULL);
   memset(cnf, 0, sizeof(corset_cnf_t));
   if ((rc = corset_defaults(cnf)) != 0)
   {
      corset_destroy(cnf);
      return(NULL);
   };

   return(cnf);
}


int
corset_set_param(
         corset_cnf_t *                cnf,
         int                           option,
         const void *                  invalue )
{
   int            rc;
   char *         str;

   cnf = ((cnf)) ? cnf : &default_cnf;

   // initialize defaults
   if (!(default_cnf_init))
      if ((rc = corset_defaults(NULL)) != 0)
         return(rc);

   switch(option)
   {
      case CORSET_OPT_CONFFILE:
      if ((str = bindle_strdup(invalue)) == NULL)
         return(-1);
      if ((cnf->cnf_conffile))
         free(cnf->cnf_conffile);
      cnf->cnf_conffile = str;
      return(0);

      case CORSET_OPT_FOREGROUND:
      if ((invalue))
         cnf->cnf_flags |= CORSET_FLG_FOREGROUND;
      if (!(invalue))
         cnf->cnf_flags &= ~CORSET_FLG_FOREGROUND;
      return(0);

      case CORSET_OPT_MODDIR:
      invalue = ((invalue)) ? invalue : default_cnf.cnf_moddir;
      if ((str = bindle_strdup(invalue)) == NULL)
         return(-1);
      if ((cnf->cnf_moddir))
         free(cnf->cnf_moddir);
      cnf->cnf_moddir = str;
      return(0);

      case CORSET_OPT_PIDFILE:
      if ((str = bindle_strdup(invalue)) == NULL)
         return(-1);
      if ((cnf->cnf_pidfile))
         free(cnf->cnf_pidfile);
      cnf->cnf_pidfile = str;
      return(0);

      case CORSET_OPT_QUIET:
      if ((invalue))
         cnf->cnf_flags |= CORSET_FLG_QUIET;
      if (!(invalue))
         cnf->cnf_flags &= ~CORSET_FLG_QUIET;
      return(0);

      case CORSET_OPT_SOCKET:
      if ((str = bindle_strdup(invalue)) == NULL)
         return(-1);
      if ((cnf->cnf_sockfile))
         free(cnf->cnf_sockfile);
      cnf->cnf_sockfile = str;
      return(0);

      case CORSET_OPT_VERBOSE:
      cnf->cnf_verbose = ((invalue)) ? *((const int *)invalue) : default_cnf.cnf_verbose;
      return(0);

      default:
      break;
   };

   return(-1);
}


/* end of source file */
