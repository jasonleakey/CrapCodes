#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Establishment date:  2009-4-23
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
#  menu.py: show basic menus operations

import pygtk
pygtk.require('2.0')
import gtk

class mywin(gtk.Window):
    def cb_select_color(self, widget, data = None):
        print 'select color'
    
    def __init__(self):
        super(mywin, self).__init__()
        
        self.set_size_request(250, 200)
        self.set_position(gtk.WIN_POS_CENTER)
        self.connect('destroy', lambda w: gtk.main_quit())
        
        vbox = gtk.VBox(False, 10)
        self.add(vbox)
        
        #define a accelerator group and add it to the Window
        acc_grp = gtk.AccelGroup()
        self.add_accel_group(acc_grp)
        
        file_menu = gtk.Menu()
#        select_item = gtk.ImageMenuItem(gtk.STOCK_NEW, acc_grp)
        select_item = gtk.MenuItem('File')
        keyval, modifier = gtk.accelerator_parse('<Control>N')
        select_item.add_accelerator('activate', acc_grp, keyval, modifier,\
                                    gtk.ACCEL_VISIBLE)
        select_item.connect('activate', self.cb_select_color)
        exit_item = gtk.MenuItem('Exit')
        exit_item.connect('activate', lambda w: gtk.main_quit())
        file_menu.append(select_item)
        file_menu.append(exit_item)
        
        file_root_item = gtk.MenuItem('File')
        file_root_item.set_submenu(file_menu)
        
        menu_bar = gtk.MenuBar()
        menu_bar.append(file_root_item)
        vbox.pack_start(menu_bar, False, False, 0)
        
        self.show_all()


if __name__ == '__main__':
    mywin()
    gtk.main()