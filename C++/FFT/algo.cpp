/*
 *  CPP_FFT - TODO
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

#include <iostream>
#include <complex>
#include <math.h>
using namespace std;

static const double PI = 3.1415;

complex<double>* recursive_FFT(complex<double>* a, int n)
{
	cout << "n=" << n << endl;
	if (1 == n)
	{
		return a;
	}

	complex<double> *Wn = new complex<double>(n);
	for (int i = 0; i < n; i++)
	{
		Wn[i] = exp(2 * PI * i / n);
	}
	complex<double> W(1.0, 0);

	complex<double> *a0 = new complex<double>(n / 2);
	complex<double> *a1 = new complex<double>(n / 2);
	for (int i = 0; i < n; i += 2)
	{
		a0[i] = a[i];
		cout << "a[" << i << "]=" << a[i] << endl;
		cout << "a[" << (i + 1) << "]=" << a[i + 1] << endl;
		a1[i] = a[i + 1];
	}
	delete[] a0;
	delete[] a1;

	complex<double> *y0 = new complex<double>(n / 2);
	y0 = recursive_FFT(a0, n / 2);
	complex<double> *y1 = new complex<double>(n / 2);
	y1 = recursive_FFT(a1, n / 2);

	complex<double> *y = new complex<double>(n / 2);
	for (int k = 0; k < n / 2; k++)
	{
		y[k] = y0[k] + W * y1[k];
		y[k + n / 2] = y0[k] - W * y1[k];
		W = W * Wn[n];
	}
	delete[] y0;
	delete[] y1;
	delete[] Wn;
	return y;
}
