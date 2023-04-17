#include "node.h"

using namespace std;

Node::Node() {
  data = 0;
  left = NULL;
  right = NULL;
  parent = NULL;
}

Node::Node(int nData) {
  data = nData;
  left = NULL;
  right = NULL;
  parent = NULL;
}

Node::Node(int nData, Node* nLeft, Node* nRight, Node* nParent) {
  data = nData;
  left = nLeft;
  right = nRight;
  parent = nParent;
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

Node* Node::getUncle() {
  if(parent == NULL || parent->getParent() == NULL) {
    return NULL;
  }
  if(parent->getParent()->getLeft() != parent) {
    return parent->getParent()->getLeft();
  }
  else {
    return parent->getParent()->getRight();
  }
}
