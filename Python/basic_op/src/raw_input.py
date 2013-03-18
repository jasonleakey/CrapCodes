#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	raw_input.py
#  Establishment date:  2009-2-17
#  Author            :	jasonleakey
#  Module Function   :  test build-in function raw_input()
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

try:
	import ctypes
	libc = ctypes.CDLL('libc.so.6')
	libc.prctl(15, 'uki_doing', 0, 0, 0)
except ImportError:
	print 'python version 2.5 is needed'

if __name__ == '__main__':
	name = raw_input('Enter your name:')
	print 'Your name is ' + name
	age = raw_input('Enter your age:')
	print 'Doubling your age is %d' % (int(age) * 2)
	print
	print 'OhOh'