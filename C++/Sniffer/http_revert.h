/*
 *  Sniffer -
 *
 *  Copyright(R) by HuangYetian <jasonleakey@gmail.com>
 *  				HouRuijie	<hourjworld@yahoo.com.cn>
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

#ifndef HTTP_REVERT_H_
#define HTTP_REVERT_H_

typedef enum
{
	CMP_ACK, CMP_SEQ
} CMP_KEY;

#define MAX_RELATIVE_URL_LEN 100
#define MAX_UNCOMPRESSED_DATA_LEN 2000000
#define MAX_SAME_ACK_PACK_CNT 30
#define MAX_SRC_URL_LEN 200

#endif /* HTTP_REVERT_H_ */
