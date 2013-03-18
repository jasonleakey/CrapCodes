#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :  FIFO_by_mkfifl.py
#  Establishment date:  2009-2-21
#  Author            :  jasonleakey
#  Module Function   :  invoke mkfifo to create a FIFO(a named pipe)
#                        and achieve communication between processes by it
#  Copyright (R) 2009jasonleakey
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

import os
import sys

(FIFO_NAME) = ('/home/jasonleakey/b.pipe')
(MESSAGE) = ('Hello World')

def main():
    #determine if there is enough arguments
    argc = len(sys.argv)
    if argc != 2:
        print 'Usage: %s 1(read)/2(write)' % sys.argv[0]
        return 1
    
    #read data from FIFO
    if sys.argv[1] == '1':
        #determine if fifo file exists
        if not os.path.exists(FIFO_NAME):
            print 'No such FIFO file!'
            return 1
        
        try:
            #open FIFO file
            file_obj = open(FIFO_NAME, 'r')
        except IOError, e:
            print 'cannot open fifo file:%s' % e
            return 1
        else:
            print 'PID:%d receive message:' % os.getpid()
            #read data from FIFO
            for line in file_obj:
                print line
            #close the file
            file_obj.close()
            #read over, remove the named pipe
            os.unlink(FIFO_NAME)
            
    if sys.argv[1] == '2':
        try:
            #create a named pipe
            os.mkfifo(FIFO_NAME, 0777)
        except OSError, e:
            print 'cannot create FIFO:%s' % e
            return 1
        else:
            try:
                #open the FIFO with write mode
                file_obj = open(FIFO_NAME, 'w')
            except IOError, e:
                print 'cannot open pipe:%s' % e
                return 1
            else:
                #write data to FIFO
                try:
                    file_obj.write(MESSAGE + '\n')
                except IOError, e:
                    print 'cannot write data:%s' % e
                    return 1
                else:
                    print 'PID:%d send message:%s'\
                        % (os.getpid(), MESSAGE)
                finally:
                    file_obj.close()

if __name__ == '__main__':
    main()
    