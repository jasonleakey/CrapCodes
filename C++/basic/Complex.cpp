/*
 *  CPP_complex - TODO
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

#include "Complex.h"
#include <iostream>
using namespace std;

//Complex::Complex(float a, float b)
//{
//	real = a;
//	img = b;
//}

Complex::~Complex()
{
	// TftODO Auto-generated destructor stub
}

Complex Complex::operator +(const Complex& a)
{
	Complex b;
	b.real = real + a.real;
	b.img = img + a.img;
	return b;
}

Complex Complex::operator -(const Complex& a)
{
	Complex b;
	b.real = real - a.real;
	b.img = img - a.img;
	return b;
}

Complex Complex::operator *(const Complex& a)
{
	Complex b;
	b.real = real * a.real - img * a.img;
	b.img = real * a.img + img * a.real;
	return b;
}

Complex Complex::operator /(const Complex& a)
{
	Complex b;
	float denom = a.real * a.real + a.img * a.img;
	b.real = (real * a.real + img * a.real) / denom;
	b.img = (img * a.real - real * a.img) / denom;
	return b;
}

Complex Complex::operator =(const Complex& a)
{
	Complex b(a.real, a.img);
	return b;
}

// friend function definition
ostream& operator <<(ostream& os, const Complex& a)
{
	cout << a.real << '+' << a.img << 'i';
	return os;
}

int Complex::operator ==(const Complex& a)
{
	return real == a.real && img == a.img;
}
