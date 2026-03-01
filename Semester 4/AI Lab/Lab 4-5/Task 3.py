#Task 3
graph = {
  'A': ['B', 'C'],
  'B': ['D', 'E'],
  'C': ['F'],
  'D': ['G'],
  'E': [],
  'F': ['H'],
  'G': [],
  'H': []
}

def dls(node, goal, depth_limit, current_depth, path, visited):
  visited.append(node)
  new_path = path + [node]
  if node == goal:
    return True, new_path
  if current_depth >= depth_limit:
    return False, None
  for neighbor in graph.get(node, []):
    found, result_path = dls(neighbor, goal, depth_limit, current_depth + 1, new_path, visited)
    if found:
      return True, result_path
  return False, None

def ids(start, goal, max_depth=10):
  print(f"Starting IDS from '{start}' to find '{goal}'")
  for depth in range(max_depth + 1):
    visited = []
    found, path = dls(start, goal, depth, 0, [], visited)
    print(f"\nDepth limit = {depth}:-")
    print(f"Nodes visited in this iteration: {' -> '.join(visited)}")
    if found:
      print(f"\nGoal found. Path: {' -> '.join(path)}")
      return path
  print(f"Goal not found within depth limit {max_depth}.")
  return None

if __name__ == "__main__":
  ids(start='A', goal='G', max_depth=5)
