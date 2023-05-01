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
  bool search();
  Node* getTop();
  Node* setTop();
  void leftRT(Node* lower, Node* upper);
  void rightRT(Node* lower, Node* upper);
 private:
  Node* top;
};
