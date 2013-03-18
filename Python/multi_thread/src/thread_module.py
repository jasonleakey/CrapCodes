#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :  thread_module.py
#  Establishment date:  2009-2-22
#  Author            :  jasonleakey
#  Module Function   :  use thread module to MT programming
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

import thread
import time

sleep_list = [4, 2]

def loop(nloop, nsec, lock):
    '''This function will be executed by threads'''
    print 'loop ID:%d' % nloop, 'start loop at:%s' % time.ctime()
    time.sleep(nsec)
    print 'loop ID:%d' % nloop, 'end loop at:%s' % time.ctime()
    lock.release()
    print 'lock ID:%d has been release' % nloop

def main():
    print 'Main thread start at:%s' % time.ctime()

    lock_list = []
    loop_time = range(len(sleep_list))
    for i in loop_time:
        #allocate two locks and store it in lock_list
        lock = thread.allocate_lock()
        lock.acquire()
        print 'lock ID:%d has been locked' % i
        lock_list.append(lock)
        
    for i in loop_time:
        #create two threads
        thread.start_new_thread(loop,\
            (i, sleep_list[i], lock_list[i]))
    
    #wait two threads for exiting
    for i in loop_time:
        while lock_list[i].locked():
            pass
    
    print 'all Done at:%s' % time.ctime()
    
if __name__ == '__main__':
    main()