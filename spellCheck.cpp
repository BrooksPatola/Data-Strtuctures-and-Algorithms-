#include "a3.h"
#include <string>
using namespace std;


SpellCheck::SpellCheck(string data[], int sz) {
		root_ = new Node();
		for (int i = 0; i < sz; i++) {
				addWord(data[i]);
		}
}

/*
adds new word to the SpellCheck. 
You can assume that newword will be purely alphabetic and lower case
*/
void SpellCheck::addWord(const string& newWord) {
		//recursive call to addWord that takes a string, int, and Node*
		addWord(newWord, 0, root_);
}


/*
looks up the word in the SpellCheck object.
If it is in the SpellCheck object,true is returned. 
You can assume that the word will be all lower case.
*/
bool SpellCheck::lookup(const string& word) const {

		
		//return lookup(word, root_, 0);

		if (!root_) {
				return false;
		}

		Node* curr = root_;

		if (word[0] == '\0') {
				return curr->isTerminal_ == true;
		}
		
		for (int i = 0; i < word.length(); ++i)
		{
				int idx = curr->getIndex(word[i]);

				if (curr->children_[idx] == nullptr) {
						return false;
				}
				//make curr the child of current node
				curr = curr->children_[idx];

		}
		return curr->isTerminal_ == true;
}

/*
given a string, this function will find all words that start with the string partialWord
within the SpellCheck object and store them into suggestions.
Function returns number of words stored within suggestions.
*/
int SpellCheck::suggest(const string& partialWord, string suggestions[]) const {

		  Node* temp; // Node* to ending of partialWord

			temp = search(partialWord, root_, 0);

			int count = 0; //initialize the reference to 0 prior to call

			suggest(partialWord, temp, suggestions, count);
					
			return count; //return the reference

}


//destructor
SpellCheck::~SpellCheck() {
		
		clear(root_);
}

//recursive clear function used within dtor
void SpellCheck::clear(Node* node) {

		if (!node) return;

		for (int i = 0; i < 26; i++) {
				clear(node->children_[i]);
		}
		delete node;
}