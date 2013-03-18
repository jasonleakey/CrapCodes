#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Aug 22, 2009
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
#  test_glade_user_data.py: function


import sys
try:
    import gtk
    import pygtk
    pygtk.require('2.0')
except:
    print 'GTK/pyGTK library is missing'
    sys.exit(-1)

class TestUD():
    def __init__(self):
        self.builder = gtk.Builder()
        self.builder.add_from_file('testGUD.glade')
        self.builder.connect_signals(self)
        
        self.mainWnd = self.builder.get_object('window1')
        self.mainWnd.show_all()
        
    def gtk_main_quit(self, data = None):
        print data
        gtk.main_quit()
        
if __name__ == '__main__':
    TestUD()
    gtk.main()