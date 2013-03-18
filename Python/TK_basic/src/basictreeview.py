#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Establishment date:  2009-4-19
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
#  basictreeview: show the basic usage of treeview

import pygtk
pygtk.require('2.0')
import gtk
import os

class BasicTreeView:
    def __init__(self):
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self.window.set_position(gtk.WIN_POS_CENTER)
        self.window.connect('destroy', lambda w: gtk.main_quit())
        self.window.set_title('Base TreeView Example')
        self.window.set_default_size(300, 200)
        
        scrl_win = gtk.ScrolledWindow()
        scrl_win.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_AUTOMATIC)
        self.window.add(scrl_win)
        
        tree_store = gtk.TreeStore(str)
        
        os.chdir(os.getenv('HOME'))
        cwd = os.getcwd()
        dir_list = os.listdir(cwd)
        dir_list.sort(cmp = lambda x, y: cmp(x.lower(), y.lower()))
        for file_dir in dir_list:
            piter = tree_store.append(None, [file_dir])
            if os.path.isdir(cwd + '/' + file_dir):
                sub_dir = os.listdir(file_dir)
                for sub_file in sub_dir:
                    tree_store.append(piter, [sub_file])
        # a tree type container
        tree_view = gtk.TreeView(tree_store)
        tree_view.set_tooltip_text('current directory!')
        
        tree_view_column = gtk.TreeViewColumn('Column 0')
        
        tree_view.append_column(tree_view_column)
        
        #create a cellrendertext to render the data
        cell = gtk.CellRendererText()
        
        #add the cell to the column and allow it to expand
        tree_view_column.pack_start(cell, True)
        
        #???
        tree_view_column.add_attribute(cell, 'text', 0)
        
        #make it searchable
        tree_view.set_search_column(0)
        
        #allow sorting on the column 
        tree_view_column.set_sort_column_id(0)
        #allow drag and drop reordering the row
        tree_view.set_reorderable(True)
        
        scrl_win.add(tree_view)
        
        self.window.show_all()
        
    def main(self):
        gtk.main()
        
if __name__ == '__main__':
    BasicTreeView().main()