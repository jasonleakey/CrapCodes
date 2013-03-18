/*
 *  C_sniffer - a simple program to capture and analyze packages
 *  Change Log:
 *  Copyleft(R) by jasonleakey
 *  <jasonleakey@gmail.com>
 *  <QQ:174481438>
 *  --------------------------------------------------------------------
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 *  --------------------------------------------------------------------
 */

#include <pcap.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "sniffer.h"


#define MAX_FILES 100 // the max number of files in a website
#define MAX_RESPOND_PACK_NUM 1000 // max number of http packets received from server
#define MAX_REQ_PACK_NUM 500 // max number of "GET" request message

pcap_t* pcap = NULL; /* device descriptor */

int main(int argc, char **argv)
{
	u_char* ptr = NULL;
	struct pcap_pkthdr pkthdr;
	struct bpf_program fp;
	pcap_if_t* allDevs = NULL; /* all devices list */
	char errbuf[PCAP_ERRBUF_SIZE];
	char* chWebSite = NULL;
	// list storing all response messages from website
	HttpLNode *httpRespondPktList = new HttpLNode[MAX_RESPOND_PACK_NUM];
	// list storing all request messages to website
	HttpLNode *httpRequestPktList = new HttpLNode[MAX_REQ_PACK_NUM];

	/*
	 * initialize error buffer to 0
	 */
	memset(errbuf, 0, PCAP_ERRBUF_SIZE);
	memset(httpRespondPktList, '\0', sizeof(HttpLNode) * MAX_RESPOND_PACK_NUM);
	memset(httpRequestPktList, '\0', sizeof(HttpLNode) * MAX_REQ_PACK_NUM);

	// check the number of arguments
	if (argc > 3)
	{
		printf("Usage: sniffer [FILTER_EXPRESSION]\n"
				"   or: sniffer FILTER_EXPRESSION WEBSITE\n");
		return 0;
	}

	// initialize devices
	chWebSite = argc == 3 ? argv[2] : NULL;
	pcap_init(argc == 1 ? NULL : argv[1], errbuf, &fp, allDevs);

	// analyze each packet captured, if get a TCP FINish from website server
	// stop capturing and reassemble http messages
	while (NULL != (ptr = next_pcap(&pkthdr)))
	{
		if (true == analyze_packet(ptr, &pkthdr,
				chWebSite, httpRespondPktList, httpRequestPktList))
		{
			cout << "found FIN." << endl;
			break;
		}
	}

	// if website filter is provided
	if (3 == argc)
	{
		revert_http(httpRespondPktList,
				httpRequestPktList,
				argv[2]);
	}
	delete[] httpRequestPktList;
	delete[] httpRespondPktList;
	return 0;
}
