/*
 *  Sniffer - Control adapter, i.e open, capture, close, etc.
 *
 *  Copyright(R) by LiuTianyang <ltryee@gmail.com>
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


#include "sniffer.h"
#include "adapter_admin.h"

extern pcap_t* pcap; /* device descriptor */

/*
 * convert a decimal IP address to a user-friendly reading string
 */
#if 0
char *ip2str(u_int decimalIp)
{
	IntByte* newIP = (IntByte*)&decimalIp;
	printf("IP address: %d.%d.%d.%d\n", newIP->byte1,\
	       m(const unsigned char* ptr,
	     	IntByte* newIP = (IntByte*)&decimalIp;
	     	printf("IP address: %d.%d.%d.%d\n", newIP->byte1,\
	     	       m(const unsigned char* ptr,
	                                 short len_tcp,
	                                 int src_addr,
	                                 int dst_addr)  newIP->byte2,\
													  newIP->byte3,\
													  newIP->byte4);
	return NULL;
}
#else

#define IP2STRBUFFERS 12
/*
 * input:
 * 		u_int in: the IP address stored in an unsigned integer
 * output:
 * 		return a user-friendly reading IP string like "202.19.223.85"
 * effect:
 * 		transform a IPv4 address from integer to string
 */
static char* ip2str(u_int in)
{
	static char output[IP2STRBUFFERS][3*4+3+1];
	static short which;
	u_char* p;
	p = (u_char*)&in;
	which = (which + 1 == IP2STRBUFFERS ? 0 : which + 1);
	sprintf(output[which], "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
	return output[which];
}
#endif

/*
 * input:
 * 		struct sockaddr *sock_addr: socket address structure
 * 		char* address: IPv6 address string you want to obtain
 * 		int addrlen: address len of IPv6 string
 * output:
 * 		return a user-friendly reading IP string like "202.19.223.85"
 * effect:
 * 		transform a IPv6 address from socket address structure to a string
 */
static char* ip62str(struct sockaddr *sock_addr, char *address, int addrlen)
{
    socklen_t sockaddrlen;

    #ifdef WIN32
    sockaddrlen = sizeof(struct sockaddr_in6);
    #else
    sockaddrlen = sizeof(struct sockaddr_storage);
    #endif

    if(getnameinfo(sock_addr,
					sockaddrlen,
					address,
					addrlen,
					NULL,
					0,
					NI_NUMERICHOST) != 0)
    {
    	address = NULL;
    }

    return address;
}

/*
 * input:
 * 		const char* filter: filter expression of string type
 * 		char* const errbuf: if pcap opening device fails,
 * 							store error information to errbuf
 * 		struct bpf_program* const fp: a structure used for setting filter
 * output:
 *		int: return 0 if successfully opened the device, otherwise return -1
 * effect:
 *		list all network cards and manual select one from stdin. then set filter
 *		expression to the program.
 */

int pcap_init(const char* filter,
					char* const errbuf,
					struct bpf_program* const fp,
					pcap_if_t* allDevs)
{
	int i = 0;
	int devCnt = 0; // the number of devices
	int selNo = 0; // selection
	char ip6str[128];
	pcap_if_t* curDev = NULL; // current device selected
	bpf_u_int32 net; /* network address pointer*/
	bpf_u_int32 mask; /*network mask pointer */
	pcap_addr_t* curAddr = NULL; // pcap address type

	// read all devices to allDevs of pcap_if_t structure
	if (-1 == pcap_findalldevs(&allDevs, errbuf))
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}
	// output information of all devices
	for (curDev = allDevs; NULL != curDev; curDev = curDev->next)
	{
		printf("%d. %s---", ++devCnt, curDev->name);
		printf("(%s)\n", NULL != curDev->description ?\
				curDev->description : "no description available!");
		for (curAddr = curDev->addresses; NULL != curAddr; curAddr = curAddr->next)
		{
			printf("\tAddress Family: #%d\n", curAddr->addr->sa_family);
			switch (curAddr->addr->sa_family)
			{
				case AF_INET:
					printf("\tAddress Family Name: AF_INET\n");
					if (NULL != curAddr->addr)
					{
						printf("\tAddress: %s\n",\
								ip2str(((struct sockaddr_in*)curAddr->addr)->sin_addr.s_addr));
					}
					if (NULL != curAddr->netmask)
					{
						printf("\tNetmask: %s\n",\
								ip2str(((struct sockaddr_in*)curAddr->netmask)->sin_addr.s_addr));
					}
					if (NULL != curAddr->broadaddr)
					{
						printf("\tBroadcast Address: %s\n",\
								ip2str(((struct sockaddr_in*)curAddr->broadaddr)->sin_addr.s_addr));
					}
					if (NULL != curAddr->dstaddr)
					{
						printf("\tDestination Address: %s\n",\
								ip2str(((struct sockaddr_in*)curAddr->dstaddr)->sin_addr.s_addr));
					}
					break;
				case AF_INET6:
					printf("\tAddress Family Name: AF_INET6\n");
					if (NULL != curAddr->addr)
					{
						printf("\tAddress: %s\n", ip62str(curAddr->addr, ip6str, sizeof(ip6str)));
					}
					break;
				default:
					printf("\tunknown Address Family!\n");
					break;
			}
		}
	}
	// no network interface found in this system
	if (0 == devCnt)
	{
		printf("No network card found, or make sure WinPcap is installed\n");
		return -1;
	}

	// manually select the network interface
	printf("Enter the interface number[1 - %d]: ", devCnt);
	scanf("%d", &selNo);
	while (selNo < 1 || selNo > devCnt) // invalid number input
	{
		printf("invalid number. Retry: ");
		while (getchar() != '\n')
		{
			;
		}
		scanf("%d", &selNo);
	}
	// look up device with the number input
	for (curDev = allDevs, i = 0; i < selNo - 1; curDev = curDev->next, i++)
	{
		;
	}
	printf("Listening on device %s...\n", curDev->name);

	/* open a live capture from the network, set it promiscuous mode */
	pcap = pcap_open_live(curDev->name, MAXBYTES2CAPTURE, PROMISC, TO_DELAY_ms, errbuf);

	// get network and netmask of the given device name
	if (-1 == pcap_lookupnet(curDev->name, &net, &mask, errbuf))
	{
		fprintf(stderr, "cannot get the network address and mask!\n");
		return -1;
	}

	/* compile filter string to BPF program */
	if (NULL != filter)
	{
		TRACE(filter);
		// compile
		if (-1 == pcap_compile(pcap, fp, filter, 0, mask))
		{
			pcap_freealldevs(allDevs);
			TRACE("cannot compile filter to program!\n");
			exit(1);
		}
		// set filter
		if (-1 == pcap_setfilter(pcap, fp))
		{
			pcap_freealldevs(allDevs);
			TRACE("cannot set filter");
			exit(1);
		}
	}

	/* no need for any more the device list, free it */
	pcap_freealldevs(allDevs);
	return 0;
}

/*
 * fill the pcap_pkthdr structure of next packet and Return a pointer to this packet
 */
u_char* next_pcap(struct pcap_pkthdr *pkthdr)
{
	u_char *ptr = NULL;
#if 0
	while ((st = pcap_next_ex(pcap, &pkthdr, &ptr)) <= 0)
	{
		if (st < 0)
		{
			fprintf(stderr, "Error reading packets:%s\n", pcap_geterr(pcap));
			return NULL;
		}
	}
#else
	while (NULL == (ptr = (u_char*)pcap_next(pcap, pkthdr)))
	{
		;
	}
#endif
	return ptr;
}

