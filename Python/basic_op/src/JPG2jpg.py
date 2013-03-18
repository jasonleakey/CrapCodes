#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Jul 17, 2009
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
#  JPG2jpg: lowercase extension JPG to jpg

import os
import os.path
import glob

def main():
    JPGDir = raw_input("JPG Directory:")
    
    if not os.path.exists(JPGDir):
        print "No such directory!"
        return False
    
    cwd = os.chdir(JPGDir)
    files = os.listdir(JPGDir)
    JPGFiles = glob.glob('*.JPG')
    for file in JPGFiles:
        prefix = file.split(".")[0]
        os.rename(file, prefix + ".jpg")
        
if __name__ == '__main__':
    main()
