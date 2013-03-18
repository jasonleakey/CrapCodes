#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	test_box.py
#  Establishment date:  2009-1-28
#  Author            :	jasonleakey
#  Copyright (R) 2009 jasonleakey
#  <jasonleakey2005@gmail.com>
#  <QQ:174481438>
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


import pygtk
pygtk.require('2.0')
import gtk

def make_box(homogeneous, spacing, expand, fill, padding):
    #Create a horizontal box with appropriate homogeneous
    #and spacing setting
    box = gtk.HBox(homogeneous, spacing)

    #Create a series of buttons with appropriate settings
    button1 = gtk.Button('gtk.pack')
    button2 = gtk.Button('(button,')
    if expand:
        button3 = gtk.Button('True,')
    else:
        button3 = gtk.Button('False,')
    ###This is the same as 'expand' above, but uses shorthand form.
    button4 = gtk.Button(('False,', 'True,')[fill])
    padstr = '%d)' % padding
    button5 = gtk.Button(padstr)

    order = [button1, button2, button3, button4, button5]
    for i in order:
        box.pack_start(i, expand, fill, padding)
    return box


class Bast():
    def destroy(self, widget):
        '''
        callback function for 'destroy' signal
        '''
        print 'destroy occured!'
        print 'exit'
        gtk.main_quit()

    def __init__(self):
        '''
        constructor
        '''
        #Create Window
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self.window.connect('destroy', self.destroy)
        self.window.set_title('Test Box')
        self.window.set_default_size(500, 200)
        self.window.set_icon_from_file\
                ('/home/jasonleakey/图片/Ubuntu_Logo.png')

        self.label1 = gtk.Label('HBox(False, 0)')
        self.label1.set_alignment(0, 0)

        self.box1 = make_box(False, 0, False, False, 0)
        self.box2 = make_box(False, 0, True, False, 0)
        self.box3 = make_box(False, 0, True, True, 0)

        self.label2 = gtk.Label('HBox(True, 0)')
        self.label2.set_alignment(0, 0)
        self.box4 = make_box(True, 0, True, False, 0)
        self.box5 = make_box(True, 0, True, True, 0)
        #create a separator
        self.separator1 = gtk.HSeparator()
        self.separator1.set_size_request(400, 30)

        #create boxes to test padding and spacing
        self.label3 = gtk.Label('HBox(False, 10)')
        self.label3.set_alignment(0, 0)
        self.box6 = make_box(False, 10, False, False, 0)
        self.box7 = make_box(False, 10, True, False, 0)
        self.box8 = make_box(False, 10, True, True, 0)
        self.label4 = gtk.Label('HBox(True, 10)')
        self.label4.set_alignment(0, 0)
        self.box9 = make_box(True, 10, True, False, 0)
        self.box10 = make_box(True, 10, True, True, 0)
        #create a separator
        self.separator2 = gtk.HSeparator()
        self.separator2.set_size_request(400, 30)

        self.label5 = gtk.Label('HBox(False, 0)')
        self.label5.set_alignment(0, 0)
        self.box11 = make_box(False, 0, False, False, 10)
        self.box12 = make_box(False, 0, True, False, 10)
        self.box13 = make_box(False, 0, True, True, 10)
        self.label6 = gtk.Label('HBox(True, 0)')
        self.label6.set_alignment(0, 0)
        self.box14 = make_box(True, 0, True, False, 10)
        self.box15 = make_box(True, 0, True, True, 10)

        #create a box packing all horizontal boxes and labels
        self.vbox = gtk.VBox(False, 0)
        order = [self.label1, self.box1, self.box2, self.box3,\
                self.label2, self.box4, self.box5, self.separator1,\
                self.label3, self.box6, self.box7, self.box8,\
                self.label4, self.box9, self.box10, self.separator2,\
                self.label5, self.box11, self.box12, self.box13,\
                self.label6, self.box14, self.box15]
        for i in order:
            self.vbox.pack_start(i, False, False, 0)
        self.window.add(self.vbox)
        self.window.show_all()

    def main(self):
        gtk.main()

if __name__ == '__main__':
    base = Bast()
    base.main()