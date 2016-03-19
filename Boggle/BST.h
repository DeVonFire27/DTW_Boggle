#pragma once
#include <fstream>
using namespace std;
template <typename Type> class BST
{

private:
	struct Node
	{
		Type Data;
		Node* left;
		Node* right;

		Node();
	};

	fstream fout;

	Node* root;
	Node* HelperInsert(const Type& v, Node* curr);
	Node* HelperFind(const Type& v, Node* curr) const;
	void HelperInOrder(Node* temp) const;
	void HelperInOrderTxt(Node* temp);
	void HelperClear(Node* curr);
	void HelperRRemove();
	void HelperRemove(Node* curr);
	typename BST<Type>::Node* HelperAssign(Node* curr);

public:
	BST();
	~BST();
	BST<Type>& operator=(const BST& that);
	BST(const BST& that);
	bool findAndRemove(const Type& v);
	bool find(const Type& v) const;
	void clear();
	void printInOrder() const;
	void printInOrderTxt();
	void insert(const Type& v);

};

template<typename Type>
BST<Type>::Node::Node()
{
	left = nullptr;
	right = nullptr;
}

/////////////////////////////////////////////////////////////////////////////
// Function : Constuctor
// Notes : constucts an empty BST
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
BST<Type>::BST()
{
	root = nullptr;
}

/////////////////////////////////////////////////////////////////////////////
// Function : Destructor
// Notes : destroys the BST cleaning up any dynamic memory
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
BST<Type>::~BST()
{
	HelperClear(root);
}

/////////////////////////////////////////////////////////////////////////////
// Function : assignment operator
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
BST<Type>& BST<Type>::operator=(const BST& that)
{
	if (this == &that)
		return *this;

	clear();
	//root = nullptr;

	root = HelperAssign(that.root); 
	return *this;
}

template <typename Type>
typename BST<Type>::Node* BST<Type>::HelperAssign(typename BST<Type>::Node* curr)
{


	if(curr == nullptr)
		return nullptr;

	Node* left = HelperAssign(curr->left);
	Node* right = HelperAssign(curr->right);
	Node* temp = new Node;
	temp->Data = curr->Data;
	temp->left = left;
	temp->right = right;

	return temp;
}

/////////////////////////////////////////////////////////////////////////////
// Function: copy constructor
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
BST<Type>::BST(const BST& that)
{
	root = nullptr;
	*this = that;
}


/////////////////////////////////////////////////////////////////////////////
// Function : insert
// Parameters :  v - the item to insert 
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
void BST<Type>::insert(const Type& v)
{
	Node* temp = new Node;
	temp->Data = v;
	Node* curr = root;
	if(root == nullptr)
		root = temp;
	else
	{
		curr = HelperInsert(v, curr);
		if(curr->Data >= v)
			curr->left = temp;
		else
			curr->right = temp;
	}

}

template <typename Type>
typename BST<Type>::Node* BST<Type>::HelperInsert(const Type& v, typename BST<Type>::Node* curr)
{
	if(v < curr->Data)
	{
		if(curr->left == nullptr)
			return curr;
		else 
			curr = HelperInsert(v, curr->left);
	}
	else if(v >= curr->Data)
	{
		if(curr->right == nullptr)
			return curr;
		else
			curr = HelperInsert(v,curr->right);

	}
	return curr;
}

/////////////////////////////////////////////////////////////////////////////
// Function : findAndRemove
// Parameters : v - the item to find (and remove if it is found)
// Return : bool - true if the item was removed, false otherwise
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
bool BST<Type>::findAndRemove(const Type& v)
{
	if(!find(v))
		return false;
	Node* temp = root;
	temp = HelperFind(v, temp);
	if(root->Data == v)
		HelperRRemove();
	else
		HelperRemove(temp);
	return true;
}

template <typename Type>
void BST<Type>::HelperRemove(Node* curr)
{
	if(curr->left == nullptr && curr->right == nullptr)
	{
		Node* temp = root;
		while(temp->left != curr && temp->right != curr)
		{
			if(temp->Data < curr->Data)
				temp = temp->right;
			else
				temp = temp->left;
		}
		if(temp->left == curr)
			temp->left = nullptr;
		else
			temp->right = nullptr;
		delete curr;
	}
	else if(curr->left == nullptr || curr->right == nullptr)
	{
		Node* parent = root;
		while(parent->left != curr && parent->right != curr)
		{
			if(parent->Data < curr->Data)
				parent = parent->right;
			else
				parent = parent->left;
		}
		Node* temp;
		if(curr->left != nullptr)
			temp = curr->left;
		else
			temp = curr->right;

		if(parent->left == curr)
			parent->left = temp;
		else
			parent->right = temp;

		delete curr;
	}
	else
	{
		Node* temp = curr->right;
		Node* parent = curr;
		if(temp->left != nullptr)
		{
			temp = temp->left;
			parent = parent->right;
		}
		for(;temp->left != nullptr; temp = temp->left)
			parent = parent->left;
		Type tmp = temp->Data;
		//curr->Data = temp->Data;
		HelperRemove(temp);
		/*if(parent == curr)
		curr->right = nullptr;
		else
		parent->left = nullptr;*/
		curr->Data = tmp;
	}
}

template <typename Type>
void BST<Type>::HelperRRemove()
{
	if(root->left == nullptr && root->right == nullptr)
	{
		delete root;
		root = nullptr;
	}
	else if(root->left == nullptr || root->right == nullptr)
	{
		if(root->left != nullptr)
		{
			Node* temp = root;
			root = temp->left;
			delete temp;
		}
		else if(root->right != nullptr)
		{
			Node* temp = root;
			root = temp->right;
			delete temp;
		}
	}
	else
	{
		Node* temp = root;
		HelperRemove(temp);
		root = temp;
	}
}

/////////////////////////////////////////////////////////////////////////////
// Function : find
// Parameters : v - the item to find
// Return : bool - true if the item was found, false otherwise
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
bool BST<Type>::find(const Type& v) const
{
	Node* curr = root;
	Node* branch = HelperFind(v, curr);
	if(branch == nullptr)
		return false;
	return true;
}

template <typename Type>
typename BST<Type>::Node* BST<Type>::HelperFind(const Type& v, typename BST<Type>::Node* curr) const
{
	if(curr == nullptr)
		return curr;
	else if(v > curr->Data)
	{
		curr = curr->right;
		curr = HelperFind(v, curr);
	}
	else if(v < curr->Data)
	{
		curr = curr->left;
		curr = HelperFind(v, curr);
	}
	return curr;
}

/////////////////////////////////////////////////////////////////////////////
// Function : clear
// Notes : clears the BST, cleaning up any dynamic memory
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
void BST<Type>::clear()
{
	HelperClear(root);
}

template <typename Type>
void BST<Type>::HelperClear(Node* curr)
{
	if(curr != nullptr)
	{
		HelperClear(curr->left);
		HelperClear(curr->right);
		delete curr;
	}
	root = nullptr;
}

/////////////////////////////////////////////////////////////////////////////
// Function : printInOrder
// Notes : prints the contents of the BST to the screen, in ascending order
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
void BST<Type>::printInOrder() const
{
	HelperInOrder(root);
	cout << '\n';
}

template <typename Type>
void BST<Type>::HelperInOrder(Node* temp) const
{
	if(temp != nullptr)
	{
		HelperInOrder(temp->left);
		cout << temp->Data << ' ';
		HelperInOrder(temp->right);
	}
}

template <typename Type>
void BST<Type>::printInOrderTxt()
{
	fout.open("HighScores.bin", ios_base::out | ios_base::binary);
	HelperInOrderTxt(root);
	fout.close();
	cout << '\n';
}

template <typename Type>
void BST<Type>::HelperInOrderTxt(Node* temp)
{
	if(temp != nullptr)
	{
		HelperInOrderTxt(temp->left);
		cout << temp->Data << '\n';
		fout << temp->Data << '\n';
		HelperInOrderTxt(temp->right);
	}
}