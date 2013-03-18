#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :  threading_module_3.py
#  Establishment date:  2009-2-22
#  Author            :  jasonleakey
#  Module Function   :  import threading module and a callable class to
#                        create threads
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

import threading
import time
import new

sleep_time = [4, 2]

#object is a base for all new style classes
class ThreadFunc(object):
    '''a callable class to be executed by the thread object'''
    def __init__(self, func, args, name = ''):
        self.func = func
        self.args = args
        self.name = name
        
    def __call__(self):
        '''this method will be called automatically'''
        #execute self.func with argument self.args
        apply(self.func, self.args)

def loop(nloop, nsec):
    print 'start loop', nloop, 'at:', time.ctime()
    time.sleep(nsec)
    print 'loop', nloop, 'Done at:', time.ctime()

def main():
    print 'Main thread starts at:', time.ctime()
    
    #list including all threads
    thread_list = []
    loops = range(len(sleep_time))
    for i in loops:
        #create threads
        thrd = threading.Thread(\
            target = ThreadFunc(loop, (i, sleep_time[i]),\
                loop.__name__))
        thread_list.append(thrd)
    
    for i in loops:
        #start all threads
        thread_list[i].start()
        
    for i in loops:
        #wait for completion
        thread_list[i].join()
        
    print 'All Done at:', time.ctime()
    
if __name__ == '__main__':
    main()