from ortools.sat.python import cp_model

model = cp_model.CpModel()

A = model.new_int_var(0, 3, "A")
B = model.new_int_var(0, 3, "B")
C = model.new_int_var(0, 3, "C")

model.add(A != B)
model.add(B != C)
model.add(A + B <= 4)

solver = cp_model.CpSolver()

status = solver.solve(model)

if status == cp_model.OPTIMAL or status == cp_model.FEASIBLE:
  print("A =", solver.value(A))
  print("B =", solver.value(B))
  print("C =", solver.value(C))
else:
  print("No solution found.")
