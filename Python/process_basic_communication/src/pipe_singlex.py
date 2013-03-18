#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :  pipe_singlex.py
#  Establishment date:  2009-2-19
#  Author            :  jasonleakey
#  Module Function   :  communicate
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

(MAX_PIPE_SIZE) = (30)

def main():
    argc = len(sys.argv)
    if argc != 2:
        print 'Usage: %s Message' % sys.argv[0]
        return 1
    
    try:
        #Create a pipe
        (fd_r, fd_w) = os.pipe()
    except OSError, e:
        print 'Create pipe Error: %s' % e
    else:
        try:
            #Create a child process
            pid = os.fork()
        except OSError, e:
            print 'Create child process Error:%s' % e
            return 1
        else:
            if pid == 0:
                #in the child process
                #Do not write to pipe in the child process
                os.close(fd_w)
                #wait for  parent process writing pipe first
                time.sleep(0.3)
                print 'In the Child Process, receive message:',
                try:
                     bufstr = os.read(fd_r, MAX_PIPE_SIZE)
                except OSError, e:
                     print 'Read Message Error:%s' % e
                     return 1
                else:
                    print bufstr
                os.close(fd_r)
                os._exit(0)
            else:
                #in the parent process
                os.close(fd_r)
                try:
                    print 'In the Parent Process, send message:%s'\
                        % sys.argv[1]
                    os.write(fd_w, sys.argv[1])
                except OSError, e:
                    print 'Write Message Error: %s' % e
                else:
                    try:
                        wait_result = os.wait()
                    except OSError, e:
                        if OSError.errno != 10:
                            print 'Wait Error:%s' % e
                    else:
                        print 'Child PID:%d exit with code %d'\
                            % wait_result
                #close fd_w when over
                os.close(fd_w)

if __name__ == '__main__':
    main()