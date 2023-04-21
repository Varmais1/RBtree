#include "RBtree.h"

void uncle(Node* current);


using namespace std;

RBtree::RBtree() {
  top = NULL;
}

RBtree::RBtree(Node* nTop) {
  top = nTop;
}

RBtree::~RBtree() {
  this->deleteAll(this->getTop());
}

void RBtree::deleteAll(Node* nTop) {
  if(nTop != NULL) {
    deleteAll(nTop->getLeft());
    deleteAll(nTop->getRight());
    nTop->setLeft(NULL);
    nTop->setRight(NULL);
    delete nTop;
  }
}

void RBtree::print(Node* nTop, int depth) {
  //if the tree is empty, say the tree is empty
  if(top == NULL) {
    cout << "The tree is empty." << endl;
    return;
  }

  //if the left isn't NULL, do this function for the left
  if(nTop->getLeft() != NULL) {
    print(nTop->getLeft(), depth + 1);
  }

  //print out the appropriate amount of spaces
  for(int i = 0; i < depth; i++) {
    cout << "\t";
  }
  //output the data
  cout << nTop->getData();
  if(nTop->getColor()) {
    cout << "B" << endl;
  }
  else {
    cout << "R" << endl;
  }

  //if the right isn't NULL, do this function for the right
  if(nTop->getRight() != NULL) {
    print(nTop->getRight(), depth + 1);
  }
}

Node* RBtree::getTop() {
  return top;
}

void RBtree::add(Node* toAdd, Node* current) {
  if(top == NULL) {
    top = toAdd;
    toAdd->setColor(true);
    return;
  }
  bool greater = toAdd->getData() > current->getData();
  if(greater) {
    if(current->getRight() == NULL) {
      if(current->getColor()) {
	current->setRight(toAdd);
	toAdd->setParent(current);
	return;
      }
      else {
	current->setRight(toAdd);
	toAdd->setParent(current);
	if(!toAdd->getUncle()->getColor()) {
	  uncle(toAdd);
	  top->setColor(true);
	}
      }
    }
    else {
      add(toAdd, current->getRight());
    }
  }
  else {
    if(current->getLeft() == NULL) {
      if(current->getColor()) {
	current->setLeft(toAdd);
	toAdd->setParent(current);
	return;
      }
      else {
	current->setRight(toAdd);
	toAdd->setParent(current);
	if(!toAdd->getUncle()->getColor()) {
	  uncle(toAdd);
	  top->setColor(true);
	}
      }
    }
    else {
      add(toAdd, current->getLeft());
    }
  }
  
}

void uncle(Node* current) {
  Node* nParent = current->getParent();
  Node* nUncle = current->getUncle();
  if(nParent != NULL) {
    nParent->setColor(true);
  }
  else {
    return;
  }
  if(nUncle != NULL) {
    nUncle->setColor(true);
  }
  uncle(current->getGP());
}
