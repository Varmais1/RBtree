#include "RBtree.h"

//void uncle(Node* current);
//void leftRT(Node* lower, Node* upper);
//void rightRT(Node* lower, Node* upper);

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
  if(nTop->getRight() != NULL) {
    print(nTop->getRight(), depth + 1);
  }

  //print out the appropriate amount of spaces
  for(int i = 0; i < depth; i++) {
    cout << "\t";
  }
  //output the data
  cout << nTop->getData();
  if(nTop->getColor()) {
    cout << " (B)" << endl;
  }
  else {
    cout << " (R)" << endl;
  }

  //if the right isn't NULL, do this function for the right
  if(nTop->getLeft() != NULL) {
    print(nTop->getLeft(), depth + 1);
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
  //if greater
  if(greater) {
    //if this is the place to insert
    if(current->getRight() == NULL) {
      //if the parent is black
      if(black) {
	//just add the node
	current->setRight(toAdd);
	toAdd->setParent(current);
	return;
      }
      //if the parent isn't black
      else {
	//add the node
	toAdd->setParent(current);
	current->setRight(toAdd);
	//if both the parent and uncle are black, call the uncle function, and if the top is red, make the top black
	if(current->getColor() == false && toAdd->getUncle() != NULL && toAdd->getUncle()->getColor() == false) {
	  unclefix(toAdd);
	  if(!top->getColor()) {
	    top->setColor(true);
	  }
	}
	//if the parent is red and the uncle is black, and the parent is the right child of the grandparent (the added node is the right child of the parent)
	else if(current->getColor() == false && (toAdd->getUncle() == NULL || toAdd->getUncle()->getColor() == true) && current->getParent()->getRight() == current) {
	  //do a left rotation with the parent and grandparent
	  leftRT(current,current->getParent());
	  //recolor
	  current->getLeft()->setColor(false);
	  current->setColor(true);
	}
	//if the parent is red and the uncle is black, and the parent is the left child of the grandparent (the added node is the right child of the parent)
	else if(current->getColor() == false && (toAdd->getUncle() == NULL || toAdd->getUncle()->getColor() == true) && current->getParent()->getLeft() == current) {
	  //left rotate the added value and the parent, and do the same thing as the previous case
	  leftRT(toAdd, current);
	  //right rotate the added value is now the parent, to right rotate the added value
	  rightRT(toAdd,toAdd->getParent());
	  //recolor
	  toAdd->getLeft()->setColor(false);
	  toAdd->setColor(true);
	}
      }
    }
    //go to the next node in the tree
    else {
      add(toAdd, current->getRight());
    }
  }
  //if the value is not greater than the current value
  else {
    //and this is the right place to add the node
    if(current->getLeft() == NULL) {
      //if the parent is black, just add the node
      if(black) {
	current->setLeft(toAdd);
	toAdd->setParent(current);
	return;
      }
      //otherwise
      else {
	//add the node
	toAdd->setParent(current);
	current->setLeft(toAdd);
	//if both the parent and the uncle are red, call the uncle function
	if(current->getColor() == false && toAdd->getUncle() != NULL && toAdd->getUncle()->getColor() == false) {
	  unclefix(toAdd);
	  //if the top is red, make it black
	  if(!top->getColor()) {
	    top->setColor(true);
	  }
	}
	//if the parent is red and the uncle is black
	if(current->getColor() == false && (toAdd->getUncle() == NULL || toAdd->getUncle()->getColor() == true)) {
	  if(current->getParent()->getLeft() == current) {
	    //do a right rotation with the parent and grandparent
	    rightRT(current,current->getParent());
	    //recolor
	    current->getRight()->setColor(false);
	    current->setColor(true);
	  }
	  else {
	    //do a left rotation with the added and parent
	    leftRT(toAdd,current);
	    //do a left rotation with teh added value which is now the parent of the former parent, and the current parent of the added value
	    rightRT(toAdd, toAdd->getParent());
	    //recolor
	    toAdd->getRight()->setColor(false);
	    toAdd->setColor(true);
	  }
	}
      }
    }
    else {
      add(toAdd, current->getLeft());
    }
  }
}

void RBtree::unclefix(Node* current) {
  if(current == top) {
    return;
  }
  Node* nParent = current->getParent();
  Node* nUncle = current->getUncle();
  //if the uncle is black
  if(nUncle == NULL || nUncle->getColor()) {
    //and the parent and grandparent aren't null
    if(nParent != NULL && nParent->getParent() != NULL) {
      //if the parent is the left
      if(nParent->getParent()->getLeft() == nParent) {
	if(nParent->getLeft() == current) {
	  rightRT(nParent, nParent->getParent());
	}
	else {
	  leftRT(current,nParent);
	  rightRT(current,current->getParent());
	}
      }
      //if the parent is the right child
      else {
	if(nParent->getRight() == current) {
	  leftRT(nParent, nParent->getParent());
	}
	else {
	  rightRT(current, nParent);
	  leftRT(current, current->getParent());
	}
      }
    }
  }
  else {
    if(nParent != NULL) {
      nParent->setColor(true);
    }
    else {
      return;
    }
    if(nUncle != NULL) {
      nUncle->setColor(true);
    }
  }
  if(current->getGP() != NULL) {
    nParent->getParent()->setColor(false);
    unclefix(current->getGP());
  }
}


void RBtree::leftRT(Node* lower, Node* upper) {
  int left;
  Node* upParent = upper->getParent();
  if(upper->getParent() == NULL) {
    left = 0;
  }
  else if(upper->getParent()->getLeft() == upper) {
    left = 1;
  }
  else {
    left = 2;
  }
  lower->setParent(upper->getParent());
  if(upper == top) {
    top = lower;
  }
  upper->setRight(lower->getLeft());
  if(upper->getRight() != NULL) {
    upper->getRight()->setParent(upper);
  }
  lower->setLeft(upper);
  upper->setParent(lower);
  if(left == 1) {
    upParent->setLeft(lower);
  }
  else if(left == 2) {
    upParent->setRight(lower);
  }
}

void RBtree::rightRT(Node* lower, Node* upper) {
  int left;
  Node* upParent = upper->getParent();
  if(upParent == NULL) {
    left = 0;
  }
  else if(upParent->getLeft() == upper) {
    left = 1;
  }
  else {
    left = 2;
  }
  lower->setParent(upper->getParent());
  if(upper == top) {
    top = lower;
  }
  upper->setLeft(lower->getRight());
  if(upper->getLeft() != NULL) {
    upper->getRight()->setParent(upper);
  }
  lower->setRight(upper);
  upper->setParent(lower);
  if(left == 1) {
    upParent->setLeft(lower);
  }
  else if(left == 2) {
    upParent->setRight(lower);
  }
}
