#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Sep 5, 2009
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
#  xclient.py: H3C 802.1x client frontend

import gtk
import pygtk
pygtk.require('2.0')

class ButtonBox(gtk.VButtonBox):
    def __init__(self):
        super(ButtonBox, self).__init__()
        self.set_layout(gtk.BUTTONBOX_SPREAD)
        
        helpBut = gtk.Button(stock = gtk.STOCK_HELP)
        connBut = gtk.Button(stock = gtk.STOCK_CONNECT)
        aboutBut = gtk.Button(stock = gtk.STOCK_ABOUT)
        closeBut = gtk.Button(stock = gtk.STOCK_CLOSE)
        
        helpBut.connect('clicked', self.on_helpBut_clicked)
        
        self.pack_start(helpBut, False, False, 0)
        self.pack_start(connBut, False, False, 0)
        self.pack_start(aboutBut, False, False, 0)
        self.pack_start(closeBut, False, False, 0)
        
    def on_helpBut_clicked(self, button, data = None):
        helpDlg = gtk.Dialog()
        
        

class ClientWindow(gtk.Window):
    def __init__(self):
        super(ClientWindow, self).__init__(gtk.WINDOW_TOPLEVEL)
        self.set_border_width(10)
        self.set_title(u'网络连接xclient')
        self.set_icon_from_file('./apple-green.png')
        self.set_size_request(600, 500)
        self.set_position(gtk.WIN_POS_CENTER)
        self.connect('delete_event', gtk.main_quit)
        
        vBoxMax = gtk.VBox()
        self.add(vBoxMax)
        
        hbox = gtk.HBox()
        vBoxMax.pack_start(hbox, True, True, 5)
        
        scrlWnd = gtk.ScrolledWindow()
        scrlWnd.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_AUTOMATIC)
        
        self.textView = gtk.TextView()
        
        buttons = ButtonBox()
        self.add(buttons)
        
        self.show_all()
        
if __name__ == '__main__':
    ClientWindow()
    gtk.main()