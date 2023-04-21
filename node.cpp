#include "node.h"

using namespace std;

Node::Node() {
  data = 0;
  left = NULL;
  right = NULL;
  parent = NULL;
  black = false;
}

Node::Node(int nData) {
  data = nData;
  left = NULL;
  right = NULL;
  parent = NULL;
  black = false;
}

Node::Node(int nData, Node* nLeft, Node* nRight, Node* nParent) {
  data = nData;
  left = nLeft;
  right = nRight;
  parent = nParent;
  black = false;
}

Node::~Node() {
  left = NULL;
  right = NULL;
  parent = NULL;
}

Node* Node::getLeft() {
  return left;
}

Node* Node::getRight() {
  return right;
}

Node* Node::getParent() {
  return parent;
}

Node* Node::getGP() {
  if(parent == NULL) {
    return NULL;
  }
  else {
    return parent->getParent();
  }
}

Node* Node::getUncle() {
  Node* gp = this->getGP();
  if(gp != NULL) {
    if(gp->getLeft() != parent) {
      return gp->getLeft();
    }
    else {
      return gp->getRight();
    }
  }
  return NULL;
}

int Node::getData() {
  return data;
}

void Node::setLeft(Node* nLeft) {
  left = nLeft;
}

void Node::setRight(Node* nRight) {
  right = nRight;
}

void Node::setParent(Node* nParent) {
  parent = nParent;
}

void Node::setData(int nData) {
  data = nData;
}

bool Node::getColor() {
  return black;
}

void Node::setColor(bool color) {
  black = color;
}
