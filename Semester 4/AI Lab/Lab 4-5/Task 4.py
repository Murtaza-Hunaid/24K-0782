#Task 4
graph = {
'S': {'A': 4, 'B': 2},
'A': {'C': 5, 'D': 10},
'B': {'E': 3},
'C': {'G': 4},
'D': {'G': 1},
'E': {'D': 4},
'G': {}
}

def ucs(graph, start, goal):
  frontier = [(start, 0)]
  visited = set()
  cost_so_far = {start: 0}
  came_from = {start: None}
  while frontier:
    frontier.sort(key=lambda x: x[1])
    current_node, current_cost = frontier.pop(0)
    if current_node in visited:
      continue
    visited.add(current_node)

    if current_node == goal:
      path = []
      while current_node is not None:
        path.append(current_node)
        current_node = came_from[current_node]
      path.reverse()
      print("Least Cost Path:", path)
      print("Total Cost:", current_cost)
      return

    for neighbor, cost in graph[current_node].items():
      new_cost = current_cost + cost
      if neighbor not in cost_so_far or new_cost < cost_so_far[neighbor]:
        cost_so_far[neighbor] = new_cost
        came_from[neighbor] = current_node
        frontier.append((neighbor, new_cost))
  print("Goal not found")

start_node = 'S'
goal_node = 'G'
ucs(graph, start_node, goal_node)
