// =====================================================================================
// 
//       Filename:  testbintree.cpp
// 
//    Description:  test the validness of binary tree
// 
//        Version:  1.0
//        Created:  09/06/2011 11:42:03 AM
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


#include	"bintree.h"
#include	<iostream>
#include    <sstream>
#include	<cstdlib>
using namespace std;

int main (int argc, char *argv[])
{
    string treestr("one two three # # # four five six # seven # # # eight nine # # #\n"); 
    istringstream sin(treestr);
    BinTree<string> tree;
    sin >> tree;
    cout << tree << endl;
    cout << "先序输出:" << endl;
    cout << "0. "; 
    tree.preorder_traverse();
    cout << "1. "; 
    tree.preorder_traverse_nore();
    cout << "2. ";
    tree.preorder_traverse_nore2();
    cout << "3. ";
    tree.preorder_traverse_nore3();
    cout << "中序输出:" << endl;
    cout << "1. ";
    tree.inorder_traverse_nore();
    cout << "2. ";
    tree.inorder_traverse_nore2();
    cout << "后序输出:" << endl;
    tree.postorder_traverse();
    cout << "层序输出:" << endl;
    tree.levelorder_traverse();
    return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
