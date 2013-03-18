#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :  redirect_by_pipe.py
#  Establishment date:  2009-2-20
#  Author            :  jasonleakey
#  Module Function   :  redirect in shell by pipe
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

def main():
    #determine there is enough arguments
    argc = len(sys.argv)
    if argc != 3:
        print 'Usage: %s command1 command2' % sys.argv[0]
        return 1
    
    try:
        #create a pipe
        (fd_r, fd_w) = os.pipe()
        #print 'fd_r = %d' % fd_r, 'fd_w = %d' % fd_w
    except OSError, e:
        print 'create pipe Error:%s' % e
        return 1
    else:
        try:
            #create a subprocess 
            pid = os.fork()
        except OSError, e:
            print 'create subprocess Error:%s' % e
            return 1
        else:
            if pid == 0:
                #in the subprocess
                #redirect stdout to the write port
                try:
                    os.dup2(fd_w, sys.stdout.fileno())
                    #print 'sys.stdout.fileno = %d' % sys.stdout.fileno()
                except OSError, e:
                    print 'dup2 Error:%s' % e
                    return 1
                else:
                    #close the read and write port in subprocess
                    os.close(fd_r)
                    os.close(fd_w)
                    
                    try:
                        #execute command1
                        os.execlp(sys.argv[1], sys.argv[1])
                    except OSError, e:
                        print 'execlp() Error:%s' % e
                        return 1
                
                os._exit(0)
            else:
                #in the parent process
                try:
                    #redirect stdin to the read port
                    os.dup2(fd_r, sys.stdin.fileno())
                    #print 'sys.stdin.fileno = %d' % sys.stdin.fileno()
                except OSError, e:
                    print 'dup2 Error:%s' % e
                else:
                    #close the read and write port in parent process
                    os.close(fd_r)
                    os.close(fd_w)
                    
                    try:
                        #execute command2
                        os.execlp(sys.argv[2], sys.argv[2])
                    except OSError, e:
                        print 'execlp() Error:%s' % e
                        return 1
                sys.exit(0)

if __name__ == '__main__':
    main()
                
                        