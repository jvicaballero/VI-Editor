#include "Editor.h"
#include <string>
#include <iostream>
#include "LinkedList.h"
#include "Command.h"
#include <conio.h>
#include "Node.h"
#include <sstream>
#include <iterator>
#include <vector>
#include <Windows.h>
#include <fstream>


void goToXY(int column, int line) {

	COORD coord;

	coord.X = column;

	coord.Y = line;

	SetConsoleCursorPosition(

		GetStdHandle(STD_OUTPUT_HANDLE),

		coord);


}

void colorText(int value) {

	COORD coord;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	FlushConsoleInputBuffer(hConsole);

	SetConsoleTextAttribute(hConsole, value);

}
void Editor::displayLines()
{

	int i, j;

	for (i = 1; i < numLines + 1; i++)
	{
		myLine = myList.getEntry(i);
		
		istringstream streamWords{ myLine };
		
		vector<string> words{
			istream_iterator<string>(streamWords), istream_iterator<string>() };
		
		bool isKeyword;

		for (string currentWord : words) {

			isKeyword = bstKeyWords->contains(currentWord);

			if (isKeyword)
				colorText(FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | 0X80);  //blue

			else
				colorText(0XF0);

				//note: updated to remove the extra blanks

				if (currentPosition == 0)
					cout << currentWord;

				else

					cout << " " << currentWord;

		}

		cout << endl;

	}

	goToXY(currentPosition, currentLine - 1);

}


	

void Editor::readFile(ifstream& inFile, ifstream& keyWordsFile)
{

	for (int i = 1; !inFile.eof(); i++)
	{
		getline(inFile, readLine);

		lengthOfLine = readLine.length();

		myList.insert(i, readLine);

		numLines++;
	}

	bstKeyWords = new BinarySearchTree<string>();
	string keyWord;

	while (!keyWordsFile.eof())
	{
		keyWordsFile >> keyWord;
		
		bstKeyWords->add(keyWord);

	}


}

Editor::Editor()
{
	currentLine = 1;
	currentPosition = 1;
	numLines = 0;
}

void Editor::processCommand(char inputCommand)
{
	string line;

	if (inputCommand == 'j') //down
	{
		if (currentLine < numLines)
			currentLine++;

		line = myList.getEntry(currentLine);
		lengthOfLine = line.length();

		if (currentPosition >= lengthOfLine)
			currentPosition = lengthOfLine;

	}
	
	if (inputCommand == 'k') //up
	{
		if (currentLine > 1)
				currentLine--;

		line = myList.getEntry(currentLine);
		lengthOfLine = line.length();

		if (currentPosition >= lengthOfLine)
			currentPosition = lengthOfLine;
	}

	if (inputCommand == 'l') //right
	{
		line = myList.getEntry(currentLine);
		lengthOfLine = line.length();
		if (currentPosition < lengthOfLine)
			currentPosition++;

	}
	if (inputCommand == 'h') //left
		if (currentPosition > 1)
			currentPosition--;

	if (inputCommand == 'd')
		if (_getch() == 'd')
			{
			commandObject.setValue(myList.getEntry(currentLine));
			commandObject.setLineNumber(currentLine);
			commandObject.setCommand("dd");
			

			undoStack.push(commandObject);
			myList.remove(currentLine);
			numLines--;
			}

	if (inputCommand == 'u')
	{

		if (!undoStack.isEmpty())
		{
			if (commandObject.getCommand() == "dd")
			{
				myList.insert(commandObject.getLineNumber(), commandObject.getValue());
				numLines++;

				undoStack.pop();
				
			}

			if (commandObject.getCommand() == "I")
			{
				myList.remove(commandObject.getLineNumber());
				numLines--;

				undoStack.pop();
			}

			if (commandObject.getCommand() == "x")
			{			
				myList.replace(commandObject.getLineNumber(), commandObject.getValue());

				undoStack.pop();
	

			}

			if (commandObject.getCommand() == "i")
			{
				myList.replace(commandObject.getLineNumber(), commandObject.getValue());

				undoStack.pop();

			}
			
			//This will update the values in the Command object
			//on the undo stack after popping off the most recent one
			if (!undoStack.isEmpty())
			{
				Command prevCommandObjectInStack;
				prevCommandObjectInStack = undoStack.peek();
				commandObject.setValue(prevCommandObjectInStack.getValue());
				commandObject.setCommand(prevCommandObjectInStack.getCommand());
				commandObject.setLineNumber(prevCommandObjectInStack.getLineNumber());
			
			}


		}

	}

	if (inputCommand == 'I')
	{
		goToXY(1, numLines);
		cout << "<Insert Mode>" << endl;

		string stringEntry;
		
		//Have to press enter to get out of insert mode, not escape since its getline
		getline(cin, stringEntry);
		
		Node<string>* newNode = new Node<string>(stringEntry);


		myList.insert(currentLine, stringEntry);

		commandObject.setValue(myList.getEntry(currentLine));
		commandObject.setLineNumber(currentLine);
		commandObject.setCommand("I");

		undoStack.push(commandObject);
		numLines++;

	}

	if (inputCommand == 'x')
	{
		deleteCharInLine = myList.getEntry(currentLine);

		lengthOfLine = deleteCharInLine.length();

		//restrict deletion so it doesn't delete past the line (the extra spaces of the file)
		if (currentPosition <= lengthOfLine)
		{
			commandObject.setValue(deleteCharInLine);
			commandObject.setLineNumber(currentLine);
			commandObject.setCommand("x");
			undoStack.push(commandObject);

			deleteCharInLine.erase(currentPosition - 1, 1);
			myList.replace(currentLine, deleteCharInLine);
		}
	
	}

	
	if (inputCommand == 'i')
	{
		string whatToInsert = "";
		insertCharInLine = myList.getEntry(currentLine);

		goToXY(1, numLines + 1);
		cout << "<Insert Mode>";

		goToXY(currentPosition + 1, currentLine - 1);
		
		char ch;
		while ((ch = _getche()) != 27)
		{
			whatToInsert += ch;
		}

		commandObject.setValue(insertCharInLine);
		commandObject.setLineNumber(currentLine);
		commandObject.setCommand("i");
		undoStack.push(commandObject);

		insertCharInLine.insert(currentPosition, whatToInsert);
		myList.replace(currentLine, insertCharInLine);


	}

	//saving the file
	if (inputCommand == ':')
		if (_getch() == 'w')
		{
			saveFile();
			
			goToXY(1, numLines + 1);
			cout << "Saved, please check external file";
			system("pause>null");
		}

}

//press ':' 
//then 'w' to save the file
void Editor::saveFile()
{
	ofstream outFile;

	outFile.open("result.txt");

	for (int i = 1; i < numLines; i++)
		outFile << myList.getEntry(i) << endl;

	outFile.close();
}

