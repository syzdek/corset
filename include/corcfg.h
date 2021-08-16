/*
 *  Corset Firewall
 *  Copyright (C) 2021 David M. Syzdek <david@syzdek.net>.
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
#ifndef __CORCFG_H
#define __CORCFG_H 1


///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark - Headers

#include <limits.h>
#include <inttypes.h>


//////////////
//          //
//  Macros  //
//          //
//////////////
#pragma mark - Macros

// Exports function type
#undef CORCFG_C_DECLS
#undef CORCFG_BEGIN_C_DECLS
#undef CORCFG_END_C_DECLS
#undef _CORCFG_I
#undef _CORCFG_F
#undef _CORCFG_V
#if defined(__cplusplus) || defined(c_plusplus)
#   define _CORCFG_I             extern "C" inline
#   define CORCFG_C_DECLS        "C"             ///< exports as C functions
#   define CORCFG_BEGIN_C_DECLS  extern "C" {    ///< exports as C functions
#   define CORCFG_END_C_DECLS    }               ///< exports as C functions
#else
#   define _CORCFG_I             inline
#   define CORCFG_C_DECLS        /* empty */     ///< exports as C functions
#   define CORCFG_BEGIN_C_DECLS  /* empty */     ///< exports as C functions
#   define CORCFG_END_C_DECLS    /* empty */     ///< exports as C functions
#endif
#ifdef WIN32
#   ifdef _LIB_LIBCORCFG_H
#      define _CORCFG_F   extern CORCFG_C_DECLS __declspec(dllexport)   ///< used for library calls
#      define _CORCFG_V   extern CORCFG_C_DECLS __declspec(dllexport)   ///< used for library calls
#   else
#      define _CORCFG_F   extern CORCFG_C_DECLS __declspec(dllimport)   ///< used for library calls
#      define _CORCFG_V   extern CORCFG_C_DECLS __declspec(dllimport)   ///< used for library calls
#   endif
#else
#   ifdef _LIB_LIBCORCFG_H
#      define _CORCFG_F   /* empty */                                   ///< used for library calls
#      define _CORCFG_V   extern CORCFG_C_DECLS                         ///< used for library calls
#   else
#      define _CORCFG_F   extern CORCFG_C_DECLS                         ///< used for library calls
#      define _CORCFG_V   extern CORCFG_C_DECLS                         ///< used for library calls
#   endif
#endif


///////////////////
//               //
//  Definitions  //
//               //
///////////////////
#pragma mark - Definitions


//////////////////
//              //
//  Data Types  //
//              //
//////////////////
#pragma mark - Data Types

struct corcfg_data
{
   struct corcfg_data * parent;
   char *               filename;
   unsigned             line;
   int                  fd;
};
typedef struct corcfg_data CORCFG;


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#pragma mark - Prototypes


//------------------//
// memory functions //
//------------------//
#pragma mark memory functions

_CORCFG_F void
corcfg_free(
         CORCFG *                      cfg );

_CORCFG_F int
corcfg_open(
         CORCFG **                     cfgp,
         const char *                  path );


#endif /* end of header */
