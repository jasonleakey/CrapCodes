#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	process_operation.py
#  Establishment date:  2009-2-7
#  Author            :	jasonleakey
#  Module Function   :  test basic operations about process parameters
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

class Proc:
	def __init__(self):
		self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
		self.window.connect('destroy', lambda wid: gtk.main_quit())
		self.window.set_icon_from_file('/home/jasonleakey/图片/Ubuntu_Logo.png')
		self.window.set_title('Process Function Test')
		self.window.set_default_size(200, 200)
		#create a table
		table = gtk.Table(3, 3)
		self.window.add(table)
		
		#the first frame
		frame = gtk.Frame('getpid')
		table.attach(frame, 0, 1, 0, 1)
		statusbar = gtk.Statusbar()
		frame.add(statusbar)
		#the get_contest_id() method returns a new or existing context 
		#identifier, given a description of the actual context specified
		#by context_description
		context_id1 = statusbar.get_context_id("getpid")
		#invoke os.getpid() to get current process's PID
		#and change it into a string
		statusbar.push(context_id1, str(os.getpid()))
		
		frame = gtk.Frame('getppid')
		table.attach(frame, 1, 2, 0, 1)
		statusbar = gtk.Statusbar()
		frame.add(statusbar)
		context_id2 = statusbar.get_context_id('getppid')
		#invoke os.getppid() to get its parent process's PID
		#and change it into a string
		statusbar.push(context_id2, str(os.getppid()))
		
		frame = gtk.Frame('getuid')
		table.attach(frame, 2, 3, 0, 1)
		statusbar = gtk.Statusbar()
		frame.add(statusbar)
		context_id3 = statusbar.get_context_id('getuid')
		#invoke os.getppid() to get the ID of current process's owner
		statusbar.push(context_id3, str(os.getuid()))
		
		frame = gtk.Frame('geteuid')
		table.attach(frame, 0, 1, 1, 2)
		statusbar = gtk.Statusbar()
		frame.add(statusbar)
		context_id4 = statusbar.get_context_id('geteuid')
		#invoke os.getppid() to get the ID of current 
		#process's efficient owner
		statusbar.push(context_id4, str(os.geteuid()))
		
		frame = gtk.Frame('getgid')
		table.attach(frame, 1, 2, 1, 2)
		statusbar = gtk.Statusbar()
		frame.add(statusbar)
		context_id5 = statusbar.get_context_id('getgid')
		#invoke os.getppid() to get the ID of current process's group
		statusbar.push(context_id2, str(os.getgid()))
		
		frame = gtk.Frame('getegid')
		table.attach(frame, 2, 3, 1, 2)
		statusbar = gtk.Statusbar()
		frame.add(statusbar)
		context_id6 = statusbar.get_context_id('getegid')
		#invoke os.getppid() to get the ID of current
		#process's efficient group
		statusbar.push(context_id2, str(os.getegid()))
		
		frame = gtk.Frame('getcwd')
		table.attach(frame, 0, 1, 2, 3)
		statusbar = gtk.Statusbar()
		frame.add(statusbar)
		context_id7 = statusbar.get_context_id('getcwd')
		#invoke os.getcwd() to get current work path
		statusbar.push(context_id7, os.getcwd())
		
		
		button = gtk.Button('Quit')
		button.connect('clicked', lambda wid: gtk.main_quit())
		button.set_size_request(20, 10)
		table.attach(button, 2, 3, 2, 3)
		
		self.window.show_all()
	
def main():
	gtk.main()
	return 0
	
if __name__ == '__main__':
	Proc()
	main()
		
		
		