#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Establishment date:  2009-2-26
#  Author            :  jasonleakey
#  Copyright (R) 2009   jasonleakey
#  <jasonleakey2005@gmail.com> <QQ:174481438>
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
#  --------------------------------------------------------------------
#  text_transmit_TCP_server.py: transmit text in Internet,using TCP
#                                this is the Server terminal

from socket import *
import time

(
    HOST,
    PORT,
    BUF_SIZE
) = ('127.0.0.1', 5099, 4096)

def main():
#    try:
    #create a socket with type TCP
    ss = socket(AF_INET, SOCK_STREAM)
    #bind the IP address
    ss.bind((HOST, PORT))
    #listen in the local port
    ss.listen(2)
    
    while True:
        print 'Waiting for connection...'
        #wait until clients connect
        try:
            (conn_sock, client_addr) = ss.accept()
        except KeyboardInterrupt:
            print 'Disconnected with %s:%s' % (HOST, PORT)
            ss.close()
            return 1
        print 'Connected from %s:%s' % client_addr
        
        while True:
            #receive data continuously until no data
            try:
                data = conn_sock.recv(BUF_SIZE)
            except KeyboardInterrupt:
                print 'Disconnected with %s:%s' % (HOST, PORT)
                ss.close()
                return 1
            
            #no data is sent
            if not data:
                break
            current_time = time.ctime()
            print '[%s]client:%s' % (current_time, data)
            send_data = '[%s]' % current_time
            conn_sock.send(send_data + 'you input:' + data)
        print 'Disconnected with %s:%s' % client_addr
        conn_sock.close()
    ss.close()
        
if __name__ == '__main__':
    main()