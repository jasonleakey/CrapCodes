#!/usr/bin/python
# -*- coding: utf-8 -*-


#  File name         :	My_cat.py
#  Establishment date:  2009-1-24
#  Author            :	jasonleakey
#  Copyright (R) 2009 jasonleakey 
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

print '***************************'
print '   模拟cat功能'
print '***************************'

import sys

def readline(filename):
	'''
	print the file to standard out
	@param filename:
	'''
	
	f = file(filename)
	while True:
		line = f.readline()
		if len(line) == 0:
			break
		print line,
	f.close()

#script starts here
if len(sys.argv) < 2:
	print 'Usage:%s filename' % sys.argv[0]

if sys.argv[1].startswith('--'):
	option = sys.argv[1][2 : ]
	if option == 'version':
		print 'Version 1.2'
	elif option == 'help':
		print ''\
			'This program prints files to the standard output.\n'\
			'Any number of files can be specified.\n'\
			'Options include:\n'\
			'--version : Prints the version number\n'\
			'--help    : Display this help\n'
	else:
		print 'Unknown option!'
		print 'Use %s --help for help' % sys.argv[0]
	sys.exit()
elif sys.argv[1].startswith('-'):
	option = sys.argv[1][1 : ]
	if option == 'v':
		print 'Version 1.2'
	elif option == 'h':
		print ''\
			'This program prints files to the standard output.\n'\
			'Any number of files can be specified.\n'\
			'Options include:\n'\
			'--version : Prints the version number\n'\
			'--help    : Display this help\n'
	else:
		print 'Unknown option!'
		print 'Use %s --help for help' % sys.argv[0]
	sys.exit()
else:
	for flname in sys.argv[1 : ]:
		readline(flname)