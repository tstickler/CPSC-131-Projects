/************************************************************
* Assignment #1                                            * 
* Created by Tyler Stickler                                *
* CPSC 131-01                                              *
*                                                          *
* GroceryList.cpp v 1.0                                    *
* March 23, 2015                                           *
*                                                          *
* This program allows the user to create a grocery list    *
*	that will store names and quantity of items. It also   *
*	allows the user to split their list into multiple      *
*	lists.                                                 *
************************************************************/

#include <iostream>
#include <string>
using namespace std;
/************************************************************
* Grocery item class                                       *
************************************************************/
class ItemType
{
public:
	string name;	//name of the item
	double qty;		// quantity of the item
	ItemType * next,  //points to the next item on the list
		*prev;  //points to the previous item on the list

	ItemType(string name = NULL, double qty = 0,
		ItemType * next = NULL,
		ItemType * prev = NULL)  //default constructor
	{
		this->name = name;  this->qty = qty;
		this->next = next;  this->prev = prev;
	}
};

/************************************************************
* Grocery List class implemented as doubly linked list     *
************************************************************/
class GroceryList
{
private:
	ItemType *head, *tail;  //head and tail pointers to the list
	int itemCount;  //count of the number of items on the list

	void goNext(ItemType * & curr) const;
	void goPrevious(ItemType * & curr) const;  //moves the pointer to point to
	//the previous item

public:
	GroceryList()
	{  //default constructor: creates an empty list
		head = tail = NULL; itemCount = 0;
	}
	~GroceryList()
	{  //destructor: delete all items on a list
		ItemType * itemToDelete = head;
		while (itemToDelete != NULL)
		{
			goNext(head);
			delete itemToDelete;
			itemToDelete = head;
			itemCount--;
		}

		head = tail = itemToDelete = NULL;
	}  

	bool isEmpty() const;  //checks for the list being empty
	int length() const;  //returns the number of items on the list, which is the
	//value for itemCount

	void addToFront(string itemName,
		double quantity);  //creates an item and adds to the front 
	//of the list
	void addToBack(string itemName,
		double quantity);  //creates an item and adds to the back
	//of the list
	void add(string itemName, double quantity,
		int pos);  //creates an item and adds to the list at  specified
	//position items are numbered from left to right

	void printForward() const;  //prints list from front to back
	void printBackward() const;  //prints list back to front

	void removeFirst();  //removes the first item from the list
	void removeLast();  //removes the last item from the list
	void remove(int pos);  //remove an item at the given position on the list
	//items are numbered from left to right

	void peek(int pos) const;  //recursive function to print item name and 
	//quantity at a specified position
	bool lookup(string itemName) const;  //recursive function to look up an
	//item by name

	void deal(GroceryList & secondList);  //removes every other item and puts
	//it into the secondList
};

/************************************************************
*	printForward will print the list of items on the       *
*		grocery list along with their quantities from      *
*		front to back                                      *
* Inputs:                                                  *
*	none                                                   *
* Return:                                                  *
*	nothing                                                *
************************************************************/
void GroceryList::printForward() const
{
	ItemType * current = head;
	int count = 1;

	cout << "------ Grocery List (item:quantity) ------" << endl;
	if (isEmpty()) cout << "You do not have any item.\n";

	while (current != NULL)
	{
		cout << count << ") " << current->name << ": " << current->qty << endl;
		goNext(current);
		count++;
	}
	cout << endl;
}

/************************************************************
*	printBackward will print the list of items on the      *
*		grocery list along with their quantities from back *
*		to front                                           *
* Inputs:                                                  *
*	none                                                   *
* Return:                                                  *
*	nothing                                                *
************************************************************/
void GroceryList::printBackward() const
{
	ItemType * current = tail;
	int count = length();

	cout << "------ Grocery List (item:quantity) ------" << endl;
	if (isEmpty()) cout << "You do not have any item.";

	while (current != NULL)
	{
		cout << count << ") " << current->name << ": " << current->qty << endl;
		goPrevious(current);
		count--;
	}
	cout << endl;
}

/************************************************************
*	goNext advances the pointer to point to the next item  *
* Inputs:                                                  *
*	curr, a pointer passed by reference, points to an      *
*		item on the grocery list                           *
* Return:                                                  *
*	nothing                                                *
************************************************************/
void GroceryList::goNext(ItemType * & curr) const
{
	curr = curr->next;
}

/************************************************************
*	goPrevious advances the pointer to point to the        *
*		previous item                                      *
* Inputs:                                                  *
*	curr, a pointer passed by reference, points to an      *
*		item on the grocery list                           *
* Return:                                                  *
*	nothing                                                *
************************************************************/
void GroceryList::goPrevious(ItemType * & curr) const
{
	curr = curr->prev;
}

/************************************************************
*	isEmpty checks the list to see if there are any items  *
* Inputs:                                                  *
*	none                                                   *
* Return:                                                  *
*	true if list is empty                                  * 
*	false if there are items in the list                   *
************************************************************/
bool GroceryList::isEmpty() const
{
	if (head == NULL)
		return true;
	else
		return false;
}

/************************************************************
*	length accesses a list's itemCount                     *
* Inputs:                                                  *
*	none                                                   *
* Return:                                                  *
*	item count of list                                     *
************************************************************/
int GroceryList::length() const
{
	return itemCount;
}

/************************************************************
*	addToFront creates an item and adds it to the front    *
*		of the list                                        *
* Inputs:                                                  *
*	itemName, string variable with the name of the         *
*		item being added                                   *
*	quanity, double variable with the number of items      *
*		being added                                        *
* Return:                                                  *
*	nothing                                                *
************************************************************/
void GroceryList::addToFront(string itemName, double quantity)
{
	ItemType * itemToAdd = new ItemType(itemName, quantity);

	if (isEmpty())
	{
		head = itemToAdd;
		tail = itemToAdd;
	}
	else
	{
		itemToAdd->next = head;
		head->prev = itemToAdd;
		head = itemToAdd;
	}
	
	itemCount++;
	itemToAdd = NULL;
}

/************************************************************
*	addToBack creates an item and adds it to the back      *
*		of the list                                        *
* Inputs:                                                  *
*	itemName, string variable with the name of the         *
*		item being added                                   *
*	quanity, double variable with the number of items      *
*		being added                                        *
* Return:                                                  *
*	nothing                                                *
************************************************************/
void GroceryList::addToBack(string itemName, double quantity)
{
	ItemType * itemToAdd = new ItemType(itemName, quantity);

	if (isEmpty())
	{
		addToFront(itemName, quantity);
	}
	else
	{
		itemToAdd->prev = tail;
		tail->next = itemToAdd;
		tail = itemToAdd;

		itemCount++;
	}

	itemToAdd = NULL;
}

/************************************************************
*	add creates an item and adds it at a specific position *
*		in the list                                        *
* Inputs:                                                  *
*	itemName, string variable with the name of the         *
*		item being added                                   *
*	quanity, double variable with the number of items      *
*		being added                                        *
*	position, int variable stating where the item should   *
*		be entered in the list							   *	
* Return:                                                  *
*	nothing                                                *
************************************************************/
void GroceryList::add(string itemName, double quantity, int position)
{
	ItemType * itemToAdd = new ItemType(itemName, quantity);

	if (isEmpty() || position <= 0)
	{
		addToFront(itemName, quantity);
	}
	else if (position >= length())
	{
		addToBack(itemName, quantity);
	}
	else
	{
		ItemType * current = head;

		for (int i = 0; i != position; i++)
			goNext(current);

		ItemType* previous = current->prev;

		itemToAdd->prev = previous;
		itemToAdd->next = current;
		current->prev = itemToAdd;
		previous->next = itemToAdd;

		itemCount++;

		current = previous = itemToAdd = NULL;
	}
}

/************************************************************
*	removeFirst removes the first item in the list         *
* Inputs:                                                  *
*	none                   							       *
* Return:                                                  *
*	nothing                                                *
************************************************************/
void GroceryList::removeFirst()
{
	try{
		if (isEmpty())
			throw 0;
		else
		{
			ItemType * itemToDelete = head;

			goNext(head);
			head->prev = NULL;

			delete itemToDelete;

			itemToDelete = NULL;

			itemCount--;
		}
	}
	catch(...){
		cout << "Can't complete this action, the list is empty\n";
	}
}

/************************************************************
*	removeLast removes the last item in the list           *
* Inputs:                                                  *
*	none                   							       *
* Return:                                                  *
*	nothing                                                *
************************************************************/
void GroceryList::removeLast()
{
	try{
		if (isEmpty())
		{
			throw 0;
		}
		else
		{
			ItemType * itemToDelete = tail;

			goPrevious(tail);
			tail->next = NULL;

			delete itemToDelete;

			itemToDelete = NULL;

			itemCount--;
		}
	}
	catch (...){
		cout << "Can't complete this action, the list is empty\n";
	}
}

/************************************************************
*	remove removes an item at a specific position in the   *
*		list                                               *
* Inputs:                                                  *
*	position, int variable stating where the item should   *
*		be removed from the list                           *
* Return:                                                  *
*	nothing                                                *
************************************************************/
void GroceryList::remove(int position)
{
	try{
		if (isEmpty())
		{
			throw 0; 
		}
		else if (position <= 0)
		{
			removeFirst();
		}
		else if (position >= length())
		{
			removeLast();
		}
		else
		{
			ItemType * itemToDelete = head;

			for (int i = 0; i != position; i++)
				goNext(itemToDelete);

			ItemType* previous = itemToDelete->prev;
			ItemType* nextItem = itemToDelete->next;

			delete itemToDelete;

			previous->next = nextItem;
			nextItem->prev = previous;

			itemCount--;

			previous = nextItem = itemToDelete = NULL;
		}
	}
	catch(...){
		cout << "Can't complete this action, the list is empty\n";
	}
}

/************************************************************
*	peek looks at a specified position to see what item is *
*		there and its quantity                             *
* Inputs:                                                  *
*	position, int variable stating what position should be *
*		checked                                            *
* Return:                                                  *
*	nothing                                                *
************************************************************/
void GroceryList::peek(int position) const
{
	try{
		if (isEmpty())
			throw 1;
		if (position > length() || position < 0)
			throw 2;
		else
		{
			ItemType * current = head;

			for (int i = 0; i < position; i++)
				goNext(current);

			cout << current->name << ": " << current->qty << endl;

			current = NULL;
		}
	}
	catch (int err){
		switch (err){
		case 1: cout << "Can't complete this action, the list is empty\n";
			return;
		case 2: cout << "Can't complete this action, position is outside the list\n";
			return;
		}
	}


}

/************************************************************
*	lookup looks for an item by the item's name in the     *
*		list                                               *
* Inputs:                                                  *
*	itemName, string variable stating the name of the item *
*		that should be looked for                          *
* Return:                                                  *
*	true if item is found on the list                      *
*	false if item is not found or list is empty            *
************************************************************/
bool GroceryList::lookup(string itemName) const
{
	try{
		if (isEmpty())
			throw 0;
		else
		{
			ItemType * current = head;

			while (current != NULL)
			{
				if (current->name == itemName)
				{
					return true;
				}

				goNext(current);

			}

			return false;
		}
	}
	catch (...){
		cout << "Can't complete this action, the list is empty\n";
	}
}

/************************************************************
*	deal takes one list and splits it into two seperate    *
*		lists. This function moves every other item to the *
*		second list                                        *
* Inputs:                                                  *
*	secondList, an empty GroceryList object used to create *
*		a second list                                      *
* Return:                                                  *
*	nothing                                                *
************************************************************/
void GroceryList::deal(GroceryList & secondList)
{
	try{
		if (isEmpty())
			throw 0;
		else
		{
			ItemType * nextItem = head, *prevItem = head, *itemToMove = head;

			const int LIST_LENGTH = length();  //assigns length of first list to a constant to use for the loop

			if (LIST_LENGTH % 2 == 0)
			{
				tail = tail->prev;
			}

			for (int i = 0; i < LIST_LENGTH; i++)  //will execute until it has reached the list length
			{
				if (i % 2 != 0)  //only executes for odd numbered items on the first list
				{
					nextItem = itemToMove->next;  //sets a pointer after item thats moving
					prevItem = itemToMove->prev;  //sets a pointer before item thats moving
					itemToMove->next = NULL;  //delinks moving items next
					itemToMove->prev = NULL;  //delinks moving items prev
					prevItem->next = nextItem;  //relinks the first list
					if (nextItem != NULL)
						nextItem->prev = prevItem;  //relinks the first list

					if (secondList.head == NULL)  //puts item at the beginning of the second list
						secondList.addToFront(itemToMove->name, itemToMove->qty);
					else  //adds items to the back of the second list
						secondList.addToBack(itemToMove->name, itemToMove->qty);

					itemCount--;  //Decrements the first list itemCount

					delete itemToMove;

					itemToMove = prevItem;  //moves itemToMove back to first list in position to keep splitting the list
				}

				goNext(itemToMove);  //advances pointer to find next item to move
			}
		}
	}
	catch (...){
		cout << "Can't complete this action, the list is empty\n";
		return;
	}
}

int main()
{
	//For add() and printBackward()
	/*
	
	GroceryList firstList;

	firstList.printForward();

	cout << "Adding an item via addToFront...\n";
	firstList.addToFront("Avocado", 5);
	firstList.printForward();

	cout << "Adding an item via addToBack...\n";
	firstList.addToBack("Lime", 2);
	firstList.printForward();

	cout << "Adding an item via add at position 1...\n";
	firstList.add("Milk", 1, 2);
	firstList.printForward();

	cout << "Printing list backwards...\n";
	firstList.printBackward();
	
	*/

	//For remove()
	/*
	
	GroceryList firstList;

	firstList.addToFront("Avocado", 5);
	firstList.addToBack("Milk", 1);
	firstList.addToBack("Lime", 2);
	firstList.addToBack("Apples", 6);
	firstList.addToBack("Oatmeal", 3);
	firstList.addToBack("Pepper", 1);
	firstList.addToBack("Eggs", 12);
	firstList.addToBack("Salsa", 1);
	firstList.addToBack("Quinoa", 1);

	firstList.printForward();

	cout << "Removing an item via removeFirst...\n";
	firstList.removeFirst();
	firstList.printForward();

	cout << "Removing an item via removeLast...\n";
	firstList.removeLast();
	firstList.printForward();

	cout << "Removing an item via remove from position 4...\n";
	firstList.remove(4);
	firstList.printForward();

	*/

	//For lookup() and peek()
	/*

	GroceryList firstList;

	firstList.addToFront("Milk", 1);
	firstList.addToBack("Lime", 2);
	firstList.addToBack("Apples", 6);
	firstList.addToBack("Oatmeal", 3);
	firstList.addToBack("Eggs", 12);
	firstList.addToBack("Salsa", 1);
	
	firstList.printForward();

	cout << "Peek at item at position 3...\n";
	firstList.peek(3);

	cout << "\nLooking up Apples...\n";
	if (firstList.lookup("Apples"))
		cout << "Apples found!\n";
	else
		cout << "Apples not found.\n";

	cout << "\nLooking up Hummus...\n";
	if (firstList.lookup("Hummus"))
		cout << "Hummus found!\n";
	else
		cout << "Hummus not found.\n";
	
	*/

	//For deal()...
	/*
	
	GroceryList betty, nicholas;
	betty.addToFront("Milk", 1);
	betty.addToBack("Lime", 2);
	betty.addToBack("Apples", 6);
	betty.addToBack("Oatmeal", 3);
	betty.addToBack("Eggs", 12);
	betty.addToBack("Salsa", 1);
	betty.addToBack("Avocado", 5);
	betty.addToBack("Pepper", 1);
	betty.addToBack("Quinoa", 1);

	cout << "Printing Betty's list....\n";
	betty.printForward();

	cout << "Printing Nicholas's list....\n";
	nicholas.printForward();

	cout << "Calling deal....\n";
	betty.deal(nicholas);

	cout << "Printing Betty's list....\n";
	betty.printForward();

	cout << "Printing Nicholas's list....\n";
	nicholas.printForward();

	*/
	return 0;
}