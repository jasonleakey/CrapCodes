#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Establishment date:  2009-4-26
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
#  buttons_signals.py: 


import gtk


class PyApp(gtk.Window):
    def __init__(self):
        super(PyApp, self).__init__()
        
        self.set_title("Signals")
        self.set_size_request(250, 200)
        self.set_position(gtk.WIN_POS_CENTER)
        self.connect("destroy", gtk.main_quit)
        
        fixed = gtk.Fixed()
        
        self.quit = gtk.Button("Quit")
        
        self.quit.connect("pressed", self.on_pressed)
        self.quit.connect("released", self.on_released)
        self.quit.connect("clicked", self.on_clicked)
        
        self.quit.set_size_request(80, 35)

        fixed.put(self.quit, 50, 50)
        
        self.add(fixed)
        self.show_all()
        self.emit_signal()
        
    def emit_signal(self):
                
        event = gtk.gdk.Event(gtk.gdk.BUTTON_RELEASE)
        event.button = 1
        event.window = self.quit.window
        event.send_event = True
                
        self.quit.emit("button-release-event", event)
        
        
    def on_clicked(self, widget):
        print "clicked"
        
    def on_released(self, widget):
        print "released"
        
    def on_pressed(self, widget):
        print "pressed"


PyApp()
gtk.main()

