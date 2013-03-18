#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	test_check_button.py
#  Establishment date:  2009-2-2
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


class ChkBut:
	'''Demonstration of Check button'''
	#callback function of button
	def fnCB_Button(self, widget, data = None):
		print '%s is %s' % (data, ('OFF', 'ON')[widget.get_active()])
	
	#callback function for delete_event
	def fnCB_delete_event(self, widget, event, data = None):
		print 'delete event occured!'
		return False
		
	
	def __init__(self):
		#Create a window
		self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
		self.window.connect('delete_event', self.fnCB_delete_event)
		self.window.set_border_width(20)
		
		#Create a vbox
		self.vbox = gtk.VBox(True, 2)
		self.window.add(self.vbox)
		
		#Create two check buttons and a normal button to quit
		self.cbutton1 = gtk.CheckButton('check button 1')
		self.cbutton1.connect('toggled', self.fnCB_Button, 'check button 1')
		self.cbutton1.set_active(False)
		self.vbox.pack_start(self.cbutton1)
		
		self.cbutton2 = gtk.CheckButton('check button 2')
		self.cbutton2.connect('toggled', self.fnCB_Button, 'check button 2')
		self.cbutton2.set_active(True)
		self.vbox.pack_start(self.cbutton2)
		
		self.button = gtk.Button('Quit')
		self.button.connect('clicked', lambda widget: gtk.main_quit())
		self.vbox.pack_start(self.button)
		
		self.window.show_all()

	def main(self):
		gtk.main()
		return 0

if __name__ == '__main__':
	tb = ChkBut()
	tb.main()