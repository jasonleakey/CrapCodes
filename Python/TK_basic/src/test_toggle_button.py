#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	test_toggle_button.py
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

class TogBut:
	'''Demonstration of Toggle button'''
	#callback function of button
	def fnCB_Button(self, widget, data = None):
		if widget.get_active():
			print '%s is ON' % data
		else:
			print '%s is OFF' % data
	
	#callback function for delete_event
	def fnCB_delete_event(self, widget, event, data = None):
		print 'delete event occured!'
		gtk.main_quit()
	
	def __init__(self):
		#Create a window
		self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
		self.window.connect('delete_event', self.fnCB_delete_event)
		self.window.set_border_width(20)
		
		#Create a vbox
		self.vbox = gtk.VBox(True, 2)
		self.window.add(self.vbox)
		
		#Create two toggle buttons and a normal button
		self.tbutton1 = gtk.ToggleButton('Toggle Button 1')
		self.tbutton1.connect('toggled', self.fnCB_Button, 'toggle button 1')
		self.tbutton1.set_active(False)
		self.vbox.pack_start(self.tbutton1, True, False, 0)
		
		self.tbutton2 = gtk.ToggleButton('Toggle Button 2')
		self.tbutton2.connect('toggled', self.fnCB_Button, 'toggle button 2')
		self.tbutton2.set_active(True)
		self.vbox.pack_start(self.tbutton2, True, False, 0)
		
		self.button = gtk.Button('Quit')
		self.button.connect('clicked', lambda widget: gtk.main_quit())
		self.vbox.pack_start(self.button, True, False, 0)
		
		self.window.show_all()
		
	def main(self):
		gtk.main()
		return 0

if __name__ == '__main__':
	tb = TogBut()
	tb.main()