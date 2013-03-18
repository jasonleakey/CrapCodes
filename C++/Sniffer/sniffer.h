/*
 *  Sniffer - Advanced Network project
 *
 *  Copyleft(R) by jasonleakey
 *  --------------------------------------------------------------------
 *  Sniffer is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Sniffer is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Sniffer; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 *  --------------------------------------------------------------------
 */

#ifndef SNIFFER_H_
#define SNIFFER_H_

/* used for debug */
#ifdef NDEBUG
	#define TRACE(s)
#else
	#include <assert.h>
	#define TRACE(s) {\
		printf("in file : %s, line : %u\n", __FILE__, __LINE__);\
		fprintf(stderr, "%s\n", (s));\
		fflush(stdout);\
	}
#endif

#include <iostream>
#include <stdlib.h>
#include <pcap.h>
#include <errno.h>
#ifndef WIN32
	#include <netdb.h>
//	#include <sys/types.h>
	#include <sys/stat.h>
	#include <unistd.h>
//	#include <signal.h>
//	#include <net/ethernet.h>
//	#include <net/ppp_defs.h>
	#include <arpa/inet.h>
	#include <sys/socket.h>
//	#include <netinet/tcp.h>
//	#include <netinet/udp.h>
//	#include <netinet/ip.h>
	#include <netinet/in.h>
#else
	#include <windows.h>
	#include <winsock.h>
	#include <ws2tcpip.h>
#endif

using namespace std;

#define MAX_WEBSITE_LEN 150 // the max length of website you want to filter

/* four parts of ip address */
typedef struct {
		u_char byte1;
		u_char byte2;
		u_char byte3;
		u_char byte4;
} IntByte;

#define MSS 1461 // additional 1 byte of '\0' makes it a string

// store http messages as you want
typedef struct _HttpLNode {
	unsigned int seq; // TCP sequence number
	unsigned int ack; // TCP acknowledge number
	short len; // the entire TCP length
	char data[MSS]; // store TCP data field, that is, HTTP content
} HttpLNode;

extern void cleanup(int sigNo);
extern int pcap_init(const char* filter,
					char* const errbuf,
					struct bpf_program* const fp,
					pcap_if_t* allDevs);
extern u_char* next_pcap(struct pcap_pkthdr *pkthdr);
extern bool analyze_packet(const unsigned char* ptr,
							const struct pcap_pkthdr* pkthdr,
							const char* website,
							HttpLNode response_pack_list[],
							HttpLNode request_pack_list[]);
extern bool revert_http(HttpLNode httpRespondPktList[],
		HttpLNode httpRequestPktList[],
		char* website);

#endif /* SNIFFER_H_ */
