choice = 0
while choice != 3:
    print("1. Add two numbers")
    print("2. Subtract two numbers")
    print("3. Exit")
    choice = int(input("Enter your choice: "))
    if choice == 1:
        num1 = int(input("Enter first number: "))
        num2 = int(input("Enter second number: "))
        print("Result:", num1 + num2)
    elif choice == 2:
        num1 = int(input("Enter first number: "))
        num2 = int(input("Enter second number: "))
        print("Result:", num1 - num2)
    elif choice == 3:
        print("Exiting program")
    else:
        print("Invalid")
