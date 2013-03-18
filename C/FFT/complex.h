/*
 *  C_FFT - TODO
 *
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

#ifndef COMPLEX_H_
#define COMPLEX_H_

typedef struct
{
	float real;
	float img;
} COMPLEX;

extern COMPLEX* ComAdd(const COMPLEX *add1,
                       const COMPLEX *add2,
                       COMPLEX *result);
extern COMPLEX* ComSub(const COMPLEX *sub1,
                       const COMPLEX *sub2,
                       COMPLEX *result);
extern COMPLEX* ComMul(const COMPLEX *mul1,
                       const COMPLEX *mul2,
                       COMPLEX *result);
extern COMPLEX* ComDiv(const COMPLEX *div1,
                       const COMPLEX * div2,
                       COMPLEX *result);
extern COMPLEX* ComCon(const COMPLEX *target, COMPLEX *result);
extern COMPLEX* ComCpy(COMPLEX* dst, const COMPLEX* src);
extern void ComDisplay(const COMPLEX *target);

#endif /* COMPLEX_H_ */
