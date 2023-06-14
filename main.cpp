#include <iostream>
#include <cstring>
#include "RBtree.h"
#include <fstream>

/* Name: Ishaan Varma
Date: 5/5/2023
Purpose: main file where the commands are taken in.

 */

void singlelowercase(char sentence[]);


using namespace std;

int main() {
  RBtree* tree = new RBtree();
  char command[10];
  int num;
  char fileName[100];
  while(true) {
    cout << "Type in quit, add or print, delete, search, file(for adding with a file), or filedelete(for deleting with a file)." << endl;
    cin >> command;
    singlelowercase(command);
    if(strcmp(command, "quit") == 0) {
      return 0;
    }
    else if(strcmp(command, "add") == 0) {
      cout << "Which number would you like to add?" << endl;
      cin >> num;
      Node* addition = new Node(num);
      tree->add(addition, tree->getTop());
    }
    else if(strcmp(command, "print") == 0) {
      tree->print(tree->getTop(),0);
    }
    else if(strcmp(command, "file") == 0) {
      cout << "Give the file name here: " << endl;
      cin >> fileName;
      ifstream finput(fileName);
      if(!finput.good()) {
	cout << "No file." << endl;
	continue;
      }
      int add;
      while(finput >> add) {
	tree->add(new Node(add), tree->getTop());
      }
    }
    else if(strcmp(command, "filedelete") == 0) {
      cout << "Give the file name here: " << endl;
      cin >> fileName;
      ifstream finput(fileName);
      if(!finput.good()) {
	cout << "No file." << endl;
	continue;
      }
      int add;
      while(finput >> add) {
	//cout << add << "e" << endl;
	if(tree->getTop() != NULL) {
	  tree->deletion(add, tree->getTop());
	  //tree->print(tree->getTop(), 0);
	}
      }
    }
    else if(strcmp(command, "search") == 0) {
      cout << "Which number do you wish to find?" << endl;
      cin >> num;
      if(tree->search(num)) {
	cout << "The tree contains that number." << endl;
      }
      else {
	cout << "No number in the tree." << endl;
      }
    }
    else if(strcmp(command, "delete") == 0) {
      cout << "Which number do you wish to delete?" << endl;
      cin >> num;
      bool test = true;
      tree->deletion(num, tree->getTop());
      test = true;
    }
  
  }
}


void singlelowercase(char sentence[]) {
  //iterating variable
   int i = 0;
   //go through the char array
   while(true) {
     int charVal = (int) sentence[i];
     //if the letter is capital, make it lowercase using ASCII
     if(65<=charVal && charVal <= 90) {
       sentence[i] = (char)(charVal+32);
     }
     //if the character is the null character, 
     else if(sentence[i] == '\0') {
       break;
     }
     //increment the variable
     i++;
   }
}
