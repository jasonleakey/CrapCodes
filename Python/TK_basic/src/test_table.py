#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	test_table.py
#  Establishment date:  2009-1-28
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

import pygtk
pygtk.require('2.0')
import gtk

class Table:
	#callback function for button to print data to stdout
	def hello_button(self, widget, data = None):
		print 'hello again - %s is pressed' % data
	
	def destroy(self, widget):
		print 'destroy occured!\nexit'
		gtk.main_quit()
		
	def delete_event(self, widget, event):
		print 'destroy_event occured!'
		return False
	
	def __init__(self):
		#Create a window
		self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
		self.window.connect('delete_event', self.delete_event)
		self.window.connect('destroy', self.destroy)
		self.window.set_border_width(20)
		self.window.set_title('Test Table')
		self.window.set_icon_from_file('/home/jasonleakey/图片/Ubuntu_Logo.png')
		
		#Create a table and add it into the window
		self.table = gtk.Table(2, 2, True)
		self.window.add(self.table)
		
		#Create three buttons and pack them into the table
		self.button1 = gtk.Button('button1')
		self.button1.connect('clicked', self.hello_button, 'button1')
		self.button2 = gtk.Button('button2')
		self.button2.connect('clicked', self.hello_button, 'button2')
		self.button3 = gtk.Button('Quit')
		#define a function to quit directly
		self.button3.connect('clicked', lambda w: gtk.main_quit())
		self.table.attach(self.button1, 0, 1, 0, 1)
		self.table.attach(self.button2, 1, 2, 0, 1)
		self.table.attach(self.button3, 0, 2, 1, 2)
		
		self.window.show_all()
		
	def main(self):
		gtk.main()
		return 0

if __name__ == '__main__':
	Table().main()