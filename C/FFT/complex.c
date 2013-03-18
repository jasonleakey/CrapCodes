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

#include "complex.h"

/*////////////////////////////////////////////////////////////////////////////////////////////
 函数功能：执行两个复数的加法
 入口参数：指向两个加数的指针
 出口参数：指向结果的指针
 注意事项：保存结果的复数需在函数外申请,本函数不处理此项内容;任何一个加数均可同时用于保存结果
 ////////////////////////////////////////////////////////////////////////////////////////////*/
COMPLEX *ComAdd(const COMPLEX *add1,
                       const COMPLEX *add2,
                       COMPLEX *result)
{
	result->real = 0.0;
	result->img = 0.0;
	result->real = add1->real + add2->real;
	result->img = add1->img + add2->img;

	return result;
}

/*////////////////////////////////////////////////////////////////////////////////////////////
 函数功能：执行两个复数的减法
 入口参数：指向两个减数的指针
 出口参数：指向结果的指针
 注意事项：保存结果的复数需在函数外申请,本函数不处理此项内容;任何一个减数均可同时用于保存结果
 ////////////////////////////////////////////////////////////////////////////////////////////*/
COMPLEX *ComSub(const COMPLEX *sub1,
                       const COMPLEX *sub2,
                       COMPLEX *result)
{
	result->real = 0.0;
	result->img = 0.0;
	result->real = sub1->real - sub2->real;
	result->img = sub1->img - sub2->img;

	return result;
}

/*////////////////////////////////////////////////////////////////////////////////////////////
 函数功能：执行两个复数的乘法
 入口参数：指向两个乘数的指针
 出口参数：指向结果的指针
 注意事项：保存结果的复数需在函数外申请,本函数不处理此项内容;任何一个乘数均可同时用于保存结果
 ////////////////////////////////////////////////////////////////////////////////////////////*/
COMPLEX *ComMul(const COMPLEX *mul1,
                       const COMPLEX *mul2,
                       COMPLEX *result)
{
	result->real = 0.0;
	result->img = 0.0;
	float m1r = mul1->real;
	float m1i = mul1->img;
	float m2r = mul2->real;
	float m2i = mul2->img;
	result->real = m1r * m2r - m1i * m2i;
	result->img = m1r * m2i + m2r * m1i;

	return result;
}

/*////////////////////////////////////////////////////////////////////////////////////////////
 函数功能：执行两个复数的除法
 入口参数：指向被除数和除数的指针
 出口参数：指向结果的指针
 注意事项：保存结果的复数需在函数外申请,本函数不处理此项内容;被除数和除数均可同时用于保存结果
 未处理除数为零的情况
 ////////////////////////////////////////////////////////////////////////////////////////////*/
COMPLEX *ComDiv(const COMPLEX *div1,
                       const COMPLEX *div2,
                       COMPLEX *result)
{
	result->real = 0.0;
	result->img = 0.0;
	float d1r = div1->real;
	float d1i = div1->img;
	float d2r = div2->real;
	float d2i = div2->img;
	result->real = (d1r * d2r + d1i * d2i) / (d2r * d2r + d2i * d2i);
	result->img = (d2r * d1i - d1r * d2i) / (d2r * d2r + d2i * d2i);

	return result;
}

COMPLEX *ComConj(const COMPLEX *target, COMPLEX *result)
{
	result->real = 0.0;
	result->img = 0.0;
	float tarrel = target->real, tarimg = target->img;
	result->real = tarrel;
	result->img = -tarimg;

	return result;
}

/*////////////////////////////////////////////////////////////////////////////////////////////
 函数功能：显示复数，用于调试
 入口参数：指向欲显示的复数的指针
 出口参数：
 注意事项：
 ////////////////////////////////////////////////////////////////////////////////////////////*/
void ComDisplay(const COMPLEX *target)
{
	printf("real = %f\t ,img = %f\n", target->real, target->img);
}

COMPLEX* ComCpy(COMPLEX* dst, const COMPLEX* src)
{
	dst->real = 0.0;
	dst->img = 0.0;
	dst->real = src->real;
	dst->img = src->img;

	return dst;
}
