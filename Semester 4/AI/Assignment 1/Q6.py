def find_start(maze):
  for i in range(len(maze)):
    for j in range(len(maze[0])):
      if maze[i][j] == 'S':
        return (i, j)
  return None

def depth_limited_dfs(maze, limit):
  start = find_start(maze)
  visited = []

  def dfs(position, depth):
    x, y = position
    if maze[x][y] == 'G':
      return True
    if depth == limit:
      return False
    visited.append(position)  
    moves = [(-1,0), (1,0), (0,-1), (0,1)]
    for move in moves:
      nx = x + move[0]
      ny = y + move[1]
      if (0 <= nx < len(maze) and
        0 <= ny < len(maze[0]) and
        maze[nx][ny] != 1 and
        (nx, ny) not in visited):
        if dfs((nx, ny), depth + 1):
          return True
    return False
  return dfs(start, 0)
  
def iterative_deepening_search(maze, max_depth):
  for depth in range(max_depth + 1):
    print("Trying depth limit:", depth)
    if depth_limited_dfs(maze, depth):
      return True
  return False

maze = [
['S', 0, 0, 1, 0],
[1, 0, 1, 0, 0],
[0, 0, 0, 0, 'G'],
[1, 1, 0, 1, 1]
]

print("Depth-Limited DFS:", depth_limited_dfs(maze, 5))
print("Iterative Deepening Search:", iterative_deepening_search(maze, 10))
