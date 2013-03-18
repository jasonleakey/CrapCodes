#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :  pipe_duplexing.py
#  Establishment date:  2009-2-20
#  Author            :  jasonleakey
#  Module Function   :  process communication by duplexing with pipe
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

(MAX_BUF_SIZE) = (50) 

def main():
    '''Create two pipes for process and subprocess communication
    one of which for reading, and the other for writing
    '''
    #determine if there are enough arguments
    argc = len(sys.argv)
    if argc != 3:
        print 'Usage: %s message_prt2chld message_chld2prt' % sys.argv[0]
        return 1
    
    try:
        #create two pipes
        #fd1: transfer data from parent process to subprocess
        #fd2: transfer data from subprocess to parent process
        (fd1_r, fd1_w) = os.pipe()
        (fd2_r, fd2_w) = os.pipe()
    except OSError, e:
        print 'Create pipe Error:%s' % e
        return 1
    else:
        try:
            #create a subprocess
            pid = os.fork()
        except OSError, e:
            print 'create subprocess Error:%s' % e
        else:
            if pid == 0:
                #in the subprocess
                sub_pid = os.getpid()
                
                os.close(fd1_w)
                os.close(fd2_r)
                try:
                    #write data into fd2
                    os.write(fd2_w, sys.argv[2])
                except OSError, e:
                    print 'Write message Error:%s' % e
                    return 1
                else:
                    print 'Child PID:%d send message:%s'\
                        % (sub_pid, sys.argv[2])
                try:
                    #wait for parent process writing message
                    time.sleep(0.3)
                    buffer = os.read(fd1_r, MAX_BUF_SIZE)
                except OSError, e:
                    print 'Subprocess Read message Error:%s' % e
                    return 1
                else:
                    print 'Child PID:%d receive message:%s'\
                        % (sub_pid, buffer)
                os._exit(0)
        
            else:
                # in the parent process
                prtpid = os.getpid() #parent PID
                
                os.close(fd1_r)
                os.close(fd2_w)
                try:
                    # write message into fd1
                    os.write(fd1_w, sys.argv[1])
                except OSError, e:
                    print 'Parent Process Write Message Error:%s' % e
                    return 1
                else:
                    print 'Parent PID:%d send message:%s'\
                        % (prtpid, sys.argv[1])
                try:
                    # read message from fd2
                    time.sleep(0.3)
                    buffer = os.read(fd2_r, MAX_BUF_SIZE)
                except OSError, e:
                    print ' Parent Process Read Message Error:%s' % e
                    return 1
                else:
                    print 'Parent PID:%d receive message:%s'\
                        % (prtpid, buffer)
                
                try:
                    #wait subprocess exiting
                    wait_stat = os.wait()
                except OSError, e:
                    print 'invoke wait() Error:%s' % e
                    return 1
                else:
                    print 'subprocess PID:%d exits with code %d'\
                        % wait_stat

if __name__ == '__main__':
    main()
                