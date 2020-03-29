#include <iostream>
using namespace std;

class List
{
private:
	typedef struct node
	{
		node* next;
		node* prev;
		int data;
	}*ptr;
	node* head;
	node* tail;
public:
	List() { head = NULL; tail = NULL; }

	node* Get_Head() { return head; }
	node* Get_Tail() { return tail; }

	bool Empty_List();
	void Create_Node(const int& x);
	void Insert_At_End(const int& x);
	void Insert_At_Front(const int& x);
	void Insert_At_Index(const int& index, const int& x);
	void Insert_After_Head(const int& x);
	void Insert_Middle(const int& x);
	int Get_Length();
	int Sum_Of_Nodes_Forward();
	int Sum_Of_Nodes_Reverse();
	bool Is_Sorted();
	void Reverse_List();	
	void Delete_Head();
	void Delete_Tail();
	void Delete_Position(const int& pos);
	void Delete_Key(const int& key);
	void Delete_Middle();
	void Display_Reverse();
	void Display_Forward();
	void Display_Reverse_Recursive(node* temp);
	void Display_Forward_Recursive(node* temp);
};

bool List::Empty_List()
{
	if (head == NULL)
		cout << "Empty\n";
	return head == NULL;	
}

void List::Create_Node(const int& x)
{
	ptr temp = new node;
	temp->data = x;
	temp->next = NULL;
	temp->prev = NULL;
	head = temp;
	tail = temp;
}
void List::Insert_At_End(const int& x)
{	
	if (Empty_List())
		Create_Node(x);
	ptr temp = new node;
	temp->data = x;
	temp->next = NULL;
	temp->prev = tail;
	tail->next = temp;
	temp->prev->next = temp;
	tail = temp;	
}
void List::Insert_At_Front(const int& x)
{	
	if (Empty_List())
		Create_Node(x);
	ptr temp = new node;
	temp->data = x;
	temp->next = head;
	temp->prev = NULL;
	temp->next->prev = temp;
	head = temp;
	head->prev = NULL;
}
void List::Insert_At_Index(const int& index, const int& x)
{
	ptr temp = new node;
	temp->data = x;
	ptr p = head;
	if (Empty_List())
		Create_Node(x);
	if (index < 0 || index > Get_Length())
	{
		cout << "out of range\n";
		return;
	}
	if (index == 0)
	{
		Insert_At_Front(x);
		return;
	}
	if (index == Get_Length())
	{
		Insert_At_End(x);
		return;
	}
	for (int i = 0; i < index - 1; i++)
		p = p->next;
	temp->next = p->next;	
	p->next = temp;
	temp->prev = p;
	temp->next->prev = temp;
}
void List::Insert_After_Head(const int& x)
{
	if (Empty_List())
		Create_Node(x);
	ptr temp = new node;
	temp->data = x;
	temp->next = head->next;
	temp->prev = head;
	head->next = temp;
	if (temp->next != NULL)
		temp->next->prev = temp;
}
void List::Insert_Middle(const int& x)
{
	if (Empty_List())
		Create_Node(x);
	ptr temp = new node;
	temp->data = x;
	ptr p = head;
	for (int i = 0; i < (Get_Length() / 2) - 1; i++)
		p = p->next;
	if (Get_Length() % 2 == 1)
	{
		cout << "Odd number of nodes, "
			<< "cannot insert in middle!\n"
			<< "Add or Delete a node...\n\n";
		return;
	}
	temp->next = p->next;
	temp->prev = p;
	p->next = temp;
	temp->next->prev = temp;
}
int List::Get_Length()
{	
	if (Empty_List())
		return NULL;
	ptr temp = head;
	int len{};
	while (temp != NULL)
	{
		len++;
		temp = temp->next;
	}
	return len;
}
int List::Sum_Of_Nodes_Forward()
{
	if (Empty_List())
		return NULL;
	ptr temp = head;
	int total{};
	while (temp != NULL)
	{
		total += temp->data;
		temp = temp->next;
	}
	return total;
}
int List::Sum_Of_Nodes_Reverse()
{
	if (Empty_List())
		return NULL;
	ptr temp = tail;
	int total{};
	while (temp != NULL)
	{
		total += temp->data;
		temp = temp->prev;
	}
	return total;
}

bool List::Is_Sorted()
{
	if (Empty_List())
		return NULL;
	int x = INT_MIN;
	ptr temp = head;
	while (temp != NULL)
	{
		if (temp->data < x)
			return false;
		x = temp->data;
		temp = temp->next;
	}
	return true;
}
void List::Reverse_List()
{
	if (Empty_List())
		return;
	ptr second = head;
	ptr first = head;

	while (first->next != NULL)
		first = first->next; // right moves to tail
	while (second != first && second->prev != first)
	{
		swap(second->data, first->data); // as moving swap the numbers
		second = second->next; // left moves to tail
		first = first->prev; // right move backs towards head
	}	
}
void List::Delete_Head()
{
	if (Empty_List())
		return;
	ptr temp = head;
	head = head->next;	
	delete temp;
	if (!Empty_List())
		head->prev = NULL;

	// *** This also seems to work ***
	/*if (Empty_List())
		return;
	ptr temp = head;
	head = head->next;
	temp->next = head;
	temp->prev = NULL;
	delete temp;
	head->prev = NULL;*/
}
void List::Delete_Tail()
{
	if (Empty_List())
		return;
	ptr temp = tail;
	tail = tail->prev;
	delete temp;
	if (!Empty_List())
		tail->next = NULL;

	// *** This also seems to work ***
	/*if (Empty_List())
		return;
	ptr temp = tail;
	tail = tail->prev;
	temp->next = NULL;
	temp->prev = tail;
	delete temp;
	tail->next = NULL;*/
}
void List::Delete_Position(const int& pos)
{
	if (Empty_List())
		return;
	else if (pos == 1)
	{
		Delete_Head();
		return;
	}
	else if (pos == Get_Length())
	{
		Delete_Tail();
		return;
	}
	else if (pos < 0 || pos > Get_Length())
	{
		cout << "out of range\n";
		return;
	}
	else
	{
		ptr temp = head;
		for (int i = 0; i < pos - 1; i++)
			temp = temp->next;
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		delete temp;
	}
}
void List::Delete_Key(const int& key)
{
	if (Empty_List())
		return;
	if (key == head->data)
	{
		Delete_Head();
		return;
	}
	ptr temp = head;
	while (key != temp->data)
	{
		temp = temp->next;
		if (temp->next == NULL)
		{
			Delete_Tail();
			return;
		}
		if (key == temp->data)
		{
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
			return;
		}
	}
}
void List::Delete_Middle()
{
	if (Empty_List())
		return;
	if (Get_Length() % 2 == 0)
	{
		cout << "Even nodes, no middle\n";
		return;
	}
	ptr temp = head;
	for (int i = 0; i < (Get_Length() / 2); i++)
	{
		temp = temp->next;
	}

	temp->next->prev = temp->prev;
	temp->prev->next = temp->next;
	delete temp;
}
void List::Display_Reverse()
{
	if (Empty_List())
		return;
	ptr temp = tail;
	while (temp != NULL)
	{
		cout << temp->data << " ";
		temp = temp->prev;		
	}
	cout << endl;
}
void List::Display_Forward()
{
	if (Empty_List())
		return;
	ptr temp = head;
	while (temp != NULL)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}
void List::Display_Reverse_Recursive(node* temp)
{
	if (Empty_List())
		return;
	if (temp == NULL)
		return;
	Display_Reverse_Recursive(temp->next);
	cout << temp->data << " ";	
}
void List::Display_Forward_Recursive(node* temp)
{
	if (Empty_List())
		return;
	if (temp == NULL)
		return;
	cout << temp->data << " ";
	Display_Forward_Recursive(temp->next);
}
int main()
{
	List list;

	list.Create_Node(30);
	list.Insert_At_End(40);
	list.Insert_At_Front(20);
	list.Insert_At_End(50);
	list.Insert_At_Front(10);
	list.Insert_At_End(60);	
	list.Insert_Middle(77);	
	list.Reverse_List();	

	list.Delete_Middle();
	list.Insert_After_Head(15);
	list.Delete_Head();
	list.Delete_Tail();
	list.Delete_Position(2);
	list.Delete_Key(40);
	list.Delete_Key(30);	

	list.Display_Forward();
	list.Display_Reverse();	
	list.Display_Reverse_Recursive(list.Get_Head());
	cout << endl;
	list.Display_Forward_Recursive(list.Get_Head());
	
	cout << "\nIs list sorted ascending?  " << boolalpha << list.Is_Sorted() << endl;

	
	
	

	cout << endl;
	system("pause");
	return 0;
}