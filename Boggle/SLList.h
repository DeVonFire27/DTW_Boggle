#pragma once
// forward declaration
template<typename Type> class SLLIter;

// class SLList
template<typename Type> class SLList
{
	// the iterator is the list’s friend
	friend class SLLIter<Type>;

	struct Node
	{
		Type Data;
		Node* next;
	};
	Node* Head;
	unsigned int nSize;

public:
	SLList();
	~SLList();
	SLList<Type>& operator=(const SLList<Type>& that);
	SLList(const SLList<Type>& that);
	void HelperOpEqual(Node* pCurr);
	void addHead(const Type& v);
	void insert(SLLIter<Type>& index, const Type& v);
	void remove(SLLIter<Type>& index);
	void clear();


	/////////////////////////////////////////////////////////////////////////////
	// Function : size
	// Return : the number of items stored in the linked list.
	/////////////////////////////////////////////////////////////////////////////
	inline unsigned int size() const { return nSize; }


};

// class SLLIter
template<typename Type> class SLLIter
{
	// the list is the iterator’s friend
	friend class SLList<Type>;
	typename SLList<Type>::Node* prev;
	typename SLList<Type>::Node* curr;
	SLList<Type>* iter;


public:
	SLLIter(SLList<Type>& listToIterate);
	SLLIter(const SLList<Type>& listToIterate);
	void begin();
	bool end() const;
	Type& current() const;
	SLLIter<Type>& operator++();

};

#pragma region SSList

/////////////////////////////////////////////////////////////////////////////
// Function : Constructor
// Notes : constructs an empty list
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
SLList<Type>::SLList()
{
	nSize = 0;
	Head = nullptr;
}

/////////////////////////////////////////////////////////////////////////////
// Function : Destructor
// Notes : Destroys the list
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
SLList<Type>::~SLList()
{
	Node* temp;
	while(Head != nullptr)
	{
		temp = Head;
		Head = temp->next;
		delete temp;
	}
}

template<typename Type>
void SLList<Type>::HelperOpEqual(Node* pCurr)
{
	if (pCurr != nullptr)
	{
		if(pCurr->next != nullptr)
			HelperOpEqual(pCurr->next);
		addHead(pCurr->Data); 
	}
}

/////////////////////////////////////////////////////////////////////////////
// Function : Assignment Operator
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
SLList<Type>& SLList<Type>::operator=(const SLList<Type>& that)
{
	if(this == &that)
		return *this;
	this->clear();
	this->nSize = 0;
	HelperOpEqual(that.Head);

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// Function : Copy Constructor
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
SLList<Type>::SLList(const SLList<Type>& that)
{
	Head = nullptr;
	*this = that;

}

/////////////////////////////////////////////////////////////////////////////
// Function : addHead
// Parameters :	v - the item to add to the list
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void SLList<Type>::addHead(const Type& v)
{
	Node *temp = new Node;
	temp->Data = v;
	temp->next = Head;
	Head = temp;
	nSize++;
}

/////////////////////////////////////////////////////////////////////////////
// Function : clear
// Notes : clears the list, freeing any dynamic memory
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void SLList<Type>::clear()
{
	Node* temp;
	while(Head != nullptr)
	{
		temp = Head;
		Head = temp->next;
		delete temp;
	}
	nSize = 0;
}

/////////////////////////////////////////////////////////////////////////////
// Function : insert
// Parameters :	index - an iterator to the location to insert at
//				v - the item to insert
// Notes : do nothing on a bad iterator
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void SLList<Type>::insert(SLLIter<Type>& index, const Type& v)
{
	if(index.curr != nullptr)
	{
		Node* temp = new Node;
		temp->Data = v;
		if(index.curr == Head)
		{
			temp->next = Head;
			index.curr = temp;
			Head = temp;
		}
		else
		{
			index.prev->next = temp;
			temp->next = index.curr;
			index.curr = temp;
		}
		nSize++;
	}
	//
}

/////////////////////////////////////////////////////////////////////////////
// Function : remove
// Parameters :	index - an iterator to the location to remove from
// Notes : do nothing on a bad iterator
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void SLList<Type>::remove(SLLIter<Type>& index)
{
	if (index.curr != nullptr)
	{
		if(index.curr == Head)
		{
			index.prev = Head;
			index.curr = Head->next;
			delete Head;
			index.prev = nullptr;
			Head = index.curr;
		}
		else
		{
			index.curr = index.curr->next;
			delete index.prev->next;
			index.prev->next = index.curr;  
		}
		nSize--;
	}
}

#pragma endregion

#pragma region SLLIter

/////////////////////////////////////////////////////////////////////////////
// Function : Constructor
// Parameters :	listToIterate - the list to iterate
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
SLLIter<Type>::SLLIter(SLList<Type>& listToIterate)
{
	iter = &listToIterate;
	prev = nullptr;
	curr = nullptr;
}

template<typename Type>
SLLIter<Type>::SLLIter(const SLList<Type>& listToIterate)
{
	iter = &(const_cast<SLList<Type>&>(listToIterate));
	prev = nullptr;
	curr = nullptr;
}

/////////////////////////////////////////////////////////////////////////////
// Function : begin
// Notes : moves the iterator to the head of the list
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void SLLIter<Type>::begin()
{
	prev = nullptr;
	curr = iter->Head;
}

/////////////////////////////////////////////////////////////////////////////
// Function : end
// Notes : returns true if we are at the end of the list, false otherwise
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
bool SLLIter<Type>::end() const
{
	if(curr == nullptr)
		return true;
	return false;

}

/////////////////////////////////////////////////////////////////////////////
// Function : operator++
// Notes : move the iterator forward one node
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
SLLIter<Type>& SLLIter<Type>::operator++()
{
	if (curr != nullptr)
	{
		prev = curr;
		curr = curr->next; 
	}
	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// Function : current
// Notes : returns the item at the current iterator location
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
Type& SLLIter<Type>::current() const
{
	return curr->Data;
}

#pragma endregion