import sys
import time
from ortools.sat.python import cp_model

class NQueenSolutionPrinter(cp_model.CpSolverSolutionCallback):
  def __init__(self, queens: list[cp_model.IntVar]):
    cp_model.CpSolverSolutionCallback.__init__(self)
    self.__queens = queens
    self.__solution_count = 0
    self.__start_time = time.time()

  @property
  def solution_count(self) -> int:
    return self.__solution_count

  def on_solution_callback(self):
    current_time = time.time()
    print(
        f"Solution {self.__solution_count}, "
        f"time = {current_time - self.__start_time} s"
    )
    self.__solution_count += 1

    all_queens = range(len(self.__queens))
    for i in all_queens:
      for j in all_queens:
        if self.value(self.__queens[j]) == i:
          print("Q", end=" ")
        else:
          print("_", end=" ")
      print()
    print()

model = cp_model.CpModel()

board_size = 4
queens = [model.new_int_var(0, board_size - 1, f"x_{i}") for i in range(board_size)]

model.add_all_different(queens)

model.add_all_different(queens[i] + i for i in range(board_size))
model.add_all_different(queens[i] - i for i in range(board_size))

solver = cp_model.CpSolver()
solution_printer = NQueenSolutionPrinter(queens)
solver.parameters.enumerate_all_solutions = True
solver.solve(model, solution_printer)
print(f"Solutions found: {solution_printer.solution_count}")
