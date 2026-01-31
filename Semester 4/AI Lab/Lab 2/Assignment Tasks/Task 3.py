class Student:
  def __init__(self, name):
    self.name = name
    self.__marks = 0   

  def set_marks(self, marks):
    self.__marks = marks

  def get_marks(self):
    return self.__marks

  def calculate_grade(self):
    if self.__marks >= 82:
      return "A"
    elif self.__marks >= 74:
      return "B"
    elif self.__marks >= 66:
      return "C"
    elif self.__marks >= 58:
      return "D"
    else:
      return "Fail"

s1 = Student("Murtaza")
s2 = Student("Adnan")
s1.set_marks(90)
s2.set_marks(80)
print("Student:", s1.name)
print("Marks:", s1.get_marks())
print("Grade:", s1.calculate_grade())
print("\nStudent:", s2.name)
print("Marks:", s2.get_marks())
print("Grade:", s2.calculate_grade())
