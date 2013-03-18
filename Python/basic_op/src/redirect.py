#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Aug 22, 2009
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
#  redirect.py: direct the stand output to a regular file

import sys


def redirect():
    f = open('/home/jasonleakey/redirect.txt', 'w')
    sys.stdout = f
    
    print 'good morning'
    sys.stdout.write('Mrs. Wang\n')
    sys.stdout.writelines(['new game\r', 'game over\r\n'])

    sys.stdout = sys.__stdout__
    
    print 'long time'
    sys.stdout.write('sodem')
    
    f.close()

if __name__ == '__main__':
    redirect()