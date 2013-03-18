#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :  mutex_by_lockf.py
#  Establishment date:  2009-2-18
#  Author            :  jasonleakey
#  Module Function   :  mutex processes with function lockf()
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
import time
import fcntl

def main():
    argc = len(sys.argv)
    if argc != 2:
        print 'Usage: %s lock_file_lock' % sys.argv[0]
        return 1
    
    file_name = sys.argv[1]
    #open file
    try:
        # On at least some systems, LOCK_EX can only be used
        # if the file descriptor refers to a file opened for
        # writing.

        fd = open(file_name, 'rw') #here you are not allowed to set 'r'
    except IOError, e:
        print 'Open Error:%s' % e
        return 1
    else:
        #try to lock file, if not succeed, then blocked
        #lockf() can lock part of file,while flock() only can lock the whole file
        try:
            #share lock
            lock_result = fcntl.lockf(fd, fcntl.LOCK_SH, 0, 0, 0)
        except IOError, e:
            print 'lockf() Invoke Error:%s' % e
        else:
            current_pid = os.getpid()
            print 'PID:%d occupy the resource!' % current_pid
            time.sleep(2)
            print 'PID:%d release the resource!' % current_pid
        finally:
            fd.close()
    
    return 0

if __name__ == '__main__':
    main()
