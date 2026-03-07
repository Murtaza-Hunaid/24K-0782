import random

def f(x):
  return -x**2 + 6*x

def hill_climbing():
  x = random.randint(0, 6)
  print("Initial x:", x)
  print("f(x) =", f(x))
  while True:
    neighbors = []
    if x - 1 >= 0:
      neighbors.append(x - 1)
    if x + 1 <= 6:
      neighbors.append(x + 1)
    best_x = x
    best_value = f(x)
    for n in neighbors:
      if f(n) > best_value:
        best_x = n
        best_value = f(n)
    if best_x == x:
      break
    x = best_x
    print("Move to x:", x, "f(x) =", f(x))

  print("Final optimal x:", x)
  print("Final optimal value f(x):", f(x))

hill_climbing()
