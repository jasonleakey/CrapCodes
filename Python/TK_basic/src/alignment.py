#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Establishment date:  2009-4-18
#  Author            :  jasonleakey
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
#  filename: function


import pygtk
pygtk.require('2.0')
import gtk

class base():
    def __init__(self):
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self.window.set_position(gtk.WIN_POS_CENTER)
        self.window.set_default_size(200, 100)
        self.window.connect('destroy', lambda w: gtk.main_quit())
        
        align = gtk.Alignment(0, 0, 0.5, 0.5)
        button = gtk.Button('Click here\nto quit')
        button.set_size_request(200, 100)
        button.connect('clicked', lambda w: gtk.main_quit())
        align.add(button)
        self.window.add(align)
        
        self.window.show_all()
        
    def main(self):
        gtk.main()
        
if __name__ == '__main__':
    base().main()