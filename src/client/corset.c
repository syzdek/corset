/*
 *  Corset Firewall
 *  Copyright (C) 2017 David M. Syzdek <david@syzdek.net>.
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

///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef __CORSET_PMARK
#pragma mark - Headers
#endif

#include "corset.h"
#include "cmd-config.h"

#include <stdio.h>
#include <getopt.h>
#include <assert.h>
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

int cfwc_cmd_version(corsetfw * cfw, int argc, char ** argv);
int cfwc_cmd_help(corsetfw * cfw, int argc, char ** argv);
const cfwc_command * corset_cmd_lookup(const char * wname, int exact);
void corset_usage(corsetfw * cfw);

int main(int argc, char * argv[]);


/////////////////
//             //
//  Variables  //
//             //
/////////////////
#ifdef __CORSET_PMARK
#pragma mark - Variables
#endif

const cfwc_command cfwc_command_map[] =
{
   {
      "config",                                             // widget name
      "Writes intepretted configuration to standard out.",  // widget description
      (const char * const[]) { NULL },                      // widget alias
      cfwc_cmd_config,                                      // widget function
   },
   {
      "configrunning",                                      // widget name
      "Retrieves daemon's running config",                  // widget description
      (const char * const[]) { NULL },                      // widget alias
      NULL /* cfw_widget_confdump */,                       // widget function
   },
   {
      "configtest",                                         // widget name
      "Validates configuration.",                           // widget description
      (const char * const[]) { NULL },                      // widget alias
      NULL /* cfw_widget_confdump */,                       // widget function
   },
   {
      "help",                                               // widget name
      "Display usage information.",                         // widget description
      (const char * const[]) { NULL },                      // widget alias
      cfwc_cmd_help,                                        // widget function
   },
   {
      "status",                                             // widget name
      "Returns daemon status",                              // widget description
      (const char * const[]) { NULL },                      // widget alias
      NULL /* cfw_widget_confdump */,                       // widget function
   },
   {
      "stop",                                               // widget name
      "Stops daemon.",                                      // widget description
      (const char * const[]) { NULL },                      // widget alias
      NULL /* cfw_widget_confdump */,                       // widget function
   },
   {
      "version",                                            // widget name
      "Display verison information.",                       // widget description
      (const char * const[]) { NULL },                      // widget alias
      cfwc_cmd_version,                                     // widget function
   },
   { NULL, NULL, NULL, NULL }
};


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#ifdef __CORSET_PMARK
#pragma mark - Functions
#endif

int cfwc_cmd_version(corsetfw * cfw, int argc, char ** argv)
{
   assert(argc > -1);
   assert(argv != NULL);
   cfw_version(cfw);
   return(0);
}


int cfwc_cmd_help(corsetfw * cfw, int argc, char ** argv)
{
   assert(argc > -1);
   assert(argv != NULL);
   corset_usage(cfw);
   return(0);
}


const cfwc_command * corset_cmd_lookup(const char * cmd_name, int exact)
{
   int                x;
   int                y;
   int                z;
   int                prefix_uniq;
   int                prefix_common;
   const cfwc_command * matched_cmd;
   const cfwc_command * cmd;

   assert(cmd_name != NULL);

   matched_cmd = NULL;
   prefix_uniq    = -1;
   prefix_common  = -1;

   for(x = 0; cfwc_command_map[x].name != NULL; x++)
   {
      cmd = &cfwc_command_map[x];

      // skip place holders
      if (cmd->func == NULL)
         continue;

      // compares widget name
      if (strcmp(cmd->name, cmd_name) == 0)
         return(cmd);
      if (!(exact))
      {
         for(z = 0; ( (cmd->name[z] != '\0') &&
                      (cmd_name[z]  != '\0') &&
                      (cmd->name[z] == cmd_name[z]) ); z++)
         {
            if (z > prefix_uniq)
            {
               matched_cmd = cmd;
               prefix_uniq    = z;
            }
            else if (z == prefix_uniq)
            {
               prefix_common = z;
            };
         };
      };

      // compares widget aliases
      if (!(cmd->alias))
         continue;
      for(y = 0; cmd->alias[y]; y++)
      {
         if (strcmp(cmd->alias[y], cmd_name) == 0)
            return(cmd);
         for(z = 0; ( (cmd->alias[y][z] != '\0') &&
                      (cmd_name[z]      != '\0') &&
                      (cmd->alias[y][z] == cmd_name[z]) ); z++)
         {
            if (z > prefix_uniq)
            {
               matched_cmd = cmd;
               prefix_uniq = z;
            }
            else if (z == prefix_uniq)
            {
               prefix_common = z;
            };
         };
      };
   };

   if (prefix_common >= prefix_uniq)
      return(NULL);

   return(matched_cmd);
}


void corset_usage(corsetfw * cfw)
{
   int  x;

   printf("Usage: %s [OPTIONS] command [COMMANDOPTS]\n", cfw->prog_name);
   printf("\n");

   cfw_usage_options(CFW_COMMON_GETOPT);
   printf("\n");

   printf("COMMANDS:\n");
   for (x = 0; cfwc_command_map[x].name; x++)
   {
      if (cfwc_command_map[x].func == NULL)
         continue;
      if (cfwc_command_map[x].desc == NULL)
         continue;
      printf("   %-24s %s\n", cfwc_command_map[x].name, cfwc_command_map[x].desc);
   };
   printf("\n");

   return;
}


int main(int argc, char * argv[])
{
   int                  rc;
   int                  c;
   int                  opt_index;
   corsetfw           * cfw;
   const cfwc_command * cmd;

   static char   short_opt[] = "+" CFW_COMMON_GETOPT;

   if ((rc = cfw_initialize(&cfw, argv[0])) == -1)
   {
      perror("cfw_initialize()");
      return(1);
   };

   while((c = cfw_getopt(cfw, argc, argv, short_opt, &opt_index)) != -1)
   {
      switch(c)
      {
         case -1:   /* no more arguments */
         case 0:    /* long options toggles */
         break;

         case 'h':
         corset_usage(cfw);
         cfw_destroy(&cfw);
         return(0);

         case 'V':
         cfw_version(cfw);
         cfw_destroy(&cfw);
         return(0);

         case 1:
         cfw_destroy(&cfw);
         return(1);

         case '?':
         fprintf(stderr, "Try `%s --help' for more information.\n", cfw->prog_name);
         cfw_destroy(&cfw);
         return(1);

         default:
         fprintf(stderr, "%s: unrecognized option `--%c'\n", cfw->prog_name, c);
         fprintf(stderr, "Try `%s --help' for more information.\n", cfw->prog_name);
         cfw_destroy(&cfw);
         return(1);
      };
   };

   if ((argc - optind) < 1)
   {
      fprintf(stderr, "%s: missing required argument\n", cfw->prog_name);
      fprintf(stderr, "Try `%s --help' for more information.\n", cfw->prog_name);
      cfw_destroy(&cfw);
      return(1);
   };
   argc = (argc - optind);
   argv = &argv[optind];
   optind   = 1;

   if (!(cmd = corset_cmd_lookup(argv[0], 0)))
   {
      fprintf(stderr, "%s: unknown or ambiguous widget -- \"%s\"\n", cfw->prog_name, argv[0]);
      fprintf(stderr, "Try `%s --help' for more information.\n", cfw->prog_name);
      return(1);
   };

   rc = cmd->func(cfw, argc, argv);

   cfw_destroy(&cfw);

   return(rc);
}

/* end of source */
