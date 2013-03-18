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
#  text_transmit_UDP_client: transmit text-based information by Mode UDP

from socket import *
import time

(
    HOST,
    PORT,
    BUFSIZE,
) = ('127.0.0.1', 17911, 4096)
(ADDR) = ((HOST, PORT))

def main():
    #create a socket with mode UDP
    sock = socket(AF_INET, SOCK_DGRAM)
    
    while True:
        try:
            data = raw_input('>>')
            if not data:
                break
            sock.sendto(data, ADDR)
            (recv_data, server_info) = sock.recvfrom(BUFSIZE)
            if not recv_data:
                break
            print '[%s]server say:\n%s' % (time.ctime(), recv_data)
        except KeyboardInterrupt:
            print 'Client is terminated'
            sock.close()
            return 1
    sock.close()
    
if __name__ == '__main__':
    main()