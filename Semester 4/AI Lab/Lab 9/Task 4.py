import numpy as np

states = ["Sunny", "Cloudy", "Rainy"]

transition_matrix = np.array([
    [0.6, 0.3, 0.1],  # Sunny
    [0.3, 0.4, 0.3],  # Cloudy
    [0.2, 0.3, 0.5]   # Rainy
])

def simulate_weather(initial_state, days):
  current = initial_state
  sequence = [current]

  for i in range(days):
    if current == "Sunny":
      current = np.random.choice(states, p=transition_matrix[0])
    elif current == "Cloudy":
      current = np.random.choice(states, p=transition_matrix[1])
    else:
      current = np.random.choice(states, p=transition_matrix[2])
    sequence.append(current)
  return sequence

def probability_at_least_3_rainy(trials):
  count = 0
  for i in range(trials):
    seq = simulate_weather("Sunny", 9)
    rainy_days = seq.count("Rainy")
    if rainy_days >= 3:
      count += 1
  return count / trials

result = simulate_weather("Sunny", 9)
print("Weather sequence:-")
print(" -> ".join(result))

prob = probability_at_least_3_rainy(10000)
print("\nProbability of at least 3 rainy days:", prob)
