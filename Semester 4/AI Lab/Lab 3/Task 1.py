class Environment:
  def __init__(self, traffic_state):
    self.traffic_state = traffic_state

  def get_percept(self):
    return self.traffic_state

class SimpleReflexAgent:
  def act(self, percept):
    if percept == "Heavy Traffic":
      return "Extend Green Time"
    else:
      return "Normal Green"

def run_agent(agent, environment):
  percept = environment.get_percept()
  action = agent.act(percept)
  print(f"Percept: {percept}, Action: {action}")

env1 = Environment("Heavy Traffic")
env2 = Environment("Light Traffic")
agent = SimpleReflexAgent()
run_agent(agent, env1)
run_agent(agent, env2)
