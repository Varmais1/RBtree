#include <iostream>
#include "node.h"

class RBtree {
 public:
  RBtree();
  RBtree(Node* nTop);
  ~RBtree();
  void deleteAll(Node* nTop);
  void add(Node* toAdd, Node* current);
  void print(Node* nTop, int depth);
  void rebalance();
  void deleter();
  bool search(int data);
  bool search(int data, Node* current);
  Node* getTop();
  Node* setTop();
  void leftRT(Node* lower, Node* upper);
  void rightRT(Node* lower, Node* upper);
  void unclefix(Node* current);
 private:
  Node* top;
};
