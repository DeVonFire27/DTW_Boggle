#pragma once
template <typename Type>
class DynArray
{

private:
	unsigned int Acap;
	Type * arr;
	unsigned int Asize;

public:
	DynArray();
	~DynArray();
	DynArray(const DynArray<Type>& that);
	DynArray<Type>& operator=(const DynArray<Type>& that);
	Type& operator[](const unsigned int index);
	const Type& operator[](const unsigned int index) const;
	unsigned int size() const;
	unsigned int capacity() const;
	void clear();
	void append(const Type& item);
	void reserve(const unsigned int & newCap = 0);
	void SetSize(int increment);

};

/////////////////////////////////////////////////////////////////////////////
// Function :	Constructor
// Notes : Constructs an empty array (Size 0 Capacity 0)
/////////////////////////////////////////////////////////////////////////////
template <typename Type>	
DynArray<Type>::DynArray()
{

	Asize = 0;
	Acap = 0;
	arr = new Type [Acap];
}

/////////////////////////////////////////////////////////////////////////////
// Function :	Destructor
// Notes : cleans up any dynamic memory
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
DynArray<Type>::~DynArray()
{
	delete [] arr;
	arr = nullptr;
}

/////////////////////////////////////////////////////////////////////////////
// Function :	Copy Constructor
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
DynArray<Type>::DynArray(const DynArray<Type>& that)
{
	arr = nullptr;
	*this = that;
}

/////////////////////////////////////////////////////////////////////////////
// Function :	Assignment Operator
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
DynArray<Type>& DynArray<Type>::operator=(const DynArray<Type>& that)
{
	if(this != &that)
	{
		delete [] arr;
		arr = new Type[that.capacity()];
		for(unsigned int x = 0; x < that.size(); x++)
			this->arr[x] = that[x];
		this->Asize = that.size();
		this->Acap = that.capacity();
	}

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// Function : operator[]
// Parameters : index - the index to access
// Return : Type & - returns the array element at [index]
// Notes : performs no error checking. user should ensure index is 
//		valid with the size() method
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
Type& DynArray<Type>::operator[](const unsigned int index)
{
	return arr[index];
}

/////////////////////////////////////////////////////////////////////////////
// Function : operator[]
// Parameters : index - the index to access
// Return : const Type & - returns the array element at [index]
// Notes : performs no error checking. user should ensure index is 
//		valid with the size() method
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
const Type& DynArray<Type>::operator[](const unsigned int index) const
{
	return arr[index];
}

/////////////////////////////////////////////////////////////////////////////
// Function :	size
// Returns : int - returns the number of items being stored
// Notes : this function returns the number of items being stored, 
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
unsigned int DynArray<Type>::size() const 
{
	return Asize;
}

/////////////////////////////////////////////////////////////////////////////
// Function : capacity
// Returns : int - returns the number of items the array can store before 
//		the next resize
// Notes : this function returns the number of items the array can store, 
//		not the number of bytes
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
unsigned int DynArray<Type>::capacity() const
{
	return Acap;
}

/////////////////////////////////////////////////////////////////////////////
// Function :	clear
// Notes : cleans up any dynamic memory and resets size and capacity to 0
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
void DynArray<Type>::clear()
{

	delete [] arr;
	arr = nullptr;
	Asize = 0;
	Acap = 0;
}

/////////////////////////////////////////////////////////////////////////////
// Function : append
// Parameters : item - the item to be appended to the next open spot
// Notes : this function will append the item to the next open spot. if 
//		no room exists, the array's capacity will be doubled and then 
//		the item will be added
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
void DynArray<Type>::append(const Type& item)
{
	if(Asize == Acap)
	{
		if(Acap == 0)
			Acap = 1;
		else
			Acap *= 2;

		Type *temp = new Type[Acap];
		for(unsigned int x = 0; x < Asize; x++)
			temp[x] = arr[x];
		delete [] arr;
		arr = temp;
	}

	arr[Asize] = item;
	Asize+=1;
}

/////////////////////////////////////////////////////////////////////////////
// Function : reserve
// Parameters : newCap - the new capacity
// Notes : 	- default parameter - reserve more space in the array, based on //		the expansion rate (100%, 1 minimum).
//		- non-default parameter, expand to the specified capacity
//		- if newCap is LESS than the current capacity, do nothing. 
//		This function should NOT make the array smaller.
/////////////////////////////////////////////////////////////////////////////
template <typename Type>
void DynArray<Type>::reserve(const unsigned int & newCap = 0)
{
	if(newCap == 0)
	{
		if(Acap == 0)
			Acap = 1;
		else
			Acap *= 2;
	}
	else if(newCap > Acap)
		Acap = newCap;

	Type *temp = new Type[Acap];
	for(unsigned int x = 0; x < Asize; x++)
		temp[x] = arr[x];
	delete [] arr;
	arr = temp;

}

template <typename Type>
void DynArray<Type>::SetSize(int increment)
{
	Asize += increment;
}
