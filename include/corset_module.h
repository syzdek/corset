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

#define CORSET_API                           0


#define CORSET_MOD_SINGLE                    0x0001


#define CORSET_USE_TRIGGER                   0x0001
#define CORSET_USE_CACHE                     0x0002
#define CORSET_USE_AUTHEN                    0x0004
#define CORSET_USE_AUTHOR                    0x0008
#define CORSET_USE_ACCT                      0x0010


/////////////////
//             //
//  Datatypes  //
//             //
/////////////////
// MARK: - Datatypes

typedef struct _corset                       corset_t;
typedef struct _corset_module                corset_mod_t;
typedef struct _corset_module_context        corset_ctx_t;
typedef struct corset_module_data            corset_dat_t;


struct _corset_module
{
   uint8_t                 mod_api;             // module API specificication version
   uint8_t                 mod_usage;           // types of module functions implemented
   uint8_t                 mod_reserved1;
   uint8_t                 mod_ctx_cnt;         // count of module contexts
   uint32_t                mod_flags;           // module options
   char *                  mod_name;            // internal name of module
   char *                  mod_path;            // directory path to module
   corset_ctx_t **         mod_ctx;             // array of module contexts

   // module functions
   int (*mod_load)(corset_t * cor);
   int (*mod_unload)(corset_t * cor);

   // context functions
   int (*mod_initialize)(corset_ctx_t * ctx);
   int (*mod_destroy)(corset_ctx_t * ctx);

   // connection functions
   int (*mod_connect)(corset_ctx_t * ctx);
   int (*mod_disconnect)(corset_ctx_t * ctx);
   int (*mod_noop)(corset_ctx_t * ctx);
};


struct _corset_module_context
{
   char *                  ctx_name;
   corset_t *              ctx_cor;
   corset_dat_t *          ctx_dat;          // context data/state
   const corset_mod_t *    ctx_mod;          // module definition
   corset_ctx_t *          ctx_conn;         // shared connection
};


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
// MARK: - Prototypes
CORSET_BEGIN_C_DECLS


CORSET_END_C_DECLS
#endif /* end of header file */
