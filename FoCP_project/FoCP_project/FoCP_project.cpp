#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"
#include <iostream>
#include <string>


using namespace std;

class Stack {
private:
	char data[100];
	int size;
public:
	Stack() {
		size = 0;
	}
	char stackTop() {
		if (size == 0)
		{
			//cout << "Empty stack " << endl;
			return '\0';
		}
		return data[size - 1];
	}
	bool stackPush(char d) {
		if (size < 100) {
			data[size++] = d;
			return true;
		}
		else {
			cout << "Error: stack full" << endl;
			return false;
		}
	}
	bool stackPop() {
		if (size == 0) {
			cout << "error: stack empty" << endl;
			return false;
		}
		else {
			size--;
			return true;
		}
	}
};


int main()
{
	//expresion given by the user
	string expressionToCalc;
	//array to store eqation in RPN
	string reversedPolishNotation[255];
	Stack stack;
	//get expression from the user
	cin >> expressionToCalc;
	expressionToCalc += '\0';
	int onp_iterator = 0;
	string helper = "";
	//implementation of the algorithm of transformation to RPN
	for (int i = 1; i<expressionToCalc.length(); i++)
	{
		char character = expressionToCalc[i - 1];
		char nextCharacter = expressionToCalc[i];

		if (character == '0' || character == '1' || character == '2' || character == '3' || character == '4'
			|| character == '5' || character == '6' || character == '7' || character == '8' || character == '9')
		{
			if (nextCharacter == '0' || nextCharacter == '1' || nextCharacter == '2' || nextCharacter == '3' || nextCharacter == '4'
				|| nextCharacter == '5' || nextCharacter == '6' || nextCharacter == '7' || nextCharacter == '8' || nextCharacter == '9')
			{
				helper += character;
			}
			else if (nextCharacter == '\0' || nextCharacter == '-' || nextCharacter == '/' || nextCharacter == '+' || nextCharacter == '*' || nextCharacter == '(' || nextCharacter == ')')
			{
				helper += character;
				reversedPolishNotation[onp_iterator] = helper;
				onp_iterator++;
				helper.clear();
			}
		}

		if (character == '-' || character == '/' || character == '+' || character == '*')
		{
			while ((character == '-' || (character == '/' && (stack.stackTop() == '*' || stack.stackTop() == '/'))
				|| (character == '+' && (stack.stackTop() == '*' || stack.stackTop() == '/')))
				&& (stack.stackTop() != '\0' && stack.stackTop() != '(' && stack.stackTop() != ')'))
			{
				string s = "";
				s += stack.stackTop();
				reversedPolishNotation[onp_iterator] = s;
				stack.stackPop();
				onp_iterator++;
			}
			stack.stackPush(character);
		}
		if (character == '(')
			stack.stackPush(character);
		if (character == ')')
		{
			while (stack.stackTop() != '(')
			{
				string s = "";
				s += stack.stackTop();
				reversedPolishNotation[onp_iterator] = s;
				stack.stackPop();
				onp_iterator++;
			}
			stack.stackPop();
		}
	}
	while (stack.stackTop() != '\0')
	{
		string s = "";
		s += stack.stackTop();
		reversedPolishNotation[onp_iterator] = s;
		stack.stackPop();
		onp_iterator++;
	}
	string s = "\0";
	reversedPolishNotation[onp_iterator] = s;

	// calculate value of an expression represented in array
	bool flag = true;
	while (flag) {
		for (int i = 0; i<255; i++)
		{
			if (reversedPolishNotation[1] == "\0")
			{
				flag = false;
				break;
			}
			if (reversedPolishNotation[i] == "-")
			{
				reversedPolishNotation[i - 2] = to_string(stof(reversedPolishNotation[i - 2]) - stof(reversedPolishNotation[i - 1]));
				i++;
				for (; reversedPolishNotation[i] != "\0"; i++) {
					reversedPolishNotation[i - 2] = reversedPolishNotation[i];
				}
				reversedPolishNotation[i - 2] = reversedPolishNotation[i];
				break;
			}
			if (reversedPolishNotation[i] == "+")
			{
				reversedPolishNotation[i - 2] = to_string(stof(reversedPolishNotation[i - 2]) + stof(reversedPolishNotation[i - 1]));
				i++;
				for (; reversedPolishNotation[i] != "\0"; i++) {
					reversedPolishNotation[i - 2] = reversedPolishNotation[i];
				}
				reversedPolishNotation[i - 2] = reversedPolishNotation[i];
				break;
			}
			if (reversedPolishNotation[i] == "/")
			{
				reversedPolishNotation[i - 2] = to_string(stof(reversedPolishNotation[i - 2]) / stof(reversedPolishNotation[i - 1]));
				i++;
				for (; reversedPolishNotation[i] != "\0"; i++) {
					reversedPolishNotation[i - 2] = reversedPolishNotation[i];
				}
				reversedPolishNotation[i - 2] = reversedPolishNotation[i];
				break;
			}
			if (reversedPolishNotation[i] == "*")
			{
				reversedPolishNotation[i - 2] = to_string(stof(reversedPolishNotation[i - 2]) * stof(reversedPolishNotation[i - 1]));
				i++;
				for (; reversedPolishNotation[i] != "\0"; i++) {
					reversedPolishNotation[i - 2] = reversedPolishNotation[i];
				}
				reversedPolishNotation[i - 2] = reversedPolishNotation[i];
				break;
			}
		}

	}
	cout << reversedPolishNotation[0] << endl;
	system("PAUSE");
	return 0;
}
