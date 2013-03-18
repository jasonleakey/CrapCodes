#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :  threading_module_1.py
#  Establishment date:  2009-2-22
#  Author            :  jasonleakey
#  Module Function   :  use threading module to create threads
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

sleep_time = [4, 2]

def loop(nloop, nsec):
    '''nloop:loop ID,nsec:sleep time.
    performed by threads'''
    print 'start loop', nloop, 'at:', time.ctime()
    time.sleep(nsec)
    print 'loop %d over' % nloop, 'at:', time.ctime()
    
def main():
    print 'Main thread starts at %s' % time.ctime()
    
    #store two threads
    thread_list = []
    
    #loop times list,which stores 
    loop_times = range(len(sleep_time))
    for i in loop_times:
        try:
            #create a thread with invoking loop() and args with()
            thrd = threading.Thread(target = loop, args = (i, sleep_time[i]))
        except threading.ThreadError, e:
            print 'create thread Error:%s' % e
            return 1
        else:
            #store the two thread in a list
            thread_list.append(thrd)
    
    #start the two threads' activity
    for i in loop_times:
        thread_list[i].start()
    
    #wait until the threads terminate
    for i in loop_times:
        thread_list[i].join()
        
    print 'All Done at:%s' % time.ctime()
    
if __name__ == '__main__':
    main()
    