/*
 *  CPP_DS_List - linear list implementation
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
#include <string>
#include <vector>
#include "SeqList.hpp"
#include "DataList.hpp"
#include "heap.hpp"
#include "SortAlgo.hpp"
using namespace std;

int main(int argc, char **argv)
{
//	CSeqList<int> myslist(20);
//	myslist.input();
//	myslist.get_length();
//	myslist.output();
//	ysk

	CDataList<int, string> studName(20);
	CElement<int, string> stud[16] = {{3, "go"},
			{4, "set"}, {9, "suck"}, {2, "meet"},
			{1, "be"}, {7, "no"}, {6, "just"},
			{8, "jk"}, {5, "cat"}, {2, "wood"},
			{7, "big"}, {4, "hl"}, {2, "uk"},
			{1, "shine"}, {0, "28"}, {-1, "goca"}};
	for (int i = 0; i < 16; i++)
	{
		studName.append(stud[i]);
	}
//	DirectInsertSort(studName, 0, studName.length());
//	QuickSort(studName, 0, studName.length() - 1); // unstable

//	CMaxHeap<int, string> studHeap(stud, 16);
//	ascend_heap_sort(studHeap);
//	cout << studHeap << endl;


	return 0;
}

