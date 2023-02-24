#ifndef __PROJ_FOUR_LEVEL_BALANCED_TREE_HPP
#define __PROJ_FOUR_LEVEL_BALANCED_TREE_HPP

#include "runtimeexcept.hpp"
#include <string>
#include <vector>

class ElementNotFoundException : public RuntimeException 
{
public:
	ElementNotFoundException(const std::string & err) : RuntimeException(err) {}
};


template<typename Key, typename Value>
class LevelBalancedTree
{
private:
	// fill in private member data here
	// If you need to declare private functions, do so here too.

	struct Node
	{
		Key key;
		Value val;

		Node* left = nullptr;
		Node* right = nullptr;
		Node* parent = nullptr;

		unsigned leftDis = 1;
		unsigned rightDis = 1;
		unsigned level = 1;

	};

	//Deconstructor helper function
	void decHelp(Node* temp){
		if (temp == nullptr){
		return;
		}
		decHelp(temp->left);
		decHelp(temp->right);
		delete temp;
	}

	//in order helper
	void inOrderHelper(Node* current, std::vector<Key> &final) const{
		if (!current->left){
			final.push_back(current->key);
		}
		else{
			inOrderHelper(current->left, final);
			final.push_back(current->key);
		}

		if (!current->right){
			return;
		}
		else{
			inOrderHelper(current->right, final);
		}
	}

	//pre order helper
	void preOrderHelper(Node* c, std::vector<Key> &final) const {
		final.push_back(c->key);
		if (c->left){
			preOrderHelper(c->left, final);
		}

		if (c->right){
			preOrderHelper(c->right, final);
		}
	}

	//post order helper
	void postOrderHelper(Node* c, std::vector<Key> &final) const {
		if (c->left){
			postOrderHelper(c->left, final);
		}

		if (c->right){
			postOrderHelper(c->right, final);
		}
		final.push_back(c->key);
	}

	//distance rebalance helper function
	void sideLevelerHelp(Node* n){
		if(!n){
			return;
		}
		if(n->left){
		n->leftDis = n->level - n->left->level;
		}
		else{
			n->leftDis = n->level;
		}
		if (n->right){
		n->rightDis = n->level - n->right->level;
		}
		else{
			n->rightDis = n->level;
		}
	}


	//insert balance helper function
	void insertHelp(Node* cur){
		if (!cur){
			return;
		}
		Node* oldpar = nullptr;
		if(cur->parent){
			oldpar = cur->parent;
		}
		
		//check if left child is on the same level
		//left
		if (cur->left and cur->level == cur->left->level){

			if(cur->rightDis ==1){
				cur->level +=1;

				sideLevelerHelp(cur);
				if (cur->parent){
					sideLevelerHelp(cur->parent);
				}
				insertHelp(cur->parent);
			}

			//check if cur can go down
			//check if right is dist 2
			else if (cur->rightDis == 2){
				cur->level -=1;

				cur->parent = cur->left;
				cur->left= cur->parent->right;
				cur->parent->right = cur;
				if (cur->left){
					cur->left->parent = cur;
				}
				if (oldpar){
					if (oldpar->key < cur->key){
						oldpar->right = cur->parent;
						cur->parent->parent=oldpar;
					}
					else{
						oldpar->left = cur->parent;
						cur->parent->parent=oldpar;
					}
				}
				else{
					cur->parent->parent = nullptr;
					this->root = cur->parent;
				}

				sideLevelerHelp(cur);
				insertHelp(cur->parent);

			}
		}
		//right
		else if (cur->right and cur->level == cur->right->level){

			if(cur->leftDis ==1){
				cur->level +=1;

				sideLevelerHelp(cur);
				if (cur->parent){
					sideLevelerHelp(cur->parent);
				}
				insertHelp(cur->parent);
			}

			//check if cur can go down
			//check if right is dist 2
			else if (cur->leftDis == 2){
				cur->level -=1;


				cur->parent = cur->right;
				cur->right= cur->parent->left;
				cur->parent->left = cur;
				if (cur->right){                                    //dont think i need this in either
					cur->right->parent = cur;
				}
				if (oldpar){
					if (oldpar->key < cur->key){
						oldpar->right = cur->parent;
						cur->parent->parent=oldpar;
					}
					else{
						oldpar->left = cur->parent;
						cur->parent->parent=oldpar;
					}
				}
				else{
					cur->parent->parent = nullptr;
					this->root = cur->parent;
				}

				sideLevelerHelp(cur);
				insertHelp(cur->parent);

			}
		}
		else if (cur->right and cur->right->left and cur->right->level == cur->right->left->level) {
			Node* mc = cur->right->left;
			mc->level += 1;
			cur -> level -=1;

			//reassign left pointer
			cur->right = mc->left;
			if (cur->right){
				cur->right->parent = cur;
			}
			mc->parent->left = mc->right;
			if (mc->right){
				mc->right->parent = mc->parent;
			}
			//fix mc pointers
			mc->right = mc->parent;
			mc->left = cur;
			mc->parent = oldpar;
			//fix old par
			if (oldpar){
					if (oldpar->key < mc->key){
						oldpar->right = mc;
						mc->parent=oldpar;
					}
					else{
						oldpar->left = mc;
						mc->parent=oldpar;
					}
			}
			else{
				this->root = mc;
			}
			//fix right child
			mc->right->parent = mc;
			//fix left child
			mc->left->parent = mc;
			sideLevelerHelp(mc);
			sideLevelerHelp(mc->left);
			sideLevelerHelp(mc->right);
		}
		else if (cur->left and cur->left->right and cur->left->level == cur->left->right->level) {
			Node* mc = cur->left->right;
			mc->level += 1;
			cur -> level -=1;

			//reassign left pointer
			cur->left = mc->right;
			if (cur->left){
				cur->left->parent = cur;
			}
			mc->parent->right = mc->left;
			if (mc->left){
				mc->left->parent = mc->parent;
			}
			//fix mc pointers
			mc->left = mc->parent;
			mc->right = cur;
			mc->parent = oldpar;
			//fix old par
			if (oldpar){
					if (oldpar->key < mc->key){
						oldpar->right = mc;
						mc->parent=oldpar;
					}
					else{
						oldpar->left = mc;
						mc->parent=oldpar;
					}
			}
			else{
				this->root = mc;
			}
			//fix left child
			mc->left->parent = mc;
			//fix right child
			mc->right->parent = mc;
			sideLevelerHelp(mc);
			sideLevelerHelp(mc->left);
			sideLevelerHelp(mc->right);
		}
		else{
			return;
		}
		sideLevelerHelp(cur);
	}

	//Delete Helper
	void delHelper(Node* cur){
		if (!cur){
			return;
		}
		if(!cur->left and cur->leftDis == 2 and cur->rightDis == 2){
			cur->level -=1;
			sideLevelerHelp(cur);
			sideLevelerHelp(cur->parent);
		}
		else if (2 < cur->rightDis){
			cur->level -=1;
			sideLevelerHelp(cur);
			sideLevelerHelp(cur->parent);
			remAdjuster(cur->left);
		}
		else if (2 < cur->leftDis){
			cur->level -=1;
			sideLevelerHelp(cur);
			sideLevelerHelp(cur->parent);
			remAdjuster(cur->right);
		}
		else if((cur->right and cur->right->left and cur->right->level == cur->right->left->level) or (cur->left and cur->left->right and cur->left->level == cur->left->right->level)){
			remAdjuster(cur);
		}
		delHelper(cur->parent);
	}

	void remAdjuster(Node* cur){
		Node* oldpar = nullptr;
		if(cur->parent){
			oldpar = cur->parent;
		}
		if (cur->parent and cur->level == cur->parent->level){
			if(cur->parent->left == cur){
				if (((cur->leftDis ==1 and cur->rightDis==1)or (cur->leftDis ==1 and cur->rightDis==2)) ){
					cur->level+=1;
					if (cur->parent->parent){
						if(cur->parent->parent->right == cur->parent){
							cur->parent->parent->right = cur;
						}
						else{
							cur->parent->parent->left = cur;
						}
						cur->parent = oldpar->parent;
					}
					else{
						cur->parent = nullptr;
						root = cur;
					}
					oldpar->left = cur->right;
					if (oldpar->left){
						oldpar->left->parent = oldpar;
					}
					cur->right = oldpar;
					oldpar->parent = cur;
					sideLevelerHelp(cur);
					sideLevelerHelp(cur->parent);
					sideLevelerHelp(cur->right);
				}
				//can't go up
				else if(cur->leftDis==2 and cur->rightDis==2){
					cur->level -=1;
					sideLevelerHelp(cur);
					sideLevelerHelp(cur->parent);
				}
				//can't go up or down
				else if(cur->leftDis==2 or cur->rightDis==2){
					cur->parent->level -=1;
					if (cur->parent->parent){
						if(cur->parent->parent->right == cur->parent){
							cur->parent->parent->right = cur;
						}
						else{
							cur->parent->parent->left = cur;
						}
						cur->parent = oldpar->parent;
					}
					else{
						cur->parent = nullptr;
						root = cur;
					}
					oldpar->left = cur->right;
					if (oldpar->left){
						oldpar->left->parent = oldpar;
					}
					oldpar->parent = cur;
					cur->right = oldpar;

					sideLevelerHelp(cur);
					sideLevelerHelp(cur->parent);
					sideLevelerHelp(cur->right);

					}
				

			}
			//parent is on left
			else if(cur->parent->right == cur){
				if (((cur->leftDis ==1 and cur->rightDis==1) or (cur->leftDis ==2 and cur->rightDis==1)) ){
					cur->level+=1;
					if (cur->parent->parent){
						if(cur->parent->parent->right == cur->parent){
							cur->parent->parent->right = cur;
						}
						else{
							cur->parent->parent->left = cur;
						}
						cur->parent = oldpar->parent;
					}
					else{
						cur->parent = nullptr;
						root = cur;
					}
					oldpar->right = cur->left;
					if (oldpar->right){
						oldpar->right->parent = oldpar;
					}
					cur->left = oldpar;
					oldpar->parent = cur;
					sideLevelerHelp(cur);
					sideLevelerHelp(cur->parent);
					sideLevelerHelp(cur->left);
				}
				//can't go up
				else if(cur->leftDis==2 and cur->rightDis==2){
					cur->level -=1;
					sideLevelerHelp(cur);
					sideLevelerHelp(cur->parent);
				}
				//can't go up or down
				else if(cur->leftDis==2 or cur->rightDis==2){
					cur->parent->level -=1;
					if (cur->parent->parent){
						if(cur->parent->parent->right == cur->parent){
							cur->parent->parent->right = cur;
						}
						else{
							cur->parent->parent->left = cur;
						}
						cur->parent = oldpar->parent;
					}
					else{
						cur->parent = nullptr;
						root = cur;
					}
					oldpar->right = cur->left;
					if (oldpar->right){
						oldpar->right->parent = oldpar;
					}
					oldpar->parent = cur;
					cur->left = oldpar;

					sideLevelerHelp(cur);
					sideLevelerHelp(cur->parent);
					sideLevelerHelp(cur->left);

					}
			}
				
			delHelper(cur);
		}
		else if (cur->left and cur->left->right and cur->left->level == cur->left->right->level) {
				Node* mc = cur->left->right;
				mc->level += 2;
				cur -> level -=1;

				//reassign left pointer
				cur->left = mc->right;
				if (cur->left){
					cur->left->parent = cur;
				}
				mc->parent->right = mc->left;
				if (mc->left){
					mc->left->parent = mc->parent;
				}
				//fix mc pointers
				mc->left = mc->parent;
				mc->right = cur;
				mc->parent = oldpar;
				//fix old par
				if (oldpar){
						if (oldpar->key < mc->key){
							oldpar->right = mc;
							mc->parent=oldpar;
						}
						else{
							oldpar->left = mc;
							mc->parent=oldpar;
						}
				}
				else{
					this->root = mc;
				}
				//fix left child
				mc->left->parent = mc;
				//fix right child
				mc->right->parent = mc;
				sideLevelerHelp(mc);
				sideLevelerHelp(mc->left);
				sideLevelerHelp(mc->right);
			}
			else if (cur->right and cur->right->left and cur->right->level == cur->right->left->level) {
			Node* mc = cur->right->left;
			mc->level += 2;
			cur -> level -=1;

			//reassign left pointer
			cur->right = mc->left;
			if (cur->right){
				cur->right->parent = cur;
			}
			mc->parent->left = mc->right;
			if (mc->right){
				mc->right->parent = mc->parent;
			}
			//fix mc pointers
			mc->right = mc->parent;
			mc->left = cur;
			mc->parent = oldpar;
			//fix old par
			if (oldpar){
					if (oldpar->key < mc->key){
						oldpar->right = mc;
						mc->parent=oldpar;
					}
					else{
						oldpar->left = mc;
						mc->parent=oldpar;
					}
			}
			else{
				this->root = mc;
			}
			//fix right child
			mc->right->parent = mc;
			//fix left child
			mc->left->parent = mc;
			sideLevelerHelp(mc);
			sideLevelerHelp(mc->left);
			sideLevelerHelp(mc->right);
		}
	}

	//Size counter
	unsigned count;
	//Root of tree
	Node* root;
	

public:
	LevelBalancedTree();

	// In general, a copy constructor and assignment operator
	// are good things to have.
	// For this quarter, I am not requiring these. 
	//	LevelBalancedTree(const LevelBalancedTree & st);
	//	LevelBalancedTree & operator=(const LevelBalancedTree & st);


	// The destructor is required. 
	~LevelBalancedTree();

	// size() returns the number of distinct keys in the tree.
	size_t size() const noexcept;

	// isEmpty() returns true if and only if the tree has no values in it. 
	bool isEmpty() const noexcept;

	// contains() returns true if and only if there
	//  is a (key, value) pair in the tree
	//	that has the given key as its key.
	bool contains(const Key & k) const noexcept; 

	// find returns the value associated with the given key
	// If !contains(k), this will throw an ElementNotFoundException
	// There needs to be a version for const and non-const LevelBalancedTrees.
	Value & find(const Key & k);
	const Value & find(const Key & k) const;

	// Inserts the given key-value pair into 
	// the tree and performs the balancing operation(s) if needed
	// operation, as described in lecture. 
	// If the key already exists in the tree, 
	// you may do as you please (no test cases in
	// the grading script will deal with this situation)
	void insert(const Key & k, const Value & v);

	// Deletes the given key from the tree
	// and performs the balancing operation(s) if needed.
	// If the key does not exist in the tree, 
	// do not modify the tree.
	void remove(const Key &k);


	// The following three functions all return
	// the set of keys in the tree as a standard vector.
	// Each returns them in a different order.
	std::vector<Key> inOrder() const;
	std::vector<Key> preOrder() const;
	std::vector<Key> postOrder() const;


};


template<typename Key, typename Value>
LevelBalancedTree<Key,Value>::LevelBalancedTree()
{
	this->count = 0;
	this->root = new Node;
}

template<typename Key, typename Value>
LevelBalancedTree<Key,Value>::~LevelBalancedTree()
{
	decHelp(this->root);
}

template<typename Key, typename Value>
size_t LevelBalancedTree<Key, Value>::size() const noexcept
{
	return this->count;
}

template<typename Key, typename Value>
bool LevelBalancedTree<Key, Value>::isEmpty() const noexcept
{
	if (count == 0){
		return true;
	}
	return false;
}


template<typename Key, typename Value>
bool LevelBalancedTree<Key, Value>::contains(const Key &k) const noexcept
{
	Node* temp = this->root;
	while (temp){
		if (temp->key < k){
			temp = temp->right;
		}
		else if (k<temp->key){
			temp = temp->left;
		}
		else if (temp->key==k){
			return true;
		}
	}
	return false;
}



template<typename Key, typename Value>
Value & LevelBalancedTree<Key, Value>::find(const Key & k)
{
	Node* temp = root;
	while (temp){
		if (temp->key < k){
			temp = temp->right;
		}
		else if (k<temp->key){
			temp = temp->left;
		}
		else if (temp->key==k){
			return temp->val;
		}
	}
	throw ElementNotFoundException("Element not in tree");
}

template<typename Key, typename Value>
const Value & LevelBalancedTree<Key, Value>::find(const Key & k) const
{
	Node* temp = root;
	while (temp){
		
		if (temp->key < k){
			temp = temp->right;
		}
		else if (k<temp->key){
			temp = temp->left;
		}
		else if (temp->key==k){
			const Value &v = temp->val;
			return v;
		}
	}
	throw ElementNotFoundException("Element not in tree");
}

template<typename Key, typename Value>
void LevelBalancedTree<Key, Value>::insert(const Key & k, const Value & v)
{
	Node* temp = this->root;
	if (this->count == 0){
		this->root->key = k;
		this->root->val = v;
	}
	else{
		Node* i = new Node;
		i->val = v;
		i->key = k;

		while (true){
			if (k < temp->key){
				if (temp->left){
					temp = temp->left;
				}
				else{
					temp->left = i;
					i->parent = temp;
					temp->leftDis = 1;
					break;
				}
			}
			else if (temp->key < k){
				if (temp->right){
					temp = temp->right;
				}
				else{
					temp->right = i;
					i->parent = temp;
					temp->rightDis = 1;
					break;
				}
			}
		}
	}
	this->count += 1;
	
	insertHelp(temp);

	return; 	
}

template<typename Key, typename Value>
void LevelBalancedTree<Key, Value>::remove(const Key &k)
//Code From Zybooks Chapet 7.4
{
	count -=1;
	//find node
	Node* temp = root;
	while (temp){
		if (temp->key < k){
			temp = temp->right;
		}
		else if (k<temp->key){
			temp = temp->left;
		}
		else if (temp->key==k){
			break;
		}
	}
	if (!temp){
		return;
	}
	Node* partemp = nullptr;
	if (temp->parent){
		partemp = temp->parent;
	}
	//Node found
	//Leaf Node
	if (!temp->left and !temp->right){
		if (!temp->parent){//root
			delete temp;
			this->root = nullptr;
		}
		else if(temp->parent->left == temp){
			delete temp->parent->left;
			partemp->left = nullptr;
			sideLevelerHelp(partemp);
		}
		else{
			delete temp->parent->right;
			partemp->right = nullptr;
			sideLevelerHelp(partemp);
		}
	}
	else if (!temp->right){
		if (!temp->parent){
			this->root = temp->left;
			delete temp;
			root->parent = nullptr;
		}
		else if (temp->parent->left == temp){
			temp->parent->left = temp->left;
			temp->left->parent = temp->parent;
			delete temp;
			sideLevelerHelp(partemp);
		}
		else{
			temp->parent->right = temp->left;
			temp->left->parent = temp->parent;
			delete temp;
			sideLevelerHelp(partemp);
		}
	}
	else if (!temp->left){
		if (!temp->parent){
			this->root = temp->right;
			delete temp;
			root->parent = nullptr;
		}
		else if (temp->parent->left == temp){
			temp->parent->left = temp->right;
			temp->right->parent = temp->parent;
			delete temp;
			sideLevelerHelp(partemp);
		}
		else{
			temp->parent->right = temp->right;
			temp->right->parent = temp->parent;
			delete temp;
			sideLevelerHelp(partemp);
		}
	}
	else{
		//find successor
		Node* suc = temp->right;
		while(suc->left){
			suc = suc->left;
		}
		Node* sucdata = new Node;
		sucdata->key = suc->key;
		sucdata->val = suc->val;
		Node* part = suc->parent;
		remove(suc->key);
		sideLevelerHelp(part);

		temp->key = sucdata->key;
		temp->val = sucdata->val;
		delete sucdata;
	}
	delHelper(partemp);
}



template<typename Key, typename Value>
std::vector<Key> LevelBalancedTree<Key, Value>::inOrder() const
{
	std::vector<Key> final;
	inOrderHelper(this->root, final);
	return final; 
}


template<typename Key, typename Value>
std::vector<Key> LevelBalancedTree<Key, Value>::preOrder() const
{
	std::vector<Key> final;
	preOrderHelper(root, final);
	return final; 
}


template<typename Key, typename Value>
std::vector<Key> LevelBalancedTree<Key, Value>::postOrder() const
{
	std::vector<Key> final;
	postOrderHelper(root, final);
	return final;
}







#endif 