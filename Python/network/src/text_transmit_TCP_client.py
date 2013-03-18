#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Establishment date:  2009-2-27
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
#  text_transmit_TCP_client: transmit text in the Internet using TCP mode 
#                           and this module is client

import time
import random
from socket import *

(
    HOST,
    PORT,
    BUF_SIZE
) = ('127.0.0.1', 5099, 4096)

def main():
    #create a socket for client with TCP mode
    ss = socket(AF_INET, SOCK_STREAM)
    ss.bind(('127.0.0.1', random.randint(10000, 30000)))
    print 'Connecting %s:%s...' % (HOST, PORT) 
    ss.connect((HOST, PORT))
    print 'Connected!'
    
    while True:
        try:
            data = raw_input('>>',)
        except KeyboardInterrupt:
            print 'Disconnected.exit..'
            ss.close()
            return 1
        else:
            if not data:
                break
            ss.send(data)
            recv_data = ss.recv(BUF_SIZE)
            if not recv_data:
                break
            print '%s' % recv_data
    ss.close()
    
if __name__ == '__main__':
    main()