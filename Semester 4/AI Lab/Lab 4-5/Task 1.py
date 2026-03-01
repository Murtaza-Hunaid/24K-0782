#Task 1
from collections import deque

building = [
[1, 1, 0, 1],
[0, 1, 1, 1],
[1, 1, 0, 1],
[1, 0, 1, 1]
]
start = (0, 0)
goal = (3, 3)

def create_graph(grid):
  rows, cols = len(grid), len(grid[0])
  graph = {}
  for r in range(rows):
    for c in range(cols):
      if grid[r][c] == 1:
        graph[(r, c)] = []
        for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
          nr, nc = r + dr, c + dc
          if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == 1:
            graph[(r, c)].append((nr, nc))
  return graph

def bfs(graph, start, goal):
  visited = []
  queue = deque()
  parent = {start: None}
  queue.append(start)
  visited.append(start)
  while queue:
    node = queue.popleft()
    if node == goal:
      path = []
      current = goal
      while current is not None:
        path.append(current)
        current = parent[current]
      path.reverse()
      return visited, path
    for neighbour in graph[node]:
      if neighbour not in visited:
        visited.append(neighbour)
        parent[neighbour] = node
        queue.append(neighbour)
  return visited, None

if __name__ == "__main__":
  print("Emergency Exit Finder:-")
  print("\n  Building Grid  (1 = Can walk On, 0 = Blocked):")
  for r, row in enumerate(building):
    line = "  "
    for c, cell in enumerate(row):
      if (r, c) == start:
        line += " S"
      elif (r, c) == goal:
        line += " E"
      elif cell == 1:
        line += " 1"
      else:
        line += " X"
    print(line)
  print(f"\n  Start position: {start}")
  print(f"  Emergency exit: {goal}")
  graph = create_graph(building)
  print("\n  Adjacency List (graph):")
  for node, neighbours in sorted(graph.items()):
    print(f"   {node}  ->  {neighbours}")
  traversal, path = bfs(graph, start, goal)
  print(f"\n  BFS Traversal Order ({len(traversal)} nodes visited):")
  print("  " + " -> ".join(str(n) for n in traversal))
  if path:
    print(f"\n  Shortest Path ({len(path) - 1} steps):")
    print("  " + " -> ".join(str(n) for n in path))
    print("\n  Path on Grid  (S=Start, E=Exit, *=path, X=blocked):")
    path_set = set(path)
    for r, row in enumerate(building):
      line = "  "
      for c, cell in enumerate(row):
        if   (r, c) == start:
          line += " S"
        elif (r, c) == goal:
          line += " E"
        elif (r, c) in path_set:
          line += " *"
        elif cell == 0:
          line += " X"
        else:
          line += " ."
      print(line)
  else:
    print("\n  No path found to the emergency exit")
