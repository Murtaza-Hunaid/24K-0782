class GoalBasedAgent:
  def __init__(self):
    self.subjects = ["AI", "Maths", "Physics"]
    self.completed = []
    
  def act(self):
    subjects = self.subjects
    completed = self.completed
    for subject in subjects:
      if subject not in completed:
        print("Studying", subject)
        completed.append(subject)
        return
    print("Goal Achieved: All subjects completed")

agent = GoalBasedAgent()
while True:
  agent.act()
  if len(agent.completed) == len(agent.subjects):
    break
agent.act()
