#pragma once
#ifndef EDITOR_
#define EDITOR_

#include <string>
#include "LinkedList.h"
#include "StackInterface.h"
#include "Node.h"
#include "ListInterface.h"
#include "LinkedStack.h"
#include "Command.h"
#include <fstream>
#include "BinarySearchTree.h"
#include "BinaryNodeTree.h"
#include "BinaryNode.h"

using namespace std;


class Editor
{
public:
		void displayLines();
		void readFile(ifstream&, ifstream&);
		Editor();
		void processCommand(char);
		void saveFile();
		

private:
	BinarySearchTree<string>* bstKeyWords;
	LinkedList<string> myList;
	LinkedStack<Command> undoStack;
	
	Command commandObject;
	int currentLine;
	int currentPosition;
	int numLines;
	string readLine;
	string myLine;

	string deleteCharInLine;
	string insertCharInLine;

	int lengthOfLine;
};
#endif // !EDITOR_
