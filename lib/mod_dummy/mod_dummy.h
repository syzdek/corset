/*
 *  Corset Firewall
 *  Copyright (C) 2023 David M. Syzdek <david@syzdek.net>.
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
/*
 *  @file lib/libcorset/libcorset.h
 */
#ifndef _LIB_MOD_DUMMY_MOD_DUMMY_H
#define _LIB_MOD_DUMMY_MOD_DUMMY_H 1


///////////////
//           //
//  Headers  //
//           //
///////////////
// MARK: - Headers

#include <corset_compat.h>

#ifdef HAVE_CONFIG_H
#   include <config.h>
#endif

#include <assert.h>
#include <time.h>

#include <corset_module.h>

#ifdef HAVE_BINDLE_PREFIX_H
#   include <bindle_prefix.h>
#else
#   include <bindle.h>
#endif


///////////////////
//               //
//  Definitions  //
//               //
///////////////////
// MARK: - Definitions


/////////////////
//             //
//  Datatypes  //
//             //
/////////////////
// MARK: - Datatypes

struct corset_module_data
{
   int                     dat_num1;
   int                     dat_num2;
};


/////////////////
//             //
//  Variables  //
//             //
/////////////////
// MARK: - Variables

extern const corset_mod_t mod_dummy;


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
// MARK: - Prototypes

extern int
mod_dummy_load(
         corset_t *                    cnf );


extern int
mod_dummy_unload(
         corset_t *                    cnf );


#endif /* end of header file */
