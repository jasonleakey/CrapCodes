/*
 *  CPP_Algorithms - TODO
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

#ifndef _SORTALGO_H_
#define _SORTALGO_H_

#include "DataList.hpp"
#include "heap.hpp"

template<class Keytype, class Infotype>
void DirectInsertSort(
					  CDataList<Keytype, Infotype>& L,
                      int left,
                      int right)
{
	CElement<Keytype, Infotype> temp;
	for (int i = left + 1; i < right; i++)
	{
		if (L[i] < L[i - 1])
		{
			temp = L[i];
			int j = i - 1;
			for (; j >= 0 && L[j] >= temp; j--)
			{
				L[j + 1] = L[j];
			}
			L[j + 1] = temp;
		}
	}
}

template<class Keytype, class Infotype>
void QuickSort(CDataList<Keytype, Infotype>& L, const int left, const int right)
{
	if (left < right)
	{
		int pivotpos = L.Partition(left, right);
		QuickSort(L, left, pivotpos - 1);
		QuickSort(L, pivotpos + 1, right);
	}
}

template<class Keytype, class Infotype>
void ascend_heap_sort(CMaxHeap<Keytype, Infotype>& H)
{
	for (int i = H.length() / 2; i > 0; i--)
	{
		H.sift_down(i, H.length());
	}
	for (int i = H.length(); i > 1; i--)
	{
		H.swap(1, i);
		H.sift_down(1, i - 1);
	}
}

template<class Keytype, class Infotype>
static void merge(CDataList<Keytype, Infotype>& L1,
				CDataList<Keytype, Infotype>& L2,
				const int left,
				const int mid,
				const int right)
{
	int i = left;
	int j = mid + 1;
	int k = 0;
	for (k = 0; i <= mid && j <= right; k++)
	{
		if (L1[i] <= L1[j])
		{
			L2[k] = L1[i++];
		}
		else
		{
			L2[k] = L1[j++];
		}
	}
	while (i <= mid)
	{
		L2[k++] = L1[i++];
	}
	while (j <= right)
	{
		L2[k++] = L1[j++];
	}
}

#endif
