/*
 *  C_sniffer - TODO
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

#ifndef ADAPTER_ADMIN_H_
#define ADAPTER_ADMIN_H_

#define MAXBYTES2CAPTURE 2048 // the maximum number of bytes to capture
#define TO_DELAY_ms 512 // the read timeout in milliseconds

// if the interface is to put into promiscuous mode
typedef enum {
		NONPROMISC,
		PROMISC
} PROMISC_MODE;

#endif /* ADAPTER_ADMIN_H_ */
