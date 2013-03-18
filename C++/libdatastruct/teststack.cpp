// =====================================================================================
// 
//       Filename:  teststack.cpp
// 
//    Description:  test the validness of stack
// 
//        Version:  1.0
//        Created:  08/30/2011 01:38:12 PM
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
#include	<vector>
#include	"stack.h"
using namespace std;

int main (int argc, char *argv[])
{
    const int size = 10;
    string strv[] = {"two", "one", "seven",\
            "nine", "ten", "eight", "five", "two",\
            "three", "four"};
//    vector<string> strv("one", "two", "three",
//            "four", "five", "six", "seven", "eight",
//            "nine", "ten");
    Stack<string> stk; 
    
    cout << "before pushing into stack" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << strv[i] << endl;
        stk.push(strv[i]);
    }
    cout << "after pushing into stack" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << stk.pop() << endl;
    }
    return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
