#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :    mutex_by_flock.py
#  Establishment date:    2009-2-18
#  Author            :    jasonleakey
#  Module Function   :    invoke flock() to mutex between processes 
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

import sys
import fcntl
import time
import os

def main():
    argc = len(sys.argv)
    if argc != 2:
        print 'Usage: %s lock_file_name' % sys.argv[0]
        return 1
    #alias for file name
    file_name = sys.argv[1]
    
    try:
        fd = open(file_name, 'rw')
    except IOError, e:
        print 'open file Error:%s' % e
        return 1
    else:
        try:
            #try to lock the file
            print repr(fd)
            fcntl.flock(fd, fcntl.LOCK_EX)
        except IOError, e:
            print 'Invoke flock() Error:%s' % e
            return 1
        else:
            cur_pid = os.getpid()
            #output the result
            print 'PID:%d occupy the resource' % cur_pid
            time.sleep(2)
            print 'PID:%d release the resource' % cur_pid
        finally:
            fd.close()
    
    return 0

if __name__ == '__main__':
    main()