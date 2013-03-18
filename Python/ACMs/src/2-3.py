#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Aug 2, 2009
#  Author:  jasonleakey
#  Change log:
#  Copyleft(R) by jasonleakey
#  <jasonleakey@gmail.com>
#  --------------------------------------------------------------------
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#  --------------------------------------------------------------------
#  2-3.py: matrix

import sys 

def main():
    while 1:
        dim = raw_input('Input dimension:')
        dim = int(dim)
        if dim == -1:
            break;
        mat = []
        for i in range(dim):
            line = raw_input()
            numbers = line.split()
            for j in range(dim):
                numbers[j] = int(numbers[j])
            mat.append(numbers)
        
        totalPathCnt = dim * dim
        minMaxSum = sys.maxint
        for i in range(1, totalPathCnt + 1):
            series = int_to_series(i, dim)
            a = sel_max_sum(mat, dim, series)
            if a < minMaxSum:
                minMaxSum = a
                
        print minMaxSum 
        
def int_to_series(intNum, dim):
    series = [0] * dim
    for i in range(dim):
        series[-i] = intNum % dim
        intNum /= dim
    return series
        
def sel_max_sum(matrix, dim, series):
    for i in range(dim):
        for j in range(int(series[i])):
            last = matrix[i].pop()
            matrix[i].insert(0, last)
            
    max = 0
    for j in range(dim):
        a = [matrix[i][j] for i in range(dim)]
        colSum = sum([matrix[i][j] for i in range(dim)])
        if colSum > max:
            max = colSum
    return max

if __name__ == '__main__':
    main()