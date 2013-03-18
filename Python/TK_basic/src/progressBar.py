#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Jul 21, 2009
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
#  progressBar: function

import gtk
import gobject

class progressBar:
    def __init__(self):
        self.Builder = gtk.Builder()
        self.Builder.add_from_file('./progressbar.glade')
        self.mainWin = self.Builder.get_object('window1')
        self.pbar = self.Builder.get_object('progressbar1')
        self.actBut = self.Builder.get_object('activityCheckButton')
        self.mainWin.show_all()
        # add a timer callback to update the value of progressbar
        self.timer = gobject.timeout_add(100, self.freshPrgBar)
        self.Builder.connect_signals(self)
        
        
    def freshPrgBar(self):
        if self.actBut.get_active() == True:
            self.pbar.pulse()
        else:
            newVal = self.pbar.get_fraction() + 0.01
            if newVal > 1.0:
                newVal = 0.0
            self.pbar.set_fraction(newVal)
            
        return True
 
    def gtk_main_quit(self, widget, data = None):
        # remove the timer
        gobject.source_remove(self.timer)
        self.timer = 0.0
        gtk.main_quit()
    
    def on_ChangeOratCheckButton_clicked(self, widget, data = None):
        if widget.get_active() == True:
            self.pbar.set_orientation(gtk.PROGRESS_RIGHT_TO_LEFT)
        else:
            self.pbar.set_orientation(gtk.PROGRESS_LEFT_TO_RIGHT)    
            
    def on_activityCheckButton_clicked(self, widget, data = None):
        if widget.get_active() == True:
            self.pbar.pulse()
        else:
            self.pbar.set_fraction(0.0)
    
    def on_ShowTextCheckButton_clicked(self, widget, data = None):
        if widget.get_active() == True:
            self.pbar.set_text("some text")
        else:
            self.pbar.set_text("")
    
        
if __name__ == '__main__':
    progressBar()
    gtk.main()
