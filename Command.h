#pragma once

#ifndef COMMAND_
#define COMMAND_

#include "StackInterface.h"
#include "Node.h"
#include "ArrayStack.h"
#include <string>


class Command 
{
public:
	string getCommand();
	void setCommand(string);
	string getValue();
	void setValue(string);
	int getLineNumber();
	void setLineNumber(int);
	void display() const;



	Command();

private:
	string key;
	string value;
	int lineNumber;



};


#endif