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
/**
 *  @file common.c
 *  Functions, datatypes, and preprocessor macros common to both corset
 *  (client utility) and corsetd (daemon). This project used the name space
 *  "CFW" (Corset Firewall) and "CORSET".  The following prefixes are
 *  employeed:
 *
 *    // Common
 *    cfw_  - Prefix for common function prototypes
 *    CFW   - prefix for common datatypes
 *    CFW_  - Prefix for common pre-processor macros
 *    cfwc_ - Prefix for client specfic function prototypes
 *    CFWC  - prefix for client specfic datatypes
 *    CFWC_ - Prefix for client specfic pre-processor macros
 *    cfwd_ - Prefix for daemon specfic function prototypes
 *    CFWD  - prefix for daemon specfic datatypes
 *    CFWD_ - Prefix for daemon specfic pre-processor macros
 */
#ifndef __CORSET_COMMON_H
#define __CORSET_COMMON_H 1


///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef __CORSET_PMARK
#pragma mark - Headers
#endif

#include <limits.h>


///////////////////
//               //
//  Definitions  //
//               //
///////////////////
#ifdef __CORSET_PMARK
#pragma mark - Definitions
#endif

#ifndef PACKAGE_BUGREPORT
#define PACKAGE_BUGREPORT "david@syzdek.net"
#endif
#ifndef PACKAGE_COPYRIGHT
#define PACKAGE_COPYRIGHT ""
#endif
#ifndef PACKAGE_NAME
#define PACKAGE_NAME "Corset Firewall"
#endif
#ifndef PACKAGE_VERSION
#define PACKAGE_VERSION ""
#endif
#ifndef PACKAGE_URL
#define PACKAGE_URL ""
#endif


#ifdef LINE_MAX
#   define CFW_LINE_MAX LINE_MAX
#elif defined _POSIX2_LINE_MAX
#   define CFW_LINE_MAX _POSIX2_LINE_MAX
#else
#   define CFW_LINE_MAX 2048
#endif
#define CFW_BUFF_MAX (CFW_LINE_MAX*20)


//////////////////
//              //
//  Data Types  //
//              //
//////////////////
#ifdef __CORSET_PMARK
#pragma mark - Data Types
#endif


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#ifdef __CORSET_PMARK
#pragma mark - Prototypes
#endif

void cfw_version(const char * prog_name);

#endif /* end of header */
