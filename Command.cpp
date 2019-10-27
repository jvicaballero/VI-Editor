#include "Command.h"
#include <string>
#include <iostream>

//Command not templated

string Command::getCommand() 
{
	return key;
}

void Command::setCommand(string inputCommand)
{
	key = inputCommand;
}

string Command::getValue() {
	return value;
}

void Command::setValue(string commandInputValue)
{
	value = commandInputValue;
}

Command::Command() 
{
	key = "\0";
	value = "\0";

}

void Command::display() const
{
	cout << "Command = " << key << endl;
	cout << "Value = " << value << endl;
	
}

int Command::getLineNumber()
{
	return lineNumber;
}

void Command::setLineNumber(int line)
{
	lineNumber = line;
}

