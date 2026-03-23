import math

class Node:
  def __init__(self, value=None):
    self.value = value         
    self.children = []
    self.minmax_value = None   

def compute_minimax(node, depth, maximizing_player, order_list):
  order_list.append(node.value)         
  if depth == 0 or not node.children:
    return node.value

  if maximizing_player:
    value = -math.inf
    for child in node.children:
      child_val = compute_minimax(child, depth - 1, False, order_list)
      value = max(value, child_val)
    node.minmax_value = value
    return value
  else:
    value = math.inf
    for child in node.children:
      child_val = compute_minimax(child, depth - 1, True, order_list)
      value = min(value, child_val)
    node.minmax_value = value
    return value

leaf_4 = Node(4) 
leaf_7 = Node(7) 
leaf_2 = Node(2) 
leaf_5 = Node(5)
leaf_1 = Node(1) 
leaf_8 = Node(8) 
leaf_3 = Node(3) 
leaf_6 = Node(6)
n3 = Node("N3") 
n3.children = [leaf_4, leaf_7]
n4 = Node("N4") 
n4.children = [leaf_2, leaf_5]
n5 = Node("N5") 
n5.children = [leaf_1, leaf_8]
n6 = Node("N6") 
n6.children = [leaf_3, leaf_6]

n1 = Node("N1")
n1.children = [n3, n4]
n2 = Node("N2")
n2.children = [n5, n6]
root = Node("Root"); root.children = [n1, n2]
order_full = []
root_minimax = compute_minimax(root, 3, True, order_full)

print("Full Minimax (depth = 3):-")
print("Minimax values:")
print(f"Root: {root.minmax_value}")
print(f"N1: {n1.minmax_value}")
print(f"N2: {n2.minmax_value}")
print(f"N3: {n3.minmax_value}")
print(f"N4: {n4.minmax_value}")
print(f"N5: {n5.minmax_value}")
print(f"N6: {n6.minmax_value}")
print(f"Order of visited nodes: {order_full}")

# Depth‑limited Minimax (depth = 2)
n3_dl = Node(5.5)   # (4+7)/2
n4_dl = Node(3.5)   # (2+5)/2
n5_dl = Node(4.5)   # (1+8)/2
n6_dl = Node(4.5)   # (3+6)/2
n1_dl = Node("N1") 
n1_dl.children = [n3_dl, n4_dl]
n2_dl = Node("N2") 
n2_dl.children = [n5_dl, n6_dl]
root_dl = Node("Root") 
root_dl.children = [n1_dl, n2_dl]
order_lim = []
compute_minimax(root_dl, 2, True, order_lim)

print("\nDepth‑Limited Minimax (depth = 2):-")
print("Minimax values:")
print(f"Root: {root_dl.minmax_value}")
print(f"N1: {n1_dl.minmax_value}")
print(f"N2: {n2_dl.minmax_value}")
print(f"N3: {n3_dl.value}")
print(f"N4: {n4_dl.value}")
print(f"N5: {n5_dl.value}")
print(f"N6: {n6_dl.value}")
print(f"Order of visited nodes: {order_lim}")
