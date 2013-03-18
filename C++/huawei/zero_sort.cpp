// =====================================================================================
// 
//       Filename:  zero_sort.cpp
// 
//    Description:  int A[nSize]，其中隐藏着若干0，其余非0整数，写一个函数
//    int Func(int* A, int nSize)，使A把0移至后面，非0整数移至 
//    数组前面并保持有序，返回值为原数据中第一个元素为0的下标。
//    (尽可能不使用辅助空间且考虑效率及异常问题，注释规范且给出设计思路)
// 
//        Version:  1.0
//        Created:  08/24/2011 11:06:20 AM
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
#include    <iomanip>
#define SWAP(A,B) \
    int temp = (A); \
    (A) = (B);\
    (B) = temp;
using namespace std;

int Func(int* A, int nSize)
{
    int i = 0;
    int j = nSize - 1;

    //----------------------------------------------------------------------
    //  derived from quick sort algorithm 
    //----------------------------------------------------------------------
    while (i <= j) 
    {
        if (A[i] == 0 && A[j] == 0)
        {
            j--;
        }
        else if (A[i] == 0 && A[j] != 0)
        {
            SWAP(A[i], A[j]);
            i++;
            j--;
        }
        else if (A[i] != 0 && A[j] == 0)
        {
            i++;
            j--;
        }
        else
        {
            i++;
        }
    }

    //----------------------------------------------------------------------
    //  bubble sort for the leftmost non-zero elements
    //----------------------------------------------------------------------
    for (int s = 0; s < i - 1; s++)
    {
        for (int t = s + 1; t < i; t++)
        {
            if (A[t] < A[s])
            {
                SWAP(A[t], A[s]);
            }
        }
    }
    return i;
}


int main (int argc, char *argv[])
{
    int size = 30;
    int arr[] = {
        3, 0, 8, 0, -7,
        0, 1, 0, 2, 3,
        -9, -7, 0, -18, -12,
        0, 0, 0, -4, 9,
        -2, -5, -7, 0, 0,
        -8, 8, 6, 0, -6
    };   
    int idx = Func(arr, size);
    cout << "index = " << idx + 1 << endl;
    for (int i = 0; i < size; i++)
    {
        cout << setw(4) << arr[i];
        if (!((i + 1) % 5))
        {
            cout << endl;
        }
    }
    return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
