class Vehicle:
  def __init__(self, vehicle_id, brand, rent_per_day):
    self.vehicle_id = vehicle_id
    self.brand = brand
    self.rent_per_day = rent_per_day

  def display_details(self):
    print("Vehicle ID:", self.vehicle_id)
    print("Brand:", self.brand)
    print("Rent per day:", self.rent_per_day)

  def calculate_rent(self, days):
    total_rent = self.rent_per_day * days
    print("Rent for", days, "days:", total_rent)

v1 = Vehicle("ABC123", "Suzuki", 5000)
v2 = Vehicle("DEF456", "Honda", 10000)
v1.display_details()
v1.calculate_rent(5)
print("\n")
v2.display_details()
v2.calculate_rent(3)
