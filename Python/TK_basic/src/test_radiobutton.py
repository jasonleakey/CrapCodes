#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	test_radiobutton.py
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


class RadBut:
	'''Demonstration of Radio button'''
	#callback function of button
	def fnCB_Button(self, widget, data = None):
		print '%s is %s' %\
			(data, ('OFF', 'ON')[widget.get_active()])
	
	#callback function for delete_event
	def fnCB_delete_event(self, widget, event, data = None):
		print 'delete event occured!'
		gtk.main_quit()
		
	
	def __init__(self):
		#Create a window
		self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
		self.window.connect('delete_event', self.fnCB_delete_event)
		self.window.set_title('Radio Button')
		self.window.set_border_width(20)
		
		#Create a vbox
		self.vbox = gtk.VBox(True, 2)
		self.window.add(self.vbox)
		
		#Create three radion buttons in a group and a normal button to quit
		self.rbutton1 = gtk.RadioButton(None, 'radio button 1')
		self.rbutton1.connect('toggled', self.fnCB_Button, 'radio button 1')
		self.vbox.pack_start(self.rbutton1, True, False, 0)
		
		self.rbutton2 = gtk.RadioButton(self.rbutton1, 'radio button 2')
		self.rbutton2.connect('toggled', self.fnCB_Button, 'radio button 2')
		self.vbox.pack_start(self.rbutton2, True, False, 0)
		
		self.rbutton3 = gtk.RadioButton(self.rbutton1, 'radio button 3')
		self.rbutton3.set_active(True)
		self.rbutton3.connect('toggled', self.fnCB_Button, 'radio button 3')
		self.vbox.pack_start(self.rbutton3, True, False, 0)
		
		self.separator = gtk.HSeparator()
		self.vbox.pack_start(self.separator, False, True, 0)
		
		
		self.button = gtk.Button('Quit')
		self.button.connect('clicked', lambda widget: gtk.main_quit())
		#the following two lines make Quit button the default button 
		#so that pressing 'Enter' key when the window is active causes
		#the button to emit 'clicked' signal 
		self.button.set_flags(gtk.CAN_DEFAULT)
		self.button.grab_default()
		self.vbox.pack_start(self.button, True, False, 0)
		
		self.window.show_all()
		
	def main(self):
		gtk.main()
		return 0

if __name__ == '__main__':
	rb = RadBut()
	rb.main()