#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	button_with_pixmap_label.py
#  Establishment date:  2009-1-31
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

def make_box(parent, xpm_file, label_text):
	'''create a box to pack xpm and label'''
	box = gtk.HBox(False, 0)
	box.set_border_width(2)
	
	#create a image
	image = gtk.Image()
	image.set_from_file(xpm_file)
	
	#create a text
	label = gtk.Label(label_text)
	
	#pack them
	box.pack_start(image, False, False, 3)
	box.pack_start(label, False, False, 3)
	
	image.show()
	label.show()
	return box

class Buttons:
	'''create Normal button with pixmap and label'''
	#callback function for button
	def button_callback(self, widget, data = None):
		print 'hello~%s was pressed' % data
	
	def __init__(self):
		#Create a window
		self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
		#it's a good idea for all windows to do this
		self.window.connect('destroy', lambda a: gtk.main_quit())	#only one argurment
		self.window.connect('delete_event', lambda b, c: gtk.main_quit()) #two arguments
		self.window.set_default_size(200, 200)
		self.window.set_title('Button with image')
		self.window.set_border_width(10)
		self.window.set_icon_from_file('/home/jasonleakey/图片/Ubuntu_Logo.png')
		
		#create the button
		self.button = gtk.Button()
		self.button.connect('clicked', self.button_callback, 'cool button')
		
		self.box = make_box(self.window, '/home/jasonleakey/图片/八神庵头像.jpg', 'Click Here')
		self.button.add(self.box)
		
		self.window.add(self.button)
		self.window.show_all()
		
	def main(self):
		gtk.main()
		return 0

if __name__ == '__main__':
	button = Buttons()
	button.main()
		