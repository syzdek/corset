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
#ifndef __CORSET_MODULE_H
#define __CORSET_MODULE_H 1


///////////////
//           //
//  Headers  //
//           //
///////////////
// MARK: - Headers

#include <stddef.h>
#include <inttypes.h>
#include <sys/types.h>


//////////////
//          //
//  Macros  //
//          //
//////////////
// MARK: - Macros

// Exports function type
#undef CORSET_C_DECLS
#undef CORSET_BEGIN_C_DECLS
#undef CORSET_END_C_DECLS
#undef _CORSET_I
#undef _CORSET_F
#undef _CORSET_V
#if defined(__cplusplus) || defined(c_plusplus)
#   define _CORSET_I             extern "C" inline
#   define CORSET_C_DECLS        "C"             ///< exports as C functions
#   define CORSET_BEGIN_C_DECLS  extern "C" {    ///< exports as C functions
#   define CORSET_END_C_DECLS    }               ///< exports as C functions
#else
#   define _CORSET_I             inline
#   define CORSET_C_DECLS        /* empty */     ///< exports as C functions
#   define CORSET_BEGIN_C_DECLS  /* empty */     ///< exports as C functions
#   define CORSET_END_C_DECLS    /* empty */     ///< exports as C functions
#endif
#ifdef WIN32
#   ifdef _LIB_LIBCORSET_H
#      define _CORSET_F   extern CORSET_C_DECLS __declspec(dllexport)   ///< used for library calls
#      define _CORSET_V   extern CORSET_C_DECLS __declspec(dllexport)   ///< used for library calls
#   else
#      define _CORSET_F   extern CORSET_C_DECLS __declspec(dllimport)   ///< used for library calls
#      define _CORSET_V   extern CORSET_C_DECLS __declspec(dllimport)   ///< used for library calls
#   endif
#else
#   ifdef _LIB_LIBCORSET_H
#      define _CORSET_F   /* empty */                                      ///< used for library calls
#      define _CORSET_V   extern CORSET_C_DECLS                         ///< used for library calls
#   else
#      define _CORSET_F   extern CORSET_C_DECLS                         ///< used for library calls
#      define _CORSET_V   extern CORSET_C_DECLS                         ///< used for library calls
#   endif
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

typedef struct _corset corset_t;


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
// MARK: - Prototypes
CORSET_BEGIN_C_DECLS


CORSET_END_C_DECLS
#endif /* end of header file */
