import math

class Node:
  def __init__(self, value=None):
    self.value = value
    self.children = []
    self.minmax_value = None
    self.best_child = None   


class Environment:
  def __init__(self):
    self.minimax_nodes = []
    self.alphabeta_nodes = []
    self.pruned_nodes = []

  def minimax(self, node, depth, maximizing=True):
    if depth == 0 or not node.children:
      self.minimax_nodes.append(node.value)
      return node.value

    if maximizing:
      value = -math.inf
      for child in node.children:
        child_val = self.minimax(child, depth-1, False)
        if child_val > value:
          value = child_val
          node.best_child = child
      node.minmax_value = value
      self.minimax_nodes.append(node.value)
      return value
    else:
      value = math.inf
      for child in node.children:
        child_val = self.minimax(child, depth-1, True)
        if child_val < value:
          value = child_val
          node.best_child = child
      node.minmax_value = value
      self.minimax_nodes.append(node.value)
      return value

  def alpha_beta(self, node, depth, alpha, beta, maximizing=True):
    self.alphabeta_nodes.append(node.value)

    if depth == 0 or not node.children:
      return node.value

    if maximizing:
      value = -math.inf
      for child in node.children:
        child_val = self.alpha_beta(child, depth-1, alpha, beta, False)
        if child_val > value:
          value = child_val
          node.best_child = child
        alpha = max(alpha, value)

        if beta <= alpha:
          self.pruned_nodes.append(child.value)
          break

      node.minmax_value = value
      return value

    else:
      value = math.inf
      for child in node.children:
        child_val = self.alpha_beta(child, depth-1, alpha, beta, True)
        if child_val < value:
          value = child_val
          node.best_child = child
        beta = min(beta, value)

        if beta <= alpha:
          self.pruned_nodes.append(child.value)
          break

      node.minmax_value = value
      return value

root = Node('Root')

n1 = Node('N1')
n2 = Node('N2')
root.children = [n1, n2]
n3 = Node('N3')
n4 = Node('N4')
n1.children = [n3, n4]
n5 = Node('N5')
n6 = Node('N6')
n2.children = [n5, n6]

n3.children = [Node(4), Node(7)]
n4.children = [Node(2), Node(5)]
n5.children = [Node(1), Node(9)]      
n6.children = [Node(3), Node(6), Node(10)]  

env = Environment()
env.minimax(root, 3, True)
print("Minimax Results:-")
print("Root:", root.minmax_value)
print("N1:", n1.minmax_value)
print("N2:", n2.minmax_value)
print("N3:", n3.minmax_value)
print("N4:", n4.minmax_value)
print("N5:", n5.minmax_value)
print("N6:", n6.minmax_value)
print("Visited Nodes (Minimax):", env.minimax_nodes)

env2 = Environment()
env2.alpha_beta(root, 3, -math.inf, math.inf, True)
print("\nAlpha Beta Results:-")
print("Root:", root.minmax_value)
print("N1:", n1.minmax_value)
print("N2:", n2.minmax_value)
print("N3:", n3.minmax_value)
print("N4:", n4.minmax_value)
print("N5:", n5.minmax_value)
print("N6:", n6.minmax_value)
print("Visited Nodes (Alpha-Beta):", env2.alphabeta_nodes)
print("Pruned Nodes:", env2.pruned_nodes)

print("\nOptimal Path:-")
current = root
while current:
    print(current.value, end=" -> ")
    current = current.best_child
print("END")
