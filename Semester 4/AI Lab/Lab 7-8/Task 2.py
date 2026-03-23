import math

class Node:
  def __init__(self, value=None):
    self.value = value
    self.children = []
    self.minmax_value = None

class Environment:
  def __init__(self):
    self.computed_nodes = []
    self.pruned_nodes = []

  def alpha_beta(self, node, depth, alpha, beta, maximizing_player=True):
    self.computed_nodes.append(node.value)

    if depth == 0 or not node.children:
      return node.value

    if maximizing_player:
      value = -math.inf
      for child in node.children:
        value = max(value, self.alpha_beta(child, depth-1, alpha, beta, False))
        alpha = max(alpha, value)
        if beta <= alpha:
          self.pruned_nodes.append(child.value)
          break
      node.minmax_value = value
      return value
    else:
      value = math.inf
      for child in node.children:
        value = min(value, self.alpha_beta(child, depth-1, alpha, beta, True))
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
n5.children = [Node(1), Node(8)]
n6.children = [Node(3), Node(6)]
env = Environment()
env.alpha_beta(root, 3, -math.inf, math.inf, True)
print("Minimax Values:-")
print("Root:", root.minmax_value)
print("N1:", n1.minmax_value)
print("N2:", n2.minmax_value)
print("N3:", n3.minmax_value)
print("N4:", n4.minmax_value)
print("N5:", n5.minmax_value)
print("N6:", n6.minmax_value)
print("\nVisited Nodes:", env.computed_nodes)
print("Pruned Nodes:", env.pruned_nodes)
''' Alpha-Beta pruning reduces computation because it stops exploring branches that cannot affect the final decision. If a node is already worse than a previously explored option, it is ignored. This avoids unnecessary recursive calls, making the algorithm faster. '''
