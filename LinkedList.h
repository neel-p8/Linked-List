#pragma once
using namespace std;
#include <vector>
#include <iostream>

template <typename T>
class LinkedList {
public:
	struct Node {
		T data;
		Node* next;
		Node* prev;
	};
private:
	Node* tail;
	Node* head;
	Node* new_node;
	unsigned int node_count; 
public:
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	~LinkedList();

	// insertion operators
	void AddHead(const T& data);
	void AddTail(const T& data);
	void AddNodesHead(const T* data, unsigned int count);
	void AddNodesTail(const T* data, unsigned int count);
	void InsertAfter(Node* node, const T& data);
	void InsertBefore(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);

	// Behaviors
	void PrintForward() const;
	void PrintReverse() const;
	void PrintForwardRecursive(const Node* node) const;
	void PrintReverseRecursive(const Node* node) const;

	// Accessors
	unsigned int NodeCount() const;
	void FindAll(vector<Node*>& outData, const T& value) const;
	
	// find first node with matching data value
	const Node* Find(const T& data) const {
		Node* new_node = head;
		unsigned int i = 0;
		while (i < node_count) {
			if (new_node->data == data) {
				return new_node;
			}
			i++;
			new_node = new_node->next;
		}
		return nullptr;
	}

	// find first node with matching data value
	Node* Find(const T& data) {
		Node* new_node = head;
		unsigned int i = 0;
		while (i < node_count) {
			if (new_node->data == data) {
				return new_node;
			}
			i++;
			new_node = new_node->next;
		}
		return nullptr;
	}

	// return pointer to the index specified, if out range: exception
	const Node* GetNode(unsigned int index) const {
		if (index >= node_count) {
			throw out_of_range("Index is out of range");
		}
		else {
			Node* new_node = head;
			unsigned int i = 0;
			while (i < index) {
				new_node = new_node->next;
				i++;
			}
			return new_node;
		}
	}
	
	// return pointer to the index specified, if out range: exception
	Node* GetNode(unsigned int index) {
		if (index >= node_count) {
			throw out_of_range("Index is out of range");
		}
		else {
			Node* new_node = head;
			unsigned int i = 0;
			while (i < index) {
				new_node = new_node->next;
				i++;
			}
			return new_node;
		}
	}
	
	// return head pointer
	Node* Head() {
		return head;
	}
	
	// return head pointer, const version
	const Node* Head() const {
		return head;
	}
	
	// return tail pointer
	Node* Tail() {
		return tail;
	}
	
	// return tail pointer, const version
	const Node* Tail() const {
		return tail;
	}

	// removal operations
	bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T& data);
	bool RemoveAt(unsigned int index);
	void Clear();

	// operators
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
	bool operator==(const LinkedList<T>& rhs) const;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);
};

template<typename T>
inline LinkedList<T>::LinkedList()
{
	head = nullptr;
	tail = nullptr;
	new_node = nullptr;
	node_count = 0;
}

// copy constructor
template<typename T>
inline LinkedList<T>::LinkedList(const LinkedList<T>& list)
{
	head = nullptr;
	tail = nullptr;
	node_count = 0;
	unsigned int i = 0;
	Node* new_node = list.head;

	while (i < list.NodeCount()) {
		AddTail(new_node->data);
		new_node = new_node->next;
		i++;
	}
}

template<typename T>
inline LinkedList<T>::~LinkedList()
{
	Clear();
}

// Addhead, if head pointing to value, point new node to head value. else if nodecount 0,
// assign new node as head
template<typename T>
inline void LinkedList<T>::AddHead(const T& data)
{
	new_node = new Node;
	new_node->data = data;
	new_node->next = nullptr;
	new_node->prev = nullptr;

	if (head != nullptr) {
		new_node->next = head;
		head->prev = new_node;
		head = new_node;
	}
	else if (node_count == 0) {
		head = new_node;
		tail = new_node;
	}
	node_count++;

}

// Addtail, if tail pointing to value, point new node to tail value. else if nodecount 0,
// assign new node as tail
template<typename T>
inline void LinkedList<T>::AddTail(const T& data)
{
	new_node = new Node;
	new_node->data = data;
	new_node->next = nullptr;
	new_node->prev = nullptr;

	if (tail != nullptr) {
		tail->next = new_node;
		new_node->prev = tail;
		tail = new_node;
		new_node = nullptr;
	}
	else if (node_count == 0) {
		head = new_node;
		tail = new_node;
	}
	node_count++;
}

// add node for each array element
template<typename T>
inline void LinkedList<T>::AddNodesHead(const T* data, unsigned int count)
{
	for (int i = count - 1; i >= 0; i--) {
		AddHead(data[i]);
	}
}

// add node for each array element in opposite order
template<typename T>
inline void LinkedList<T>::AddNodesTail(const T* data, unsigned int count)
{
	for (int i = 0; i <= count - 1; i++) {
		AddTail(data[i]);
	}
}

// create node to store value after node
template<typename T>
inline void LinkedList<T>::InsertAfter(Node* node, const T& data)
{
	if (node != nullptr) {
		Node* new_node2 = new Node;
		new_node2->data = data;
		new_node2->prev = node;
		new_node2->next = node->next;
		node->next = new_node2;
		if (node->next == nullptr) {
			tail = new_node2;
		}
		else {
			node->next->prev = new_node2;
		}
	}
	else {
		AddTail(data);
	}
	node_count++;
	
}

// create node to store value before node
template<typename T>
inline void LinkedList<T>::InsertBefore(Node* node, const T& data)
{
	if (node != nullptr) {
		Node* new_node2 = new Node;
		new_node2->data = data;
		new_node2->next = node;
		new_node2->prev = node->prev;
		if (node->prev == nullptr) {
			head = new_node2;
		}
		else {
			node->prev->next = new_node2;
		}
		node->prev = new_node2;
	}
	else {
		AddTail(data);
	}
	node_count++;
}

// insert node at index location with specified data
template<typename T>
inline void LinkedList<T>::InsertAt(const T& data, unsigned int index)
{
	Node* new_node = head;
	
	if (index > node_count) {
		throw out_of_range("Invalid index");
	}
	else if (index == node_count) {
		Node* new_node2 = new Node;
		new_node2->data = data;
		new_node2->next = nullptr;
		tail->next = new_node2;
		new_node2->prev = tail;
		tail = new_node2;
		node_count++;
	}
	else {
		unsigned int i = 0;
		while (i < index) {
			new_node = new_node->next;
			i++;
		}
		InsertBefore(new_node, data);
	}
}

// print all nodes and their values
template<typename T>
inline void LinkedList<T>::PrintForward() const
{
	if (node_count != 0) {
		Node* new_node2 = head;

		while (new_node2 != nullptr) {
			cout << new_node2->data << endl;
			new_node2 = new_node2->next;
		}
	}
}

// print all nodes in reverse order
template<typename T>
inline void LinkedList<T>::PrintReverse() const
{
	if (node_count != 0) {
		Node* new_node2 = tail;

		while (new_node2 != nullptr) {
			cout << new_node2->data << endl;
			new_node2 = new_node2->prev;
		}
	}
}

// print forward using recursion
template<typename T>
inline void LinkedList<T>::PrintForwardRecursive(const Node* node) const
{
	cout << node->data << endl;
	if (node != tail) {
		PrintForwardRecursive(node->next);
	}
}

//print in reverse using recursion
template<typename T>
inline void LinkedList<T>::PrintReverseRecursive(const Node* node) const
{
	cout << node->data << endl;
	if (node != head) {
		PrintReverseRecursive(node->prev);
	}
}

// return total nodes
template<typename T>
inline unsigned int LinkedList<T>::NodeCount() const
{
	return node_count;
}

// saves all nodes with matching parameter into vector
template<typename T>
inline void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const
{
	Node* new_node = head;
	unsigned int i = 0;
	while (i < node_count) {
		if (new_node->data == value) {
			outData.push_back(new_node);
		}
		i++;
		new_node = new_node->next;
	}
}

// remove first node of list
template<typename T>
inline bool LinkedList<T>::RemoveHead()
{
	if (head != nullptr && node_count != 0) {
		Node* new_node = head->next;
		delete head;
		head = new_node;
		if (head == nullptr) {
			head = nullptr;
			tail = nullptr;
		}
		else {
			head->prev = nullptr;
		}
		node_count--;
		return true;
	}
	else {
		return false;
	}
}

// return last node of list
template<typename T>
inline bool LinkedList<T>::RemoveTail()
{
	if (tail != nullptr && node_count != 0) {
		Node* new_node = tail->prev;
		delete tail;
		tail = new_node;
		if (tail == nullptr) {
			tail = nullptr;
			head = nullptr;
		}
		else {
			tail->next = nullptr;
		}
		node_count--;
		return true;
	}
	else {
		return false;
	}
}

// remove all nodes matching parameter value
template<typename T>
inline unsigned int LinkedList<T>::Remove(const T& data)
{
	unsigned int instances = 0;
	unsigned int i = 0;
	Node* cur_loop = head;

	while (i < node_count) {

		Node* new_node = cur_loop->next;

		if (cur_loop->data == data) {
			Node* next_node = cur_loop->next;
			Node* prev_node = cur_loop->prev;
			
			if (cur_loop->prev == head->prev) {
				this->RemoveHead();
			}
			else if (cur_loop->next == tail->next) {
				this->RemoveTail();
			}
			else {
				prev_node->next = cur_loop->next;
				next_node->prev = cur_loop->prev;
			}
			instances++;
			delete cur_loop;
		}
		i++;
		cur_loop = new_node;
	}
	node_count -= instances;
	return instances;
}

// remove node at specific index value
template<typename T>
inline bool LinkedList<T>::RemoveAt(unsigned int index)
{
	if (index >= node_count) {
		return false;
	}
	else {
		Node* new_node = head;
		unsigned int i = 0;

		while (i < index) {
			new_node = new_node->next;
			i++;
		}
		Node* next_node = new_node->next;
		Node* prev_node = new_node->prev;

		if (new_node->prev == head->prev) {
			this->RemoveHead();
		}
		else if (new_node->next == tail->next) {
			this->RemoveTail();
		}
		else {
			prev_node->next = new_node->next;
			next_node->prev = new_node->prev;
		}
		delete new_node;
		node_count--;
	}
	return true;
}

// remove all nodes
template<typename T>
inline void LinkedList<T>::Clear()
{
	while (head != nullptr) {
		Node* new_node = head;
		head = head->next;
		delete new_node;
	}
	head = nullptr;
	tail = nullptr;
	node_count = 0;
}

//returns data from specified index node, const version
template<typename T>
inline const T& LinkedList<T>::operator[](unsigned int index) const
{
	if (index >= node_count) {
		throw out_of_range("Invalid index");
	}
	else {
		Node* new_node = head;
		unsigned int i = 0;
		while (i < index) {
			new_node = new_node->next;
			i++;
		}
		return new_node->data;
	}
}

//returns data from specified index node, const version
template<typename T>
inline T& LinkedList<T>::operator[](unsigned int index)
{
	if (index >= node_count) {
		throw out_of_range("Invalid index");
	}
	else {
		Node* new_node = head;
		unsigned int i = 0;
		while (i < index) {
			new_node = new_node->next;
			i++;
		}
		return new_node->data;
	}
}

// check if two linked lists are equal
template<typename T>
inline bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const
{
	if (node_count == rhs.node_count) {
		Node* new_node = head;
		Node* new_node_rhs = rhs.head;

		unsigned int i = 0;
		while (i < rhs.node_count && new_node->data == new_node_rhs->data) {
			new_node = new_node->next;
			new_node_rhs = new_node_rhs->next;
			i++;
		}
		if (i == rhs.node_count - 1) {
			return true;
		}
	}
	else {
		return false;
	}
}

// assignment operator
template<typename T>
inline LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
	Clear();
	unsigned int i = 0;
	Node* new_node = rhs.head;

	while (i < rhs.NodeCount()) {
		AddTail(new_node->data);
		new_node = new_node->next;
		i++;
	}
	return *this;
}