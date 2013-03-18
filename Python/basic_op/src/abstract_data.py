#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Establishment date:  Jun 9, 2009
#  Author            :  jasonleakey
#  Copyleft(R) by jasonleakey
#  <jasonleakey@gmail.com>
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
#  abstract_data.py: get irradiance from irrchart.txt

import os
import os.path
import sys

class abstract_data:
    def __init__(self):
        if len(sys.argv) != 3:
            print "Usage: %s input_file output_file" % sys.argv[0]
            return False
        
        input_file = sys.argv[1]
        output_file = sys.argv[2]
        
        cur_dir = os.getenv("HOME", None)
        os.chdir(cur_dir)
        if not os.path.exists(input_file):
            print cur_dir + input_file + "is not exist!"
            return False
        
        try:
            input_stream = open(input_file, "r")
            output_stream = open(output_file, "w")
        except IOError, e:
            print "cannot open file:%s" % e
            return False
        
        output_stream.writelines(['alpha beta gamma irr\r\n'])
        input_lines = input_stream.readlines()
        for i in range(0, 378):
            angle_line = input_lines[12 * i + 8]
            angles = angle_line.lstrip('User comments: ')
            angles = angles.rstrip('\r\n')
            if angles:
                [alpha, beta, gamma] = angles.split('-')
                irr_line = input_lines[12 * i + 11]
                irr = irr_line.partition('  ')[2]
                irr = irr.rstrip('\r\n')
                output_stream.writelines(\
                    [alpha + ' ' + beta + ' ' + gamma + ' ' + irr + '\r\n'])
        input_stream.close()
        
if __name__ == "__main__":
    abstract_data()