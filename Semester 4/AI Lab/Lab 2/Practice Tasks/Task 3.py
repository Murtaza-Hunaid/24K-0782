class BankAccount:
  def __init__(self, balance):
    self.__balance = balance

  def deposit(self, amount):
    self.__balance += amount

  def withdraw(self, amount):
    if amount <= self.__balance:
      self.__balance -= amount
    else:
      print("Unable to withdraw")

  def get_balance(self):
    return self.__balance

account1 = BankAccount(10000)
account1.deposit(2500)
print(account1.get_balance())
account2 = BankAccount(5000)
account2.withdraw(1500)
print(account2.get_balance())
