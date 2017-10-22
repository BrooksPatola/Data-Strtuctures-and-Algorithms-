/*
Hash Table that uses linear probing as its collision resolution method 
Author: Aaron Brooks Patola 105368153
*/

/*
in SimpleTable the following functions were granted performance bonuses:
Update: removed sort() function as was uneeded for the operation
Assignment Operator: Removed a for loop that made a redundant call to remove()
Destructor:  Removed a for loop that made a redundant call to remove()
*/


#pragma once
#include <string>
#include <utility>

using namespace std;

template <class TYPE>
class Table {
public:
		Table() {}
		virtual bool update(const string& key, const TYPE& value) = 0;
		virtual bool remove(const string& key) = 0;
		virtual bool find(const string& key, TYPE& value) = 0;
		virtual ~Table() {}
};

template <class TYPE>
class SimpleTable :public Table<TYPE> {

		struct Record {
				TYPE data_;
				string key_;
				Record(const string& key, const TYPE& data) {
						key_ = key;
						data_ = data;
				}

		};

		Record** records_;   //the table
		int max_;           //capacity of the array
		int size_;          //current number of records held
		int search(const string& key);
		void sort();
		void grow();
public:
		SimpleTable(int maxExpected);
		SimpleTable(const SimpleTable& other);
		SimpleTable(SimpleTable&& other);
		virtual bool update(const string& key, const TYPE& value);
		virtual bool remove(const string& key);
		virtual bool find(const string& key, TYPE& value);
		virtual const SimpleTable& operator=(const SimpleTable& other);
		virtual const SimpleTable& operator=(SimpleTable&& other);
		virtual ~SimpleTable();
};


//returns index of where key is found.
template <class TYPE>
int SimpleTable<TYPE>::search(const string& key) {
		int rc = -1;
		for (int i = 0; i<size_; i++) {
				if (records_[i]->key_ == key) {
						rc = i;
				}
		}
		return rc;
}
//sort the according to key in table
template <class TYPE>
void SimpleTable<TYPE>::sort() {
		int minIdx = 0;
		for (int i = 0; i<size_; i++) {
				minIdx = i;
				for (int j = i + 1; j<size_; j++) {
						if (records_[j]->key_ < records_[minIdx]->key_) {
								minIdx = j;
						}
				}
				Record* tmp = records_[i];
				records_[i] = records_[minIdx];
				records_[minIdx] = tmp;
		}
}

//grow the array by one element
template <class TYPE>
void SimpleTable<TYPE>::grow() {
		Record** newArray = new Record*[max_ + 1];
		max_ = max_ + 1;
		for (int i = 0; i<size_; i++) {
				newArray[i] = records_[i];
		}
		delete[] records_;
		records_ = newArray;
}

/* none of the code in the function definitions below are correct.  You can replace what you need
*/
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int maxExpected) : Table<TYPE>() {
		records_ = new Record*[maxExpected];
		max_ = maxExpected;
		size_ = 0;
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other) {
		records_ = new Record*[other.max_];
		max_ = other.max_;
		size_ = 0;
		for (int i = 0; i<other.size_; i++) {
				update(other.records_[i]->key_, other.records_[i]->data_);
		}
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& other) {
		size_ = other.size_;
		max_ = other.max_;
		records_ = other.records_;
		other.records_ = nullptr;
		other.size_ = 0;
		other.max_ = 0;
}

template <class TYPE>
bool SimpleTable<TYPE>::update(const string& key, const TYPE& value) {
		int idx = search(key);
		if (idx == -1) {
				if (size_ == max_) {
						grow();
				}
				records_[size_++] = new Record(key, value);
				/*sort();*/
		}
		else {
				records_[idx]->data_ = value;
		}
		return true;
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const string& key) {
		int idx = search(key);
		if (idx != -1) {
				delete records_[idx];
				for (int i = idx; i<size_ - 1; i++) {
						records_[i] = records_[i + 1];
				}
				size_--;
				return true;
		}
		else {
				return false;
		}
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const string& key, TYPE& value) {
		int idx = search(key);
		if (idx == -1)
				return false;
		else {
				value = records_[idx]->data_;
				return true;
		}
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other) {
		if (this != &other) {
				if (records_) {
				/*		int sz = size_;
						for (int i = 0; i<sz; i++) {
								remove(records_[0]->key_);
						}*/
						delete[] records_;
				}
				records_ = new Record*[other.max_];
				max_ = other.max_;
				size_ = 0;
				for (int i = 0; i<other.size_; i++) {
						update(other.records_[i]->key_, other.records_[i]->data_);
				}

		}
		return *this;
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& other) {
		swap(records_, other.records_);
		swap(size_, other.size_);
		swap(max_, other.max_);
		return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable() {
		/*if (records_) {
				int sz = size_;
				for (int i = 0; i<sz; i++) {
						remove(records_[0]->key_);
				}*/
				delete[] records_;
		/*}*/
}


/*
LPTable is a hash table that uses linear probing as its collision resolution method. 
*/
template <class TYPE>
class LPTable :public Table<TYPE> {

		struct Record {
				TYPE data_;
				string key_;
				bool isDeleted; //flag for lazy deletion

				//default ctor to make the Record in a safe empty state
			Record() {
					key_ = "";
					data_ = 0;
						isDeleted = false;

				}
				//2param ctor that initializes the key and data elements
				Record(const string& key, const TYPE& data) {
						key_ = key;
						data_ = data;
						isDeleted = false;
				}

		};

		Record** records_;   //the table
		int LargerMax;       // *1.35 max_
		int max_;           //capacity of the array
		int size_;          //current number of records held
		int MyHash(string key); // custom hash function 

public:
		LPTable(int maxExpected);
		LPTable(const LPTable& other);
		LPTable(LPTable&& other);
		virtual bool update(const string& key, const TYPE& value);
		virtual bool remove(const string& key);
		virtual bool find(const string& key, TYPE& value);
		virtual const LPTable& operator=(const LPTable& other);
		virtual const LPTable& operator=(LPTable&& other);
		virtual ~LPTable();
};

//LPTable ctor that takes the max expected Records as its only param
template <class TYPE>
LPTable<TYPE>::LPTable(int maxExpected) : Table<TYPE>() {
		LargerMax = maxExpected * 1.35;

		records_ = new Record*[LargerMax];  

		for (int i = 0; i < LargerMax; i++)
		{
				records_[i] = nullptr;
		}

		size_ = 0;
}


//custom hash function using std::hash
template <class TYPE>
int LPTable<TYPE>::MyHash(string key) {

		size_t idx = hash<string>()(key) % LargerMax;
		return idx;
}


//copy ctor
template <class TYPE>
LPTable<TYPE>::LPTable(const LPTable<TYPE>& other){


		max_ = other.max_;
		LargerMax = other.LargerMax;
		size_ = other.size_;
		records_ = nullptr;
		//if there is something to copy
		if (other.size_)
		{
				//make records_ a Record pointer containing max elements
				records_ = new Record*[other.LargerMax];


				for (int i = 0; i < other.LargerMax; i++) 
				{
						//if there is nothing to copy in the records_ simply mark as nullptr		
						if (other.records_[i] == nullptr)
						{
								records_[i] = nullptr;
						}
						else
						{
								//else declare a new Record and copy the elements
								records_[i] = new Record();
								records_[i]->key_ = other.records_[i]->key_;
								records_[i]->data_ = other.records_[i]->data_;
								records_[i]->isDeleted = other.records_[i]->isDeleted;
						}
						
				}
		}
		else
				size_ = 0;

}


// move ctor
template <class TYPE>
LPTable<TYPE>::LPTable(LPTable<TYPE>&& other) {

		//simply steal the others resources and leave object in a safe empty state
		size_ = other.size_;
		max_ = other.max_;
		LargerMax = other.LargerMax;
		records_ = other.records_;
		other.records_ = nullptr;
		other.size_ = 0;
		other.max_ = 0;
		other.LargerMax = 0;

}

/*
This function is passed a key - value pair.
If your table already has a record with a matching key, the record's
value is replaced by the value passed to this function. If no record exists, 
a record with key-value pair is added to the table as long as it is possible to do so 
(some implementations restrict the amount of data it can hold). 
If the record was successfully added or updated, function returns true.
Otherwise false is returned.
*/
template <class TYPE>
bool LPTable<TYPE>::update(const string& key, const TYPE& value) {

		size_t h = MyHash(key); //hash they key to find 
		int insert = -1;
		/*
		fixMe is a variable that will determing weather to make a new Record(key, value)
		in case of finding a nullptr. Otherwise it will update the key,value of the dead
		records_ index and flip its isDeleted variable to false.
		*/
		int fixMe;

				//if nothing there, simply make a new Record with the key/value
				if (records_[h] == nullptr)
				{
		
						records_[h] = new Record(key, value); 
						size_++;
						records_[h]->isDeleted = false;
						return true;
				}
				//if dead element, simply update key/value pair and turn isDeleted = false
				 if (records_[h]->isDeleted == true)
				{
						records_[h]->key_ = key;
						records_[h]->data_ = value;
						records_[h]->isDeleted = false;
						size_++;
						return true;
				}
		
				 //update the data_ member if matching key and turn isDeleted = false
				if (records_[h]->key_ == key)
				{
						records_[h]->data_ = value; 
						records_[h]->isDeleted = false;
						return true;
				}
		
		//don't go over capacity
			if (size_ == max_)
				{
						return false;
				}
		
			//this iteration will determing how to update the proper index if isDeleted = true
				for (int i = 0; i < LargerMax && insert < 0; i++)
				{
						int idx = (h + i) % LargerMax;
						if (records_[idx] == nullptr)
						{
								insert = idx;
								fixMe = 1;
						}
						else if (records_[idx]->isDeleted == true)
						{
								insert = idx;
								fixMe = 2;
						}
						else if (records_[idx]->key_ == key) {
								records_[idx]->data_ = value;
								records_[idx]->isDeleted = false;
								return true;
						}
		
				}
		     if (insert == -1)
			 	 {
						return false;
				 }

				 else if (fixMe = 1) 
				 {
						 records_[insert] = new Record(key, value);
						 records_[insert]->isDeleted = false;
						 size_++;
						 return true;
				 }

				 else if (fixMe = 2)  
				 {
						 records_[insert]->key_ = key;
						 records_[insert]->data_ = value;
						 records_[insert]->isDeleted = false;
						 size_++;
						 return true;
				 }
				 return false;
}



/*
This function is passed a key.If your table contains a record with a matching key, 
the record(both the key and the value) is removed from the table
*/
template <class TYPE>
bool LPTable<TYPE>::remove(const string& key) {

		size_t hash = MyHash(key);

		//return false if no record at that index
		if (records_[hash] == nullptr )
		{
				return false;
		}
		//remove key and mark isDeleted as true
		if (records_[hash]->key_ == key)
		{
				records_[hash]->key_ = ""; 
				records_[hash]->isDeleted = true;			
				size_--;
				
				return true;
		}

		for (int i = 0; i < LargerMax; i++)
		{
				int idx = (hash + i) % LargerMax;
				//return false if no record at that index
				if (records_[idx] == nullptr )
				{
					
						return false;
					
				}
						if (records_[idx]->key_ == key)
						{
								//remove key and mark isDeleted as true
								records_[idx]->key_ = "";
								records_[idx]->isDeleted = true;						
								size_--;
								
								return true;
						}
				
		}
		return false;
}

/*
This function is passed a key and a reference for passing back a found value.
If your table contains a record with a matching key, the function returns true,
and passes back the value from the record.If it does not find a record with a matching key, 
function returns false.
*/
template <class TYPE>
bool LPTable<TYPE>::find(const string& key, TYPE& value) {

		size_t index = MyHash(key);

		
		if (records_[index] == nullptr)
		{
				return false;
		}

		if (records_[index]->key_ == key)
		{
				value = records_[index]->data_;
				return true;
		}

		for (int i = 0; i < LargerMax; i++)   
		{
				int hash = (index + i) % LargerMax;     
				if (records_[hash] == nullptr )
				{
						return false;
				}
				if (records_[hash]->key_ == key)
				{
						    value = records_[hash]->data_;
								return true;				
				}
				
		}
		return false;
}





//assignment operator
template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(const LPTable<TYPE>& other) 
{
		//make sure not same object
		if (this != &other) {
				if (records_)
						delete[] records_;

				max_ = other.max_;
				LargerMax = other.LargerMax;
				size_ = other.size_;
				records_ = nullptr;
				if (other.size_)
				{
						records_ = new Record*[other.LargerMax];


						for (int i = 0; i < other.LargerMax; i++)
						{

								if (other.records_[i] == nullptr)
								{
										records_[i] = nullptr;
								}
								else
								{
										records_[i] = new Record();

										records_[i]->key_ = other.records_[i]->key_;
										records_[i]->data_ = other.records_[i]->data_;
										records_[i]->isDeleted = other.records_[i]->isDeleted;
								}

						}
				}
				else
						size_ = 0;
		}

				return *this;
}

// move assignment
template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(LPTable<TYPE>&& other) {
		swap(records_, other.records_);
		swap(size_, other.size_);
		swap(max_, other.max_);
		swap(LargerMax, other.LargerMax);
		return *this;

}
template <class TYPE>
LPTable<TYPE>::~LPTable() {

		 delete[] records_;
}