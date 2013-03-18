#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	dialog.py
#  Establishment date:  2009-2-15
#  Author            :	jasonleakey
#  Module Function   :  test how to use dialog widget
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
import pango

import pygtk
pygtk.require('2.0')
import gtk

class Test_Dialog:
	'''test how to use dialog'''
	
	#callback to select font for label
	def cb_font_button(self, font_but, label, data = None):
		font_desc = pango.FontDescription(font_but.get_font_name())
		label.modify_font(font_desc)
		
	
	#callback to select a foreground for label
	def cb_color_button(self, color_but, label, data = None):
		color_sel = color_but.get_color()
		print color_sel
		label.modify_fg(gtk.STATE_NORMAL, color_sel)
	
	
	
	def cb_exit_button(self, widget, data = None):
		#Create a dialog and Pop up it when 'exit' is clicked
		dialog = gtk.MessageDialog(None,\
					gtk.DIALOG_MODAL | gtk.DIALOG_DESTROY_WITH_PARENT,\
					gtk.MESSAGE_QUESTION, gtk.BUTTONS_YES_NO,\
					'Are you really want to Quit?')
		#set the default position the dialog appears
		dialog.set_position(gtk.WIN_POS_CENTER_ON_PARENT)
		#like 'gtk.main()' blocks in a recursive loop to wait for
		#'response' signal raising. 
		ret = dialog.run()
		#destroy dialog
		dialog.destroy()
		#if user clicked the 'Yes' button,then quit
		if ret == gtk.RESPONSE_YES:
			gtk.main_quit()
		else:
			print 'No pressed!'
			return True

		
	def __init__(self):
		#Create a window
		self.main_window = gtk.Window(gtk.WINDOW_TOPLEVEL)
		self.main_window.connect('delete_event', self.cb_exit_button)
		self.main_window.set_title('Test Dialog')
		#set the default position the main window appears
		self.main_window.set_position(gtk.WIN_POS_CENTER)
		self.main_window.set_size_request(600, 500)
		
		vbox = gtk.VBox(False, 0)
		self.main_window.add(vbox)
		
		label = gtk.Label('This is a dog,这是一条狗')
		label.set_line_wrap(True)
		label.set_selectable(True)
		label.set_single_line_mode(False)
		vbox.pack_start(label, True, True, 0)
				
		font_sel_but = gtk.FontButton()
		#the signal 'font-set' is emit when selected a font.
		#and set the label's font style corresponding to this
		font_sel_but.connect('font-set', self.cb_font_button, label)
		font_sel_but.set_title('Select Font')
		font_sel_but.set_use_font(False)
		font_sel_but.set_use_size(True)
		font_sel_but.set_font_name('微软雅黑 18')
		font_sel_but.set_show_style(True)
		font_sel_but.set_show_size(True)
		vbox.pack_start(font_sel_but, False, False, 0)
		
		
		color_but = gtk.ColorButton(gtk.gdk.Color(65535, 0, 0))
		color_but.set_title('Select Color')
		color_but.connect('color-set', self.cb_color_button, label)
		vbox.pack_start(color_but, False, False, 0)
		
		
		exit_but = gtk.Button('Exit')
		exit_but.set_size_request(30, 50)
		exit_but.connect('clicked', self.cb_exit_button)
		vbox.pack_start(exit_but, False, False, 0)
		
		self.main_window.show_all()
	def main(self):
		gtk.main()
	
if __name__ == '__main__':
	Test_Dialog().main()