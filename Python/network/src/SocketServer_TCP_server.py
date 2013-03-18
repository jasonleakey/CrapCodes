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
#  SocketServer_TCP_server: create a TCP server with socketserver module

import SocketServer
import time

(
    HOST,
    PORT
) = ('127.0.0.1', 21999)

class SvrHandler(SocketServer.StreamRequestHandler):
    #override the base class's 'handle' method to handle incoming 
    #connections
    def handle(self):
        print '...connected from:%s:%s' % self.client_address
        self.wfile.write('[%s]%s' % (time.ctime(), self.rfile.readline()))
                         
def main():
    srv_sock = SocketServer.TCPServer((HOST, PORT), SvrHandler)
    print 'waiting for connection...'
    try:
        srv_sock.serve_forever()
    except KeyboardInterrupt:
        print 'Server is terminated!'
        srv_sock.server_close()
        return 1
    
if __name__ == '__main__':
    main()