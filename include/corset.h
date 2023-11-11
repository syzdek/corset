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
#ifndef __CORSET_H
#define __CORSET_H 1


///////////////
//           //
//  Headers  //
//           //
///////////////
// MARK: - Headers

#include <stddef.h>
#include <inttypes.h>
#include <sys/types.h>
#include <stdio.h>
#include <corset_module.h>


///////////////////
//               //
//  Definitions  //
//               //
///////////////////
// MARK: - Definitions

// general options
#define CORSET_OPT_PIDFILE          0x0101   // (char *)
#define CORSET_OPT_SOCKET           0x0102   // (char *)
#define CORSET_OPT_CONFFILE         0x0103   // (char *)
#define CORSET_OPT_MODDIR           0x0104   // (char *)
#define CORSET_OPT_VERBOSE          0x0105   // (int)
#define CORSET_OPT_QUIET            0x0106   // (int)
#define CORSET_OPT_FOREGROUND       0x0107   // (int)


// flags
#define CORSET_FLG_QUIET            0x0001
#define CORSET_FLG_FOREGROUND       0x0002


/////////////////
//             //
//  Datatypes  //
//             //
/////////////////
// MARK: - Datatypes

typedef struct _corset_cnf corset_cnf_t;
struct _corset_cnf
{
   int                  cnf_verbose;
   int                  cnf_flags;
   char *               cnf_conffile;
   char *               cnf_moddir;
   char *               cnf_pidfile;
   char *               cnf_sockfile;
};


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
// MARK: - Prototypes

//-------------------------//
// cli arguments functions //
//-------------------------//
// MARK: daemon functions

_CORSET_F int
corset_getopt(
         corset_cnf_t *                cnf,
         int                           argc,
         char * const *                argv,
         const char *                  optstring );


_CORSET_F void
corset_usage(
         const char *                  optstring );


_CORSET_F void
corset_usage_options(
         const char *                  optstring );


//------------------//
// daemon functions //
//------------------//
// MARK: daemon functions

_CORSET_F const char *
corset_prog_name(
         const char *                  str );


//-----------------//
// debug functions //
//-----------------//
// MARK: debug functions

_CORSET_F void
corset_debug_config(
         corset_cnf_t *                cnf,
         FILE *                        fs );


//------------------//
// memory functions //
//------------------//
// MARK: memory functions

_CORSET_F void
corset_destroy(
         corset_cnf_t *                cnf );


_CORSET_F int
corset_get_param(
         corset_cnf_t *                cnf,
         int                           option,
         void *                        outvalue );


_CORSET_F corset_cnf_t *
corset_init(
         void );


_CORSET_F int
corset_set_param(
         corset_cnf_t *                cnf,
         int                           option,
         const void *                  invalue );


#endif /* end of header */
