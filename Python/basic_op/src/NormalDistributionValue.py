#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Sep 16, 2009
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
#  NormalDistributionValue: calculate the function value with normal distribution

from math import *
import sys

class ND():
    def __init__(self, u, omiga):
        self.u = u
        self.omiga = omiga
        
    def get_value(self, x):
        if isinstance(x, float):
            value = exp(-pow((x - self.u) / self.omiga, 2) / 2)\
                    / (pow(2 * pi, 0.5) * self.omiga)
        return value
            
if __name__ == '__main__':
    d1 = ND(1, 1)
    d2 = ND(0, 1.0/4)
    try:
        while True:
            x = raw_input('Input x:')
            g1 = 1.0/3 * d1.get_value(float(x))
            g2 = 2.0/3 * d2.get_value(float(x))
            g3 = 1.0/6 * (d1.get_value(float(x)) + 2 * d2.get_value(float(x)))
            print 'g1=%f,g2=%f,g3=%f' % (g1, g2, g3)
    except KeyboardInterrupt,e:
        print '%s' % e
        sys.exit(1)