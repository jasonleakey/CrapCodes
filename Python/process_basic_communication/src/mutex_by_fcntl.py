#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	mutex_by_fcntl.py
#  Establishment date:  2009-2-16
#  Author            :	jasonleakey
#  Module Function   :  use fcntl() to mutex processes
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

#struct flock {
#	short l_type;
#	short l_whence;
#	off_t l_start;
#	off_t l_len;
#	pid_t l_pid;
#...
#};

#####Notice: Deprecated since release Python 1.5

import os
import sys
import errno
import time
import struct #To define a structure
import fcntl
import posixfile

def fcntl_lock_file():
	#Check argument amounts
	argc = len(sys.argv)
	if argc != 2:
		print 'Usage: %s lock_file_name' % sys.argv[0]
		return 1
	
	file_name = sys.argv[1]
	#Obtain lock file description
	if not os.path.exists(file_name):
		print os.strerror(errno.EEXIST)
		return 1
	
	try:
		fd = open(file_name, 'rw')
	except IOError, e:
		print 'Cannot Open File: %s' % e
	else:
		lock = struct.pack('hhllhh', fcntl.F_WRLCK, 0, 0, 0, 0, 0)
		print 'lock=', repr(lock)
		count = 0 #retry times
		#Try to occupy the lock_file.retry to 5 times when fail
		while True:
			try:
				fcntl.fcntl(fd, fcntl.F_SETLKW, lock)
			except IOError, e:
				print 'fcntl invoke Error:%s' % e
				#resouce is owned by other process 
				if errno.EACCES or errno.EAGAIN:
					count += 1
					if count < 5:
						time.sleep(1)
					else:
						try:
							fcntl.fcntl(fd, fcntl.F_GETLK, lock)
						except IOError, e:
							print 'fcntl invoke Error:%s' % e
						finally:
							fd.close()
					print 'Function fcntl call fail!'
					return 1
			else:
				break
		print 'PID:%ld lock the file!' % os.getpid()
		time.sleep(3)
		print 'PID:%d release the file!' % os.getpid()
		return 0
	
if __name__ == '__main__':
    fcntl_lock_file()
						