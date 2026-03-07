import random

n = 5 #5 bits for 31
population_size = 10
mutation_rate = 0.1
max_generations = 15

def calculate_fitness(individual):
  x = int(''.join(map(str, individual)), 2)
  return x**2 + 2*x

def create_random_individual():
  return random.choices([0, 1], k=n)

def select_parents(population, fitness_scores):
  sorted_population = [ind for _, ind in sorted(zip(fitness_scores, population), reverse=True)]
  return sorted_population[:len(population) // 2]

def crossover(parent1, parent2):
  point = random.randint(1, n - 2)
  child = parent1[:point] + parent2[point:]
  return child

def mutate(individual):
  idx1, idx2 = random.sample(range(n), 2)
  individual[idx1], individual[idx2] = individual[idx2], individual[idx1]
  return individual

def genetic_algorithm():
  population = [create_random_individual() for _ in range(population_size)]
  best_fitness = 0
  for generation in range(max_generations):
    fitness_scores = [calculate_fitness(ind) for ind in population]
    best_fitness = max(fitness_scores)
    print(f"Generation {generation + 1}, Best Fitness: {best_fitness}")
    parents = select_parents(population, fitness_scores)
    new_population = [crossover(random.choice(parents), random.choice(parents)) for _ in range(population_size)]
    for i in range(len(new_population)):
      if random.random() < mutation_rate:
        new_population[i] = mutate(new_population[i])
    population = new_population
  fitness_scores = [calculate_fitness(ind) for ind in population]
  best_individual = max(population, key=calculate_fitness)
  return best_individual, calculate_fitness(best_individual)

solution, fitness = genetic_algorithm()
x_val = int(''.join(map(str, solution)), 2)
print(f"\nBest Chromosome : {solution}")
print(f"Best x value : {x_val}")
print(f"Best Fitness : {fitness}")
