class Light: 
  def __init__(self, room, status):
      self.room = room
      self.status = status

  def LightSwitch(self):
    if self.status == "ON":
      self.status = "OFF"
    elif self.status == "OFF":
      self.status = "ON"
    print(f"{self.room} light turned {self.status}")

  def LightStatus(self):
    print(f"{self.room} light is {self.status}")

room1 = Light("Bedroom", "ON")
room2 = Light("Kitchen", "OFF")

room1.LightSwitch()
room2.LightStatus()
