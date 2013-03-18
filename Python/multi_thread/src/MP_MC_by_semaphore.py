#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :  MP_MC_by_semaphore.py
#  Establishment date:  2009-2-26
#  Author            :  jasonleakey
#  Module Function   :  solve multi-producers and multi-consumers problem
#                        by using semaphore
#  Copyright (R) 2009 jasonleakey
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
import operator #the 'mod' operator

(
    BUFFER_SIZE,
    PRODUCER_ACCOUNT,
    CONSUMER_ACCOUNT
) = (10, 15, 15)

class Producer(threading.Thread):
    def __init__(self, threadname):
        self.threadname = threadname
        threading.Thread.__init__(self, name = threadname)
    
    def run(self):
        global g_sem_full
        global g_sem_empty
        global g_sem_mutex
        global g_buffer
        global g_producer_index
        #wait for available buffer
        g_sem_empty.acquire()
        #apply to enter critical area
        g_sem_mutex.acquire()
        
        #critical area
        g_buffer[g_producer_index] =  '\'' + str(self.threadname) + '\''
        print self.threadname, 'put', g_buffer[g_producer_index], 'to the buffer'
        g_producer_index = operator.mod(g_producer_index + 1, BUFFER_SIZE)
        
        g_sem_full.release()
        g_sem_mutex.release()
        
class Consumer(threading.Thread):
    def __init__(self, threadname):
        self.threadname = threadname
        threading.Thread.__init__(self, name = threadname)
    
    def run(self):
        global g_sem_full
        global g_sem_empty
        global g_sem_mutex
        global g_buffer
        global g_consumer_index
        #wait for available data in the buffer
        g_sem_full.acquire()
        #apply to enter critical area
        g_sem_mutex.acquire()
        
        #critical area
        str = g_buffer[g_consumer_index]
        print self.threadname, 'get', str, 'from the buffer'
        g_consumer_index = operator.mod(g_consumer_index + 1, BUFFER_SIZE)
        
        g_sem_empty.release()
        g_sem_mutex.release()

def main():
    producer_list = []
    consumer_list = []
    
    for i in range(PRODUCER_ACCOUNT):
        my_thread = Producer('Producer' + str(i))
        producer_list.append(my_thread)
        
    for i in range(CONSUMER_ACCOUNT):
        my_thread = Consumer('Consumer' + str(i))
        consumer_list.append(my_thread)
        
    for thread in producer_list:
        thread.start()
    
    for thread in consumer_list:
        thread.start()
    
    for thread in producer_list:
        thread.join()
        
    for thread in consumer_list:
        thread.join()

if __name__ == '__main__':
    #semaphore specifing the remain available room in the buffer
    g_sem_full = threading.Semaphore(0)
    #semaphore specifing the remain amount of data in the buffer
    g_sem_empty = threading.Semaphore(BUFFER_SIZE)
    #mutual exclusive semaphore
    g_sem_mutex = threading.Semaphore(1)
    g_producer_index = 0
    g_consumer_index = 0
    g_buffer = [0 for i in range(BUFFER_SIZE)]
    main()