#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Jun 17, 2009
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
#  create_BRDF.py: collect angles info and irradiance info,and then store
#                it in a .brdf binary file.

from __future__ import with_statement
import os
import os.path as path
import sys
import array
from ctypes import *

#class ANGLEIRR(Structure):
#   _fields_ = [('alpha', c_double),
#               ('beta', c_double),
#               ('gamma', c_double),
#               ('Itheta', c_double),
#               ('Iphi', c_double),
#               ('Rtheta', c_double),
#               ('Rphi', c_double),
#               ('irr', c_double * 697)]
    
class brdf:
    def __init__(self):
        cwd = raw_input('Input Directory path:')
        
        if not path.exists(cwd):
            print 'No such Directory'
            return
        os.chdir(cwd)
        
        
        try:
            with open('./angles.txt', 'r+') as anglesStream:
                with open('./angles_new.txt', 'w') as anglesNewStream:
                    for line in anglesStream:
                        line = line.strip()
                        [alpha, beta, gamma, Itheta, Iphi, Rtheta, Rphi] =\
                            line.split()
                        alpha = float(alpha)
                        beta = float(beta)
                        gamma = float(gamma)
                        Itheta = float(Itheta)
                        Iphi = float(Iphi)
                        Rtheta = float(Rtheta)
                        Rphi = float(Rphi)
                        intAlpha = int(alpha) if int(alpha) == alpha else alpha
                        intBeta = int(beta) if int(beta) == beta else beta
                        intGamma = int(gamma) if int(gamma) == gamma else gamma
                        anglesNewStream.writelines(str(intAlpha) + ' ' + str(intBeta)\
                            + ' ' + str(intGamma) + ' ' + str(Itheta) + ' '\
                            + str(Iphi) + ' ' + str(Rtheta) + ' ' + str(Rphi)\
                            + '\r\n')
#                        angleirr.alpha = alpha
#                        angleirr.beta = beta
#                        angleirr.gamma = gamma
#                        angleirr.Itheta = Itheta
#                        angleirr.Iphi = Iphi
#                        angleirr.Rtheta = Rtheta
#                        angleirr.Rphi = Rphi
#                        angleirr = ANGLEIRR(alpha, beta, gamma, Itheta, Iphi,\
#                                            Rtheta, Rphi)
#                        print repr(angleirr.raw)
                            
                        
                    
        except IOError, e:
            sys.stderr.write("IOError:%s\n" % e)
            return
        

if __name__ == '__main__':
    brdf()
        