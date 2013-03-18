#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	mutex_by_file.py
#  Establishment date:  2009-2-15
#  Author            :	jasonleakey
#  Module Function   :  mutex each other process by normal file
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

import pygtk
pygtk.require('2.0')
import gtk
import os
import errno
import time
import sys

def get_access_right(file_name, retry_times, inq_interval):
	'''determine wheter the resource is valid.
	if YES, return True
	else return False'''
	#current retry times
	count = 0
	while os.path.exists('%s/%s' % (os.getcwd(), file_name)):
		#cannot find or no right to access the file.
		print 'PID:%d try to get access right...' % os.getpid()
		count += 1
		if count < retry_times:
			time.sleep(inq_interval)
		else:
			return False
	try:
		fd = open(file_name, 'w')
	except IOError, e:
		print 'IOError occured:%s' % e
		return False
	try:
		fd.close()
	except:
		return False
	else:
		return True
		
def release_right(file_name):
	'''remove flag file
	if it is removed successfully, return True
	else return False
	'''
	try:
		result = os.remove(file_name)
	except OSError, e:
		print 'cannot remove flag file:%s' % e
		return False
	else:
		print 'PID:%d release the resource!' % os.getpid()
		return True

def main():
	#In Python, there is no 'argc' key word
	argc = len(sys.argv)
	if argc != 4:
		print 'Usage: %s retry_times inquire_interval file_name' % sys.argv[0]
		return 1
	
	retry_times = int(sys.argv[1])
	if retry_times <= 0:
		print 'illegal retry times!'
		return 1
	
	inquire_interval = int(sys.argv[2])
	if inquire_interval <= 0:
		print 'illegal inquire interval'
		return 1
	
	file_name = sys.argv[3]
	file_len = len(sys.argv[3])
	if file_len == 0:
		print 'illegal file name!'
		return 1
	
	#if the resource is valid
	if get_access_right(file_name, retry_times, inquire_interval) == 1:
		for i in range(5):
			print 'Round %d, PID %d is occupying the resource' % (i, os.getpid())
			#sleep for 1s
			time.sleep(inquire_interval)
	
		#after using the resource, release it
		release_right(file_name)
	else:
		print 'PID:%d cannot access the resource! retry %d times'\
			% (os.getpid(), retry_times)
		
	return 0

if __name__ == '__main__':
	main()