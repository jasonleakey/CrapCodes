#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Nov 16, 2009 - search algorithms for agents
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

from pacman import PacmanRules
from util import PriorityQueue
import util
import time
## Abstract Search Classes

class SearchProblem:
  """
  Abstract SearchProblem class. Your classes
  should inherit from this class and override 
  all the methods below
  """
  def getStartState(self):
     """
     Returns the start state for the search problem 
     """
     util.raiseNotDefined()

  def isGoalState(self, state):
     """
       state: Search state
    
     Returns True if and only if the state is a valid goal state
     """
     util.raiseNotDefined()

  def getSuccessors(self, state):
     """
       state: Search state
     
     For a given state, this should return a list of triples, 
     (successor, action, stepCost), where 'successor' is a 
     successor to the current state, 'action' is the action
     required to get there, and 'stepCost' is the incremental 
     cost of expanding to that successor
     """
     util.raiseNotDefined()

  def getCostOfActions(self, actions):
     """
      actions: A list of actions to take
 
     This method returns the total cost of a particular sequence of actions.  The sequence must
     be composed of legal moves
     """
     util.raiseNotDefined()


def tinyMazeSearch(problem):
  """Returns a sequence of moves that solves tinyMaze.  For any other
  maze, the sequence of moves will be incorrect, so only use this for tinyMaze"""
  from game import Directions
  s = Directions.SOUTH
  w = Directions.WEST
  return  [s, s, w, s, w, w, s, w]


def getActions(path):

  startTime = time.time()

  index = len(path) - 1
  actions = []

  if(index < 0):
    print "path is empty!"
    return False

  (parentState, state, action) = path[index]
  index -= 1

  while index >= 0:
    (grandparentState, state, action) = path[index]
    if (parentState == state) and not(action == None):
      parentState = grandparentState
    else:
      path[index] = None;
    index -= 1


  for index in range(0, len(path)):
    if not (path[index] == None):
      actions.append(path[index][2])

  return actions


def depthFirstSearch(problem):
  """
  Search the deepest nodes in the search tree first. [p 74].
  
  Your search algorithm needs to return a list of actions that reaches
  the goal.  
  """
  "*** YOUR CODE HERE ***"
  return graph_search(problem, util.Stack())

def breadthFirstSearch(problem):
  "Search the shallowest nodes in the search tree first. [p 74]"
  "*** YOUR CODE HERE ***"
  return graph_search(problem, util.Queue())


def uniformCostSearch(problem):
  "Search the node of least total cost first. "
  "*** YOUR CODE HERE ***"
  visited = []
  fringe = util.FasterPriorityQueue()
  # priority stands for cost here
  fringe.push(Node(problem.getStartState()), 0)
  while not fringe.isEmpty():
      node = fringe.pop()
      visited.append(node.state)
      if problem.isGoalState(node.state):
          return node.get_actions()
      for subNode in node.expand(problem):
          if subNode.state not in visited:
              fringe.push(subNode, subNode.path_cost)
  return None


def nullHeuristic(state):
  """
  A heuristic function estimates the cost from the current state to the nearest
  goal in the provided searchProblem.  This one is trivial.
  """
  return 0


def aStarSearch(problem, heuristic = nullHeuristic):
  "Search the node that has the lowest combined cost and heuristic first."
  "*** YOUR CODE HERE ***"
  fn = lambda x: x.path_cost + heuristic(x.state)
  return best_first_graph_search(problem, fn)

def greedySearch(problem, heuristic = nullHeuristic):
  "Search the node that has the lowest heuristic first."
  "*** YOUR CODE HERE ***"
  fn = lambda x: heuristic(x.state)
  return best_first_graph_search(problem, fn)


def best_first_graph_search(problem, fn):
  """
  search the node with lowest evaluation for a expansion
  """
  visited = []
  fringe = util.PriorityQueue()
  # priority stands for cost evaluation here
  rootNode = Node(problem.getStartState())
  fringe.push(rootNode, fn(rootNode))
  while not fringe.isEmpty():
      node = fringe.pop()
      visited.append(node.state)
      if problem.isGoalState(node.state):
          return node.get_actions()
      for subNode in node.expand(problem):
          if subNode.state not in visited:
              fringe.push(subNode, fn(subNode))
  return None



class Node:
    """
    A node in a search tree
    """
    def __init__(self, state, parent = None, action = None, path_cost = 0, depth = 0):
        """
        Create a search tree Node, derived from a parent by an action.
        """
        self.state = state
        self.parent = parent
        self.action = action
        self.path_cost = path_cost
        self.depth = depth

    def __repr__(self):
        return "<Node %s>" % (self.state,)

    def get_actions(self):
        "Create a list of nodes from the root to this node."
        node = self
        actions = []
        while node.parent:
            actions.append(node.action)
            node = node.parent
        actions.reverse()
        return actions

    def expand(self, problem):
        """
        Return a list of nodes reachable from this node.
        """
        successors = []
        for (nextState, action, stepcost) in problem.getSuccessors(self.state):
            s = Node(nextState,
                     self,
                     action,
                     path_cost = self.path_cost + stepcost,
                     depth = self.depth + 1)
            successors.append(s)
        return successors

# the general tree search algorithm
def graph_search(problem, fringe):
    """
    Search through the successors of a problem to find a goal.
    The argument fringe should be an empty queue.
    """
    visited = [] # store nodes visited that should not be visited again
    fringe.push(Node(problem.getStartState()))
    while not fringe.isEmpty():
        node = fringe.pop()
        visited.append(node.state)
        if problem.isGoalState(node.state):
            return node.get_actions()
        for subNode in node.expand(problem):
            if subNode.state not in visited:
	            fringe.push(subNode)
    return None
