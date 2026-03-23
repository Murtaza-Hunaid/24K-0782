from ortools.sat.python import cp_model

model = cp_model.CpModel()

x = model.new_int_var(0, 20, "x")
y = model.new_int_var(0, 20, "y")
z = model.new_int_var(0, 20, "z")

model.add(x + 2*y + z <= 20)
model.add(3*x + y <= 18)

model.maximize(4*x + 2*y + z)

solver = cp_model.CpSolver()

status = solver.solve(model)

if status == cp_model.OPTIMAL or status == cp_model.FEASIBLE:
  print("Optimal Value =", solver.objective_value)
  print("x =", solver.value(x))
  print("y =", solver.value(y))
  print("z =", solver.value(z))
else:
  print("No solution found.")
