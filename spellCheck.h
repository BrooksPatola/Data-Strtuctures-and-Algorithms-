#ifndef A3_H
#define A3_H
#include <string>
using namespace std;

/*
SpellCheck class that will be capable of quickly determining
if a word is spelled correctly or not and offer a suggestions list
*/
class SpellCheck {
		struct Node {
				bool isTerminal_; //valid word entry
				char ch_;
				Node* children_[27]; //need to allocate space for all the letters of the alphabet 
				Node(char c = '\0') { //ctor to make Node in a safe empty state
						isTerminal_ = false;
						ch_ = c;
						for (int i = 0; i < 26; i++) {
								children_[i] = nullptr;
						}
				}
				//given lower case alphabetic charachters ch, returns 
				//the associated index 'a' --> 0, 'b' --> 1...'z' --> 25
				int getIndex(char ch) {
						return ch - 'a' ;	
				}
		};
		Node* root_; 

		/*
		find the node that represents the end of the partial word
		we call this search within our suggest function
		*/
		Node* search(const string& word, Node* node, int index) const {
				
				// Return immediately on failure.
			
				if (index >= word.length())
				{
						return node;
				}

				int child_index = node->getIndex(word[index]);

				// we either have this child or we don't...
				if (node->children_[child_index] == nullptr) {
						return nullptr;
				}
				else {
				
								return search(word, node->children_[child_index], index + 1);
						
				}

			}
		
		void addWord(const string& newWord, int currChar, Node* rt) {
				
				//check if currChar index is still in newWord
				if (currChar < newWord.length()) {
						//find index of currChar
						char currLetter = newWord[currChar];
						 int idx = rt->getIndex(currLetter);

						//if no letter at that index create a new node
						if (!rt->children_[idx])
								//make a new node
								rt->children_[idx] = new Node(currLetter);
						//continue to add
						addWord(newWord, currChar + 1, rt->children_[idx]);
				}
				else
						rt->isTerminal_ = true; //last char
		}

		/*
		int passed by reference so everytime you add to suggest, it is updated.  
		once you find the node corresponding to the ending letter,
		you will want to do a traversal (pre-order) of that subtree.
		*/
		void suggest(const string& partialWord, Node* rt, string suggestions[], int& count) const {
			
				if (rt) {
						if (rt->isTerminal_) { //check if terminal node
								suggestions[count++] = partialWord;
						}
						for (int i = 0; i < 26; i++) { // traversal 
								if (rt->children_[i] != nullptr) { 
										suggest(partialWord + rt->children_[i]->ch_, rt->children_[i], suggestions, count);
								}
						}
				}
				return;

		}

		//recursive lookup function that will take string, Node*, and int
		//iterative version currently main function call for lookup
		bool lookup(const string& word, Node* root, int check) const{

				if (!root) {
						return false;
				}
				if (check == word.length() && root->isTerminal_ == true) {// you have reached the end of the word.
						return true;
				}

				int i = 0;

				while (root->children_[i] != nullptr) {//while there is children
						if (root->children_[i]->getIndex(i) == word[check]) {// character matches the one in your string.
								root = root->children_[i];  // change root to current child node.
								check++;  // increase the counter on check by one

													// Recursive call, if character matches at this point. then call the 
													//function recursively and return whatever the next instance of lookup returns.
								return lookup(word, root, check);

						}
						i++;
				}
				// if no child value matches the current value you need.
				return false;
		}
	

public:
		SpellCheck(string data[], int sz);
		void addWord(const string& newWord);
		bool lookup(const string& word) const; 
		int suggest(const string& partialWord, string suggestions[]) const;
		~SpellCheck();
		void clear(Node* node);

};
#endif
