
// list for template class implementation (template classes implementation is done is .hpp, not .cpp files)

#include <iostream>

namespace cop4530 {
	template <typename T>
		class List {
			private:
				// nested Node class
				struct Node {
					T data;
					Node *prev;
					Node *next;

					Node(const T & d = T{}, Node *p = nullptr, Node *n = nullptr) 
						: data{d}, prev{p}, next{n} {}
					Node(T && d, Node *p = nullptr, Node *n = nullptr)
						: data{std::move(d)}, prev{p}, next{n} {}
				};

			public:
				//nested const_iterator class
				class const_iterator {
					public:
                        // default zero parameter constructor
						const_iterator() {
                            current = nullptr;
                        };

                        // operator*() to return element
						const T & operator*() const {
                            return const retrieve();
                        };

                         // operator->() to return pointer to element
						const T * operator->() const {
							return const &retrieve();
                        };


						// increment/decrement operators
						const_iterator & operator++() {
							current = current->next;
							return *this;
						};
						const_iterator operator++(int) {
							const_iterator temp = *this;
							current = current->next;
							return temp;
						};
						const_iterator & operator--() {
							current = current->prev;
							return *this;
						};
						const_iterator operator--(int) {
							const_iterator temp = *this;
							current = current->prev;
							return temp;
						};

						// comparison operators
						bool operator==(const const_iterator &rhs) const {
							return current == rhs.current;
						};
						bool operator!=(const const_iterator &rhs) const {
							return current != rhs.current;
						};

					protected:
						Node *current; // pointer to node in List

                        // retrieve the element refers to
						T & retrieve() const {
							return current->data;
                        };

						// protected constructor
						const_iterator(Node *p) {
							current = p;
						};

						friend class List<T>;
				};

				// nested iterator class
				class iterator : public const_iterator {
					public:
						iterator() {
							current = nullptr;
						};

						T & operator*() {
							return retrieve();
						}
                        // already implemented in const_iterator the right way
						// const T & operator*() const;

						// return pointer to element
						T* operator->() {
							return &retrieve();
						};
						// already implemented in const_iterator the right way
						// const T* operator->() const; // return pointer to content element

						// increment/decrement operators
						iterator & operator++() {
							current = current->next;
							return *this;
						};
						iterator operator++(int) {
							iterator temp = *this;
							current = current->next;
							return temp;
						};
						iterator & operator--() {
							current = current->prev;
							return *this;
						};
						iterator operator--(int) {
							iterator temp = *this;
							current = current->prev;
							return temp;
						};

					protected:
						iterator(Node *p) {
							current = p;
						};
						friend class List<T>;
				};

			public:
				// constructor, desctructor, copy constructor
				// Initialize the size to zero
				List() {
					init();
				}
				// copy constructor
				List(const List &rhs) {
					init();
					for (auto &val : rhs)
						push_back(val);
				};
				// move constructor
				List(List && rhs) {
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
				explicit List(int num, const T& val = T{}) {
					init();
					for (int i = 0; i < num; i++)
						push_back(val);
				}
				// constructs with elements [start, end)
				List(const_iterator start, const_iterator end) {
					init();
					// when start reaches end, while wont execute so end el will not be added
					while (start != end) {
						push_back(*start);
						++start;
					}
				};

				// destructor
				~List() {
					clear();
					delete head;
					delete tail;
				}; 

				// copy assignment operator
				const List& operator=(const List &rhs) {
					if (this != &rhs) {
						clear();
						for (auto &val : rhs)
							push_back(val);
					}
					return *this;
				};
				// move assignment operator
				List & operator=(List && rhs) {
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
				int size() const {
					return theSize;
				} ;

				// check if list is empty
				bool empty() const {
					return size() == 0;
				};

				// delete all elements
				void clear() {
					 while (!empty())
            			pop_front();		
				};

				// reverse the order of the elements
				void reverse() {
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

				T &front() {
					return *begin();
				}; // reference to the first element
				const T& front() const {
					// compilator will pick the right overload due to the const state
					return *begin();
				};
				T &back() {
					return *(--end());
				}; // reference to the last element
				const T & back() const {
					return *(--end());
				}; 

				// insert to the beginning
				void push_front(const T & val) {
					insert(begin(), val);
				}; 
				// move version of insert
				void push_front(T && val) {
					insert(begin(), std::move(val));
				}; 
				// insert to the end
				void push_back(const T & val) {
					insert(begin(), val);
				};
				// move version of insert
				void push_back(T && val) {
					insert(begin(), std::move(val));
				}; 
				// delete first element
				void pop_front() {
					erase(begin());
				};
				// delete last element
				void pop_back() {
					erase(--end());
				};

				// remove all elements with value = val
				void remove(const T &val) {
					auto itr = begin();
					while (itr != end()) {
						if (*itr == val)
							itr = erase(itr);
						else
							++itr;
					}
				};

				// print out all elements. ofc is deliminitor
				void print(std::ostream& os, char ofc = ' ') const {
					for (const_iterator itr = begin(); itr != end(); ++itr)
						os << *itr << ofc;
				}; 

				// iterator to first element
				iterator begin() {
					return iterator(head->next);
				}; 
				const_iterator begin() const {
					return const_iterator(head->next);
				};
				// end marker iterator
				iterator end() {
					return iterator(tail);
				}; 
				const_iterator end() const {
					return const_iterator(tail);
				}; 

				// insert val ahead of itr
				iterator insert(iterator itr, const T& val) {
					Node *p = itr.current;
					theSize++;
					p->prev->next = new Node{val, p->prev, p};
					p->prev = p->prev->next;
					return p->prev;
				}; 
				// move version of insert
				iterator insert(iterator itr, T && val) {
					Node *p = itr.current;
					theSize++;
					p->prev->next = new Node{std::move(val), p->prev, p};
					p->prev = p->prev->next;
					return p->prev;
				}; 

				// erase one element
				iterator erase(iterator itr) {
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
				iterator erase(iterator start, iterator end) {
					while (start != end)
						start = erase(start);

					// effectively returning end iterator
					return start;
				}; 
			private:
				int theSize; // number of elements
				Node *head; // head node
				Node *tail; // tail node

				// initialization
				void init() {
					// initialize the size to zero
					theSize = 0; 

					// create head and tail mock nodes
					head = new Node();
					tail = new Node();

					// make it looped
					head->next = tail;
					tail->prev = head;
				};
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

} // end of namespace 4530