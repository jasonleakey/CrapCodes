#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Jul 23, 2009
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
#  entry.py: 

import gtk

class Entry:
    def __init__(self):
        self.builder = gtk.Builder()
        self.builder.add_from_file('Entry.glade')
        self.builder.connect_signals(self)
        
        
        self.mainWnd = self.builder.get_object('window1')
        self.mainWnd.show_all()
    
    def gtk_main_quit(self, widget, data = None):
        gtk.main_quit()
        
    def on_editchkbutton_toggled(self, widget, data = None):
        entry = self.builder.get_object('entry1')
        entry.set_editable(widget.get_active())
    
    def on_visiblechkbutton_toggled(self, widget, data = None):
        entry = self.builder.get_object('entry1')
        entry.set_visibility(widget.get_active())
        
    def on_entry1_activate(self, widget, data = None):
        statusbar = self.builder.get_object('statusbar1')
        context_id = statusbar.get_context_id('entry')
        statusbar.push(context_id, widget.get_text())
    
    def on_entry1_changed(self, widget, data = None):
        entry = self.builder.get_object('entry1')
        print entry.get_text()
        
if __name__ == '__main__':
    Entry()
    gtk.main()