#Task 5
from queue import PriorityQueue

class Node:
  def __init__(self, position, parent=None):
    self.position = position
    self.parent = parent
    self.g = 0
    self.h = 0
    self.f = 0

  def __lt__(self, other):
    return self.f < other.f

def heuristic(current_pos, goals):
  return min(abs(current_pos[0] - g[0]) + abs(current_pos[1] - g[1]) for g in goals)

def bestfs_multi(maze, start, goals):
  rows, cols = len(maze), len(maze[0])
  total_path = []
  current_start = start
  remaining_goals = set(goals)

  while remaining_goals:
    frontier = PriorityQueue()
    start_node = Node(current_start)
    frontier.put(start_node)
    visited = set()
    found_goal = None

    while not frontier.empty():
      current_node = frontier.get()
      current_pos = current_node.position
      if current_pos in remaining_goals:
        found_goal = current_node
        break
      visited.add(current_pos)

      for dx, dy in [(1,0), (-1,0), (0,1), (0,-1)]:
        new_pos = (current_pos[0] + dx, current_pos[1] + dy)
        if (0 <= new_pos[0] < rows and
          0 <= new_pos[1] < cols and
          maze[new_pos[0]][new_pos[1]] == 0 and
          new_pos not in visited):
          new_node = Node(new_pos, current_node)
          new_node.g = current_node.g + 1
          new_node.h = heuristic(new_pos, remaining_goals)
          new_node.f = new_node.h
          frontier.put(new_node)
          visited.add(new_pos)

    path = []
    while found_goal:
      path.append(found_goal.position)
      found_goal = found_goal.parent
    path.reverse()
    if total_path:
      total_path.extend(path[1:])
    else:
      total_path.extend(path)
    current_start = path[-1]
    remaining_goals.remove(current_start)

  return total_path


maze = [
    [0,0,1,0,0],
    [0,0,0,0,0],
    [0,0,1,0,1],
    [0,0,1,0,0],
    [0,0,0,1,0]
]

start = (0,0)
goals = [(4,4), (2,1), (0,4)]
path = bestfs_multi(maze, start, goals)
print("Path:", path)
