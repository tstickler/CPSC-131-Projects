/***********************************************************
* Assignment #3                                            *
* Created by Tyler Stickler                                *
* CPSC 131-01                                              *
*                                                          *
* TaskList.cpp v 1.0                                       *
* May 8, 2015                                              *
*                                                          *
* This program takes a task list in random order and sorts *
* it into a queue such that the highest priority is given  * 
* to the tasks associated with the lowest number.          *
***********************************************************/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/************************************************************
* PriorityQueue class to store the task list                *
************************************************************/
class PriorityQueue
{
private:
	/************************************************************
	* Task node class                                           *
	************************************************************/
	class NodeType
	{
	public:
		string task;	//name of the task
		int priority;		// priority of the task
		NodeType * next;  //points to the next task on the queue

		NodeType(string task = "", int priority = -1,
			NodeType * next = NULL)  //default constructor
		{
			this->task = task;  this->priority = priority;
			this->next = next;
		}
	};

public:
	PriorityQueue()
	{  //default constructor: creates an empty queue
		head = NULL; taskCount = 0;
	}
	~PriorityQueue();  //destructor: delete all tasks from the queue

	bool isEmpty() const;  //checks for the queue being empty

	int size() const;  //returns the number of tasks in the queue

	void insert(string taskName, int priority);
	//creates a task and inserts it in order of priority

	void min() const; //prints the task and its priority (the one with the 
	//highest priority)

	void removeMin();  //removes the highest priority task 
	//from the queue

private:
	NodeType *head;  //head pointer to the list
	int taskCount;  //count of the number of tasks on the list

	void goNext(NodeType * & curr) const; //moves the pointer to point to
	//the next task
};

/************************************************************
* Function ~PriorityQueue() deletes all tasks from the      *
* queue.                                                    *
*      Input: none                                          *
*      Renturn: none                                        *
************************************************************/
PriorityQueue::~PriorityQueue(){
	if (isEmpty())
		return;
	else{
		NodeType * current = head;
		
		while (current != NULL){
			goNext(current);
			delete head;
			head = current;
		}
	}

}

/************************************************************
* Function goNext() takes a pointer to a node, curr, and    *
* moves it to the next node in the queue.                   *
*      Input: curr, NodeType pointer holding reference to a *
*             node.                                         *
*      Return: none                                         *
************************************************************/
void PriorityQueue::goNext(NodeType * & curr) const{
	curr = curr->next;
}

/************************************************************
* Function isEmpty() checks if there are any nodes in the   *
* queue.                                                    *
*      Input: none                                          *
*      Return: True if the head is null, false otherwise    *
************************************************************/
bool PriorityQueue::isEmpty() const{
	if (head == NULL)
		return true;
	else
		return false;
}

/************************************************************
* Function size() is a getter function. Returns the number  *
* of tasks in the queue, which is tracked by a class level  *
* variable.                                                 *
*      Input: none                                          *
*      Return: taskCount, int variable holding number of    *
*              tasks in the queue                           *
************************************************************/
int PriorityQueue::size() const {
	return taskCount;
}

/************************************************************
* Function insert() adds a task to the queue. It takes two  *
* parameters, a string variable holding the name of the     *
* task and an int variable with the priority of the task.   *
* Tasks are put in order from highest priority(lowest num)  *
* to lowest priority(highest num). If the task priorities   *
* are equal, the first task of that priority has a higher   *
* priority than the one being added.                        *
*      Input: string variable, taskName, holding the task   *
*             int variable, priority, holding the priority  *
*      Return: none                                         *
************************************************************/
void PriorityQueue::insert(string taskName, int priority){
	NodeType * task = new NodeType(taskName, priority);
	
	if (isEmpty())
		head = task;
	else{
		NodeType * current = head, * previous = head;
		
		/*
		* There are three things that can happen when adding
		* a new task to the queue. 1) It has a higher priority 
		* than another task on the list. 2) It has an equal
		* priority to something on the list. 3) It's priority
		* is lower than all others on the list.
		*/
		while (current != NULL){
			/*
			* The first if statement deals handles adding a
			* higher priority item to the queue. Since the
			* queue is sorted, the first instance it finds
			* that the priority of the task being added is higher
			* than another task's priority , it will be added before
			* it.
			*/
			if (task->priority < current->priority){
				if (current == head){
					task->next = head;
					head = task;

					return;
				}

				previous->next = task;
				task->next = current;

				current = previous = task = NULL;

				return;
			}

			/*
			* If the priority of the task being added is not
			* lower than a task in the queue, this will check
			* if it's priority is equal to another. If it is,
			* then it will go into a loop until it finds the
			* last task with that priority and it will be added
			* after.
			*/
			else if (task->priority == current->priority){
				while (task->priority == current->priority){
					previous = current;
					goNext(current);
				}

				task->next = current;
				previous->next = task;

				current = previous = task = NULL;

				return;
			}

			/*
			* If the priority of the task being added is not higher
			* or equal to the task being checked, keep going.
			*/
			else{
				previous = current;
				goNext(current);
			}
		}

		/*
		* If we make it out of the loop, then the priority
		* of the task being added is lower than the priority
		* of all the other tasks in the queue. So we place
		* this task at the end.
		*/
		previous->next = task;

		current = previous = task = NULL;
	}
}

/************************************************************
* Function min() prints the task with the highest priority. *
*      Input: none                                          *
*      Return: none                                         *
************************************************************/
void PriorityQueue::min() const{
	cout << head->priority << head->task << endl;
}

/************************************************************
* Function removeMin() removes the task with the highest    *
* priority from the queue.                                  *
*      Input: none                                          *
*      Return: none                                         *
************************************************************/
void PriorityQueue::removeMin(){
	NodeType * deleteTask = head;

	head = head->next;
	delete deleteTask;

	deleteTask = NULL;
}

/************************************************************
* Function buildTaskList() takes an empty queue and         *
* populates it by reading a task list into it.              *
*      Input: taskList, an empty PriorityQueue passed by    *
*             reference                                     *
*      Return: none                                         *
************************************************************/
void buildTaskList(PriorityQueue & taskList){
	ifstream in;

	in.open("input.txt");
	if (in.fail()){
		cout << "Input file failed to open.\n";
		exit(1);
	}
	while (!in.eof()){
		string input;
		int priority;

		in >> priority;
		getline(in, input);

		taskList.insert(input, priority);
	}
	in.close();
}

/************************************************************
* Function printTasks() takes a sorted priority queue,      *
* prints, and then removes each task until the queue is     *
* empty.                                                    *
*       Input: taskList, a sorted priority queue passed by  *
*              reference                                    *
*       Return: none                                        *
************************************************************/
void printTasks(PriorityQueue & taskList){
	while (!taskList.isEmpty()){
		taskList.min();
		taskList.removeMin();
	}
}

int main()
{
	PriorityQueue taskList; 

	buildTaskList(taskList);
	
	cout << "Removing all tasks in order of priority and printing...\n";
	printTasks(taskList);

	return 0;
}
