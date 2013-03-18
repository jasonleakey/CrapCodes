#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	daemon_process.py
#  Establishment date:  2009-2-13
#  Author            :	jasonleakey
#  Module Function   :  something about daemon process operation
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
import os.path
import sys
import time

print '***********************************'
print '   create a daemon process'
print '***********************************'
try:
	pid = os.fork()
except OSError:
	print 'Cannot create process!'
else:
	if pid > 0:
		#let the parent process exit,and make the child one zombie process
		sys.exit()
	else:
		#create a new session and make current process the leading process
		pid = os.setsid()
		#change current work directory the root directory '/'
		os.chdir('/')
		#redirect standard output to /home/jasonleakey/daemon_out.log
		#redirect standard input to /dev/null
		#redirect standard error to /home/jasonleakey/daemon_error.log
		stdin = '/dev/null'
		stdout = '/home/jasonleakey/daemon_out.log'
		stderr = '/home/jasonleakey/daemon_error.log'
		try:
			si = open(stdin, 'r')
			so = open(stdout, 'a+')
			se = open(stderr, 'a+', 0)
		except IOError, e:
			print 'Cannot open file: (%d) %s' % (e.error, e.strerror)
			sys.exit(1)
		os.dup2(si.fileno(), sys.stdin.fileno())
		os.dup2(so.fileno(), sys.stdout.fileno())
		os.dup2(se.fileno(), sys.stderr.fileno())
		#set the new numeric umask
		os.umask(0027)
		#print ten times into daemon_out.log
		for i in range(11):
			print ('%d.Current Time: %s' % (i, time.ctime(time.time())))
			sys.stdout.flush()
			time.sleep(2)