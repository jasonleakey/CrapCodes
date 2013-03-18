#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :  redirect_by_popen.py
#  Establishment date:  2009-2-21
#  Author            :  jasonleakey
#  Module Function   :  to emulate pipe in shell by using popen()
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

(MAX_BUF_SIZE) = (200)

def main():
    #determine there are enough arguments
    argc = len(sys.argv)
    if argc != 3:
        print 'Usage:%s command1 command2' % sys.argv[0]
        return 1
    
    try:
        #create two singlex pipes to make a duplexing pipe
        stream_in = os.popen(sys.argv[1], 'r')
        stream_out = os.popen(sys.argv[2], 'w')
    except OSError, e:
        print 'cannot create pipes:%s' % e
        return 1
    else:
        #flush standart output buffer
        sys.stdout.flush()
        
        try:
            #read data from stream_in put by sys.argv[1]
            buf = os.read(stream_in.fileno(), MAX_BUF_SIZE)
        except OSError, e:
            print 'read data Error:%s' % e
            return 1
        else:
            try:
                #write data into stream out for sys.argv[2]
                os.write(stream_out.fileno(), buf)
            except OSError, e:
                print 'Write data Error:%s' % e
        #close two pipes
        stream_in.close()
        stream_in.close()

if __name__ == '__main__':
    main()
        