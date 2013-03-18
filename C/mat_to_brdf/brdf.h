/*
 *  Date:   Jun 15, 2009
 *  Author:	jasonleakey
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
 *  brdf.h:
 */

#ifndef BRDF_H_
#define BRDF_H_

/*
#include <stdarg.h>

#ifdef DEBUG
	void TRACE(char* fmt, ...);
#else
	#define TRACE(char* fmt, ...) ;
#endif
*/

#define ANGLE_INFO_CNT 203
#define WAVE_INFO_CNT 697
#define MAX_DIR_NAME_LEN 100
#define MAX_LINE_LEN 80
#define IRR_FILE_NAME_LEN 22
#define pi 3.141592


typedef struct _wave_irr{
	double lambda;
	double irr;
} wave_irr_t;

typedef struct {
	double alpha;
	double beta;
	double gamma;
	double Itheta;
	double Iphi;
	double Rtheta;
	double Rphi;
	wave_irr_t wave_irr[WAVE_INFO_CNT];
} angle_irr_t;


/*

void TRACE(char* fmt, ...)
{
	va_list body;
	va_start(body, fmt);
	vsprintf(stdin, fmt, body);
	va_end(body);
}
*/
#endif /* BRDF_H_ */
