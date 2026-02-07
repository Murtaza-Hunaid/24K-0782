class UtilityBasedAgent:
  def __init__(self):
    self.restaurants = {"A": {"distance": 3, "rating": 7}, "B": {"distance": 5, "rating": 9}}

  def calculate_utility(self, rating, distance):
    return rating - distance

  def act(self):
    best_restaurant = None
    best_utility = -100
    for name, info in self.restaurants.items():
      utility = self.calculate_utility(info["rating"], info["distance"])
      print(f"Restaurant {name} Utility = {utility}")
      if utility > best_utility:
        best_utility = utility
        best_restaurant = name
    print("Selected Restaurant:", best_restaurant)

agent = UtilityBasedAgent()
agent.act()
