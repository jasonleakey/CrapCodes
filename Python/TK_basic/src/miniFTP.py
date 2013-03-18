#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Establishment date:  2009-4-15
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
#  filename: function



import pygtk
import gtk
import ftplib
import os
import socket
import webbrowser

class miniFTP:

    __license__ = """
miniFTP is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
"""
    ftp = ""

    def __init__(self):
        self.window = gtk.Window()
        self.window.set_default_size(200, 100)
        self.window.set_title("miniFTP")
        self.window.set_border_width(2)
        self.window.connect("destroy", self.kill)
    
        self.vbox_login = gtk.VBox()
        self.window.add(self.vbox_login)

        self.menu = gtk.Menu()
        self.menu_items = {"Exit": self.kill, "Disconnect": self.logoutFTP} #menuitems (Name, action)
        self.menuItemsAdd(self.menu, self.menu_items)
        self.root_menu = gtk.MenuItem("Main")
        self.root_menu.set_submenu(self.menu)

        self.about_menu = gtk.Menu()
        self.about_menu_items = {"About": self.aboutDialog}
        self.menuItemsAdd(self.about_menu, self.about_menu_items)
        self.root_about_menu = gtk.MenuItem("Help")
        self.root_about_menu.set_submenu(self.about_menu)

        self.menu_bar = gtk.MenuBar()
        self.menu_bar.append(self.root_menu)
        self.menu_bar.append(self.root_about_menu)

        self.l1 = gtk.Label("host")
        self.l2 = gtk.Label('port')
        self.l3 = gtk.Label('user')
        self.l4 = gtk.Label('password')
        self.login_host = gtk.Entry()
        self.login_host.set_text('192.168.1.188')
        self.login_port = gtk.Entry()
        self.login_port.set_text('18021')
        self.login_name = gtk.Entry()
        self.login_name.set_text('12345')
        self.login_pw = gtk.Entry()
        self.login_pw.set_text('12345')
        self.login_pw.set_visibility(False) # ********

        self.login_button = gtk.Button("login")
        self.login_button.connect("clicked", self.loginFTP)

        self.vbox_login.pack_start(self.menu_bar, False, False, 2)
        self.vbox_login.pack_start(self.l1, False, False)
        self.vbox_login.pack_start(self.login_host, False, False)
        self.vbox_login.pack_start(self.l2, False, False) 
        self.vbox_login.pack_start(self.login_port, False, False)
        self.vbox_login.pack_start(self.l3, False, False)
        self.vbox_login.pack_start(self.login_name, False, False)
        self.vbox_login.pack_start(self.l4, False, False)
        self.vbox_login.pack_start(self.login_pw, False, False)
        self.vbox_login.pack_start(self.login_button, False, False)

        self.window.show_all()

    def cb_click_website(self, dialog, link, data = None):
        webbrowser.open(link)
        
    def aboutDialog(self, event):
        gtk.about_dialog_set_url_hook(self.cb_click_website)
        
        self.about_dialog = gtk.AboutDialog()
        self.about_dialog.set_name("miniFTP")
        self.about_dialog.set_version("0.0.1")
        self.about_dialog.set_copyright("copyleft(R) by jasonleakey")
        self.about_dialog.set_comments("Comments:use it for free!")
        self.about_dialog.set_website("http://www.g.cn")
        self.about_dialog.set_website_label('click here')
        self.about_dialog.set_license(self.__license__)
        self.about_dialog.set_authors(["Jason Leakey"])
        self.about_dialog.set_documenters(["jasonleakey", 'uKi'])
        self.about_dialog.set_artists(['google', 'baidu'])
        self.about_dialog.set_translator_credits('look\nsoso')
        self.about_dialog.set_logo(gtk.gdk.pixbuf_new_from_file
            ('/home/jasonleakey/图片/logo.jpg'))
        self.about_dialog.set_program_name('miniftp')
        self.about_dialog.connect("response", self.aboutDialogHide)
        self.about_dialog.show()

    def aboutDialogHide(self, widget, event):
        self.about_dialog.hide()

    # generate liststore where is current working dir files and directorys in local 
    # if update is True it creates new treeview
    # else just update it
    def listLocal(self, update=True):
        if update == False:
            os.chdir(os.getenv("HOME"))
            self.local_files = os.listdir(os.getcwd()) # hakee oletuksena kotikansion tiedostot
            self.store_local = gtk.ListStore(str)
        
            self.local_files.insert(0,"..")
            for s in self.local_files:
                if s[0] != "." or s == "..":
                    self.store_local.append(["%s" % s]) #data

            self.view_local = gtk.TreeView(self.store_local)
            self.view_local.add_events(gtk.gdk.BUTTON_PRESS_MASK)
            self.view_local.connect("button-press-event", self.actionLocal)
            
            self.local_col = gtk.TreeViewColumn("local")
            self.view_local.append_column(self.local_col)
            self.local_cell = gtk.CellRendererText()
            self.local_col.pack_start(self.local_cell, True)
            self.local_col.add_attribute(self.local_cell, 'text', 0)

            self.scroll_local = gtk.ScrolledWindow()
            self.scroll_local.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_AUTOMATIC)
            self.scroll_local.add(self.view_local)

            self.hbox.pack_start(self.scroll_local, True, True, 2)
        elif update == True:
            self.local_files = os.listdir(os.getcwd())
            self.local_files.insert(0,"..")
            self.store_local.clear()
            for s in self.local_files:
                if s[0] != "." or s == "..":
                    self.store_local.append(["%s" % s]) #data

    # generate liststore where is current working dir files and directorys in ftp server 
    # if update is True it creates new treeview
    # else just update it
    def listFtp(self, update=True):
        if update == False:
            self.ftp_files = []
            self.store_ftp = gtk.ListStore(str)
            self.ftp.retrlines('LIST', self.ftpFilesCallback)

            for s in self.ftp_files:
                self.store_ftp.append(["%s" % s]) #data

            self.view_ftp = gtk.TreeView(self.store_ftp)
            self.view_ftp.add_events(gtk.gdk.BUTTON_PRESS_MASK)
            self.view_ftp.connect("button-press-event", self.actionFtp)

            self.ftp_col = gtk.TreeViewColumn("ftp")
            self.view_ftp.append_column(self.ftp_col)
            self.ftp_cell = gtk.CellRendererText()
            self.ftp_col.pack_start(self.ftp_cell)
            self.ftp_col.add_attribute(self.ftp_cell, 'text', 0)

            self.scroll_ftp = gtk.ScrolledWindow()
            self.scroll_ftp.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_AUTOMATIC)
            self.scroll_ftp.add(self.view_ftp)

            self.hbox.pack_start(self.scroll_ftp, True, True, 2)

        elif update == True:
            self.ftp_files = [] # empty list for the files of the new folder
            self.ftp_files.insert(0,"..")
            self.ftp.retrlines('LIST', self.ftpFilesCallback)
            self.store_ftp.clear()
            for s in self.ftp_files:
                self.store_ftp.append(["%s" % s]) # data

    # generates list of files in current working dir
    def ftpFilesCallback(self, line):
        split = line.split(None, 8)
        self.ftp_files.append(split[8])

    # returns row name (str) which is selected
    def getSelection(self, source): #source = "local" or "ftp"
        if source == "local":
            treeselection = self.view_local.get_selection()
            (model, iter) = treeselection.get_selected()
            self.data = self.store_local.get_value(iter, 0)
        elif source == "ftp":
            treeselection = self.view_ftp.get_selection()
            (model, iter) = treeselection.get_selected()
            self.data = self.store_ftp.get_value(iter, 0)

        return self.data

    # notice if listLocal got click
    def actionLocal(self, widget, event):
        if event.type == gtk.gdk._2BUTTON_PRESS:
            data = self.getSelection("local")
            if data == "..": # parent directory
                os.chdir("..")
                self.listLocal() #refresh
            else:
                pbackup = os.getcwd() #path backup
                try:
                    p = os.getcwd()+"/"+data
                    os.chdir(p)
                    self.listLocal() #refresh

                except NameError:
                    print "Not directory"
                    os.chdir(pbackup)

        elif event.type == gtk.gdk.BUTTON_PRESS and event.button == 3:
            popmenu_items = {"Remove": self.removeLocal, "Refresh": self.refreshLocal} #menuitems (Name, action)
            self.listPopMenu(popmenu_items, event.button)

    # notice if listFtp got click
    def actionFtp(self, widget, event):
        if event.type == gtk.gdk._2BUTTON_PRESS:
            data = self.getSelection("ftp")
            if data == "..": # parent directory
                p = self.ftp.pwd().rfind("/")
                if p == 0:
                    self.ftp.cwd("/")
                else:
                    self.ftp.cwd(self.ftp.pwd()[:p])
                self.listFtp() #refresh

            else:
                try:
                    p = self.ftp.pwd()+"/"+data
                    self.ftp.cwd(p)
                    self.listFtp() #refresh

                except ftplib.error_perm:
                    print "Not directory"

        elif event.type == gtk.gdk.BUTTON_PRESS and event.button == 3:
            popmenu_items = {"Remove": self.removeFtp, "New dir": self.newDir, "Refresh": self.refreshFtp} #menuitems (Name, action)
            self.listPopMenu(popmenu_items, event.button)

    # local funcs
    def putFile(self, event):
        try:
            data = self.getSelection("local")
            file = open(os.getcwd()+"/"+data, 'rb')
            self.ftp.storbinary("STOR "+data, file)
            file.close()
            self.listFtp() #refresh

        except IOError:
            print data+" is directory"

    def removeLocal(self, event):
        selection = self.getSelection("local")
        #file
        try:
            os.remove(selection)
            self.listLocal() #refresh

        #dir
        except:
            os.rmdir(selection)
            self.listLocal() #refresh

    def refreshLocal(self, event):
        self.listLocal() #refresh

    # ftp funcs
    def getFile(self, event):
        data = self.getSelection("ftp")
        outfile = file(data, 'w+b')
        self.ftp.retrbinary("RETR "+data, outfile.write)
        self.listLocal() #refresh

    def removeFtp(self, event):
        selection = self.getSelection("ftp")
        #file
        try:
            self.ftp.delete(selection)
            self.listFtp() #refresh

        #dir
        except:
            self.ftp.rmd(selection)
            self.listFtp() #refresh

    # create new directory to FTP server
    # first open dialog window 
    def newDir(self, event, id=None, action="dialog"):
        if action == "dialog":
            self.ndd = gtk.Dialog("New directory")
            self.nde = gtk.Entry()
            self.ndd.add_action_widget(self.nde, 0)
            self.ndd.add_button("Create", 1)
            self.ndd.show_all()
            self.ndd.connect("response", self.newDir, "create")

        elif action == "create":
            try:
                dirname = self.nde.get_text()
                self.ftp.mkd(dirname)
                self.ndd.destroy()
                self.listFtp() #refresh
            except:
                print "close"

    def refreshFtp(self, event):
        self.listFtp() #refresh

    # Generates gtk.Menu content
    # menu = gtk.Menu() object 
    # menu_items_dic is dictionary where key is menu item name (str) and value is callback function (def)
    def menuItemsAdd(self, menu, menu_items_dic):
        for item in menu_items_dic.keys():
                menu_item = gtk.MenuItem(item)
                menu_item.connect("activate", menu_items_dic[item])
                menu.append(menu_item)
                menu_item.show()

    # Generates popupmenu content when you click listLocal or listFtp with button 3 (right button)
    # items is dictionary where key is menu item name (str) and value is callback function (def)
    def listPopMenu(self, items, button):
        self.popmenu = gtk.Menu()
        self.menuItemsAdd(self.popmenu, items)
        self.popmenu.popup(None, None, None, button, 0, None)

    #login to the ftp server and creates listFtp and listLocal liststores
    def loginFTP(self, widget):
        #when login ftp failed, if you continued to visit it
        #it should delete the notify in the under of vbox_login
        if hasattr(self, 'no_perm'):
            self.vbox_login.remove(self.no_perm)
            del self.no_perm
        if hasattr(self, 'temp'):
            self.vbox_login.remove(self.temp)
            del self.temp
        try:
            self.ftp = ftplib.FTP()
            self.ftp.connect(self.login_host.get_text(), self.login_port.get_text())
            print "connected host: %s" % self.login_host.get_text()
            self.ftp.login(self.login_name.get_text(),self.login_pw.get_text())
            print "logged user: %s" % self.login_name.get_text()

            self.window.resize(600, 400)

            self.vbox_logged = gtk.VBox()
            self.window.remove(self.vbox_login)
            self.window.add(self.vbox_logged)
            
            self.vbox_login.remove(self.menu_bar)
#            self.menu_bar.prepend(self.root_menu)
            self.vbox_logged.pack_start(self.menu_bar, False, False, 2)

            put_img = gtk.image_new_from_stock(gtk.STOCK_GO_FORWARD, gtk.ICON_SIZE_MENU)
            get_img = gtk.image_new_from_stock(gtk.STOCK_GO_BACK, gtk.ICON_SIZE_MENU)
            quit_img = gtk.image_new_from_stock(gtk.STOCK_QUIT, gtk.ICON_SIZE_MENU)

            put_but = gtk.ToolButton(put_img, "Put")
            put_but.connect("clicked", self.putFile)
            get_but = gtk.ToolButton(get_img, "Get")
            get_but.connect("clicked", self.getFile)
            quit_but = gtk.ToolButton(quit_img, "Quit")
            quit_but.connect("clicked", self.kill)

            self.actions = gtk.Toolbar()
            self.actions.set_orientation(gtk.ORIENTATION_VERTICAL)
            self.actions.set_style(gtk.TOOLBAR_ICONS)
            putitem = self.actions.insert(put_but, -1)
            getitem = self.actions.insert(get_but, -1)
            quititem = self.actions.insert(quit_but, -1)

            self.hbox = gtk.HBox()

            self.listLocal(False) #create list
            self.hbox.pack_start(self.actions, False, False) # get and put buttons
            self.listFtp(False) #create list

            self.vbox_logged.pack_start(self.hbox)
            
            self.menu_bar.show_all()
            self.actions.show_all()
            self.hbox.show_all()
            put_img.show()
            get_img.show()
            quit_img.show()
            self.vbox_logged.show_all()
        
        except socket.error:
            self.temp = gtk.Label('Cannot connect to server!')
            self.vbox_login.pack_start(self.temp)
            self.vbox_login.show_all()
            print 'cannot connect to server!'
            
        except ftplib.error_perm:
            self.no_perm = gtk.Label("Wrong username or password, try again.")
            self.vbox_login.pack_start(self.no_perm)
            self.vbox_login.show_all()
            print "wrong username or password"

    # logout from ftp server and reshow login entrys
    def logoutFTP(self, event):
        self.ftp.close()
        self.vbox_logged.remove(self.menu_bar)
        self.window.remove(self.vbox_logged)
        self.vbox_login.pack_start(self.menu_bar)
        self.vbox_login.reorder_child(self.menu_bar, gtk.PACK_START)
        self.window.add(self.vbox_login)
        self.window.resize(200, 100)
        self.vbox_login.show_all()
    
    # kill program and logout if connection is still open
    def kill(self, event):
        if bool(self.ftp) == True:
            self.ftp.close()
            gtk.main_quit()
            print "logout & quit"
        else:
            gtk.main_quit()
            print "quit"
   
    def main(self):
        gtk.main()

miniFTP().main() 