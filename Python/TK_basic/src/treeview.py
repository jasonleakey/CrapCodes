#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Aug 26, 2009
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
#  treeview.py: practice treeview

import gobject
import gtk
import pygtk
pygtk.require('2.0')

class TreeViewWnd(gtk.Window):
    def __init__(self):
        super(TreeViewWnd, self).__init__(gtk.WINDOW_TOPLEVEL)
        
        self.set_title('Tree View')
        self.set_border_width(5)
        self.set_position(gtk.WIN_POS_CENTER)
        self.set_size_request(400, 300)
        self.connect('destroy', gtk.main_quit)
        
        tree = gtk.TreeView()
        tree.set_search_column(0) # searchable
        tree.set_reorderable(True) # reorderable
        tree.set_headers_clickable(False) # header responds to click event 
        
        languages = gtk.TreeViewColumn('Programming languages')
        languages.set_sort_column_id(0) # allow sorting on this column    
        languages.set_spacing(5)
        
        cell = gtk.CellRendererText()
        languages.pack_start(cell, True)
        languages.add_attribute(cell, 'text', 0)
        
        treestore = gtk.TreeStore(gobject.TYPE_STRING)
        
        it = treestore.append(None, ['Scripting languages'])
        treestore.append(it, ['Python'])
        treestore.append(it, ['Ruby'])
        treestore.append(it, ['PHP'])
        treestore.append(it, ['Perl'])
        
        
        it = treestore.append(None, ['Compiling languages'])
        compileLang = ['C', 'C++', 'C#', 'Basic', 'Delphi']
        for lang in compileLang:
            treestore.append(it, [lang])
        
        tree.append_column(languages)
        tree.set_model(treestore)
        
        self.add(tree)
        self.show_all()
        
if __name__ == '__main__':
    TreeViewWnd()
    gtk.main()