/*
 *  Sniffer - analyze a packet from data link layer up to application layer
 *  		  and if packet contains http data, store it.
 *  Copyright(R) by YangZhiying <yangzhiyin007@163.com>
 *  				DingLing <d000000000000000@163.com>
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

#include <string.h>
#include "sniffer.h"
#include "analyze_packet.h"

static const char* s_website = NULL; // website filter copy
static short s_src_port = 0;
static short s_dst_port = 0;
static char s_src_addr[20];
static char s_dst_addr[20];
static char s_website_IP_addr[20] = { 0 }; // the IP address of website filter

static HttpLNode *s_http_respond_packet_list = NULL;
static HttpLNode *s_http_request_packet_list = NULL;
static int s_http_respond_packet_cnt = 0; // the number of response packets received
static int s_http_request_packet_cnt = 0; // the number of request packets received

static bool s_bIsFinish = false; // flag for checking TCP link to website is over

/*
 * input:
 * 		const unsigned char* ptr: pointer to the beginning of TCP segment
 * 		short len_tcp: the length of TCP segment
 * 		int src_addr: source address
 * 		int dst_addr: destination address
 * output:
 * 		bool: return true if checksum is correct, false otherwise.
 * effect:
 * 		compute checksum of TCP segment, and check its correctness
 * **************** NOT TESTED **********************
 */
static bool tcp_check_sum(const unsigned char* ptr,
                          short len_tcp,
                          int src_addr,
                          int dst_addr)
{
	unsigned short padd = 0;
	int sum = 0;
	char* buf = NULL;


	// Find out if the length of data is even or odd number. If odd,
	// add a padding byte = 0 at the end of packet
	if (len_tcp & 0x1 == 0x1)
	{
		padd = 1;
	}

	// allocate a buffer storing all data needed to check.
	if (NULL == (buf = new char[12 + len_tcp + padd]))
	{
		fprintf(stderr,
		        "new:%s, Line %d in %s\n",
		        strerror(errno),
		        __LINE__,
		        __FILE__);
		return false;
	}
	memset(buf, '\0', 12 + len_tcp + padd);


	// pseudo-header
	memcpy(buf, &src_addr, 4);
	memcpy(buf + 4, &dst_addr, 4);
	buf[8] = 0x0; // should be zero
	buf[9] = 0x6; // protocol: TCP
	// the length of segment, need to be network octet sequence, two bytes
	buf[10] = len_tcp & 0xff;
	buf[11] = (len_tcp & 0xff00) >> 8;
	//copy all data of TCP segment
	memcpy(buf + 12, ptr, len_tcp);


	// an unsigned short pointer to buffer, pointing to the beginning initially
	unsigned short* bufHeader = (unsigned short*)buf;
	// length of buffer
	int len = 12 + len_tcp + padd;
	while (len > 1)
	{
		sum += *(bufHeader)++; // read two bytes
		if (sum & 0x80000000) /* if high order bit set, fold */
			sum = (sum & 0xFFFF) + (sum >> 16);
		len -= 2;
	}

	// keep only the last 16 bits of the 32 bit calculated sum and add the carries
	while (sum >> 16)
	{
		sum = (sum & 0xFFFF) + (sum >> 16);
	}

	delete[] buf;
	// get its complement and check if it equals to zeros
	return 0x0 == (unsigned short)~sum ? true : false;
}

/*
 * input:
 * 		const struct my_iphdr* header: pointer to IP header
 * 		int hdlen: IP header length
 * output:
 * 		bool: true if checksum is correct, false otherwise
 * effect:
 * 		compute checksum field of IP header, and check the correctness of data
 */

static bool ip_check_sum(const struct my_iphdr* header, int hdlen)
{
	assert(header != NULL);
	unsigned short* myHeader = (unsigned short*)header;
	long sum = 0; /* assume 32 bit long, 16 bit short */

	while (hdlen > 1)
	{
		sum += *(myHeader)++;
		if (sum & 0x80000000) /* if high order bit set, fold */
			sum = (sum & 0xFFFF) + (sum >> 16);
		hdlen -= 2;
	}

	if (hdlen) /* take care of left over byte */
	{
		sum += (unsigned short)*(unsigned char *)myHeader;
	}

	// keep only the last 16 bits of the 32 bit calculated sum and add the carries
	while (sum >> 16)
	{
		sum = (sum & 0xFFFF) + (sum >> 16);
	}


	// get its complement and check if it equals to zero
	return 0x0 == (unsigned short)~sum ? true : false;
}

static int analyze_application_layer(const unsigned char* ptr,
                                     const short remain_len,
                                     const unsigned int seqnum = 0,
                                     const unsigned int acknum = 0)
{
	assert(remain_len > 0);
	const unsigned char* pHttp = ptr;
	char chHost[MAX_HOST_LEN];
	// FTP message
	if (21 == s_src_port || 21 == s_dst_port)
	{
		printf("FTP:\n");
	}
	/* HTTP response packet */
	else if (80 == s_src_port && 0 != remain_len)
	{
		for (int i = 0; i < s_http_request_packet_cnt; i++)
		{
			// search request packet list and check if this response packet is
			// what we want, that is, the one has its Acknowledge sequence number
			// equivalent to the sum of seq and len of request packet list
			if (s_http_request_packet_list[i].seq
			        + s_http_request_packet_list[i].len == acknum)
			{
				// add this response packet to list
				HttpLNode hp;
				hp.ack = acknum;
				hp.seq = seqnum;
				hp.len = remain_len;
				memcpy(hp.data, ptr, remain_len);
				s_http_respond_packet_list[s_http_respond_packet_cnt++] = hp;
			}
		}
	}
	/* HTTP request packet, small remain_len should not be a request message */
	else if (80 == s_dst_port && remain_len > 10)
	{
		// if website filter is not specified or not a GET request message, then return
		if (0 == strlen(s_website) || *pHttp != 'G' || *(pHttp + 1) != 'E'
		        || *(pHttp + 2) != 'T')
		{
			return 1;
		}

		// extract host domain
		for (; (*pHttp) != 'H' || *(pHttp + 1) != 'o' || *(pHttp + 2) != 's'
		        || *(pHttp + 3) != 't'; pHttp++)
		{
			; // jump to 'host' field
		}
		pHttp += 6; // jump to domain field
		char* p = chHost; // copy domain
		while (*(pHttp) != CR)
		{
			*p++ = *pHttp++;
		}
		*p = '\0';
		printf("----------- Domain: %s-----------", chHost);


		// if this request message is to website, record the website IP address
		if (0 == strcmp(chHost, s_website))
		{
			strcpy(s_website_IP_addr, s_dst_addr);
		}

		// add this message to request packet list
		HttpLNode hp;
		hp.ack = acknum;
		hp.seq = seqnum;
		hp.len = remain_len;
		memcpy(hp.data, ptr, remain_len);
		s_http_request_packet_list[s_http_request_packet_cnt++] = hp;
	}
	// not analyze for more
	else
	{
		printf("unknown application layer protocol!\n");
		return -1;
	}
	return 0;
}

/*
 * input:
 * 		const unsigned char ip_protocol: the transport protocol specified in IP header
 * 		int src_addr: source address
 * 		int dst_addr: destination address
 * 		const unsigned char* ptr: pointer to transport layer Segment
 * 		const short remain_len: remaining length of Data
 * output:
 * 		int: 0 if successfully analyzed, -1 otherwise
 * effect:
 * 		analyze transport layer protocol and data
 */
static int analyze_transport_layer(const unsigned char ip_protocol,
                                   int src_addr,
                                   int dst_addr,
                                   const unsigned char* ptr,
                                   const short remain_len)
{
	assert(remain_len > 0);
	int hlen = 0;
	switch (ip_protocol)
	{
		case 0x06: // TCP segment
		{
			printf("TCP:\n");
			struct tcphdr *tcph = (struct tcphdr*)ptr; // TCP header pointer

			// output information of all fields
			printf("\tsrc port: %d\n\tdst port: %d\n",
			       ntohs(tcph->source),
			       ntohs(tcph->dest));
			printf("\tSeq: %u,  ACK seq: %u\n",
			       (unsigned int)ntohl(tcph->seq),
			       (unsigned int)ntohl(tcph->ack_seq));
			printf("\tdata offset: %d\n", tcph->doff);
			printf("\tURG=%d, ACK=%d, PSH=%d, RST=%d, SYN=%d, SYN=%d\n",
			       tcph->urg,
			       tcph->ack,
			       tcph->psh,
			       tcph->rst,
			       tcph->syn,
			       tcph->fin);
			printf("\tWindow:%-6d\n", ntohs(tcph->window));

			// check sum
			bool isTcpChkSumCorrect = false;
			isTcpChkSumCorrect = tcp_check_sum(ptr,
			                                   remain_len,
			                                   src_addr,
			                                   dst_addr);
			printf("\tChecksum: %#x (%s)\n",
			       ntohs(tcph->check),
			       isTcpChkSumCorrect ? "correct" : "incorrect");

			hlen = (tcph->doff) << 2;

			// record source and destination port
			s_src_port = ntohs(tcph->source);
			s_dst_port = ntohs(tcph->dest);


			// analyze the upper layer
			if (remain_len - hlen > 0)
			{
				analyze_application_layer(ptr + hlen,
				                          remain_len - hlen,
				                          ntohl(tcph->seq),
				                          ntohl(tcph->ack_seq));
			}

			// determine if TCP flow is finished
			if (strlen(s_website_IP_addr) != 0
					&& strcmp(s_src_addr, s_website_IP_addr) && tcph->fin == 0x1)
			{
				s_bIsFinish = true;
			}
			break;
		}
		case 0x11:
		{
			printf("UDP:\n");
			struct udphdr* udph = NULL;
			udph = (struct udphdr*)ptr;
			printf("\tsrc port: %d\n\tdst port: %d\n",
			       ntohs(udph->source),
			       ntohs(udph->dest));
			printf("\tlen: %d\n", ntohs(udph->len));
			printf("\tChecksum: %#x\n", ntohs(udph->check));

			// the same as TCP
			s_src_port = ntohs(udph->source);
			s_dst_port = ntohs(udph->dest);

			// UDP has a header length of 8
			if (remain_len - 8 > 0)
			{
				analyze_application_layer(ptr + 8, remain_len - 8);
			}
			break;
		}
		case 0x01:
			printf("ICMP:\n");
			break;
		case 0x02:
			printf("IGMP:\n");
			break;
		default:
			printf("unknown transport layer protocol!\n");
			return -1;
	}
	return 0;
}

/*
 * input:
 * 		const unsigned short ethernet_type: the ethernet_type specified in IP header
 * 		const unsigned char* ptr: pointer to the beginning of Network Layer
 * 		const short remain_len: remaining length of Data
 * output:
 * 		int: 0 if successfully analyzed, -1 otherwise
 * effect:
 * 		analyze network layer protocol and data
 */
static int analyze_network_layer(unsigned short ethernet_type,
                                 const unsigned char* ptr,
                                 const short remain_len)
{
	assert(remain_len > 0);
	switch (ethernet_type)
	{
		case ETHERTYPE_IP:
		{
			printf("IP: \n");
			// analyze IP header
			struct my_iphdr* iphdr = (struct my_iphdr*)ptr;
			unsigned int hlen = 0;

			if (IP_V(iphdr) != 4)
			{
				printf("Error IP version.\n");
				return -1;
			}
			hlen = IP_HL(iphdr) << 2; /* header length, 4bytes per unit */
			// incorrect IP header
//			if (hlen < sizeof(struct my_iphdr))
//			{
//				fprintf(stderr, "IP len %d is error.\n", IP_HL(iphdr));
//				return -1;
//			}
			// save src and dst IP address
			inet_ntop(AF_INET, (void*)&iphdr->saddr, s_src_addr, 20);
			inet_ntop(AF_INET, (void*)&iphdr->daddr, s_dst_addr, 20);

			printf("\tIP version: %d\n", IP_V(iphdr));
			printf("\theader length: %d bytes\n", hlen);
			printf("\ttotal len:%dbytes\n", ntohs(iphdr->tot_len));
			printf("\tidentification: %d\n", ntohs(iphdr->id));
			printf("\tfragment offset:%d\n", ntohs(iphdr->frag_off) & IP_OFFMASK);
			printf("\tMF = %d, DF = %d\n", (ntohs(iphdr->frag_off) & IP_MF)
			        >> 13, (ntohs(iphdr->frag_off) & IP_DF) >> 14);
			printf("\tTTL: %d\n", iphdr->ttl);
			printf("\tProtocol: %#x\n", iphdr->protocol);
			printf("\tsource IP address: %s\n", s_src_addr);
			printf("\tdst IP address: %s\n", s_dst_addr);

			// check correctness with checksum
			bool isChkSumCor = ip_check_sum(iphdr, hlen);
			printf("\tChecksum: %#x (%s)\n",
			       ntohs(iphdr->check),
			       isChkSumCor ? "Correct" : "incorrect");

			// if data is correct and not empty
			if (isChkSumCor && ntohs(iphdr->tot_len) > 0)
			{
				analyze_transport_layer(iphdr->protocol,
				                        iphdr->saddr,
				                        iphdr->daddr,
				                        ptr + hlen,
				                        // get rid of IP header length
				                        //and drop frame padding octets
				                        ntohs(iphdr->tot_len) - hlen);
			}
			break;
		}
		case ETHERTYPE_ARP:
			printf("ARP: \n");
			break;
		case ETHERTYPE_REVARP:
			printf("Reverse ARP: \n");
			break;
		case ETHERTYPE_IPX:
			printf("IPX: \n");
			break;
		case ETHERTYPE_IPV6:
			printf("IPv6: \n");
			break;
		case ETHERTYPE_LOOPBACK:
			printf("Loopback: \n");
			break;
		default:
			printf("unknown network layer protocol!\n");
			return -1;
	}

	return 0;
}

/*
 * input:
 * 		const unsigned short datalink_type: the datalink_type obtained from pcap_datalink()
 * 		const unsigned char* ptr: pointer to the beginning of DataLink Layer
 * 		const short remain_len: remaining length of Data
 * output:
 * 		int: 0 if successfully analyzed, -1 otherwise
 * effect:
 * 		analyze datalink layer protocol and data
 */
static int analyze_datalink_layer(const unsigned short datalink_type,
                                  const unsigned char* ptr,
                                  const short remain_len)
{

	int i = 0;
	assert(NULL != ptr);
	switch (datalink_type)
	{
		case DLT_NULL: /* BSD loopback encapsulation */
			printf("BSD loopback encapsulation!\n");
			break;
		case DLT_EN10MB: /* Ethernet 10/100/1000Mbps */
		{
			printf("Ethernet:\n");
			// Ethernet header
			struct ether_header* ethdr = (struct ether_header*)ptr;

			// output the MAC address information in header
			// source MAC address
			printf("\tsource MAC address: ");
			for (i = 0; i < 5; i++)
			{
				printf("%.2X.", ethdr->ether_shost[i]);
			}
			printf("%.2X\n", ethdr->ether_shost[i]);
			// destination MAC address
			printf("\tdestination MAC address: ");
			for (i = 0; i < 5; i++)
			{
				printf("%.2X.", ethdr->ether_dhost[i]);
			}
			printf("%.2X\n", ethdr->ether_dhost[i]);

			/* output Ethernet type */
			printf("\tEthernet type: %#.4x\n", ntohs(ethdr->ether_type));

			// Ethernet has a 14 octets header
			if (remain_len - 14 > 0)
			{
				analyze_network_layer(ntohs(ethdr->ether_type),
				                      ptr + 14,
				                      remain_len - 14);
			}
			break;
		}
		case DLT_SLIP:
		case DLT_PPP:
			printf("PPP Frame!\n");
			break;
		case DLT_PPP_ETHER:
			printf("PPPoE over Ethernet Frame!\n");
			break;
		case DLT_IEEE802_11:
			printf("WiFi 802.11 Frame!\n");
		default:
			printf("unknown data link layer protocol!\n");
			return -1;
	}
	return 0;
}

/*
 * input:
 * 		const unsigned char* ptr: pointer to packet
 * 		const struct pcap_pkthdr* pkthdr: pointer to structure of packet information
 * 		const char* website: website filter
 * 		HttpLNode* response_pack_list: all responding packet list
 * 		HttpLNode* request_pack_list: all request packet list
 * output:
 * 		if TCP FINish return true
 * 			else return false
 * effect:
 * 		analyze packet starting from here
 */
bool analyze_packet(const unsigned char* ptr,
                    const struct pcap_pkthdr* pkthdr,
                    const char* website,
                    HttpLNode *response_pack_list,
                    HttpLNode *request_pack_list)
{
	assert(NULL != ptr);
	int i = 0;
	int lineIdx = 0;
	char hexstr[MAXLINEWIDTH]; // Hex form of an octet
	char prtstr[MAXLINEWIDTH]; // printable characteristic form of an actet
	static u_int sPacketCnt = 1; // the number of snapped packets
	unsigned short wDataLinkType = 0; // datalink type

	memset(hexstr, 0x00, MAXLINEWIDTH);
	memset(prtstr, 0x00, MAXLINEWIDTH);


	// assign value for global variable website
	s_website = website;
	s_http_respond_packet_list = response_pack_list;
	s_http_request_packet_list = request_pack_list;

	// captured an incorrect packet
	if (pkthdr->caplen != pkthdr->len)
	{
		fprintf(stderr, "invalid capture length");
		return -1;
	}
	printf("*****************************************************************\n");
	printf("%8.8s:%ld",
	       ctime((time_t*)&pkthdr->ts.tv_sec) + 11,
	       pkthdr->ts.tv_usec); // output snapping time
	printf("Packet count: %d\n", sPacketCnt++);
	printf("caplen: %d\n", pkthdr->caplen);
	printf("len: %d\n", pkthdr->len);
	printf("Payload:\n");

	/* output the whole packet with hex and characteristic for user-friendly reading*/
	for (i = 0; i < pkthdr->len; i += 4)
	{
		if (i % 16 == 0 && 0 != i)
		{
			printf("%s\t%s\n", hexstr, prtstr);
			memset(hexstr, 0x00, MAXLINEWIDTH);
			memset(prtstr, 0x00, MAXLINEWIDTH);
		}
		uint32_t dword = ntohl(*((uint32_t*)(ptr + i)));
		IntByte* fourBytes = (IntByte*)&dword;
		sprintf(&hexstr[lineIdx * 3],
		        "%.2X %.2X %.2X %.2X ",
		        fourBytes->byte4,
		        fourBytes->byte3,
		        fourBytes->byte2,
		        fourBytes->byte1);
		sprintf(&prtstr[lineIdx],
		        "%c%c%c%c",
		        isprint(fourBytes->byte4) ? fourBytes->byte4 : '.',
		        isprint(fourBytes->byte3) ? fourBytes->byte3 : '.',
		        isprint(fourBytes->byte2) ? fourBytes->byte2 : '.',
		        isprint(fourBytes->byte1) ? fourBytes->byte1 : '.');
		lineIdx = (lineIdx + 4) % 16;
	}
	if (strlen(hexstr) != 0 && strlen(prtstr) != 0)
	{
		if (lineIdx != 0)
		{
			memset(&hexstr[lineIdx * 3], ' ', 48 - lineIdx * 3); /* pad the blank */
		}
		printf("%s\t%s\n", hexstr, prtstr);
	}

	// get datalink type
	wDataLinkType = pcap_datalink(pcap);
	analyze_datalink_layer(wDataLinkType, ptr, pkthdr->caplen);

	return s_bIsFinish;
}
