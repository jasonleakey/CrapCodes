#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Sep 10, 2009
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
#  miniGRE.py: mini program to help you recite GRE more efficiently

import os
import ctypes
import sys
import time
import gobject
import random
import pygtk
pygtk.require('2.0')
import gtk
#class InfoDialog(gtk.MessageDialog):
#    def __init__(self):
#        super(InfoDialog, self).__init__(self, )

SYS_NAME = os.name
WORD_CNT_EVERYDAY = 300 # max word count needed recited everyday

class GRE():
    def __init__(self):
        self.builder = gtk.Builder()
        try:
            gladefile = os.path.join(
                        unicode(os.path.dirname(os.path.realpath(__file__)),\
                                '%s' % ('GB2312' if SYS_NAME == 'nt' else 'utf-8')),
                        'data',
                        'reciteGRE.glade')
            #gladefile = unicode(gladefile, 'utf8')
            self.builder.add_from_file(gladefile)
        except IOError, e:
            print 'Not found reciteGRE.glade file, determine you deleted it?',
            for i in range(3):
                time.sleep(1)
                print '.',
            print 'program exit!'
            sys.exit(1)
        self.builder.connect_signals(self)
        
        self.mainWnd = self.builder.get_object('mainwindow')
        self.wordEntry = self.builder.get_object('wordEntry')
        self.nextBut = self.builder.get_object('nxtBut')
        self.showsavedelBox = self.builder.get_object('showsavedelBox')
        self.selectVBox = self.builder.get_object('selectVBox')
        self.playBut = self.builder.get_object('playButton')
        self.showBut = self.builder.get_object('showTransBut')
        self.fstBut = self.builder.get_object('fstBut')
        self.intervalEntry = self.builder.get_object('intervalEntry')
        self.transTextView = self.builder.get_object('transTextView')
        self.statusBar = self.builder.get_object('statusBar')
        self.contextID = self.statusBar.get_context_id('status bar')
        self.infoDlg = self.builder.get_object('infodialog')
        self.dateComBox = self.builder.get_object('dateComBox')
        self.dateList = self.builder.get_object('dateList')
        self.aboutDlg = self.builder.get_object('aboutDialog')
        self.autoRadioButton = self.builder.get_object('autoRadioButton')
        self.manRadioButton = self.builder.get_object('manRadioButton')
        self.manBox = self.builder.get_object('manBox')
        self.autoBox = self.builder.get_object('autoBox')
        self.questDlg = self.builder.get_object('questionDialog')
        self.statusIcon = self.builder.get_object('statusIcon')
        self.saveBut = self.builder.get_object('saveBut')
        self.delBut = self.builder.get_object('delBut')
        self.helpWnd = self.builder.get_object('helpPopUpWindow')
        self.textBuf = self.builder.get_object('textBuf')
        self.texttagtable = self.builder.get_object('texttagtable')
#        self.texttag = self.builder.get_object('textTag')
        self.tag = self.textBuf.create_tag(font = 'SimSun 18')
        self.textBuf.apply_tag(self.tag, self.textBuf.get_start_iter(), self.textBuf.get_end_iter())
        
        # date list
        cell = gtk.CellRendererText()
        self.dateComBox.pack_start(cell, True)
        self.dateComBox.add_attribute(cell, 'text', 0)
        
        self.wordlist = WordList()
        self.wordlist.create_today_wordfile() # create a word library file for today.
        self.allWordsList = WordList()
        self.allWordsList.get_allwords()
        
        self.update_date_list()
    
        self.mainWnd.show_all()
    

    
    def set_current_word(self, index = 0):
        self.wordEntry.set_text(self.wordlist[index][0])
#        self.indexLabel.set_label('单词数：%d  当前序号：%d' % (self.wordlistLen, index))
        
    def on_aboutBut_clicked(self, widget):
        self.aboutDlg.run()
        self.aboutDlg.hide()
        
    def on_readBut_clicked(self, widget):
        random.seed() # seed for pseudo-random integer
        listStore = self.dateComBox.get_model() 
        
        
        # read the word list according to date shown in the active item of comboBox
        # if there is no word list, -1 is returned. 
        if self.dateComBox.get_active() == -1:
            return False
        
        self.selectVBox.set_sensitive(True)
        self.showsavedelBox.set_sensitive(True)
        if listStore[self.dateComBox.get_active()][0] == 'user_defined_list':
            if not self.__is_empty_dat_file(listStore[self.dateComBox.get_active()][0]):
                self.saveBut.set_sensitive(False)
                self.delBut.set_sensitive(True)
            else:
                self.show_info_dialog('No word in user defined list')
                return False
        else:
            self.saveBut.set_sensitive(True)
            self.delBut.set_sensitive(False)
            
        self.wordlist.get_wordlist_from_filename(listStore[self.dateComBox.get_active()][0]) 
        self.wordlistLen = len(self.wordlist)
        self.idx = 0 # the sequence of current word in the list
        self.set_current_word(0)
        self.show_message_in_statusbar('Word Amount：%d  Current Sequence：%d' % (self.wordlistLen, self.idx))
        self.__clean_textview()
        
    def on_fstBut_clicked(self, widget):
        if not self.__if_wordlist_loaded():
            return False
        self.idx = 0
        self.set_current_word(self.idx)
        self.show_message_in_statusbar('Word Amount：%d  Current Sequence：%d' % (self.wordlistLen, self.idx))
        self.textBuf.delete(self.textBuf.get_start_iter(), self.textBuf.get_end_iter())
        self.__clean_textview()
    
    def on_preBut_clicked(self, widget):
        if not self.__if_wordlist_loaded():
            return False
        if self.idx > 0:
            self.idx -= 1
            self.set_current_word(self.idx)
        self.show_message_in_statusbar('Word Amount：%d  Current Sequence：%d' % (self.wordlistLen, self.idx))
        self.textBuf.delete(self.textBuf.get_start_iter(), self.textBuf.get_end_iter())
        self.__clean_textview()
        
    def on_nxtBut_clicked(self, widget):
        if not self.__if_wordlist_loaded():
            return False
        if self.idx < len(self.wordlist) - 1:
            self.idx += 1
            self.set_current_word(self.idx)
        self.show_message_in_statusbar('Word Amount：%d  Current Sequence：%d' % (self.wordlistLen, self.idx))
        self.textBuf.delete(self.textBuf.get_start_iter(), self.textBuf.get_end_iter())
        self.__clean_textview()
        
    def on_lstBut_clicked(self, widget):
        if not self.__if_wordlist_loaded():
            return False
        self.idx = len(self.wordlist) - 1
        self.set_current_word(self.idx)
        self.show_message_in_statusbar('Word Amount：%d  Current Sequence：%d' % (self.wordlistLen, self.idx))
        self.textBuf.delete(self.textBuf.get_start_iter(), self.textBuf.get_end_iter())
        self.__clean_textview()
        
    def on_rdmBut_clicked(self, widget):
        if not self.__if_wordlist_loaded():
            return False
        self.idx = random.randint(0, len(self.wordlist) - 1)
        self.set_current_word(self.idx)
        self.show_message_in_statusbar('Word Amount：%d  Current Sequence：%d' % (self.wordlistLen, self.idx))
        self.textBuf.delete(self.textBuf.get_start_iter(), self.textBuf.get_end_iter())
        self.__clean_textview()
        
    def on_showTransBut_clicked(self, widget):
        if not self.__if_wordlist_loaded():
            return False
#        meanings = self.wordlist[self.idx][1].split('；')
#        # notice the using enumerate()
#        meanings = ['%d. ' % (i + 1) + mean for i, mean in enumerate(meanings)]
        self.textBuf.set_text(self.wordlist[self.idx][1])
        self.textBuf.apply_tag(self.tag, self.textBuf.get_start_iter(), self.textBuf.get_end_iter())
        
    def on_saveBut_clicked(self, widget):
        if not self.__if_wordlist_loaded():
            return False
        userDefinedFile = os.path.join(
                            unicode(os.path.dirname(os.path.realpath(__file__)),\
                                    '%s' % ('GB2312' if SYS_NAME == 'nt' else 'utf-8')),
                            'save',
                            'user_defined_list.dat')
        try:
            udStream = open(userDefinedFile, 'a+')
            words = [word.rstrip('\r\n').split()[0] for word in udStream if word.rstrip('\r\n') != '']
            if self.wordlist[self.idx][0] not in words:
                line = ' '.join(self.wordlist[self.idx]) + '\r\n'
                udStream.writelines(line)
                self.show_info_dialog('%s saved!' % self.wordlist[self.idx][0])
            else:
                self.show_info_dialog('%s has already in the user defined list!' % self.wordlist[self.idx][0])
        finally:
            udStream.close()
    
    def on_delBut_clicked(self, widget):
        if not self.__if_wordlist_loaded():
            return False
        userDefinedFile = os.path.join(
                            unicode(os.path.dirname(os.path.realpath(__file__)),\
                                    '%s' % ('GB2312' if SYS_NAME == 'nt' else 'utf-8')),
                            'save',
                            'user_defined_list.dat')
        try:
            udStream = open(userDefinedFile, 'r+')
            words = [word.rstrip('\r\n').split() for word in udStream if word.rstrip('\r\n') != '']
            searchWord = list(self.wordlist[self.idx])
            if searchWord in words:
                words.remove(searchWord)
                line = [' '.join(word) + '\r\n' for word in words]
                # clear the old file and renew it.
                udStream.seek(0)
                udStream.truncate()
                udStream.writelines(line)
                self.show_info_dialog('%s deleted!' % self.wordlist[self.idx][0])
                self.wordlist.pop(self.idx)
                self.wordlistLen -= 1
                self.show_message_in_statusbar('Word Amount：%d  Current Sequence：%d'\
                                               % (self.wordlistLen, self.idx))
                if self.wordlistLen == 0:
                    self.wordEntry.set_text('')
                else:
                    self.idx -= 1
                    self.nextBut.clicked()
        finally:
            udStream.close()
            
    def on_RadioButton_toggled(self, widget):
        if widget is self.autoRadioButton:
            self.manBox.set_sensitive(False)
            self.autoBox.set_sensitive(True)
        else:
            self.manBox.set_sensitive(True)
            self.autoBox.set_sensitive(False)
            
    def on_intervalEntry_insert_at_cursor(self, widget, string):
        if string.isdigit():
            self.intervalEntry.set_text(string)
            
    def on_playButton_clicked(self, widget):
        if self.intervalEntry.get_text() == '':
            self.show_info_dialog('Please Input interval time!')
        else:
            if self.playBut.get_label() == 'gtk-media-play':
                interval = int(self.intervalEntry.get_text())
#                myThread = threading.Thread(target = self.__play_words, args = (interval,))
                self.source_id = gobject.timeout_add_seconds(interval, self.__play_words, interval)
#                myThread.start()
                self.playBut.set_label('gtk-media-pause')
#                gobject.idle_add(self.__play_words, interval)
#                while True:
#                    self.__play_words(interval)
#                    if self.idx == len(self.wordlist) - 1:
#                        self.idx = 0
            else:
                self.playBut.set_label('gtk-media-play')
                gobject.source_remove(self.source_id)
                
    def on_wordEntry_activate(self, widget):
        searchWord = self.wordEntry.get_text()
        allwords = [word[0] for word in self.allWordsList]
        try:
            index = allwords.index(searchWord)
            self.textBuf.set_text(self.allWordsList[index][1])
        except ValueError:
            self.textBuf.set_text('Not found meaning for "%s"' % searchWord)
        finally:
            self.textBuf.apply_tag(self.tag, self.textBuf.get_start_iter(), self.textBuf.get_end_iter())
    def on_helpBut_clicked(self, widget):
        self.helpWnd.show_all()
    
    def on_helpPopUpWindow_button_press_event(self, widget, event):
        self.helpWnd.hide_all()
    
    def __play_words(self, interval):
        if self.idx == len(self.wordlist) - 1:
            self.idx = -1
        self.nextBut.clicked()
        gobject.timeout_add(int(interval) * 500, self.showBut.clicked)
        return True

    def __clean_textview(self):
        self.textBuf.delete(self.textBuf.get_start_iter(), self.textBuf.get_end_iter())

    def __if_wordlist_loaded(self):
        if not hasattr(self, 'idx'):
            self.show_info_dialog('No word list loaded!')
            return False
        return True
        
    def show_info_dialog(self, message = 'nothing'):
        self.infoDlg.set_title('information')
        self.infoDlg.set_markup('<big><b>' + message + '</b></big>')
#        self.infoDlg.show_all()
        self.infoDlg.run()
        self.infoDlg.hide()
        
#    def show_question_dialog(self, message = 'nothing'):
#        self.questDlg.set_title('Question')
#        self.questDlg.set_markup('<big><b>' + message + '</b></big>')
#        self.questDlg.run()

    def show_message_in_statusbar(self, message = ''):
        self.statusBar.push(self.contextID, message)

    def update_date_list(self):
        self.dateList.clear()
        dateFileNames = os.listdir(os.path.join(
                                unicode(os.path.dirname(os.path.realpath(__file__)),\
                                        '%s' % ('GB2312' if SYS_NAME == 'nt' else 'utf-8')),
                                'save'))
        
        dateFileNames.sort()
        length = len(dateFileNames)
        # preserve the word lists in the past 15 days, and discard the preceded.
        if length > 17:
            for i in range(length - 17):
                dateFileNames.pop(i)
                print dateFileNames[i].split('_')[:]
            dateFileNames.sort()

        for filename in dateFileNames:
            if filename.endswith('.dat') and filename != 'GRE.dat':
                self.dateList.append([filename.split('.')[0]])
        
        self.dateComBox.set_active(len(self.dateList) - 2\
                                   if len(self.dateList) > 1 else len(self.dateList) - 1)
    
    def on_statusIcon_activate(self, widget):
        self.mainWnd.show_all()
        
    def __is_empty_dat_file(self, datname):
        filename = os.path.join(unicode(os.path.dirname(os.path.realpath(__file__)),\
                                        '%s' % ('GB2312' if SYS_NAME == 'nt' else 'utf-8')),
                            'save',
                            datname + '.dat')
        return True if os.stat(filename).st_size == 0 else False
        
    def gtk_main_quit(self, widget, data = None):
        gtk.main_quit()

class WordList():
    def __init__(self):
        self.wordList = [] # format: (word, translation)
        
    def get_wordlist_from_filename(self, dat_file):
        if not dat_file:
            self.infoDlg.set_title('invalid date')
            self.infoDlg.set_markup('<big><b>None date is selected!</b></big>')
        filename = os.path.join(unicode(os.path.dirname(os.path.realpath(__file__)),\
                                        '%s' % ('GB2312' if SYS_NAME == 'nt' else 'utf-8')),
                            'save',
                            dat_file + '.dat')
        self.wordList = []
        try:
            wordStream = open(filename)
            for line in wordStream:
                line = line.rstrip('\r\n')
                if line is not '':
                    [key, value] = line.split()
                    self.wordList.append((key, value))
        finally:    
            wordStream.close()
        return self.wordList
    
    def __extract_words_from_GRELib(self):
        '''extract three hundred words from the GRE lib'''
        GREfilename = os.path.join(unicode(os.path.dirname(os.path.realpath(__file__)),\
                                           '%s' % ('GB2312' if SYS_NAME == 'nt' else 'utf-8')),
                            'save',
                            'GRE.dat')
        extractWords = []
        try:
            GREstream = open(GREfilename, 'r')
            ttlWords = []
            n = 0
            for line in GREstream:
                line.rstrip('\r\n')
                if line != '':
                    n += 1
                    [key, value] = line.split()
                    ttlWords.append((key, value))
            ttlWordCnt = len(ttlWords)
            for i in range(WORD_CNT_EVERYDAY):
                extractWords.append(ttlWords[random.randint(0, ttlWordCnt)])
        finally:
            GREstream.close()
        return extractWords
                
    def create_today_wordfile(self):
        curDateStructure = time.gmtime(time.time())
        curDateStr = str(curDateStructure.tm_year)\
                        + '_' + str(curDateStructure.tm_mon)\
                        + '_' + str(curDateStructure.tm_mday)
        path = os.path.join(unicode(os.path.dirname(os.path.realpath(__file__)),\
                                    '%s' % ('GB2312' if SYS_NAME == 'nt' else 'utf-8')),
                            'save',
                            curDateStr + '.dat')
#        print 'size=%ld' % os.stat(path).st_size
        if os.path.exists(path) and os.stat(path).st_size != 0:
            return True 
        try:
            todayStream = open(path, 'w')
            extractWords = self.__extract_words_from_GRELib()
            lines = [' '.join(extractWords[i]) + '\r\n' for i in range(len(extractWords))]
#            for i in range(len(extractWords)):
#                lines.append(' '.join(extractWords[i]) + '\r\n')
            todayStream.writelines(lines)
        except IOError, e:
            print '%s' % e
        finally:
            todayStream.close()
            
    def get_allwords(self):
        return self.get_wordlist_from_filename('GRE')
            
    def __len__(self):
        return len(self.wordList)
    
    def pop(self, index):
        return self.wordList.pop(index)
    
    def __getitem__(self, key):
        return self.wordList[key]

def set_process_name(process_name):
    libc = ctypes.CDLL('libc.so.6')
    libc.prctl(15, '%s' % process_name, 0, 0, 0)
    
if __name__ == '__main__':
    if SYS_NAME == 'posix':
        set_process_name('miniGRE')
    print SYS_NAME
    GRE()
    gtk.main()
