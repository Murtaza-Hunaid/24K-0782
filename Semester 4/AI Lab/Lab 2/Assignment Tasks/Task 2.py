class Employee:
  def __init__(self, name, emp_id):
    self.name = name
    self.emp_id = emp_id

  def calculate_salary(self):
    pass

class FullTimeEmployee(Employee):
  def __init__(self, name, emp_id, monthly_salary):
    super().__init__(name, emp_id)
    self.monthly_salary = monthly_salary

  def calculate_salary(self):
    print("Full Time Employee Salary:", self.monthly_salary)

class PartTimeEmployee(Employee):
  def __init__(self, name, emp_id, hours_worked, hourly_rate):
    super().__init__(name, emp_id)
    self.hours_worked = hours_worked
    self.hourly_rate = hourly_rate

  def calculate_salary(self):
    salary = self.hours_worked * self.hourly_rate
    print("Part Time Employee Salary:", salary)

e1 = FullTimeEmployee("Murtaza", "F782", 80000)
e2 = PartTimeEmployee("Adnan", "P656", 20, 1500)
e1.calculate_salary()
e2.calculate_salary()
