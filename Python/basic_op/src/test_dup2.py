#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :  test_dup2.py
#  Establishment date:  2009-2-20
#  Author            :  jasonleakey
#  Module Function   :  test dup2 to redirect input/output
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
        fd = open('/home/jasonleakey/dup2.txt', 'a')
        print 'fd=', fd
    except IOError, e:
        print 'cannot open file:%s' % e
        return 1
    else:
        os.dup2(fd.fileno(), sys.stdout.fileno())
        print 'Message will be redirected into dup2.txt'
        fd.close()

if __name__ == '__main__':
    main()