from ortools.sat.python import cp_model

model = cp_model.CpModel()

A = model.new_int_var(0, 3, "A")
B = model.new_int_var(0, 3, "B")
C = model.new_int_var(0, 3, "C")

model.add(A != B)
model.add(B != C)
model.add(A + B <= 4)

class SolutionPrinter(cp_model.CpSolverSolutionCallback):
  def __init__(self, A, B, C):
    cp_model.CpSolverSolutionCallback.__init__(self)
    self.A = A
    self.B = B
    self.C = C
    self.solution_count = 0

  def on_solution_callback(self):
    self.solution_count += 1
    print("Solution", self.solution_count, ":", "A =", self.value(self.A), "B =", self.value(self.B), "C =", self.value(self.C))

solver = cp_model.CpSolver()

solver.parameters.enumerate_all_solutions = True

solution_printer = SolutionPrinter(A, B, C)
solver.solve(model, solution_printer)

print(f"\nTotal Solutions:", solution_printer.solution_count)
print(f"Status: {solver.status_name(status)}")
