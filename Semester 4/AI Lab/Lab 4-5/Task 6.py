#Task 6
import random

graph = {
  'A': {'B': 4, 'C': 3},
  'B': {'E': 12, 'F': 5},
  'C': {'D': 7, 'E': 10},
  'D': {'E': 2},
  'E': {'G': 5},
  'F': {'G': 16},
  'G': {},
}

heuristic = {'A': 14, 'B': 12, 'C': 11, 'D': 6, 'E': 4, 'F': 11, 'G': 0}


def change_random_edge(graph):
  nodes = [n for n in graph if graph[n]]
  u = random.choice(nodes)
  v = random.choice(list(graph[u].keys()))
  old_cost = graph[u][v]
  change = random.randint(-3, 5)
  new_cost = max(1, old_cost + change)
  graph[u][v] = new_cost
  print(f"\nEdge cost changed: {u}-{v} from {old_cost} -> {new_cost}")


def reconstruct_path(came_from, current):
  path = []
  while current is not None:
    path.append(current)
    current = came_from[current]
  return list(reversed(path))


def a_star_dynamic(graph, start, goal):

  frontier = [(start, heuristic[start])]
  g_costs = {start: 0}
  came_from = {start: None}
  visited = set()

  step = 0

  while frontier:

    frontier.sort(key=lambda x: x[1])
    current_node, current_f = frontier.pop(0)

    if current_node in visited:
      continue

    visited.add(current_node)
    print("Visiting:", current_node)

    if current_node == goal:
      path = reconstruct_path(came_from, current_node)
      print("\nOptimal Path:", path)
      print("Total Cost:", g_costs[goal])
      return

    for neighbor, cost in graph[current_node].items():

      new_g = g_costs[current_node] + cost

      if neighbor not in g_costs or new_g < g_costs[neighbor]:
        g_costs[neighbor] = new_g
        came_from[neighbor] = current_node
        f_cost = new_g + heuristic[neighbor]
        frontier.append((neighbor, f_cost))

    step += 1

    if step % 2 == 0:
      change_random_edge(graph)

      frontier = []
      for node in g_costs:
        f_cost = g_costs[node] + heuristic[node]
        frontier.append((node, f_cost))

  print("Goal not found")

start_node = 'A'
goal_node = 'G'
a_star_dynamic(graph, start_node, goal_node)
