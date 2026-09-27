import sys
import json

room_no = sys.argv[1]

with open("room_config.json") as f:
    config = json.load(f)

print(config.get(str(room_no), "Unknown"))
