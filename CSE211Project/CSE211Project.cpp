
#include <iostream>
#include <fstream>  
#include <string>

using namespace std;

struct Node {			
	string name_node;	
	int age_node;				
	struct Node* next;
	struct Node* prev;
};

void add(struct Node* head, string name, int age);
void update(struct Node* head, string name, int age);
void printByAge(struct Node* head);
void printByName(struct Node* head);
void loadFile(string& filename, int age_arr[], string name_arr[]);
void saveToFileByAge(string& filename, Node* head);
void saveToFileByName(string& filename, Node* head);
void linkedListCreation(struct Node* head, string name_Array[], int age_Array[], struct Node* tail);
Node* sort_byAge(Node* head);
Node* sort_byName(Node* head);

// add a new person to the list
void add(struct Node* head, string name, int age)		
{
	Node* temp;
	Node* newNode = new Node();
	newNode -> name_node = name;
	newNode -> age_node = age;
	temp = head;
	
	while (temp -> next != NULL) 
	{
		temp = temp -> next;
	}
	temp -> next = newNode;
	newNode -> prev = temp;
	newNode -> next = NULL;
}

// remove a person from the list
bool removePerson(struct Node*& head, string name)
{
	if (head == NULL) {
		return false; 
	}

	Node* current = head;

	// if name is head
	if (current->name_node == name) {
		head = current->next; 
		if (head != NULL) {
			head->prev = NULL; 
		}
		delete current; 
		return true;
	}

	// traversing the list
	while (current != NULL && current->name_node != name) {
		current = current->next;
	}

	// if found remove the person
	if (current != NULL) {
		if (current->next == NULL) {
			current->prev->next = NULL;
		}
		else {
			if (current->prev != NULL) {
				current->prev->next = current->next;
			}
			if (current->next != NULL) {
				current->next->prev = current->prev;
			}
		}
		delete current; 
		return true;
	}
	return false; 
}

// updates the age of a given person
void update(struct Node *head, string name, int age)  
{
	removePerson(head, name);
	add(head, name, age);
}

// prints the list of the people sort by age
void printByAge(struct Node* head) {
	Node* sortedList = sort_byAge(head); 
	Node* printAgePtr = sortedList;

	while (printAgePtr != NULL) {
		cout << printAgePtr->age_node << "->";
		printAgePtr = printAgePtr->next;
	}
	cout << endl;
}

// prints the list of the people sort by name
void printByName(struct Node* head) {
	Node* sortedList = sort_byName(head); 
	Node* printNamePtr = sortedList;

	while (printNamePtr != NULL) {
		cout << printNamePtr->name_node << "->";
		printNamePtr = printNamePtr->next;
	}
	cout << endl;
}

// loads a database file with txt extension.
void loadFile(string& filename, int age_arr[], string name_arr[])		
{
	string name_in_text;
	int age_in_text, lineNum = 0;

	fstream input_file;
	input_file.open(filename, ios::in);          

	while (input_file >> name_in_text >> age_in_text) 
	{
		name_arr[lineNum] = name_in_text;
		age_arr[lineNum] = age_in_text;
		lineNum++;
	}
	input_file.close();
}

// saves the list of sorted person according to age to a file.
void saveToFileByAge(string& filename, Node* head)	
{
	fstream file_age(filename, ios::out);
	head = sort_byAge(head);
	while (head != NULL)
	{
		file_age << head->age_node << " " << head->name_node << endl;
		head = head->next;
	}
	file_age.close();
}

// saves the list of sorted person database according to name to a file.
void saveToFileByName(string& filename, Node* head)		
{
	fstream name_file(filename, ios::out);
	head = sort_byName(head);
	while (head != NULL)
	{
		name_file << head->name_node << " " << head->age_node << endl;
		head = head->next;
	}
	name_file.close();
}

// creates a linked list from two arrays
void linkedListCreation(struct Node* head, string name_Array[], int age_Array[], struct Node* tail)
{
	int array_length = name_Array->size();
	
	head -> name_node = name_Array[0];   
	head -> age_node = age_Array[0];     
	head -> prev = nullptr;
	head -> next = nullptr;
	tail = head;						

	for (int i = 1; i < array_length; i++)    
	{
		Node* node = new Node();
		node -> name_node = name_Array[i];
		node -> age_node = age_Array[i];
		node -> prev = tail;
		node -> next = nullptr;
		tail -> next = node;				
		tail = node;
	}
}

// sort the list of people by age
Node* sort_byAge(Node* head) {
	if (head == NULL || head->next == NULL) return head; 

	Node* tempHead = NULL;
	Node* current = head;

	// copy list to temp
	while (current != NULL) {
		Node* newNode = new Node();
		newNode->age_node = current->age_node;
		newNode->name_node = current->name_node;
		newNode->next = tempHead;
		newNode->prev = NULL;

		if (tempHead != NULL) tempHead->prev = newNode;
		tempHead = newNode;

		current = current->next;
	}

	// bubble sort
	int swapped;
	Node* ptr1;
	Node* lptr = NULL;

	do {
		swapped = 0;
		ptr1 = tempHead;

		while (ptr1->next != lptr) {
			if (ptr1->age_node > ptr1->next->age_node) {
				swap(ptr1->age_node, ptr1->next->age_node);
				swap(ptr1->name_node, ptr1->next->name_node);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);

	return tempHead; 
}

// sort the list of people by name
Node* sort_byName(Node* head) {
	if (head == NULL || head->next == NULL) return head;

	Node* tempHead = NULL;
	Node* current = head;

	// copy list to temp
	while (current != NULL) {
		Node* newNode = new Node();
		newNode->age_node = current->age_node;
		newNode->name_node = current->name_node;
		newNode->next = tempHead;
		newNode->prev = NULL;

		if (tempHead != NULL) tempHead->prev = newNode;
		tempHead = newNode;

		current = current->next;
	}

	// bubble sort
	int swapped;
	Node* ptr1;
	Node* lptr = NULL;

	do {
		swapped = 0;
		ptr1 = tempHead;

		while (ptr1->next != lptr) {
			if (ptr1->name_node > ptr1->next->name_node) {
				swap(ptr1->name_node, ptr1->next->name_node);
				swap(ptr1->age_node, ptr1->next->age_node);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);

	return tempHead; 
}

int main()
{
	struct Node *head = new Node();
	struct Node* tail = new Node();
	struct Node* tmp = new Node();
	string file = "input.txt";
	string name_file = "name.txt";
	string age_file = "age.txt";
	string name;
	int age = 0;
	string name_array[5];
	int age_array[5] = {};

	loadFile(file, age_array, name_array);
	linkedListCreation(head, name_array, age_array, tail);

	int operation;

	cout<< " +-------------Database Management Program---------------+" << endl
		<< " | 1) Add a new person                                   |" << endl
		<< " | 2) Remove a person                                    |" << endl
		<< " | 3) Update a person's age                              |" << endl
		<< " | 4) Display persons' ages in a sorted order            |" << endl
		<< " | 5) Display persons' names in a sorted order           |" << endl
		<< " | 6) Save the sorted names to a file                    |" << endl
		<< " | 7) Save the sorted ages to a file                     |" << endl
		<< " | 8) Exit                                               |" << endl
		<< " +-------------------------------------------------------+\n" << endl;

	while (true) 
	{
		sort_byAge(head);
		sort_byName(head);

		cout << "Enter the number of the operation that you want to perform: " << endl;
		cin >> operation;

		if (operation == 1) 
		{
			cout << "Enter the name of the person: ";
			cin >> name;
			cout << "Enter the age of the person: ";
			cin >> age;

			add(head, name, age);
			cout << "Person added." << endl;
		}
		else if (operation == 2) 
		{
			tmp = head;
			cout << "Enter the name that you want to remove: " << endl << endl;
			while (tmp != NULL)
			{
				cout << tmp->name_node << endl;
				tmp = tmp->next;
			}
			cout << endl;

			cin >> name;
			removePerson(head, name);
			cout << "Person removed." << endl;
		}
		else if (operation == 3) 
		{
			cout << "Enter the name that you want to update the age: ";
			cin >> name;
			cout << "Update the age: ";
			cin >> age;
			update(head, name, age);
			cout << "Age updated." << endl;
		}
		else if (operation == 4) 
		{
			printByAge(head);
		}
		else if (operation == 5)
		{
			printByName(head);
		}
		else if (operation == 6)
		{
			saveToFileByName(name_file, head);
			cout << "File saved" << endl;
		}
		else if (operation == 7)
		{
			saveToFileByAge(age_file, head);
			cout << "File saved" << endl;
		}
		else if (operation == 8)
		{
			cout << "Exitting..." << endl;
			break;
		}
		else 
		{
			cout << "You entered an incorrect input... Please try again." << endl;
		}
		cout << endl;
	}
	system("pause");
}