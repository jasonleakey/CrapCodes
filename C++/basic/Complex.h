/*
 *  CPP_complex - TODO
 *  Change Log:
 *  Copyleft(R) by jasonleakey
 *  <jasonleakey@gmail.com>
 *  <QQ:174481438>
 *  --------------------------------------------------------------------
 *  CPP_complex is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  CPP_complex is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with CPP_complex; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 *  --------------------------------------------------------------------
 */

#ifndef COMPLEX_H_
#define COMPLEX_H_

#include <iostream>
using namespace std;

class Complex
{
// real part of a complex number
		float real;
		float img;
public:
// Constructor and destructor
//		initializer list
		Complex(float a = 0.0, float b = 0.0) : real(a), img(b)
		{
			;
		}
		virtual ~Complex();

// Attribute
		inline float get_real() const;
		float get_image() const ;
// Method
		Complex operator +(const Complex& a);
		Complex operator -(const Complex& a);
		Complex operator *(const Complex& a);
		Complex operator /(const Complex& a);
		Complex operator =(const Complex& a);
		friend ostream& operator <<(ostream& os, const Complex& a);
		int operator ==(const Complex& a);
};

inline float Complex::get_real() const
{
	return real;
}

inline float Complex::get_image() const
{
	return img;
}

#endif /* COMPLEX_H_ */
