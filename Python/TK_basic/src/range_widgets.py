#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	range_widgets.py
#  Establishment date:  2009-2-3
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

#convenience functions
def make_menu_item(name, callback, data = None):
	item = gtk.MenuItem(name)
	item.connect('activate', callback, data)
	item.show()
	return item

def scale_set_default_values(scale):
	scale.set_update_policy(gtk.UPDATE_CONTINUOUS)
	scale.set_digits(1)
	scale.set_value_pos(gtk.POS_TOP)
	scale.set_draw_value(True)
	
class RangeWidgets:
	def cb_pos_menu_select(self, item, pos):
		#set the value position on both scale widgets
		self.hscale.set_value_pos(pos)
		self.vscale.set_value_pos(pos)
		
	def cb_update_menu_select(self, item, policy):
		#Set the update policy for both scale widgets
		self.hscale.set_update_policy(policy)
		self.vscale.set_update_policy(policy)
		self.hscrollbar.set_update_policy(policy)
	
	def cb_digits_scale(self, adj):
		#Set the number of decimal places to which adj->value is rounded
		self.hscale.set_digits(adj.value)
		self.vscale.set_digits(adj.value)
		
	def cb_page_size(self, get, set):
		#Set the page size and the page increment of the sample
		#adjust to the value specified by the scale 'Page Size' scale
		set.page_size = get.value
		set.page_incr = get.value
		#Now emit "changed" signal to reconfigure all widgets that
		#are attached to this adjustment
		set.emit('changed')
		
	def cb_draw_value(self, button):
		#Turn the value display on the scale widgets off or on
		#depending on the state of the check button
		self.hscale.set_draw_value(button.get_active())
		self.vscale.set_draw_value(button.get_active())
		
	#make the sample window
	
	def __init__(self):
		#Standard window-creating stuff(upper - page_size)
		self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
		self.window.connect('destroy', lambda wid: gtk.main_quit())
		self.window.set_title('Range Widgets')
		
		self.vbox = gtk.VBox(False, 0)
		self.window.add(self.vbox)
		self.vbox.show()
		
		self.hbox1 = gtk.HBox(False, 10)
		self.hbox1.set_border_width(10)
		self.vbox.pack_start(self.hbox1, True, True, 0)
		self.hbox1.show()
		
		#value, lower, upper, step_incr, page_incr, page_size
		#Note that the page_size value only makes a difference for 
		#scrollbar widgets, and the highest value you'll get is 
		#actually (upper - page_size)
		self.adj1 = gtk.Adjustment(0.0, 0.0, 100.0, 0.1, 1.0, 0.0)
		
		#Reuse the same adjustment 
		self.vscale = gtk.VScale(self.adj1)
		self.vscale.set_size_request(50, 200)
		scale_set_default_values(self.vscale)
		self.hbox1.pack_start(self.vscale, True, True, 0)
		self.vscale.show()
		
		self.vbox2 = gtk.VBox(False, 10)
		self.vbox2.set_border_width(10)
		self.hbox1.pack_start(self.vbox2, True, True, 0)
		self.vbox2.show()
		
		self.hscale = gtk.HScale(self.adj1)
		#sets 'the minimum size' of a widget to the values specified by width and height. 
		self.hscale.set_size_request(200, 50)
		scale_set_default_values(self.hscale)
		self.vbox2.pack_start(self.hscale, True, True, 0)
		self.hscale.show()
		
		self.hscrollbar = gtk.HScrollbar(self.adj1)
		self.hscrollbar.set_size_request(300, 60)
		#Notice how this causes the scales to always to be updated
		#continuously when the scroll bar is moved
		self.hscrollbar.set_update_policy(gtk.UPDATE_CONTINUOUS)
		self.vbox2.pack_start(self.hscrollbar, True, True, 0)
		self.hscrollbar.show()

		self.cbutton = gtk.CheckButton('Display value on the scale widgets')
		self.cbutton.connect('toggled', self.cb_draw_value)
		self.cbutton.set_active(True)
		self.vbox.pack_start(self.cbutton, True, True, 5)
		self.cbutton.show()
		
		self.hbox2 = gtk.HBox(False, 10)
		self.hbox2.set_border_width(20)
		self.vbox.pack_start(self.hbox2, True, True, 0)
		self.hbox2.show()
		
		self.label1 = gtk.Label('Scale Value Position')
		self.hbox2.pack_start(self.label1, True, True, 0)
		
		#Create a optional menu and add submenus into it
		#gtk.OptionMenu is recommended to be replaced with gtk.ComboBox
		self.optionMenu = gtk.OptionMenu()
		self.menu = gtk.Menu()
		self.item = make_menu_item('Top', self.cb_pos_menu_select, gtk.POS_TOP)
		self.menu.append(self.item)
		self.item = make_menu_item('Bottom', self.cb_pos_menu_select, gtk.POS_BOTTOM)
		self.menu.append(self.item)
		self.item = make_menu_item('Left', self.cb_pos_menu_select, gtk.POS_LEFT)
		self.menu.append(self.item)
		self.item = make_menu_item('Rigth', self.cb_pos_menu_select, gtk.POS_RIGHT)
		self.menu.append(self.item)
		self.optionMenu.set_menu(self.menu)
		self.hbox2.pack_start(self.optionMenu, True, True, 0)
		self.optionMenu.show()
		
		#Create another optional menu for update-policy
		hbox3 = gtk.HBox(False, 10)
		hbox3.set_border_width(10)
		self.vbox.pack_start(hbox3, True, True, 0)
		hbox3.show()
		
		label2 = gtk.Label('Scale Update Policy')
		hbox3.pack_start(label2, True, True, 0)
		label2.show()
		
		optionMenu2 = gtk.OptionMenu()
		menu2 = gtk.Menu()
		item = make_menu_item('Continuous',\
				 self.cb_update_menu_select, gtk.UPDATE_CONTINUOUS)
		menu2.append(item)
		item = make_menu_item('Delayd',\
				self.cb_update_menu_select, gtk.UPDATE_DELAYED)
		menu2.append(item)
		item = make_menu_item('DisContinuous',\
				self.cb_update_menu_select, gtk.UPDATE_DISCONTINUOUS)
		menu2.append(item)
		optionMenu2.set_menu(menu2)
		hbox3.pack_start(optionMenu2, True, True, 0)
		optionMenu2.show()
		
		#Create a range widget to adjust the scale digits above
		hbox4 = gtk.HBox(False, 10)
		hbox4.set_border_width(10)
		self.vbox.pack_start(hbox4, True, True, 0)
		
		label3 = gtk.Label('Scale digits')
		hbox4.pack_start(label3, True, True, 0)
		label3.show()
		
		adj2 = gtk.Adjustment(1, 0, 5, 1, 1, 1)
		adj2.connect('value_changed', self.cb_digits_scale)
		hscale2 = gtk.HScale(adj2)
		hscale2.set_digits(0)
		hbox4.pack_start(hscale2, True, True, 0)
		hscale2.show()
		
		#Create a range widget to adjust the Scrollbar Page Size
		hbox5 = gtk.HBox(False, 10)
		hbox5.set_border_width(10)
		self.vbox.pack_start(hbox5, True, True, 0)
		hbox5.show()
		
		label4 = gtk.Label('Scrollbar Page Size:')
		hbox5.pack_start(label4, True, True, 0)
		label4.show()
		
		adj3 = gtk.Adjustment(1.0, 0.0, 101.0, 0.1, 2.0, 0.0)
		adj3.connect('value_changed', self.cb_page_size, adj3)
		hscale3 = gtk.HScale(adj3)
		hscale3.set_digits(1)
		hbox5.pack_start(hscale3, True, True, 0)
		hscale3.show()
		
		#Create a seperator
		seperator = gtk.HSeparator()
		self.vbox.pack_start(seperator, True, True, 0)
		seperator.show()
		
		button = gtk.Button('Quit')
		button.connect('clicked', lambda wid: gtk.main_quit())
		button.set_border_width(10)
		self.vbox.pack_start(button, True, True, 0)
		button.set_flags(gtk.CAN_DEFAULT)
		button.grab_default()
		button.show()
	
		self.window.show_all()
	
	def main(self):
		gtk.main()
		return 0

if __name__ == '__main__':
	rw = RangeWidgets()
	rw.main()