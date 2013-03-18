#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :  alarm.py
#  Establishment date:  2009-2-19
#  Author            :  test alarm() function
#  Module Function   :  Module_function
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

import signal
import os
import errno

def main():
    #Create 5 child processes
    for i in range(5):
        try:
            #invoke fork () to create process
            pid = os.fork()
        except OSError, e:
            print 'Cannot Create Process:%s' % e
            return 1
        else:
            if pid == 0:
                print 'Child PID:%d,'\
                    'the process will terminate in %d seconds'\
                    % (os.getpid(), i + 1)
                #set a alarm and invoke pause() to wait
                signal.alarm(i + 1)
                signal.pause()
        
    for i in range(5):
        wait_result = os.wait()
        # if the child process is terminated by signal
        if os.WIFSIGNALED(wait_result[1]):
            print 'Child PID:%d Receive SIG:%d, Exit!'\
                % (pid, os.WTERMSIG(wait_result[1]))
        # if the child process normally exits
        if os.WIFEXITED(wait_result[1]):
             print 'Child PID:%d normally exits!' % pid

if __name__ == '__main__':
    main()