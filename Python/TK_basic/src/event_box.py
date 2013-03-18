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
#  event_box.py: 

import pygtk
pygtk.require('2.0')
import gtk

class EventBox:
    def __init__(self):
        mainWnd = gtk.Window(gtk.WINDOW_TOPLEVEL)
        mainWnd.set_position(gtk.WIN_POS_CENTER)
        mainWnd.set_title('event box')
        mainWnd.set_border_width(10)
        mainWnd.connect('delete_event', lambda w, e: gtk.main_quit())
        
        eventBox = gtk.EventBox()
        eventBox.set_events(gtk.gdk.BUTTON_PRESS_MASK)
        eventBox.connect('button_press_event', lambda w, e: gtk.main_quit())
        mainWnd.add(eventBox)
        
        label = gtk.Label('click here to quit')
        label.set_events(gtk.gdk.ENTER_NOTIFY_MASK)
        label.connect('event', self.on_label_but_motion)
        eventBox.add(label)
        
        mainWnd.show_all()
        gtk.main()        
        
    def on_label_but_motion(self, widget, event, data = None):
        print 'event:%s' % event
        
if __name__ == '__main__':
    EventBox()
    gtk.main()