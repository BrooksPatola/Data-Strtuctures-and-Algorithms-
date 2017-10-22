#include <iostream>
#include <algorithm> // for use of swap function
using namespace std;

template <typename T>
//doubly linked list class creation
class DList {
		struct Node {
				T data_;
				Node* next_; //pointer to next node in list
				Node* prev_; // pointer to previous node in list
				//for new Node creation
				Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr) {
						data_ = data;
						next_ = next;
						prev_ = prev;
				}
		};
		Node* front_; // pointer to front of the list
		Node* back_; // pointer to back of the list
		int listSz; // variable used to store the current size of the linked list
public:

		class const_iterator {
				friend class DList;
				//pointer to current iterator 
				Node* curr_; 
			  //address of the list that the node belongs to.	
				const DList* myList_; 
				//create a constant iterator of a specified position in a list
				const_iterator(Node* curr, const DList* myList) {
						curr_ = curr;
						myList_ = myList;
				}
		public:
				//ctor to make iterator in a safe empty state
				const_iterator() {
						curr_ = nullptr;
						myList_ = nullptr;
				}
				const_iterator operator++() {
						//++x
						curr_ = curr_->next_;
						return *this;
				}
				const_iterator operator++(int) {
						//x++
						const_iterator old = *this;
						curr_ = curr_->next_;
						return old;
				}
				const_iterator operator--() {
						//--x
						curr_ = curr_->prev_;
						return *this;

				}
				const_iterator operator--(int) {
						//x--
						const_iterator old = *this;
						curr_ = curr_->prev_;
						return old;

				}
				//for dereferencing the current pointed to data
				const T& operator*() const {
						return curr_->data_;
				}
				bool operator==(const_iterator rhs) const {
						return (curr_ == rhs.curr_ && myList_ == rhs.myList_);
				}
				bool operator!=(const_iterator rhs) const {
						return !(*this == rhs);
						//return (curr_ != rhs.curr_ || myList_ != rhs.myList_);
				}
		};
		class iterator :public const_iterator {
				friend class DList;
				iterator(Node* curr, DList* myList) :const_iterator(curr, myList) {
				}
		public:
				iterator() :const_iterator() {
				}
				iterator operator++() {
						//++x
						this->curr_ = this->curr_->next_;
						return *this;
				}
				iterator operator++(int) {
						//x++
						iterator old = *this;
						this->curr_ = this->curr_->next_;
						return old;
				}
				iterator operator--() {
						//--x
						this->curr_ = curr_->prev_; // this.curr_->prev_;
						return *this;

				}
				iterator operator--(int) {
						//x--
						iterator old = *this;
						this->curr_ = this->curr_->prev_;
						return old;
				}
				T& operator*() {
						return (this->curr_)->data_;
				}
				bool operator==(iterator rhs) const {
						return (this->curr_ == rhs.curr_ && this->myList_ == rhs.myList_);
				}
				bool operator!=(iterator rhs) const {
				  	//return !(*this==rhs) <-- alternative way 
						return (this->curr_ != rhs.curr_ || this->myList_ != rhs.myList_);
				}
		};

		//empty doubly linked list creation using sentinels
		DList() {
	  		//creating front sentinel 
				front_ = new Node(); 
				//creating back sentinel									 ; 
				back_ = new Node(); 
			  //make them point to eachother
				front_->next_ = back_;
				back_->prev_ = front_;
				listSz = 0; //ignore 2 dummy(sentinel) nodes and set size of list to zero

		}

		//adds data to the front of the linked list O(1)
		void push_front(const T& data) {
				//insert( begin( ), data); <<-- re use of code to perform function
				Node* firstData = front_->next_;
				Node* beforeFirst = firstData->prev_;
				Node* nn = new Node(data, firstData, beforeFirst);
				firstData->prev_ = nn;
				beforeFirst->next_ = nn;
				listSz++;

		}

		//adds data to the back of the linked list O(1)
		void push_back(const T& data) {
				//insert( end( ), data ); <<-- re use of code to perform function
				Node* temp = new Node(data, back_, back_->prev_);
				back_->prev_ = temp;
				back_->prev_->prev_->next_ = temp;
				listSz++;

		}

		//removes the front node in the linked list O(1)
		void pop_front() {
				//erase(begin()); <<-- re use of code to perform function
				Node* popped = front_->next_;
				popped->next_->prev_ = front_;
				front_->next_ = popped->next_;
				delete popped;
				listSz--;

		}

		//removes the back node in the linked list O(1)
		void pop_back() {
				//erase(--end()); <<-- re use of code to perform function
				Node* popped = back_->prev_;
				popped->prev_->next_ = back_;
				back_->prev_ = popped->prev_;
				delete popped;
				listSz--;

		}

		//simple print function for displaying data in a list
		void print() const {
				Node* curr = front_->next_;
				while (curr != back_) 
				{
						cout << curr->data_ << endl;
						curr = curr->next_;
				}

		}
		//returns const_iterator to first node in LL
		const_iterator begin() const {
				return const_iterator(front_->next_, this);
		}
		//returns const_iterator to the node that follows the last node
		const_iterator end() const {
				return const_iterator(back_, this);
		}
		//returns const_iterator to first node in LL
		iterator begin() {
				return iterator(front_->next_, this);
		}
		//returns const_iterator to the node that follows the last node
		iterator end() {
				return iterator(back_, this);
		}


		/*
		inserts data before the node referred by loc. Note that it is allowed for loc to be end().
		function returns iterator to the newly inserted node. O(1)
		*/
		iterator insert(iterator loc, const T& data) {

				/*
				assign pointers of the previous and next nodes in the linked list 
				to Node pointers and then create a new Node using these as paramaters
				along with data
				*/
				Node* before = loc.curr_->prev_;
				Node* after = loc.curr_;
				Node* nn = new Node(data, after, before);
				
				//safely re assign pointers
				nn->prev_->next_ = nn;
				nn->next_->prev_ = nn;
				loc--;
				listSz++;
				return loc;

		}

		//removes the node referred to by it. O(1)
		void erase(iterator it) {
				//Node to be removed from list
				Node* remove = it.curr_;
				//safely assign pointers so no memory leak
				Node* left = remove->prev_;
				Node* right = remove->next_;

				delete remove; //delete the pointed to Node

				//safely assign next and previous pointers
				if (left)
						left->next_ = right;
				else
						front_ = right;

				if (right)
						right->prev_ = left;
				else
						back_ = left;

				--listSz; 

		}

		/*
    removes the nodes between the nodes referred to by iterator first to last. 
		This includes the node referred to by first but NOT the node referred to by last.
    O(n) to the number of nodes between first and last
		*/
		void erase(iterator first, iterator last) {

				iterator start = first;

				if (empty())
				{
						cout << "trying to erase from empty list" << endl;
				}

				//keep erasing Nodes until you get to the last iterator 
				while (first != last)
				{
						first++;
						erase(start); // just call erase on the Nodes to be removed
						start = first;

				}

		}

		//returns iterator to the node containing data.If data is not found, returns end(). O(n)
		iterator search(const T& data)
		{

				iterator it = begin();
				iterator notIt = end();

				//perform loop as long as there are Nodes in the list to be searched
				while (it != notIt)
				{   // if found return the iterator 
						if (it.curr_->data_ == data)
						{
							/*	cout << "found it" << endl;*/
								return it;
						}
						++it;
				}
				/*cout << "not found" << endl;*/
				return it; //returns end of list iterator if not found
		}

		//returns iterator to the node containing data. If data is not found, returns end(). O(n)
		const_iterator search(const T& data) const {

				const_iterator it = begin();
				const_iterator notIt = end();


				while (it != notIt)
				{
						if (it.curr_->data_ == data)
						{
								/*cout << "found it" << endl;*/
								return it;
						}
						++it;
				}
		/*		cout << "not found" << endl;*/
				return it;

		}

		//function returns true if the list is empty, false otherwise. O(1)
		bool empty() const {
				return front_->next_ == back_;
		}

		//function returns number of pieces of data stored in the list. O(1)
		int size() const {
				return listSz;
		}

		//destructor
		~DList() {

				Node* current = front_;

				while (current->next_ != back_) 
				{
						front_ = front_->next_;
						delete current;
						current = front_;

				}

		}

		// copy ctor
		DList(const DList& rhs) : back_(nullptr), front_(nullptr), listSz(0) {
				/*cout << "in ctor" << endl;*/
				const Node* current = rhs.front_;
				const Node* previous = rhs.front_->prev_;
				Node* temp = nullptr;
				if (current != rhs.back_)
				{
					/*	cout << "in if" << endl;*/
						front_ = new Node(current->data_);
						temp = front_;
						current = current->next_;		

				}
				while (current != rhs.back_)
				{
						/*	cout << "in while" << endl;*/
						Node* nn = new Node(current->data_);
						temp->next_ = nn;
						nn->prev_ = temp;
						temp = temp->next_;

						current = current->next_;
						listSz++;
				}
			/*	cout << "test" << endl;*/

		}

		//copy assignment
		DList& operator=(const DList& rhs) {
		/*cout << "in assignment" << endl;*/
				DList temp(rhs);
				/*
				using swap to perform deep copy assignment
				as we re use our copy ctor
				*/
				std::swap(temp.front_, front_);
				std::swap(temp.back_, back_);
				std::swap(temp.listSz, listSz);
				return *this;

		}


		// move ctor
		DList(DList&& rhs) :
				listSz{ rhs.listSz }, front_{ rhs.front_ }, back_{ rhs.back_ }
		{
				/*	*this = std::move(rhs);*/

			/*	cout << "in move ctor" << endl;*/
				rhs.listSz = 0;
				rhs.front_ = nullptr;
				rhs.back_ = nullptr;


		}

		// move assignment
		DList& operator=(DList&& rhs) { 

			/*	cout << "in move assignment" << endl;*/
				std::swap(listSz, rhs.listSz);
				std::swap(front_, rhs.front_);
				std::swap(back_, rhs.back_);

				return *this;

		}

};
