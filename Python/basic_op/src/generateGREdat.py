#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Sep 25, 2009
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
#  filename: function

import os



class WordList():
    def __init__(self):
        self.wordList = [] # format: (word, translation)
        
    def save_wordlist_to_file(self, dat_name):
        filename = '/home/jasonleakey/' + dat_name + '~.dat'
        try:
            wordStream = open(filename, 'w')
            wordStream.writelines([word + ' ' + trans + '\r\n' for word, trans in self.wordList])
        finally:
            wordStream.close()
        print 'create new file done!'
        
        
    def get_wordlist_from_filename(self, dat_file):
        filename = dat_file
        self.wordList = []
        try:
            wordStream = open(filename)
            n = 0
            for line in wordStream:
                line = line.strip(' \r\n')
                if line is not '':
                    n += 1
                    strings = line.split()
                    key = strings[0]
                    value = ''.join(strings[1:])
                    self.wordList.append((key, value))
                    print n 
        finally:    
            wordStream.close()
        return self.wordList
    
    def __extract_words_from_GRELib(self):
        '''extract three hundred words from the GRE lib'''
        GREfilename = os.path.dirname(os.path.realpath(__file__)) + '/save/' + 'GRE.dat'
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
        path = os.path.dirname(os.path.realpath(__file__)) + '/save/' + curDateStr + '.dat'
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
    
    def __getitem__(self, key):
        return self.wordList[key]
    
if __name__ == '__main__':
    wordlist = WordList()
    wordlist.get_wordlist_from_filename('/home/jasonleakey/GRE.dat')
    wordlist.save_wordlist_to_file('newGRE')