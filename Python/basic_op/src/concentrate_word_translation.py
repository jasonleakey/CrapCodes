#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Sep 22, 2009
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
#  concentrate_word_translation: function

import os

def main():
    enFile = '/home/jasonleakey/project/pyGTK_basic/src/save/GRE.dat'
    cnFile = '/home/jasonleakey/project/pyGTK_basic/src/save/GREcn.dat'
    greFile = '/home/jasonleakey/project/pyGTK_basic/src/save/GRE.txt'
    try:
        enStream = open(enFile)
        cnStream = open(cnFile)
        greStream = open(greFile, 'w')
        enList = [line.rstrip('\r\n') for line in enStream]
        cnList = [line.rstrip('\r\n') for line in cnStream]
        greList = [' '.join([enList[i], cnList[i]]) + '\r\n' for i in range(1239)]
        greStream.writelines(greList)
    finally:
        enStream.close()
        cnStream.close()
if __name__ == '__main__':
    main()