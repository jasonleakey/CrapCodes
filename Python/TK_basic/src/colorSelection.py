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
#  colorSelection.py: function

import gtk

class ColorSelection:
    def __init__(self):
        self.builder = gtk.Builder()
        self.builder.add_from_file('ColorSelection.glade')
        self.builder.connect_signals(self)
        
        self.drawingarea = self.builder.get_object('drawingarea1')
        self.color = self.drawingarea.get_colormap().alloc_color(0, 65535, 0)
        
        self.mainWnd = self.builder.get_object('mainWnd')
        self.mainWnd.show_all()
    
    def gtk_main_quit(self, widget, data = None):
        gtk.main_quit()
    
    def on_drawingarea1_button_press_event(self, widget, data = None):
        colorselectiondialog = self.builder.get_object('colorselectiondialog1')
        clrSel = colorselectiondialog.get_color_selection()
        clrSel.set_previous_color(self.color)
        clrSel.set_current_color(self.color)
        clrSel.connect('color-changed', self.on_colorsel_color_changed)
        #clrSel.connect("color_changed", self.on_colorsel_color_changed, widget)
        response = colorselectiondialog.run()
        if response == gtk.RESPONSE_OK:
            self.color = clrSel.get_current_color()
        elif response == gtk.RESPONSE_CANCEL:
            widget.modify_bg(gtk.STATE_NORMAL, self.color)
        else:
            print 'change color'
        colorselectiondialog.hide()
        
    def on_colorsel_color_changed(self, widget):
        curColor = widget.get_current_color()
        self.drawingarea.modify_bg(gtk.STATE_NORMAL, curColor)

if __name__ == '__main__':
    ColorSelection()
    gtk.main()