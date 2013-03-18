#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Aug 2, 2009
#  Author:  jasonleakey
#  Change log:
#  Copyleft(R) by jasonleakey
#  <jasonleakey@gmail.com>
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
#  --------------------------------------------------------------------
#  layout.py: 

import pygtk
pygtk.require('2.0')
import gtk
import random

class Layout:
    def __init__(self):
        self.builder = gtk.Builder()
        self.builder.add_from_file('layout.glade')
        self.builder.connect_signals(self)
        self.mainWnd = self.builder.get_object('window1')
        
        vScrBar = self.builder.get_object('vscrollbar1')
        hScrBar = self.builder.get_object('hscrollbar1')
        self.layOut = self.builder.get_object('layout1')
        vAdjust = self.layOut.get_vadjustment()
        vScrBar.set_adjustment(vAdjust)
        hAdjust = self.layOut.get_hadjustment()
        hScrBar.set_adjustment(hAdjust)
        
        self.mainWnd.show_all()
        
    def gtk_main_quit(self, widget, data = None):
        gtk.main_quit()
        
    def on_button_enter(self, button, data = None):
        self.layOut.move(button, random.randint(0, 500), random.randint(0, 500))
        
if __name__ == '__main__':
    Layout()
    gtk.main()