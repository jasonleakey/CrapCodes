#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	test_label.py
#  Establishment date:  2009-2-4
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

class Labels:
	#def cb_delete_event(self, widget, event, data = None):
	#	window = gtk.Window(gtk.WINDOW_POPUP)
		#vbox = gtk.VBox(False, 10)
	#	window.add(vbox)
		#label = gtk.Label('Are you sure to quit?')
		#vbox.pack_start(label)
		#button_yes = gtk.Button('Yes')
		#button_yes.connect('clicked', lambda flag: False)
		#button_no = gtk.Button('No')
		#button_no.connect('clicked', lambda flag: True)
		#hbox = gtk.HBox(False, 10)
		#hbox.pack_end(button_yes, False, False, 0)
		#hbox.pack_end(button_no, False, False, 0)
		#vbox.pack_start(hbox)
	#	return flag
	
	def __init__(self):
		#Create a window
		self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
		#self.window.connect('delete_event', self.cb_delete_event)
		self.window.connect('destroy', lambda wid: gtk.main_quit())
		self.window.set_title('Test Label')
		
		hbox = gtk.HBox(False, 5)
		hbox.set_border_width(10)
		self.window.add(hbox)
		vbox_left = gtk.VBox(False, 5)
		hbox.pack_start(vbox_left, True, True, 0)
		vbox_right = gtk.VBox(False, 5)
		hbox.pack_start(vbox_right, True, True, 0)
		
		frame = gtk.Frame('Normal Label')
		label = gtk.Label('This is a Normal Label')
		frame.add(label)
		vbox_left.pack_start(frame)
		
		frame = gtk.Frame('Multi-line Label')
		label = gtk.Label('This is a multi-line label,\n'
						'Second Line.\nThird Line')
		frame.add(label)
		vbox_left.pack_start(frame)
		
		frame = gtk.Frame('Left Justified Label')
		label = gtk.Label('This is a Left-Justified\nMulti-Line Label\nThird Line')
		label.set_justify(gtk.JUSTIFY_LEFT)
		frame.add(label)
		vbox_left.pack_start(frame)
		
		frame = gtk.Frame('Right Justified Label')
		label = gtk.Label('This is a Right-Justified\nMulti-Line Label\nThird Line')
		label.set_justify(gtk.JUSTIFY_RIGHT)
		frame.add(label)
		vbox_left.pack_start(frame)
		
		frame = gtk.Frame('Line wrapped Label')
		label = gtk.Label('This is an example of a line-wrapped label.  It '
	                       "should not be taking up the entire             "
	                       "width allocated to it, but automatically "
	                       "wraps the words to fit.  "
	                       "The time has come, for all good men, to come to "
	                       "the aid of their party.  "
	                       "The sixth sheik's six sheep's sick.\n"
	                       "     It supports multiple paragraphs correctly, "
                           "many          extra  spaces. ")
		label.set_line_wrap(True)
		frame.add(label)
		vbox_right.pack_start(frame)
		
		frame = gtk.Frame('Filled, wrapped label')
		label = gtk.Label('This is an example of a line-wrapped, filled label.  '
                           "It should be taking "
                           "up the entire              width allocated to it.  "
                           "Here is a sentence to prove "
                           "my point.  Here is another sentence. "
                           "Here comes the sun, do de do de do.\n"
                           "    This is a new paragraph.\n"
                           "    This is another newer, longer, better "
                           "paragraph.  It is coming to an end, "
                           "unfortunately.")
		label.set_line_wrap(True)
		label.set_justify(gtk.JUSTIFY_FILL)
		frame.add(label)
		vbox_right.pack_start(frame)
		
		#Cannot come true......
		frame = gtk.Frame('Underlined Label')
		label = gtk.Label('This label is underlined!\n'
	                      "This one is underlined in quite a funky fashion")
		label.set_justify(gtk.JUSTIFY_LEFT)
		label.set_pattern("_______________________ __ _")
		frame.add(label)
		vbox_right.pack_start(frame)
		
		self.window.show_all()
		
def main():
	gtk.main()
	return 0

if __name__ == '__main__':
	Labels()
	main()
		
	
	
	