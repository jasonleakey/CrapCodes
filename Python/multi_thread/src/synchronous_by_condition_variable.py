#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :  synchronous_by_condition_variable.py
#  Establishment date:  2009-2-25
#  Author            :  jasonleakey
#  Module Function   :  use condition variable and lock to synchronize
#                        between threads
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

class Producer(threading.Thread):
    def __init__(self, args = [], threadname = ''):
        '''
        construtor of class producer
        @param args: args[0], the critical resource
                    args[1], condition variable
        @param threadname: producer name
        '''
        self.args = args
        self.name = threadname
        threading.Thread.__init__(self, name = threadname)
        
    def run(self):
        time.sleep(0.002)
        self.args[1].acquire()
        if self.args[0] == 100000:
            self.args[1].wait()
            pass
        else:
            for i in range(100000):
                self.args[0] += 1
            self.args[1].notify()
        print self.args[0]
        self.args[1].release()

class Consumer(threading.Thread):
    def __init__(self, args = [], threadname = ''):
        '''
        construtor of class consumer
        @param args: args[0], the critical resource
                    args[1], condition variable
        @param threadname: consumer name
        '''
        self.args = args
        self.name = threadname
        threading.Thread.__init__(self, name = threadname)
        
    def run(self):
        #
        self.args[1].acquire()
        if self.args[0] == 0:
            self.args[1].wait()
            pass
        else:
            for i in range(100000):
                self.args[0] -= 1
            self.args[1].notify()
        print self.args[0]
        self.args[1].release()
        
def main():
    #the critical resource
    x = 0
    
    #create a condition variable
    cond = threading.Condition()
    
    prd = Producer([x, cond], 'producer')
    csm = Consumer([x, cond], 'consumer')
    
    prd.start()
    csm.start()
    
    prd.join()
    csm.join()
    
    print x
    
if __name__ == '__main__':
    main()
    