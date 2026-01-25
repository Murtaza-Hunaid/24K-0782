def calculate_average(marks):
    total = 0
    for m in marks:
        total = total + m
    return total / len(marks)

n = int(input("Enter the number of marks: "))
marks = []
for i in range(n):
    m = int(input("Enter marks: "))
    marks.append(m)
print("Marks:", marks)
print("Average Marks:", calculate_average(marks))
