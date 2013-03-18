/*
 *  C_sniffer - header structures of TCP, IP, UDP...
 *
 *  Copyleft(R) by jasonleakey
 *  <jasonleakey@gmail.com>
 *  <QQ:174481438>
 *  --------------------------------------------------------------------
 *  C_sniffer is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  C_sniffer is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with C_sniffer; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 *  --------------------------------------------------------------------
 */

#ifndef ANALYZE_PACKET_H_
#define ANALYZE_PACKET_H_

extern pcap_t* pcap; /* device descriptor */

#define MAXLINEWIDTH 60 // set the max length of a line in terminal
#define MAX_HOST_LEN 30 // the max length of server domain
#define CR 0x0d // Carriage Return
#define LF 0x0a // Line Feed

// IP header structure
struct my_iphdr
{
	u_int8_t ip_vhl; /* ip version and head length */
#if __BYTE_ORDER == __LITTLE_ENDIAN
#define IP_V(iphdr) (((iphdr)->ip_vhl & 0xf0)>>4) // macro to get version
#define IP_HL(iphdr) ((iphdr)->ip_vhl & 0x0f) // macro to get head length
#elif __BYTE_ORDER == __BIG_ENDIAN
#define IP_V(iphdr) ((iphdr)->ip_vhl & 0x0f)
#define IP_HL(iphdr) (((iphdr)->ip_vhl & 0xf0)>>4)
#else
#error "please fix <bits/endian.h>" /* stop compiling and output error info */
#endif
	u_int8_t tos;  // Type of service, should be zeros
	u_int16_t tot_len; // total length
	u_int16_t id; // identification
	u_int16_t frag_off; // flags and fragment offset
#if __BYTE_ORDER == __LITTLE_ENDIAN
#define IP_DF 0x4000 // get "don't fragment" field by frag_off & IP_DF
#define IP_MF 0x2000 // get "More fragment" field by frag_off & IP_MF
#define IP_OFFMASK 0x1fff // get "fragment offset" field by frag_off & IP_OFFMASK
#elif __BYTE_ORDER == __BIG_ENDIAN
#define IP_DF 0x0004
#define IP_MF 0x0002
#define IP_OFFMASK 0xfff1
#else
#error "please fix <bits/endian.h>" /* stop compiling and output error info */
#endif
	u_int8_t ttl; // time to live
	u_int8_t protocol; // protocol
	u_int16_t check; // header checksum
	u_int32_t saddr; // source IP address
	u_int32_t daddr; // destination IP address
	/* The options start here, and padding if necessary */
};

// TCP header structure
struct tcphdr
{
	u_int16_t source; // source port
	u_int16_t dest; // destination port
	u_int32_t seq; // sequence number
	u_int32_t ack_seq; // acknowledge number
#  if __BYTE_ORDER == __LITTLE_ENDIAN
	u_int16_t res1 :4; // reserved, should be zero
	u_int16_t doff :4; // data offset
	u_int16_t fin :1; // FIN, finish
	u_int16_t syn :1; // SYN, synchronous
	u_int16_t rst :1; // RST, reset
	u_int16_t psh :1; // PSH, push
	u_int16_t ack :1; // ACK
	u_int16_t urg :1; // URG, urgent
	u_int16_t res2 :2; // reserved, should be zero
#  elif __BYTE_ORDER == __BIG_ENDIAN
	u_int16_t doff:4;
	u_int16_t res1:4;
	u_int16_t res2:2;
	u_int16_t urg:1;
	u_int16_t ack:1;
	u_int16_t psh:1;
	u_int16_t rst:1;
	u_int16_t syn:1;
	u_int16_t fin:1;
#  else
#   error "Adjust your <bits/endian.h> defines"
#  endif
	u_int16_t window; // Window size
	u_int16_t check; // TCP checksum
	u_int16_t urg_ptr; // urgent pointer
};

// UDP header structure
struct udphdr
{
	u_int16_t source; // source port
	u_int16_t dest; // destination port
	u_int16_t len; // length in octet
	u_int16_t check; // UDP checksum
};

/* 10Mb/s ethernet header */
struct ether_header
{
	unsigned char ether_dhost[6]; /* destination eth addr	*/
	unsigned char ether_shost[6]; /* source ether addr	*/
	unsigned short ether_type; /* packet type ID field	*/
};

/* Ethernet protocol ID's */
#define	ETHERTYPE_PUP		0x0200          /* Xerox PUP */
#define ETHERTYPE_SPRITE	0x0500		/* Sprite */
#define	ETHERTYPE_IP		0x0800		/* IP */
#define	ETHERTYPE_ARP		0x0806		/* Address resolution */
#define	ETHERTYPE_REVARP	0x8035		/* Reverse ARP */
#define ETHERTYPE_AT		0x809B		/* AppleTalk protocol */
#define ETHERTYPE_AARP		0x80F3		/* AppleTalk ARP */
#define	ETHERTYPE_VLAN		0x8100		/* IEEE 802.1Q VLAN tagging */
#define ETHERTYPE_IPX		0x8137		/* IPX */
#define	ETHERTYPE_IPV6		0x86dd		/* IP protocol version 6 */
#define ETHERTYPE_LOOPBACK	0x9000		/* used to test interfaces */

#endif
