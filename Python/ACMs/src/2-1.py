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
#  2-1.py: fake gold

class FakeGold:
    (N, K) = (5, 3)
    (WEIGHT_REC) = (
                  ((2, 1, 2, 3, 4), '<'),
                  ((1, 1, 4), '='),
                  ((1, 2, 5), '='),
                  )
    
    def __init__(self):
        fakes = []
        for i in range(0, FakeGold.N):
            for j in range(0, FakeGold.K):
                if not self.jd(i, j):
                    break
            else:
                fakes.append(i)
        if len(fakes) == 1:
            print fakes[0]
        else:
            print '0'
            
    # determine the correspondence
    def jd(self, curFakeGold, compTime):
        if curFakeGold not in FakeGold.WEIGHT_REC[compTime][0][1:]\
            and FakeGold.WEIGHT_REC[compTime][1] == '='\
            or curFakeGold in FakeGold.WEIGHT_REC[compTime][0][1:]\
            and FakeGold.WEIGHT_REC[compTime][1] != '=':
            return True
        else:
            return False

if __name__ == '__main__':
    FakeGold()