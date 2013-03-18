//
//
//  NAME: remove the m-th node and print until all the nodes are
//  printed
//  DATE: Sun 03 Jul 2011 04:09:21 PM CST
//
//  Copyleft(R) by jasonleakey
//  <jasonleakey@gmail.com>
//
//  GPLv2 licence
//  --------------------------------------------------------------------
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//  MA 02110-1301, USA.
//  --------------------------------------------------------------------
//

#include <iostream>
#include <string>
#include "linklist.h"

#include	"circlelist.h"
using namespace std;

template < class T >
void printdata(const T& val)
{
    cout << val << endl;
}


template <class T>
void printjosephus (const T& val)
{
    cout << "Deleted: " << val << endl;
}		// -----  end of template function printjosephus  -----

int main(int argc, char** argv)
{
    int SIZE = 12;
    const string strs[] = {"one",  "two", "three", "four", "five", "six",
        "seven", "eight", "nine", "ten", "eleven", "twelve"};
    List<string> circle(strs, SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        cout << *(circle.remove(1)) << endl;
    }
    circle.clear();

//    CircleList<string> circ(strs, SIZE);
//    CircleList<string> copycirc;
//    copycirc = circ;
//    circ.traverse(&printdata<string>);
//    circ.josephus(9, 5, &printdata<string>);
//    circ.clear();
//    cout << "copyed list:" << endl;
//    copycirc.traverse(&printdata<string>);
//    copycirc.clear();
    return 0;
}


