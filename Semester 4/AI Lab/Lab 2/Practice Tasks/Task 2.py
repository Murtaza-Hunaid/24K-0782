class Staff:
  def __init__(self, name, staff_id, department):
    self.name = name
    self.staff_id = staff_id
    self.department = department
  def staff_details(self):
    print(f"Name: {self.name}")
    print(f"Staff ID: {self.staff_id}")
    print(f"Department: {self.department}")

class Teacher(Staff):
  def __init__(self, Staff, courses, salary, courseToTeach):
    self.courses = courses
    self.salary = salary
    self.courseToTeach = courseToTeach
    super().__init__(Staff.name, Staff.staff_id, Staff.department)

  def displayInfo(self):
    self.staff_details()
    print(f"Courses: {self.courses}")
    print(f"Salary: {self.salary}")
    print(f"Course to teach: {self.courseToTeach}")

class Admin_Staff(Staff):
  def __init__(self, Staff, role, workinghHours, tasks):
    self.role = role
    self.workinghHours = workinghHours
    self.tasks = tasks
    super().__init__(Staff.name, Staff.staff_id, Staff.department)

  def displayInfo(self):
    print("\n")
    self.staff_details()
    print(f"Role: {self.role}")
    print(f"Working Hours: {self.workinghHours}")
    print(f"Tasks: {self.tasks}")

class Research_Assistant(Staff):
  def __init__(self, Staff, research_topic, stipend, researchWork):
    self.research_topic = research_topic
    self.stipend = stipend
    self.researchWork = researchWork
    super().__init__(Staff.name, Staff.staff_id, Staff.department)

  def displayInfo(self):
    print("\n")
    self.staff_details()
    print(f"Research Topic: {self.research_topic}")
    print(f"Stipend: {self.stipend}")
    print(f"Research Work: {self.researchWork}")

staff1 = Staff("Murtaza", "12345", "HR")
courses = ["Operating Systems", "Calculus", "DataBase"]
Teacher1 = Teacher(staff1, courses, 50000, "DataBase")
Teacher1.displayInfo()

admin1 = Admin_Staff(staff1, "Manager", 8, "Manage Staff")
admin1.displayInfo()

researcher = Research_Assistant(staff1, "Artificial Intelligence", 10000, "Researching Artificial Intelligence")
researcher.displayInfo()
