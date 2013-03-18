#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	process_manage.py
#  Establishment date:  2009-2-10
#  Author            :	jasonleakey
#  Module Function   :  test functions to create and manage process
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
import signal
import sys
import time

print '***********************************'
print '   test function os.fork()'
print '***********************************'
#os.fork() returns twice
print 'Before invoking fork(), code will be executed once'
try:
	pid = os.fork()
except:
	print 'Cannot create a new process'
else:
	if pid < 0:
		print 'Cannot create a new process'
	elif pid == 0:
		print 'In the Child Process'
		#replace program with child_program
		os.execlp('./child_program', 'child_program', '2')
	else:
		print 'Waiting for child process exiting...'
		#wait child process to exit
		t = os.wait()
		print 'Child Process ID:%d,exit_code:%#x' % t
		
print '***********************************'
print '   test function os.waitpid()'
print '***********************************'
try:
	pid = os.fork()
except:
	print 'Cannot create a new process'
else:
	if pid == 0:
		print 'Child Process ID:%d' % os.getpid()
		#let child process to pause here
		signal.pause()
		os._exit(0)
	else:
		#How-to make a 'do-while' in python,do as follows
		while True:
			try:
				#wait for the status change of child process
				wait_pid = os.waitpid(pid, os.WUNTRACED | os.WCONTINUED)
			except:
					print 'Cannot invoke waitpid'
			else:
			
				#if child process has exited,then print the status
				if os.WIFEXITED(wait_pid[1]):
					print 'child process exits, status is %d' % os.WEXITSTATUS(wait_pid[1])
				#if child process has been terminated by signal
				if os.WIFSIGNALED(wait_pid[1]):
					print 'child process is killed by Signal %d' % os.WTERMSIG(wait_pid[1])
				#if child process has stopped
				if os.WIFSTOPPED(wait_pid[1]):
					print 'child process is stopped by signal %d' % os.WSTOPSIG(wait_pid[1])
				#if child process continue to run?
				if os.WIFCONTINUED(wait_pid[1]):
					print 'child process resume running...'
				
				flag = os.WIFEXITED(wait_pid[1]) or os.WIFSIGNALED(wait_pid[1])
				if flag:
					break
				
print '***********************************'
print '   test zombie process'
print '***********************************'
try:
	pid = os.fork()
except OSError:
	print 'Cannot create a new process!'
else:
	if pid == 0:
		time.sleep(20)
	else:
		print 'Parent process exit!'
		print 'Child Process ID:%d has been Zombie Process' % pid
		sys.exit(0)

