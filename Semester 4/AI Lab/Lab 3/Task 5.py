import random

class LearningAgent:
  def __init__(self):
    self.Q = {"Play": 0, "Rest": 0}
    self.alpha = 0.1
    self.actions = ["Play", "Rest"]

  def choose_action(self):
    return random.choice(self.actions)

  def get_reward(self, action):
    if action == "Play":
      return 5
    else:
      return 1

  def update_Q(self, action, reward):
    self.Q[action] = self.Q[action] + self.alpha * (reward - self.Q[action])

  def run(self, steps):
    for step in range(1, steps + 1):
      action = self.choose_action()
      reward = self.get_reward(action)
      print(f"Step {step}: Action {action} Reward {reward}")
      self.update_Q(action, reward)
    print("Q-table Updated:", self.Q)

agent = LearningAgent()
agent.run(10)
