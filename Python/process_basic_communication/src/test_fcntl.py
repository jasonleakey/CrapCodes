#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	test_fcntl.py
#  Establishment date:  2009-2-16
#  Author            :	jasonleakey
#  Module Function   :  invoke fcntl() to get file descriptors
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

import sys
import os
import fcntl

if __name__ == '__main__':
	argc = len(sys.argv)
	if argc != 2:
		print 'Usage: %s filename' % sys.argv[0]
		return 1
	
	#Determine if the file exists
	if not os.path.exists(filename):
		print 'No such File!'
		return 1
	
	try:
		fd = open(filename, 'r')
	except IOError, e:
		print 'Open File Error:%s' % e
		return 1
	else:
		try:
			file_status = fcntl.fcntl(fd, fcntl.F_GETFL)
		except IOError, e:
			print 'invoke fcntl() Error:%s' % e
		else:
			