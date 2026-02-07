import random

class Environment:
  def __init__(self):
    self.light_status = "OFF"

  def get_percept(self):
    students = random.choice(["Yes", "No"])
    percept = f"Students Present: {students}, Light Status: {self.light_status}"
    return percept, students, self.light_status

  def turn_on_light(self):
    self.light_status = "ON"

  def turn_off_light(self):
    self.light_status = "OFF"

class ModelBasedAgent:
  def __init__(self):
    self.students_present = None
    self.light_status = None

  def act(self, students, light):
    self.students_present = students
    self.light_status = light
    if students == "Yes" and light == "OFF":
      return "Turn ON"
    elif students == "No" and light == "ON":
      return "Turn OFF"
    else:
      return "No Action"

def run_agent(agent, environment, steps):
  for step in range(steps):
    percept, students, light = environment.get_percept()
    action = agent.act(students, light)
    print(f"Step {step + 1}: Percept - {percept}, Action - {action}")
    print(f"Agent Model: Students Present: {agent.students_present}, Light Status: {agent.light_status}")
    if action == "Turn ON":
      environment.turn_on_light()
    elif action == "Turn OFF":
      environment.turn_off_light()

env = Environment()
agent = ModelBasedAgent()
run_agent(agent, env, 8)
