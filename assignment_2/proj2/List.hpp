
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
				List(List && rhs); 
				// num elements with value of val
				explicit List(int num, const T& val = T{}); 
				// constructs with elements [start, end)
				List(const_iterator start, const_iterator end); 

				~List(); // destructor

				// copy assignment operator
				const List& operator=(const List &rhs);
				// move assignment operator
				List & operator=(List && rhs);

				// member functions
				int size() const; // number of elements
				bool empty() const; // check if list is empty
				void clear(); // delete all elements
				void reverse(); // reverse the order of the elements

				T &front(); // reference to the first element
				const T& front() const;
				T &back(); // reference to the last element
				const T & back() const; 

				void push_front(const T & val); // insert to the beginning
				void push_front(T && val); // move version of insert
				void push_back(const T & val); // insert to the end
				void push_back(T && val); // move version of insert
				void pop_front(); // delete first element
				void pop_back(); // delete last element

				void remove(const T &val); // remove all elements with value = val

				// print out all elements. ofc is deliminitor
				void print(std::ostream& os, char ofc = ' ') const; 

				iterator begin(); // iterator to first element
				const_iterator begin() const;
				iterator end(); // end marker iterator
				const_iterator end() const; 
				iterator insert(iterator itr, const T& val); // insert val ahead of itr
				iterator insert(iterator itr, T && val); // move version of insert
				iterator erase(iterator itr); // erase one element
				iterator erase(iterator start, iterator end); // erase [start, end)


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
		bool operator==(const List<T> & lhs, const List<T> &rhs);

	template <typename T>
		bool operator!=(const List<T> & lhs, const List<T> &rhs);

	// overloading output operator
	template <typename T>
		std::ostream & operator<<(std::ostream &os, const List<T> &l);

} // end of namespace 4530