#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Jul 24, 2009
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
#  spinbutton.py: function

import gtk

class SpinButton:
    def __init__(self):
        self.builder = gtk.Builder()
        self.builder.add_from_file('SpinButton.glade')
        self.builder.connect_signals(self)
        
        self.mainWnd = self.builder.get_object('mainWnd')
        self.mainWnd.show_all()
        
    def gtk_main_quit(self, widget, data = None):
        gtk.main_quit()
                
    def on_getValueBut_clicked(self, widget):
        sbutton4 = self.builder.get_object('spinbutton4')
        label = self.builder.get_object('label8')
        if widget is self.builder.get_object('intBut'):
            label.set_text(str(int(sbutton4.get_value())))
        else:
            label.set_text(str(sbutton4.get_value()))
    
    def on_numericchkbut_toggled(self, widget, data = None):
        sbutton4 = self.builder.get_object('spinbutton4')
        sbutton4.set_numeric(widget.get_active())
    
    def on_snapchkbut_toggled(self, widget, data = None):
        sbutton4 = self.builder.get_object('spinbutton4')
        sbutton4.set_snap_to_ticks(widget.get_active())
    
    def on_digitspinbutton_value_changed(self, widget, data = None):
        sbutton4 = self.builder.get_object('spinbutton4')
        sbutton4.set_digits(widget.get_value_as_int())

if __name__ == '__main__':
    SpinButton()
    gtk.main()