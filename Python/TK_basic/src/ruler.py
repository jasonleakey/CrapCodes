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
#  ruler.py: show ruler

import gtk

class Ruler:
    def __init__(self):
        self.builder = gtk.Builder()
        self.builder.add_from_file('ruler.glade')
        self.builder.connect_signals(self)
        
        drawingarea = self.builder.get_object('drawingarea1')
        #drawingarea.set_events(gtk.gdk.POINTER_MOTION_MASK\
        #                      | gtk.gdk.POINTER_MOTION_HINT_MASK)
        self.statusbar = self.builder.get_object('statusbar1')
        
        self.mainWin = self.builder.get_object('window1')
        self.mainWin.show_all()
        
    
    def gtk_main_quit(self, widget, data = None):
        gtk.main_quit()
        
    def on_drawingarea1_motion_notify_event(self, ruler, event):
        ruler.emit('motion_notify_event', event)
        lower, upper, curPos, maxSize = ruler.get_range()
        context_id = self.statusbar.get_context_id('Status Bar')
        self.statusbar.push(context_id, str(curPos))
        
if __name__ == '__main__':
    Ruler()
    gtk.main()