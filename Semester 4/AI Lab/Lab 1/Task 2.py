n = int(input("Enter a number: "))
count = 0
print("Even numbers:")
for i in range(1, n + 1):
    if i % 2 == 0:
        print(i)
        count = count + 1
print("Total even numbers:", count)
