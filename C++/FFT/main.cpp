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
#include <fstream>
#include <complex>
using namespace std;

extern complex<double>* recursive_FFT(complex<double>* a, int n);

int main(int argc, char **argv)
{
	int n = 0;
	ifstream datfile("fft.dat");
	if (!datfile)
	{
		cerr << "error: could not open file!" << endl;
		return -1;
	}
	datfile >> n;
	complex<double> *Ak = new complex<double>(n);
	complex<double> *Xn = NULL;
	for (int i = 0; i < n; i++)
	{
		datfile >> Ak[i];
	}
	datfile.close();

	for (int i = 0; i < n; i++)
	{
		cout << Ak[i] << endl;
	}
	Xn = recursive_FFT(Ak, n);
	for (int i = 0; i < n; i++)
	{
		cout << Xn[i] << endl;
	}

	delete[] Ak;
	delete[] Xn;
	return 0;
}
