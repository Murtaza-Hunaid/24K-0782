#Task 2
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

def dls(node, goal, depth_limit, current_depth, path, visited_nodes):
  visited_nodes.append(node)
  new_path = path + [node]
  if node == goal:
    return True, new_path
  if current_depth >= depth_limit:
    return False, None
  for neighbor in graph.get(node, []):
    found, result_path = dls(neighbor, goal, depth_limit, current_depth + 1, new_path, visited_nodes)
    if found:
      return True, result_path
  return False, None

def run_dls(start, goal, depth_limit):
  print(f"\nDLS with depth limit = {depth_limit}:-")
  visited_nodes = []
  found, path = dls(start, goal, depth_limit, 0, [], visited_nodes)
  print("Nodes visited in order:", " -> ".join(visited_nodes))
  if found:
    print("Goal found. Path:", " -> ".join(path))
  else:
    print("Goal not found within depth limit.")

if __name__ == "__main__":
  start = 'A'
  goal = 'H'
  run_dls(start, goal, depth_limit=2)
  run_dls(start, goal, depth_limit=3)
