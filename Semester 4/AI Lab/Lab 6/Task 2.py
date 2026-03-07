import heapq

def h(n):
  return abs(20 - n)

def beam_search(start, goal, beam_width=2):
  beam = [(h(start), [start])]
  print(f"Level 0 : {[path[-1] for _, path in beam]}")
  level = 1
  while beam:
    candidates = []
    for cost, path in beam:
      current = path[-1]
      if current == goal:
        return path
      for next_val in [current + 2, current + 3, current * 2]:
        new_path = path + [next_val]
        candidates.append((h(next_val), new_path))
    beam = heapq.nsmallest(beam_width, candidates, key=lambda x: x[0])
    for cost, path in beam:
      if path[-1] == goal:
        print(f"Level {level} : {[path[-1] for _, path in beam]}")
        return path
    print(f"Level {level} : {[path[-1] for _, path in beam]}")
    level += 1
  return None

start = 1
goal = 20
beam_width = 2
path = beam_search(start, goal, beam_width)
if path:
  print(f"Final path to reach {goal}: {path}")
else:
  print("No path found.")
