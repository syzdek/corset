/*
 *  Corset Firewall
 *  Copyright (C) 2020 David M. Syzdek <david@syzdek.net>.
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
 *  @file src/examples/example-nfqueue.c example NFQueue program
 */
/*
 *  Simple Build:
 *     CFLAGS='-DPROGRAM_NAME="example-nfqueue" -Wall -Werror'
 *     LDFLAGS='-lnetfilter_queue'
 *     gcc ${CFLAGS}  -c -o example-nfqueue.o example-nfqueue.c
 *     gcc ${LDFLAGS}    -o example-nfqueue   example-nfqueue.o
 *
 *  Simple Clean:
 *     rm -f example-nfqueue.lo example-nfqueue
 *
 *  Libtool Build:
 *     CFLAGS='-DPROGRAM_NAME="example-nfqueue" -Wall -Werror'
 *     LDFLAGS='-lnetfilter_queue'
 *     libtool --mode=compile --tag=CC gcc ${CFLAGS}  -c example-nfqueue.c
 *     libtool --mode=link    --tag=CC gcc ${LDFLAGS} -o example-nfqueue \
 *             example-nfqueue.lo
 *
 *  Libtool Clean:
 *     libtool --mode=clean rm -f example-nfqueue.lo example-nfqueue
 */
#define _CORSET_EXAMPLES_EXAMPLE_NFQUEUE_C 1


///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef __CORSET_PMARK
#pragma mark - Headers
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
#include <arpa/inet.h>
#include <linux/netfilter.h>
#include <libnetfilter_queue/libnetfilter_queue.h>
#include <linux/ip.h>
#include <linux/ipv6.h>


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

void my_signal(int sig);
int  my_callback(struct nfq_q_handle * qh, struct nfgenmsg * nfmsg, struct nfq_data * nfad, void * data);
int  main(int argc, char * argv[]);


/////////////////
//             //
//  Variables  //
//             //
/////////////////
#ifdef __CORSET_PMARK
#pragma mark - Variables
#endif

int          should_exit     = 0;
uint32_t     verdict_current = NF_ACCEPT;
const char * verdict_string  = "ACCEPT";
char       * prog_name       = NULL;


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#ifdef __CORSET_PMARK
#pragma mark - Functions
#endif

void my_signal(int sig)
{
   signal(sig, my_signal);
   switch(sig)
   {
      case SIGUSR1:
      verdict_string  = (verdict_current == NF_ACCEPT) ? "DROP"  : "ACCEPT";
      verdict_current = (verdict_current == NF_ACCEPT) ? NF_DROP : NF_ACCEPT;
      printf("%s changing policy to \"%s\"\n", prog_name, verdict_string);
      break;

      case SIGINT:
      case SIGQUIT:
      case SIGTERM:
      case SIGHUP:
      printf("%s exiting\n", prog_name);
      should_exit = 1;
      break;

      default:
      break;
   };
   return;
}


int my_callback(struct nfq_q_handle * qh, struct nfgenmsg * nfmsg, struct nfq_data * nfad, void * data)
{
   int                             id;
   struct nfqnl_msg_packet_hdr   * ph;
   int                             payload_len;
   unsigned char                 * payload;
   struct iphdr                  * ip4;
   struct ipv6hdr                * ip6;
   char                            addr_src[INET6_ADDRSTRLEN];
   char                            addr_dst[INET6_ADDRSTRLEN];

   assert(data != NULL);

   if ((ph = nfq_get_msg_packet_hdr(nfad)) == NULL)
      return(0);
   id = ntohl(ph->packet_id);


   // obtain packet information
   if ((payload_len = nfq_get_payload(nfad, &payload)) == -1)
   {
      return(nfq_set_verdict(qh, id, NF_ACCEPT, 0, NULL));
   };
   ip4 = ((struct iphdr *)   payload);
   ip6 = ((struct ipv6hdr *) payload);
   switch(ip4->version)
   {
      case 4:
      inet_ntop(AF_INET, &ip4->saddr, addr_src, sizeof(addr_src));
      inet_ntop(AF_INET, &ip4->daddr, addr_dst, sizeof(addr_dst));
      break;

      case 6:
      inet_ntop(AF_INET6, &ip6->saddr, addr_src, sizeof(addr_src));
      inet_ntop(AF_INET6, &ip6->daddr, addr_dst, sizeof(addr_dst));
      break;

      default:
      break;
   };


   // print packet information
   switch((ip4->version == 4) ? ip4->protocol : ip6->nexthdr)
   {
      case 1:  printf("%s (%i) %s ICMP src=%s dst=%s\n",      prog_name, id, verdict_string, addr_src, addr_dst); break;
      case 6:  printf("%s (%i) %s TCP src=%s dst=%s\n",       prog_name, id, verdict_string, addr_src, addr_dst); break;
      case 17: printf("%s (%i) %s UDP src=%s dst=%s\n",       prog_name, id, verdict_string, addr_src, addr_dst); break;
      case 58: printf("%s (%i) %s IPv6-ICMP src=%s dst=%s\n", prog_name, id, verdict_string, addr_src, addr_dst); break;
      default: printf("%s (%i) %s UNKNOWN src=%s dst=%s\n",   prog_name, id, verdict_string, addr_src, addr_dst); break;
   };
   fflush(stdout);


   return(nfq_set_verdict(qh, id, verdict_current, 0, NULL));
}


int main(int argc, char * argv[])
{
   int                     queue_num;
   int                     rc;
   int                     fd;
   struct nfq_handle     * nh;
   struct nfq_q_handle   * qh;
   char                    msg[0xffff];
   ssize_t                 msglen;


   // determine program name for error messages
   if ((prog_name = rindex(argv[0], '/')) == NULL)
   {
      prog_name = argv[0];
   } else {
      prog_name = &prog_name[1];
   };


   // process user supplied parameters
   if (argc != 2)
   {
      fprintf(stderr, "Usage: %s <queue number>\n", prog_name);
      return(1);
   };
   queue_num = strtol(argv[1], NULL, 0);
   if ( (queue_num < 1) || (queue_num > 65536) )
   {
      fprintf(stderr, "%s: queue number must be between 1 and 65536\n", prog_name);
      return(1);
   };


   // checks user
   if (getuid() != 0)
   {
      fprintf(stderr, "%s: must run as root\n", prog_name);
      return(1);
   };


   // print helpful information to end user
   printf("Switch behavior with:\n");
   printf("    kill -USR1 %i\n", getpid());
   printf("\n");
   printf("firewall setup examples:\n");
   printf("    ip6tables -A INPUT -p tcp  --dport %-5i -j NFQUEUE --queue-num %i\n", queue_num, queue_num);
   printf("    iptables  -A INPUT -p tcp  --dport %-5i -j NFQUEUE --queue-num %i\n", queue_num, queue_num);
   printf("    ip6tables -A INPUT -p ipv6-icmp          -j NFQUEUE --queue-num %i\n", queue_num);
   printf("    iptables  -A INPUT -p icmp               -j NFQUEUE --queue-num %i\n", queue_num);
   printf("\n");


   // catches signals
   signal(SIGINT,    my_signal);
   signal(SIGQUIT,   my_signal);
   signal(SIGTERM,   my_signal);
   signal(SIGHUP,    my_signal);
   signal(SIGVTALRM, SIG_IGN);
   signal(SIGPIPE,   SIG_IGN);
   signal(SIGALRM,   SIG_IGN);
   signal(SIGUSR1,   my_signal);
   signal(SIGUSR2,   SIG_IGN);


   // initialize queue handle
   if ((nh = nfq_open()) == NULL)
   {
      perror("nfq_open()");
      return(1);
   };


   // initializes queue
   if ((qh = nfq_create_queue(nh, ((uint16_t)queue_num), my_callback, prog_name)) == NULL)
   {
      perror("nfq_create_queue()");
      nfq_close(nh);
      return(1);
   };
   if ((rc = nfq_set_mode(qh, NFQNL_COPY_PACKET, 0xffff)) == -1)
   {
      perror("nfq_set_mode()");
      nfq_destroy_queue(qh);
      nfq_close(nh);
      return(1);
   };


   if ((fd = nfq_fd(nh)) == -1)
   {
      perror("nfq_fd()");
      nfq_destroy_queue(qh);
      nfq_close(nh);
      return(1);
   };


   // mark start time
   should_exit = 0;
   while(!(should_exit))
   {
      if ((msglen = recv(fd, msg, sizeof(msg), MSG_DONTWAIT)) == -1)
         continue;
      nfq_handle_packet(nh, msg, msglen); // send packet to callback
      usleep(1);
   };


   // frees resources
   nfq_destroy_queue(qh);
   nfq_close(nh);

   return(0);
}


