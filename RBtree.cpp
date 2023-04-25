#include "RBtree.h"

void uncle(Node* current);
void leftRT(Node* lower, Node* upper);
void rightRT(Node* lower, Node* upper);

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

/*void RBtree::add(Node* toAdd, Node* current) {
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
  
}*/

void RBtree::add(Node* toAdd, Node* current) {
  if(top==NULL) {
    top = toAdd;
    toAdd->setColor(true);
    return;
  }
  bool greater = toAdd->getData() >= current->getData();
  bool black = current->getColor();
  if(greater) {
    if(current->getRight() == NULL) {
      if(black) {
	current->setRight(toAdd);
	toAdd->setParent(current);
	return;
      }
      else {
	toAdd->setParent(current);
	current->setRight(toAdd);
	if(current->getColor() == false && toAdd->getUncle()->getColor() == false) {
	  uncle(toAdd);
	  if(!top->getColor()) {
	    top->setColor(true);
	  }
	}
	else if(current->getColor() == false && (toAdd->getUncle() == NULL || toAdd->getUncle()->getColor() == true) && current->getParent()->getRight() == current) {
	  leftRT(current,current->getParent());
	  current->getLeft()->setColor(false);
	  current->setColor(true);
	}
	else if(current->getColor() == false && (toAdd->getUncle() == NULL || toAdd->getUncle()->getColor() == true) && current->getParent()->getLeft() == current) {
	  rightRT(toAdd, current);
	  leftRT(toAdd,toAdd->getParent());
	  toAdd->getLeft()->setColor(false);
	  toAdd->setColor(true);
	}
      }
    }
    else {
      add(toAdd, current->getRight());
    }
  }
  else {
    if(current->getLeft() == NULL) {
      if(black) {
	current->setLeft(toAdd);
	toAdd->setParent(current);
	return;
      }
      else {
	toAdd->setParent(current);
	current->setLeft(toAdd);
	if(current->getColor() == false && toAdd->getUncle()->getColor() == false) {
	  uncle(toAdd);
	  if(!top->getColor()) {
	    top->setColor(true);
	  }
	}
	if(current->getColor() == false && toAdd->getUncle()->getColor() == true) {
	  
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
  if(current->getGP() != NULL) {
    nParent->getParent()->setColor(false);
    uncle(current->getGP());
  }
}


void leftRT(Node* lower, Node* upper) {
  lower->setParent(upper->getParent());
  upper->setRight(lower->getLeft());
  lower->setLeft(upper);
  upper->setParent(lower);
}

void rightRT(Node* lower, Node* upper) {
  lower->setParent(upper->getParent());
  upper->setLeft(lower->getRight());
  lower->setRight(upper);
  upper->setParent(lower);
}
