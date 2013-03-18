#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Establishment date:  Jun 11, 2009
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
#  tit2txt: transform tit files to txt files MATLAB can load

import os
import os.path


class Transform:
    def __init__(self):
        try:
            cwd = raw_input('Input directory path including .tit files:')
        except EOFError, e:
            print 'Program is interrupt by CTRL+D:%s' % e
            return False
        
        if not os.path.exists(cwd):
            print 'No such Directory:%s' % cwd
            return False
        
        # get file names in current directory
        os.chdir(cwd)
        tit_files = []
        files = os.listdir(cwd)
        for file in files:
            if file.endswith('.tit'):
                tit_files.append(file)
        
        #sort .tit list
        tit_files.sort()
        
        # for each tit file, transform it to txt
        for file in tit_files:
            self.tit2txt(file)
            
        #create a turn angle txt file to record 'alpha beta gamma' info
        txt_files = []
        files = os.listdir(cwd)
        for file in files:
            if file.endswith('.txt'):
                txt_files.append(file)
        self.record_alpha_beta_gamma_txt(txt_files)
    
    def tit2txt(self, titFileName):
        ''' transform .tit to .txt'''
        ''' titFileName: tit file name'''
        global count
        count = count + 1
        
        try:
            titStream = open(titFileName, 'r')
        except IOError, e:
            print 'cannot open %s:%s' % [titFileName, e]
            return False
        
        lines = titStream.readlines()
        lines[0] = lines[0].rstrip() 
        alpha_beta_gamma = lines[0].split('-')
        if alpha_beta_gamma == ['']:
            titStream.close()
            return False
        
        print 'count = %d' % count
        
        if alpha_beta_gamma[0] == '00':
            alpha_beta_gamma[0] = '0'
        if alpha_beta_gamma[1] == '00':
            alpha_beta_gamma[1] = '0'
        
        txtFileName = 'J' + '-'.join(alpha_beta_gamma) + '.txt'
        try:
            txtStream = open(txtFileName, 'w')
        except IOError, e:
            print 'cannot create %s:%s' % [txtFileName, e]
            titStream.close()
            return False
        
        for i in range(7, 704):
            element = lines[i].split(';')
            (wave, irr) = (element[0], element[4])
            try:
                txtStream.writelines([wave + ' ' + irr + '\r\n'])
            except IOError, e:
                print 'cannot write data to %s:%s' % [txtFileName, e]
                titStream.close()
                txtStream.close()
                return False
        titStream.close()
        txtStream.close()
        
        
    def record_alpha_beta_gamma_txt(self, txt_file_seq):
        angleFileName = 'turnAngle.txt'
        try:
            angleStream = open(angleFileName, 'w')
        except IOError, e:
            print 'cannot create %s:%s' % [angleFileName, e]
            return -1
        
        for anglestr in txt_file_seq:
            anglestr = anglestr.strip('.txtJ')
            alpha_beta_gamma = anglestr.split('-')
            if len(alpha_beta_gamma) == 3:
                alpha_beta_gamma = ' '.join(alpha_beta_gamma)
                alpha_beta_gamma = alpha_beta_gamma + '\r\n'
                angleStream.writelines(alpha_beta_gamma)
                    
        angleStream.close()

if __name__ == '__main__':
    count = 1
    Transform()
    