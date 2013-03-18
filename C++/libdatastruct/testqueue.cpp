// =====================================================================================
// 
//       Filename:  testqueue.cpp
// 
//    Description:  test the validness of queue
// 
//        Version:  1.0
//        Created:  08/31/2011 12:30:50 PM
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
#include	"quene.h"
using namespace std;

int main (int argc, char *argv[])
{
    int size = 10;
    string strs[] = {"gay", "seven", \
    "team", "better", "safe", "stream",\
    "MOD", "sphere", "letter", "sophisticated" };
    Queue<string> que(strs, size);

    for (int i = 0; i < size; i++)
    {
        cout << que.dequeue() << endl;
    }
    return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
