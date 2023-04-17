#include <iostream>
#include <cstring>

class Node {
 public:
  Node();
  Node(int nData);
  Node(int nData, Node* nLeft, Node* nRight, Node* nParent);
  ~Node();
  Node* getLeft();
  Node* getRight();
  Node* getParent();
  Node* getUncle();
  int getData();
  bool getColor();
  Node* getGP();
  void setLeft(Node* nLeft);
  void setRight(Node* nRight);
  void setParent(Node* nParent);
  void setData(int nData);
  void setColor(bool color);
 private:
  int data;
  Node* left;
  Node* right;
  Node* parent;
  bool black;
};
