/*
 *  CPP_basic - TODO
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

#include "Stack.h"
#include <iostream>

using namespace std;

Stack::Stack(int size)
{
	stk = new float[size];
	max = size;
	sp = 0;
}

Stack::~Stack()
{
	delete [] stk;
}

bool Stack::is_stack_empty() const
{
	return 0 == sp;
}

int Stack::length() const
{
	return sp;
}
bool Stack::is_stack_full() const
{
	return sp == max;
}

float Stack::top() const
{
	if (sp > 0)
	{
		return stk[sp - 1];
	}
	else
	{
		return NULL;
	}
}

bool Stack::push(float a)
{
	if (sp < max)
	{
		stk[sp++] = a;
		return true;
	}

	return false;
}
float Stack::pop()
{
	if (sp > 0)
	{
		return stk[--sp];
	}

	return false;
}

void Stack::traverse()
{
	cout << "traverse result:" << endl;
	for (int i = 0; i < sp; i++)
	{
		cout << stk[i] << endl;
	}
}
