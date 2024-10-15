
// list for template class implementation (template classes implementation is done is .hpp, not .cpp files)

#include <iostream>


// default zero parameter constructor
template <typename T>
List<T>::const_iterator::const_iterator() {
	current = nullptr;
};

// operator*() to return element
template <typename T>
const T & List<T>::const_iterator::operator*() const {
	return retrieve();
};

// operator->() to return pointer to element
template <typename T>
const T * List<T>::const_iterator::operator->() const {
	return &retrieve();
};


// increment/decrement operators
template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++() {
	current = current->next;
	return *this;
};
template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int) {
	const_iterator temp = *this;
	current = current->next;
	return temp;
};
template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--() {
	current = current->prev;
	return *this;
};
template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int) {
	const_iterator temp = *this;
	current = current->prev;
	return temp;
};

// comparison operators
template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const {
	return current == rhs.current;
};
template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const {
	return current != rhs.current;
};

template <typename T>
T & List<T>::const_iterator::retrieve() const {
	return current->data;
};

// protected constructor
template <typename T>
List<T>::const_iterator::const_iterator(Node *p) {
	current = p;
};


template <typename T>
List<T>::iterator::iterator() {
	this->current = nullptr;
};

template <typename T>
T & List<T>::iterator::operator*() {
	return this->retrieve();
}
// already implemented in const_iterator the right way
// const T & operator*() const;

// return pointer to element
template <typename T>
T* List<T>::iterator::operator->() {
	return &this->retrieve();
};
// already implemented in const_iterator the right way
// const T* operator->() const; // return pointer to content element

// increment/decrement operators
template <typename T>
typename List<T>::iterator & List<T>::iterator::operator++() {
	this->current = this->current->next;
	return *this;
};
template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int) {
	iterator temp = *this;
	this->current = this->current->next;
	return temp;
};
template <typename T>
typename List<T>::iterator & List<T>::iterator::operator--() {
	this->current = this->current->prev;
	return *this;
};
template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int) {
	iterator temp = *this;
	this->current = this->current->prev;
	return temp;
};


template <typename T>
List<T>::iterator::iterator(Node *p) {
	this->current = p;
};


// constructor, desctructor, copy constructor
// Initialize the size to zero
template <typename T>
List<T>::List() {
	init();
}
// copy constructor
template <typename T>
List<T>::List(const List &rhs) {
	init();
	for (auto &val : rhs)
		push_back(val);
};
// move constructor
template <typename T>
List<T>::List(List && rhs) {
	// transferring data ownership to the current container
	head = rhs.head;
	tail = rhs.tail;
	theSize = rhs.theSize;

	// preventing access to this data from the previous container
	rhs.head = nullptr;
	rhs.tail = nullptr;
	rhs.theSize = 0;
};

// num elements with value of val
template <typename T>
List<T>::List(int num, const T& val) {
	init();
	for (int i = 0; i < num; i++)
		push_back(val);
}
// constructs with elements [start, end)
template <typename T>
List<T>::List(const_iterator start, const_iterator end) {
	init();
	// when start reaches end, while wont execute so end el will not be added
	while (start != end) {
		push_back(*start);
		++start;
	}
};

// destructor
template <typename T>
List<T>::~List() {
	clear();
	delete head;
	delete tail;
}; 

// copy assignment operator
template <typename T>
const List<T>& List<T>::operator=(const List &rhs) {
	if (this != &rhs) {
		clear();
		for (auto &val : rhs)
			push_back(val);
	}
	return *this;
};
// move assignment operator
template <typename T>
List<T> & List<T>::operator=(List && rhs) {
	if (this != &rhs) {
		clear();

		// transferring data ownership to the current container
		head = rhs.head;
		tail = rhs.tail;
		theSize = rhs.theSize;

		// preventing access to this data from the previous container
		rhs.head = nullptr;
		rhs.tail = nullptr;
		rhs.theSize = 0;
	}
	return *this;
};

// member functions
// number of elements
template <typename T>
int List<T>::size() const {
	return theSize;
} ;

// check if list is empty
template <typename T>
bool List<T>::empty() const {
	return size() == 0;
};

// delete all elements
template <typename T>
void List<T>::clear() {
		while (!empty())
		pop_front();		
};

// reverse the order of the elements
template <typename T>
void List<T>::reverse() {
	if (empty()) return;

	// reversing the prev/next pointers of the nodes
	Node *current = head->next;
	Node *temp = nullptr;
	while (current != tail) {
		temp = current->next;
		current->next = current->prev;
		current->prev = temp;
		current = current->prev;
	}

	// adjusting the object properties
	temp = head;
	head = tail;
	tail = temp;
}; 

template <typename T>
T& List<T>::front() {
	return *begin();
}; // reference to the first element
template <typename T>
const T& List<T>::front() const {
	// compilator will pick the right overload due to the const state
	return *begin();
};
template <typename T>
T& List<T>::back() {
	return *(--end());
}; // reference to the last element
template <typename T>
const T& List<T>::back() const {
	return *(--end());
}; 

// insert to the beginning
template <typename T>
void List<T>::push_front(const T & val) {
	insert(begin(), val);
}; 
// move version of insert
template <typename T>
void List<T>::push_front(T && val) {
	insert(begin(), std::move(val));
}; 
// insert to the end
template <typename T>
void List<T>::push_back(const T & val) {
	insert(begin(), val);
};
// move version of insert
template <typename T>
void List<T>::push_back(T && val) {
	insert(begin(), std::move(val));
}; 
// delete first element
template <typename T>
void List<T>::pop_front() {
	erase(begin());
};
// delete last element
template <typename T>
void List<T>::pop_back() {
	erase(--end());
};

// remove all elements with value = val
template <typename T>
void List<T>::remove(const T &val) {
	auto itr = begin();
	while (itr != end()) {
		if (*itr == val)
			itr = erase(itr);
		else
			++itr;
	}
};

// print out all elements. ofc is deliminitor
template <typename T>
void List<T>::print(std::ostream& os, char ofc) const {
	for (const_iterator itr = begin(); itr != end(); ++itr)
		os << *itr << ofc;
}; 

// iterator to first element
template <typename T>
typename List<T>::iterator List<T>::begin() {
	return iterator(head->next);
}; 
template <typename T>
typename List<T>::const_iterator List<T>::begin() const {
	return const_iterator(head->next);
};
// end marker iterator
template <typename T>
typename List<T>::iterator List<T>::end() {
	return iterator(tail);
}; 
template <typename T>
typename List<T>::const_iterator List<T>::end() const {
	return const_iterator(tail);
}; 

// insert val ahead of itr
template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val) {
	Node *p = itr.current;
	theSize++;
	p->prev->next = new Node{val, p->prev, p};
	p->prev = p->prev->next;
	return p->prev;
}; 
// move version of insert
template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val) {
	Node *p = itr.current;
	theSize++;
	p->prev->next = new Node{std::move(val), p->prev, p};
	p->prev = p->prev->next;
	return p->prev;
}; 

// erase one element
template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr) {
	Node* p = itr.current;
	iterator next_el = p->next;

	// linking neighboring elements
	p->prev->next = p->next;
	p->next->prev = p->prev;

	delete p;
	theSize--;
	return next_el;
}; 
// erase [start, end)
template <typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end) {
	while (start != end)
		start = erase(start);

	// effectively returning end iterator
	return start;
}; 

template <typename T>
void List<T>::init() {
	// initialize the size to zero
	theSize = 0; 

	// create head and tail mock nodes
	head = new Node();
	tail = new Node();

	// make it looped
	head->next = tail;
	tail->prev = head;
};


// overloading comparison operators
template <typename T>
bool operator==(const List<T> & lhs, const List<T> &rhs) {
	// checking if the sizes are equal
	if (lhs.size() != rhs.size()) {
		return false;
	}
	
	// iterating through both lists and compare elements
	auto lhsIt = lhs.begin();
	auto rhsIt = rhs.begin();
	
	while (lhsIt != lhs.end() && rhsIt != rhs.end()) {
		if (*lhsIt != *rhsIt) { 
			return false;
		}
		++lhsIt;
		++rhsIt;
	}
	
	// all elements have matched
	return true;
};
template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs) {
	return !lhs.operator==(rhs);
};

// overloading output operator
template <typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l) {
	// reuse the List class method for printing itself
	l.print(os);
	return os;
};

// end of namespace 4530