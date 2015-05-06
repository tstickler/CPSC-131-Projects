/***********************************************************
* Assignment #2                                            *
* Created by Tyler Stickler                                *
* CPSC 131-01                                              *
*                                                          *
* Postfix Calculator.cpp v 1.0                             *
* April 26, 2015                                           *
*                                                          *
* This program takes a postfix expression that is entered  *
* by the user and evaluates it by utilizing a stack. It    *
* also checks to make sure that the expression that is     *
* entered is valid i.e. one final answer with no left over *
* operators.                                               *
***********************************************************/

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/************************************************************
* Stack to store operands of postfix expression             *
************************************************************/
class OperandStack
{
private:
	double * s;  //pointer to 1D dynamic array for storing stack elements
	int capacity,  //stack capacity
		t;  //index of the top element on stack
	void growStack(int newCapacity);  //increases the stack if it is full
	//must be called from the push function if the stack is full

public:
	OperandStack(){ capacity = 0; s = NULL; t = -1; };
	OperandStack(int capacity);
	~OperandStack();
	int size() const;  //return the number of elements in the stack
	bool isFull() const;
	bool isEmpty() const;
	double top() const;  //returns the element at the top of the stack
	//without removing it from the stack
	void push(double x);
	void pop();
};

/************************************************************
* Parameterized Constructor that takes an int variable,     *
* capacity, and creates a stack of that size.               *
*      Input: int variable, capacity                        *
*      Return: none                                         *
************************************************************/
OperandStack::OperandStack(int capacity){
	this->capacity = capacity;
	s = new double[capacity];
	t = -1;
}

/************************************************************
* Destuctor. Deletes the stack.                             *
************************************************************/
OperandStack::~OperandStack(){
	delete[] s;
	s = NULL;
}

/************************************************************
* Function size() returns the number of elements in the     *
* stack.                                                    *
*      Input: none                                          *
*      Return: (t+1), which is the index of the top item.   *
*                 The +1 accounts for starting t at         *
*                 index -1                                  *
************************************************************/
int OperandStack::size() const{
	return (t + 1);
}

/************************************************************
* Function isFull() evaluates to true of false, depending   *
* on if the top of the stack is equal to the capacity - 1.  *
*      Input: none                                          *
*      Return: True if t = capacity - 1                     *
*              False otherwise                              *
************************************************************/
bool OperandStack::isFull() const{
	if (t == capacity - 1)
		return true;
	else
		return false;
}

/************************************************************
* Function isEmpty() evaluates to true or false, depending  *
* on if the top of the stack is equal to -1                 *
*       Input: none                                         *
*       Return: True if t = -1                              *
*               False otherwise                             *
************************************************************/
bool OperandStack::isEmpty() const{
	if (t == -1)
		return true;
	else
		return false;
}

/************************************************************
* Function top() returns the value for the top item in the  *
* stack without removing it from the stack.                 *
*      Input: none                                          *
*      Return: double element at index t                    *
************************************************************/
double OperandStack::top() const{

	try{
		if (isEmpty()){
			throw 0;
		}
		else
			return s[t];
	}
	catch (int err){
		cout << "Error: no elements in the stack...";
		return err;
	}
}

/************************************************************
* Function push() takes a double variable, elem, and pushes *
* it onto the top of the stack. If capacity is reached,     *
* function growStack() is called to increase the capacity.  *
*      Input: double variable, elem                         *
*      Return: none                                         *
************************************************************/
void OperandStack::push(double elem){
	t++;
	if (t == capacity)
		growStack(capacity * 2);
	s[t] = elem;
}

/************************************************************
* Function growStack() takes an int variable, newCapacity,  *
* and creates a new stack of that size(double the           *
* original's size). Then, the calling object's stack is     *
* copied into the new stack, and its pointer is reassigned  *
* to the new stack, while the old stack is deleted.         *
*     Input: int variable, newCapcity                       *
*     Return: none.                                         *
************************************************************/
void OperandStack::growStack(int newCapacity){
	double * temp = new double[newCapacity];

	for (int i = 0; i < capacity; i++)
		temp[i] = s[i];

	delete s;
	s = temp;
	temp = NULL;
	capacity = newCapacity;
}

/************************************************************
* Function pop() removes the top element of the stack       *
* without returning it. Using an array, this is achieved    *
* simply by decrementing the top.                           *
*      Input: none                                          *
*      Return: none                                         *
************************************************************/
void OperandStack::pop(){
	t--;
}

//Function declarations:
void doCalculation(OperandStack &, char);
void solvePostfix(const string &);
string getExpression();

//Main function:
void main(){
	char ans;
	do{
		solvePostfix(getExpression());
		cout << "Again? (y/n): ";
		cin >> ans;
		tolower(ans);
		cin.ignore();
		system("cls");
	} while (ans == 'y');

	cout << "Closing...\n";
}

/************************************************************
* Function getExpression() retrieves a postfix expression   *
* from the user.                                            *
*      Input: none                                          *
*      Return: string variable containing the expression    *
************************************************************/
string getExpression(){
	string expression;
	cout << "Please enter postfix expression: ";
	getline(cin, expression);
	return expression;
}

/************************************************************
* Function solvePostfix() takes a string expression from    *
* getExpression() and deciphers what to do with it. If the  *
* element is a white space, it skips it. If the element is  *
* a number, it is pushed onto the stack. If the element is  *
* an operator it calls for the doCalculation() function.    *
* This function also determines if an expression is valid   *
* or malformed.                                             *
*      Input: string variable, postfixExp                   *
*      Return: none                                         *
************************************************************/
void solvePostfix(const string & postfixExp){
	OperandStack myStack(5);
	stringstream ss(postfixExp);

	int numberCounter = 0, operatorCounter = 0;

	char element;
	double num;

	/*
	* While loop will execute as long as there are still 
	* elements in the stream.                            
	*/
	element = ss.peek();  //Prepares the loop
	while (element != EOF){
		if (isspace(element)){
			ss.get();  //Remove the white space from the string
			element = ss.peek();  //Readies the loop for the next char
			continue;
		}
		else if (isdigit(element)){
			ss >> num;  //Extract the value from the string
			myStack.push(num);  //Pushes the number onto the stack

			element = ss.peek();  //Readies the loop for the next char
			numberCounter++;
			continue;
		}
		else{
			char oper = element;  //Save the operator in case element is moved to a white space

			ss.get();  //Remove the operator from the string
			element = ss.peek();  //Readies the loop for the next char, allows to check for a digit

			/*
			* This if/else block allows the use of negative
			* numbers. By assigning and removing the operator
			* from the stream, peek() can see if the next
			* element in the stream is a number. If it is,
			* and the operator was negative, the number is
			* converted and pushed onto the stack. Otherwise,
			* the operation indicated is performed.
			*/
			if (oper == '-' && isdigit(element)){
				ss >> num;  // Extracts the value from the string
				num *= -1;  // Converts it to a negative
				myStack.push(num);  //Pushes the negative number onto the stack

				element = ss.peek();  //Readies the loop for the next char
				numberCounter++;
				continue;
			}
			else{
				/*
				* If, at any point, there are as many or more
				* operators as numbers pushed on to the stack,
				* then the expression is malformed...
				*/
				operatorCounter++;
				if (operatorCounter >= numberCounter){
					cout << "Malformed expression entered >:(\n\n";
					return;
				}
				else{
					doCalculation(myStack, oper);
				}
			}
		}
	}

	/*
	* At the end of the expression, there should always be one 
	* less operator than number(the final answer). If there    
	* are remaining numbers in the stack at this point and     
	* no more operators, the expression is malformed.          
	*/
	if (operatorCounter + 1 == numberCounter)
		cout << "Result: " << myStack.top() << endl << endl;
	else
		cout << "Malformed expression entered >:(\n\n";
}

/************************************************************
* Function doCalculation() takes two inputs, a stack and    *
* an operator. It pops off the top two elements of the      *
* stack, uses the operator to determine what operation      *
* should be done, then pushes the total back on the stack   *
*      Input: stack, an OperandStack object which contains  *
*                the stack of numbers to calculate          *
*             oper, a char which indicates the operation to *
*                be performed                               *
*      Return: none                                         *
************************************************************/
void doCalculation(OperandStack & stack, char oper){
	double rightOperand = stack.top();
	stack.pop();

	double leftOperand = stack.top();
	stack.pop();

	double total;

	switch (oper){
	case '+':
		total = leftOperand + rightOperand;
		break;
	case '-':
		total = leftOperand - rightOperand;
		break;
	case '*':
		total = leftOperand * rightOperand;
		break;
	case '/':
		total = leftOperand / rightOperand;
		break;
	case '^':
		total = leftOperand;
		for (int i = 1; i < rightOperand; i++)
			total = total * leftOperand;
		break;
	}

	stack.push(total);
}