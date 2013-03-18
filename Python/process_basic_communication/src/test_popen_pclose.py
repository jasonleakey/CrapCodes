#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :  test_popen_pclose.py
#  Establishment date:  2009-2-20
#  Author            :  jasonleakey
#  Module Function   :  invoke popen() to create a pipe
#  Copyright (R) 2009jasonleakey
#  <jasonleakey2005@gmail.com>
#  <QQ:174481438>
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

import os
import sys

def main():
    try:
        #create a pipe and return a file object
        file_obj = os.popen('sort', 'w')
    except OSError, e:
        print 'cannot create a pipe:%s' % e
        return 1
    else:
        print >> file_obj, "this is python"
        print >> file_obj, "like this game"
        print >> file_obj, 'more and more'
        print >> file_obj, 'so beat it'
            

if __name__ == '__main__':
    main()