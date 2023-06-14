#include "RBtree.h"
 /* Name: Ishaan Varma
Date: 5/19/2023
Purpose: to implement the red black tree functions
*/
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
    cout << "\t\t";
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



void RBtree::add(Node* toAdd, Node* current) {
  //if the tree is empty, put the node into the top *tested
  if(top==NULL) {
    top = toAdd;
    toAdd->setColor(true);
    return;
  }
  /*  cout << "Address:" << toAdd << " Value to be Added: " << toAdd->getData();
  cout << "Current left: " << current->getLeft() << endl;
  if(current->getLeft() != NULL) {
    cout << " Data: " << current->getLeft()->getData() << endl;
  }
  cout << "Current right: " << current->getRight() << endl;
  if(current->getRight() != NULL) {
    cout << " Data: " << current->getRight()->getData() << endl;
    }*/
  bool greater = toAdd->getData() >= current->getData();
  bool black = current->getColor();
  //if greater
  if(greater) {
    //if this is the place to insert
    if(current->getRight() == NULL) {
      //if the parent is black *tested
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
	//if both the parent and uncle are red, call the uncle function, and if the top is red, make the top black *
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
	//if the parent is red and the uncle is black, and the parent is the left child of the grandparent (the added node is the right child of the parent) *tested
	else if(current->getColor() == false && (toAdd->getUncle() == NULL || toAdd->getUncle()->getColor() == true) && current->getParent()->getLeft() == current) {
	  //left rotate the added value and the parent, and do the same thing as the previous case
	  leftRT(toAdd, current);
	  //right rotate the added value is now the parent, to right rotate the added value
	  rightRT(toAdd,toAdd->getParent());
	  //recolor
	  toAdd->getRight()->setColor(false);
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
	  //if the parent is the left child of the grandparent *tested
	  if(current->getParent()->getLeft() == current) {
	    //do a right rotation with the parent and grandparent
	    rightRT(current,current->getParent());
	    //recolor
	    current->getRight()->setColor(false);
	    current->setColor(true);
	  }
	  else {
	    //do a right rotation with the added and parent
	    rightRT(toAdd,current);
	    //do a left rotation with teh added value which is now the parent of the former parent, and the current parent of the added value
	    leftRT(toAdd, toAdd->getParent());
	    //recolor
	    toAdd->getLeft()->setColor(false);
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
  if(nParent == NULL || nParent->getColor()) {
    return;
  }
  //if the uncle is black
  if(nUncle == NULL || nUncle->getColor()) {
    //and the parent and grandparent aren't null
    if(nParent != NULL && nParent->getParent() != NULL) {
      //if the parent is the left *tested
      if(nParent->getParent()->getLeft() == nParent) {
	//and the child is the left, then right rotate the parent and the grandparent *tested 2
	if(nParent->getLeft() == current) {
	  nParent->setColor(true);
	  nParent->getParent()->setColor(false);
	  rightRT(nParent, nParent->getParent());
	}
	//otherwise, left rotate the current and the parent, then right rotate the child and the parent *tested 2
	else {
	  leftRT(current,nParent);
	  nParent->setColor(true);
	  nParent->getParent()->setColor(false);
	  rightRT(current,current->getParent());
	}
      }
      //if the parent is the right child
      else {
	//if current is the right child of the current, the left rotate the parent and the grandparent *tested
	if(nParent->getRight() == current) {
	  nParent->setColor(true);
	  nParent->getParent()->setColor(false);
	  leftRT(nParent, nParent->getParent());
	}
	//otherwise, right rotate the current and the parent first, then left rotate current and current's current parent, which was previously the grandparent *tested 2
	else {
	  rightRT(current, nParent);
	  current->setColor(true);
	  current->getParent()->setColor(false);
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


bool RBtree::search(int data) {
  return search(data, top);
}

bool RBtree::search(int data, Node* current) {
  if(current->getData() == data) {
    return true;
  }
  else {
    if(data < current->getData()) {
      if(current->getLeft() == NULL) {
	return false;
      }
      else {
	return search(data, current->getLeft());
      }
    }
    else {
      if(current->getRight() == NULL) {
	return false;
      }
      else {
	return search(data,current->getRight());
      }
    }
  }
}

void RBtree::deletion(int data, Node* current) {
  bool isTop = top == current;
  if(current->getData() == data) {
    //no child
    if(current->getLeft() == NULL && current->getRight() == NULL) {
      if(isTop) {
	top = NULL;
	delete current;
	return;
      }
      if(current->getColor()) {
	if(!current->getParent()->getColor()) {
	  current->getParent()->setColor(true);
	  bool rightChild = current->getParent()->getRight() == current;
	  if(rightChild) {
	    current->getParent()->setRight(NULL);
	  }
	  else {
	    current->getParent()->setLeft(NULL);
	  }
	  return;
	}
	else {
	  Node* parent = current->getParent();
	  bool rightChild = current->getParent()->getRight() == current;
	  Node* sibling = NULL;
	  if(rightChild) {
	    parent->setRight(NULL);
	    sibling = parent->getLeft();
	  }
	  else {
	    parent->setLeft(NULL);
	    sibling = parent->getRight();
	  }
	  delete current;
	  doubleBlackFix(NULL, parent, sibling, rightChild);
	}
      }
      else {
	if(current->getParent()->getRight() == current) {
	  current->getParent()->setRight(NULL);
	}
	//if the node to be deleted has no children and is red, just set the parents pointer to the child to NULL, and delete the node *tested
	else {
	  current->getParent()->setLeft(NULL);
	}
      }
      delete current;
    }
    //has a right child but not a left child
    else if(current->getRight() != NULL && current->getLeft() == NULL) {
      //and is black
      if(current->getColor()) {
	//and the child is red, set the parent of right to current's right, and put current's right in current's place, then delete current
	if(!current->getRight()->getColor()) {
	  current->getRight()->setParent(current->getParent());
	  if(current->getParent() != NULL) {
	    if(current->getParent()->getRight() == current) {
	      current->getParent()->setRight(current->getRight());
	    }
	    else {
	      current->getParent()->setLeft(current->getLeft());
	    }
	  }
	  current->getRight()->setColor(true);
	  if(isTop) {
	    top = current->getRight();
	  }
	  delete current;
	}
	
	//if the child is black
	else {
	  //case 1, if current is the top
	  if(isTop) {
	    top = current->getRight();
	    current->getRight()->setParent(NULL);
	    top->setColor(true);
	    delete current;
	    return;
	  }
	  //all other cases
	  else {
	    //set up the double black
	    Node* actual = current->getRight();
	    bool rightParent = current->getParent()->getRight() == current;
	    Node* sibling = NULL;
	    if(rightParent) {
	      current->getParent()->setRight(current->getRight());
	      current->getRight()->setParent(current->getParent());
	      sibling = current->getParent()->getLeft();
	    }
	    else {
	      current->getParent()->setLeft(current->getRight());
	      current->getRight()->setParent(current->getParent());
	      sibling = current->getParent()->getRight();
	    }
	    delete current;
	    doubleBlackFix(actual, actual->getParent(), sibling, rightParent);
	    
	  }
	}
      }
      //and is red
      else {
	current->getRight()->setParent(current->getParent());
	if(isTop) {
	  top = current->getRight();
	  current->getRight()->setColor(true);
	  delete current;
	}
	else {
	  if(current->getParent()->getRight() == current) {
	    current->getParent()->setRight(current->getRight());
	  }
	  else {
	    current->getParent()->setLeft(current->getLeft());
	  }
	  delete current;
	}
      }
    }
    //has a left child but not a right child
    else if(current->getLeft() != NULL && current->getRight() == NULL) {
      //and current is black
      if(current->getColor()) {
	//and the child is red, set the child's parent to current's parent, and replace current with the child
	if(!current->getLeft()->getColor()) {
	  current->getLeft()->setParent(current->getParent());
	  if(current->getParent() != NULL) {
	    if(current->getParent()->getRight() == current) {
	      current->getParent()->setRight(current->getLeft());
	    }
	    else {
	      current->getParent()->setLeft(current->getLeft());
	    }
	  }
	  current->getLeft()->setColor(true);
	  if(isTop) {
	    top = current->getRight();
	  }
	  delete current;
	}
	else {
	  //case 1, if current is the top
	  if(isTop) {
	    top = current->getLeft();
	    current->getLeft()->setParent(NULL);
	    delete current;
	    return;
	  }
	  //all other cases
	  else {
	    //set up the double black
	    Node* actual = current->getLeft();
	    bool rightParent = current->getParent()->getRight() == current;
	    Node* sibling = NULL;
	    if(rightParent) {
	      current->getParent()->setRight(current->getLeft());
	      current->getLeft()->setParent(current->getParent());
	      sibling = current->getParent()->getLeft();
	    }
	    else {
	      current->getParent()->setLeft(current->getLeft());
	      current->getLeft()->setParent(current->getParent());
	      sibling = current->getParent()->getRight();
	    }
	    delete current;
	    doubleBlackFix(actual, actual->getParent(), sibling, rightParent);
	  }
	}
      }
      //and current is red
      else {
	if(isTop) {
	  top = current->getLeft();
	  delete current;
	}
	else {
	  current->getLeft()->setParent(current->getParent());
	  if(current->getParent()->getRight() == current) {
	    current->getParent()->setRight(current->getLeft());
	  }
	  else {
	    current->getParent()->setLeft(current->getLeft());
	  }
	}
      }
    }
    //has 2 children
    else {
      if(current->getLeft() != NULL) {
      Node* itr = current->getLeft();
      while(itr->getRight() != NULL) {
	itr = itr->getRight();
      }
      current->setData(itr->getData());
      deletion(itr->getData(), itr);
      }
      else {
	Node* itr = current->getRight();
	while(itr->getLeft() != NULL) {
	  itr = itr->getLeft();
	}
	current->setData(itr->getData());
	deletion(itr->getData(), itr);
      }
    }
  }
  else if(current->getData() > data) {
    deletion(data, current->getLeft());
  }
  else {
    deletion(data, current->getRight());
  }
}



void RBtree::doubleBlackFix(Node* u, Node* sparent, Node* sibling, bool rightParent) {
  if(u != NULL && u == top) {
    u->setColor(true);
    return;
  }
  //if the double black node is the right child of the parent
  if(rightParent) {
    //the sibling is the left child
    //if the sibling isn't null
    if(sibling != NULL) {
      //and the sibling is black
      if(sibling->getColor()) {
	//if the left child of sibling is red, do the left left case
	if(sibling->getLeft() != NULL && !sibling->getLeft()->getColor()) {
	  //right rotate the sibling and the parent
	  rightRT(sibling, sparent);
	}
	//if the right child of sibling is red and the left child isn't, do the left right case
	else if(sibling->getRight() != NULL && !sibling->getRight()->getColor()) {
	  //left rotate the siblign and the child
	  leftRT(sibling->getRight(), sibling);
	  //recolor
	  sibling->getParent()->setColor(true);
	  sibling->setColor(false);
	  //rotate the child, which is now sibling's parent, and siblings old parent.
	  rightRT(sibling->getParent(), sparent);
	}
	//both
	else {
	  sibling->setColor(false);
	  Node* nParent = sparent->getParent();
	  bool rightchild = true;
	  Node* nsibling = NULL;
	  if(nParent != NULL) {
	    rightchild = nParent->getRight() == sparent;
	    if(rightchild) {
	      nsibling = nParent->getLeft();
	    }
	    else {
	     nsibling = nParent->getRight();
	    }
	  }
	  if(sparent->getColor()) {
	    doubleBlackFix(sparent, nParent, nsibling, rightchild);
	  }
	  else {
	    sparent->setColor(true);
	    return;
	  }
	}
      }
      //the sibling is red
      else {
	sparent->setColor(false);
	sibling->setColor(true);
	rightRT(sibling, sparent);
	bool rightchild = sparent->getRight() == u;
	Node* nsibling = NULL;
	if(rightchild) {
	  nsibling = sparent->getLeft();
	}
	else {
	  nsibling = sparent->getRight();
	}
	if(nsibling != NULL) {
	  nsibling->setColor(false);
	}
	if(sparent->getColor()) {
	  doubleBlackFix(sparent, sparent->getParent(), sparent->getParent()->getRight(), true);
	}
	else {
	  sparent->setColor(true);
	}
      }
    }
    else {
      return;
    }
  }
  //if the double black node is the left child of the parent
  else {
    //the sibling is the right child
    //if the sibling isn't null
    if(sibling != NULL) {
      //and the sibling is black
      if(sibling->getColor()) {
	//if siblings right child is red, do the right right case
	if(sibling->getRight() != NULL && !sibling->getRight()->getColor()) {
	  //left rotate the parent and sibling
	  leftRT(sibling, sparent);
	}
	//if sibling left child is red and the right child isn't, do the left left case
	else if(sibling->getLeft() != NULL && !sibling->getLeft()) {
	  //right rotate the sibling
	  rightRT(sibling->getLeft(), sibling);
	  //recolor
	  sibling->getParent()->setColor(true);
	  sibling->setColor(false);
	  //left rotate sibling previous child, which is now its parent due to the previous right rotation, with sparent
	  leftRT(sibling->getParent(), sparent);
	}
	//do a different case
	else {
	  sibling->setColor(false);
	  Node* nParent = sparent->getParent();
	  bool rightchild = true;
	  Node* nsibling = NULL;
	  if(nParent!= NULL) {
	    rightchild = nParent->getRight() == sparent;
	    if(rightchild) {
	      nsibling = nParent->getLeft();
	    }
	    else {
	      nsibling = nParent->getRight();
	    }
	  }
	  if(sparent->getColor()) {
	    doubleBlackFix(sparent, nParent, nsibling, rightchild);
	  }
	  else {
	    sparent->setColor(true);
	  }
	}
      }
      //the sibling is red
      else {
	sparent->setColor(false);
	sibling->setColor(true);
	leftRT(sibling, sparent);
	bool rightchild = sibling->getRight() == sparent;
	if(sparent->getColor()) {
	  doubleBlackFix(sparent, sibling, sibling->getRight(), rightchild);
	}
	else {
	  sparent->setColor(true);
	}
      }
    }
    //if the sibling is null
    else {
      return;
    }
  }
}
