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

#include <iostream>
#include <cstdlib>
#include "Complex.h"
#include "Stack.h"

using namespace std;

int main(int argc, char **argv)
{
//	test complex number
//	Complex c(0.8, 2.5);
//	Complex d(2.2, 0.4);
//	Complex e;
//	cout << (c / d) << endl;
//	cout << (d + e) << endl;

//	test stack
	srand(time(NULL));
	Stack S(30);
	Stack& T = S;
	for (int i = 0; i < 15; i++)
	{
		S.push((float)rand() / RAND_MAX * 10);
	}
	S.pop();
	S.traverse();S.pop();
	T.push(9.9);
	S.traverse();
	cout << "stack top:" << S.top() << endl;
	cout << "is empty:" << (S.is_stack_empty() ? "True" : "False") << endl;
	cout << "is full:" << (S.is_stack_full() ? "True" : "False") << endl;
	return 0;
}

