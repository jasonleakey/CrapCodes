#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Nov 19, 2009 -- a convenient menu to run pacman with special argument
#
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
from platform import system

import time
import sys
import os

def main():
    print '*' * 34
    print '*' * 4, 'Welcome to Pacman World!', '*' * 4
    print '*' * 34

    print 'Command list:'
    commandList = ['pacman.py --layout tinyMaze --pacman TinyMazeSearchAgent',
		    'pacman.py --layout tinyMaze --pacman DepthFirstSearchAgent',
		    'pacman.py --layout mediumMaze --pacman DepthFirstSearchAgent',
		    'pacman.py --layout mediumMaze --pacman BreadthFirstSearchAgent',
		    'pacman.py --layout bigMaze --pacman BreadthFirstSearchAgent -z .5',
		    'pacman.py --layout mediumMaze --pacman UniformCostSearchAgent',
		    'pacman.py --layout mediumDottedMaze --pacman StayEastSearchAgent',
		    'pacman.py --layout mediumScaryMaze --pacman StayWestSearchAgent',
		    'pacman.py --layout bigMaze --pacman ManhattanAStarSearchAgent -z .5',
		    'pacman.py --layout testSearch --pacman UniformCostFoodSearchAgent',
		    'pacman.py --layout tinySearch --pacman TrivialAStarFoodSearchAgent',
		    'pacman.py --layout trickySearch --pacman AStarFoodSearchAgent',
		    'pacman.py --layout bigSearch --pacman GreedyFoodSearchAgent -z .5',
            'pacman.py --layout trickySearch --pacman GreedyFoodSearchAgent',
            'pacman.py --layout bigSearch --pacman AStarFoodSearchAgent -z .5']
    for i, item in enumerate(commandList):
        print '%2d. %s' % (i + 1, item)
    while True:
        try:
            sel = raw_input('\nSelect a command(CTRL+C to quit):')
        except KeyboardInterrupt:
	        print 'Gook Luck! Bye~'
	        sys.exit(0)
        else:
            sel = int(sel) - 1
            if sel < 0 or sel > len(commandList) - 1:
                print >> sys.stderr, '\tillegal Input'
                time.sleep(0.3)
                continue

            map = commandList[sel].split()[2]
            agent = commandList[sel].split()[4]
            print '\tyou have selected MAP:  %s AGENT:  %s' % (map, agent)
            print '\tBegin{'
            time.sleep(0.3)
            os.system('python ' + commandList[sel])
            print '\t}Game Over!'


if __name__ == '__main__':
    main()
