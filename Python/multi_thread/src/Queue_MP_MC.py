#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :  Queue_MP_MC.py
#  Establishment date:  2009-2-25
#  Author            :  jasonleakey
#  Module Function   :  solve multi_producers and multi_consumers
#                        problem by using queue
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
import Queue

(
    PRODUCER_ACCOUNT,
    CONSUMER_ACCOUNT
) = (15, 15)

class Producer(threading.Thread):
    '''producer thread'''
    def __init__(self, queue, condvar, name = ''):
        self.condvar = condvar
        self.queue = queue
        self.name = name
        threading.Thread.__init__(self, name = name)
    
    def run(self):
        self.condvar.acquire()
        if self.queue.full():
            print 'Queue is full!,%s wait consumer to fetch!'\
                % self.name
            self.condvar.wait()
            
        #block until the room is available
        self.queue.put(self.name, True)
        print self.name, 'put', self.name, 'to queue'
        print 'Queue size is %d' % self.queue.qsize()
        self.condvar.release()
        
class Consumer(threading.Thread):
    '''consumer thread'''
    def __init__(self, queue, condvar, name = ''):
        self.condvar = condvar
        self.queue = queue
        self.name = name
        threading.Thread.__init__(self, name = name)
    
    def run(self):
        self.condvar.acquire()
        if self.queue.empty():
            print 'Queue is empty!,%s wait producer to put'\
                % self.name
            self.condvar.wait()
        #block until the queue is not empty
        print self.name, 'get',\
            self.queue.get(True), 'from queue' 
        print 'Queue size is %d' % self.queue.qsize()
        self.condvar.notify()
        self.condvar.release()

def main():
    #create a queue with maxsize 10
    my_queue = Queue.Queue(10)
    
    #create a condition variable
    cond = threading.Condition()
    
    #two list to store threads object
    producer_list = []
    consumer_list = []
    
    for i in range(PRODUCER_ACCOUNT):
        p = Producer(my_queue, cond, 'producer' + str(i))
        producer_list.append(p)
    
    for i in range(CONSUMER_ACCOUNT):
        c = Consumer(my_queue, cond, 'consumer' + str(i))
        consumer_list.append(c)
    
    #start producer and consumer threads
    for thread in producer_list:
        thread.start()
    
    for thread in consumer_list:
        thread.start()
    
    #wait producer and consumer threads to quit
    for thread in producer_list:
        thread.join()
    
    for thread in consumer_list:
        thread.join()

if __name__ == '__main__':
    main()