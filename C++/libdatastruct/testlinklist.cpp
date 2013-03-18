// =====================================================================================
// 
//       Filename:  testlinklist.cpp
// 
//    Description:  test the validness of linked list
// 
//        Version:  1.0
//        Created:  08/29/2011 02:24:51 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  jasonleakey (uKi), jasonleakey@gmail.com
//        Company:  HIT
//        licence:  GPLv2
// 
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
// =====================================================================================


#include	<iostream>
#include	<cstdlib>
#include	"linklist.h"
using namespace std;

int main (int argc, char *argv[])
{
    int SIZE = 12;
    const string strs[] = {"one",  "two", "three", "four", "five", "six",
        "seven", "eight", "nine", "ten", "eleven", "twelve"};
    List<string> strlist(strs, SIZE);
    cout << "BEFORE reverse:" << endl;
    strlist.traverse();
    strlist.reverse();
    cout << "AFTER reverse:" << endl;
    strlist.traverse();
    return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
