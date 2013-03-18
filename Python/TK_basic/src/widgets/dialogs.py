#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Sep 20, 2009
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
#  dialogs.py: basic dialogs

import os
import time
import gtk
import pygtk
pygtk.require('2.0')
import urllib2
import consts

class BaseMessageDialog(gtk.MessageDialog):
    def __init__(self, type, buttons):
#        print type, buttons
        # invoke the parent's constructor
        super(BaseMessageDialog, self).__init__(self,
                                             gtk.DIALOG_MODAL | gtk.DIALOG_DESTROY_WITH_PARENT,
                                             type,
                                             buttons)
        
    def set_content(self, title = None, message = '', second_message = None):
        self.set_title(title)
        self.set_markup('<big><b>%s</b></big>' % message)
        self.format_secondary_markup(second_message)
        
        
class InfoDialog(BaseMessageDialog):
    def __init__(self, title = None, message = ''):
        super(InfoDialog, self).__init__(gtk.MESSAGE_INFO, gtk.BUTTONS_OK)
        self.set_content(title, message)

class WarningDialog(BaseMessageDialog):
    def __init__(self, title = None, message = ''):
        super(WarningDialog, self).__init__(gtk.MESSAGE_WARNING, gtk.BUTTONS_YES_NO)
        self.set_content(title, message)

class QustionDialog(BaseMessageDialog):
    def __init__(self, title = None, message = ''):
#        print message, title, self.__class__
#        print gtk.MESSAGE_QUESTION, gtk.BUTTONS_YES_NO
        super(QustionDialog, self).__init__(gtk.MESSAGE_QUESTION, gtk.BUTTONS_YES_NO)
        self.set_content(title, message)
        
class ErrorDialog(BaseMessageDialog):
    def __init__(self, title = None, message = ''):
        super(ErrorDialog, self).__init__(gtk.MESSAGE_ERROR, gtk.BUTTONS_YES_NO)
        self.set_content(title, message)
        
class MyAboutDialog(gtk.AboutDialog):
    def __init__(self, 
                 program_name,
                 version,
                 copyright = 'copyleft(r) jasonleakey',
                 comments = None,
                 license = None,
                 website = None,
                 website_label = None,
                 authors = None,
                 documenters = None,
                 artists = None,
                 tranlator_credits = None,
                 logo_filename = None
                 ):
        super(MyAboutDialog, self).__init__()
        self.set_name(program_name)
        self.set_version(version)
        self.set_copyright(copyright)
        if comments:
            self.set_comments(comments)
        if license:
            self.set_wrap_license(True)
            self.set_license(license)
        if website:
            self.set_website(website)
        if website_label:
            self.set_website_label(website_label)
        if authors and isinstance(authors, list):
            self.set_authors(authors)
        if documenters and isinstance(documenters, list):
            self.set_documenters(documenters)
        if artists and isinstance(artists, list):
            self.set_artists(artists)
        if tranlator_credits and isinstance(tranlator_credits, list):
            self.set_translator_credits(tranlator_credits)
        if logo_filename and os.path.exists(logo_filename):
            pixbuf = gtk.gdk.pixbuf_new_from_file_at_size(logo_filename, 48, 48)
            self.set_logo(pixbuf)

    def openURL(dialog, link, data = None):
        urllib2.urlopen(link)
    

if __name__ == '__main__':
    d = QustionDialog('This is a Title', "dog's day")
    d.run()
    d.destroy()
    a = MyAboutDialog('Glade',
                    '0.1',
                    'jasonleakey2009',
                    'it can be very used',
                    consts.licence % ('Glade', 'Glade', 'Glade'),
                    'http://www.g.cn/',
                    'Google',
                    ['jasonleakey'],
                    logo_filename = '/home/jasonleakey/project/pyGTK_basic/src/apple-green.png')
    gtk.about_dialog_set_url_hook(MyAboutDialog.openURL)
    a.run()
    a.destroy()
    