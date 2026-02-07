class Environment:
  def __init__(self):
    self.grid = {
        'a': 'safe', 'b': 'safe', 'c': 'fire',
        'd': 'safe', 'e': 'fire', 'f': 'safe',
        'g': 'fire', 'h': 'safe', 'j': 'fire'}

  def get_status(self, room):
    return self.grid[room]

  def extinguish_fire(self, room):
    self.grid[room] = 'safe'

  def display(self, current_room):
    print("\nEnvironment Status:")
    order = ['a','b','c','d','e','f','g','h','j']
    for i in range(0, 9, 3):
      row = ""
      for r in order[i:i+3]:
        if r == current_room:
          row += " R "
        elif self.grid[r] == 'fire':
          row += " F "
        else:
          row += "   "
      print("|" + row + "|")

class FirefightingRobot:
  def __init__(self, path):
    self.path = path

  def act(self, environment):
    for room in self.path:
      status = environment.get_status(room)
      print(f"\nRobot at room {room}")
      if status == 'fire':
        print("Fire in room. Extinguishing fire.")
        environment.extinguish_fire(room)
      else:
        print("Room is safe.")
      environment.display(room)

path = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'j']
env = Environment()
robot = FirefightingRobot(path)
robot.act(env)
print("\nFinal Environment Status:")
env.display(None)
