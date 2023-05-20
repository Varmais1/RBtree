#include <iostream>
#include "node.h"
/*Name: Ishaan Varma
  Date: 5/19/2023
  Purpose: framework for red black tree class
 */


class RBtree {
 public:
  RBtree();
  RBtree(Node* nTop);
  ~RBtree();
  void deleteAll(Node* nTop);
  void add(Node* toAdd, Node* current);
  void print(Node* nTop, int depth);
  void rebalance();
  void deletion(int data, Node* current);
  bool search(int data);
  bool search(int data, Node* current);
  Node* getTop();
  Node* setTop();
  void leftRT(Node* lower, Node* upper);
  void rightRT(Node* lower, Node* upper);
  void unclefix(Node* current);
  void doubleBlackFix(Node* u, Node* sparent, Node* sibling, bool rightParent);
 private:
  Node* top;
};
