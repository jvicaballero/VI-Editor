#include <iostream>
#include "ArrayStack.h""
#include "Node.h"
#include "LinkedStack.h"
#include "StackInterface.h"
#include "PrecondViolatedExcept.h"
#include "Command.h"
#include <fstream>
#include "ListInterface.h"
#include "LinkedList.h"
#include "Editor.h"
#include <conio.h>


using namespace std;

int main()
{
	ifstream inFile;

	string readLine;

	Editor myEditor;
	string replaceLine;

	int length;

	ifstream keyWordFile;
	//open  for key words txt file

	
	keyWordFile.open("keyWords.txt");

	if (!keyWordFile)
	{
		cout << "File not found/could not be opened" << endl;
		system("pause");
		return 1;
	}


	inFile.open("sampleText.txt");

	if (!inFile)
	{
		cout << "File cannot be opened/not found" << endl;
		system("pause");
		return 1;
	}// end if


	
	myEditor.readFile(inFile , keyWordFile);

	myEditor.displayLines();

	char ch = _getch();

	do {

		myEditor.processCommand(ch);

		system("cls");

		myEditor.displayLines();

		ch = _getch();



	} while (ch != 'q');
	cout << endl;
	


	keyWordFile.close();
	inFile.close();

	system("pause");
	
	//do while loop

	return 0;


}
