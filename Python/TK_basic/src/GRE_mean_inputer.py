#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Sep 15, 2009
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
#  GRE_mean_inputer.py: function

import os

class ChineseInput():
    def __init__(self):
        enFileName = os.path.dirname(os.path.realpath(__file__)) + '/save/' + 'GRE.dat'
        cnFileName = os.path.dirname(os.path.realpath(__file__)) + '/save/' + 'GRE_cn.dat'
        try:
            enStream = open(enFileName, 'r')
            cnStream = open(cnFileName, 'a')
            for line in enStream:
                
                line = line.rstrip('\r\n')
                    if line is not '':
                        wordlist[line] = raw_input(line + ':')
                        wordfileStream.writelines([line + ' ' + wordlist[line]])
                else:
                    wordfileStream.writelines([line])
        except KeyboardInterrupt, e:
            print 'KeyboardInterrupt:%s' % e
        finally:
            wordfileStream.close()
            
if __name__ == '__main__':
    ChineseInput()