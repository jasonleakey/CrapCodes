#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :  thread_basic_op.py
#  Establishment date:  2009-2-24
#  Author            :  jasonleakey
#  Module Function   :  basic operation of thread
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

g_var = 100

class MyThread(threading.Thread):
    #override the base class's constructor
    def __init__(self, args, name = ''):
        self.args = args
        self.name = name
        threading.Thread.__init__(self)
        print 'subthread __init__ complete!\n'
    
    def run(self):
        global g_var
        #wait for main thread for 0.02s
        time.sleep(0.02)
        
        print '%s starts at:%s' % (self.name, time.ctime())
        
        for i in range(5):
            #acquire a lock
            self.args[0].acquire()
            #critical area
            print '%s:let g_var minor 3' % self.name
            g_var -= 3
            print '%s:now g_var is %d' % (self.name, g_var)
            #release the lock
            self.args[0].release()
            #make subthread and main thread be asynchronous
            time.sleep(0.06)
        
        #name of this thread
        print 'old self.getName = %s' % self.getName()
        new_name = raw_input('Input new name for thread:')
        self.setName(new_name)
        print 'new self.getName = %s' % self.getName()
        
        print 'currentThread is %s' % threading.currentThread()
        
        #judge if this thread is daemonic
        print 'isDaemon?:%s' % self.isDaemon()
        
        time.sleep(3)
        
        print '%s ends at:%s' % (self.name, time.ctime()) 
        
def main():
    global g_var
    
    print 'Main Thread starts at:%s' % time.ctime()
    
    #create a lock
    lock_1 = threading.RLock()
    
    #create a new thread with name 'Thread_1'
    thread_1 = MyThread((lock_1,), 'Thread_1')
    #set it daemonic
    thread_1.setDaemon(1)

    
    print 'before invoking start(),thread_1.isAlive() = %s'\
        % thread_1.isAlive()
    
    thread_1.start()
    
    print 'after invoking start(),thread_1.isAlive() = %s'\
        % thread_1.isAlive()
        
    print 'Now activeCount() = %d' % threading.activeCount()
    print 'enumerate() = %s' % threading.enumerate()

    for i in range(5):
        #acquire a lock
        lock_1.acquire()
        #critical area
        print 'Main Thread:let g_var add 5'
        g_var += 5
        print 'Main Thread:now g_var is %d' % g_var
        #release the lock
        lock_1.release()
        #make subthread and main thread be asynchronous
        time.sleep(0.05)
        
    
    #wait subthread to quit
    thread_1.join()
    
    print 'Main Thread ends at:%s' % time.ctime()
    
if __name__ == '__main__':
    main()
        