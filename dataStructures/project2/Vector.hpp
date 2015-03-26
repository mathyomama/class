#ifndef VECTOR_HPP_
#define VECTOR_HPP_

// zero parameter constructor
template <typename T>
Vector<T>::Vector() :
	theCapacity{0}, theSize{0}, array{nullptr}
{
}

// copy constructor
template <typename T>
Vector<T>::Vector(const Vector &rhs) :
	theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, array{nullptr}
{
	array = new T[theCapacity];
	for (int i = 0; i < theSize; ++i) {
		array[i] = rhs.array[i];
	}
}

// move constructor
template <typename T>
Vector<T>::Vector(Vector &&rhs) :
	theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, array{rhs.array}
{
	rhs.array = nullptr;
	rhs.theCapacity = 0;
	rhs.theSize = 0;
}

// constructor given number of elements and the value with which each element will be instantiated
template <typename T>
Vector<T>::Vector(int num, const T& val) :
	theCapacity{num}, theSize{num}, array{nullptr}
{
	array = new T[theCapacity];
	for (int i = 0; i < theSize; ++i) {
		array[i] = val;
	}
}

// constructor from range of iterators, start and end
template <typename T>
Vector<T>::Vector(Vector<T>::const_iterator start, Vector<T>::const_iterator end) :
	array{nullptr}
{
	// start and end are pointers, so the size can be deduced by substracting start from end and dividing by 4
	theSize = end - start;
	// It wasn't specified what the starting capacity should be, so it will follow suit like the constructor right above and have the same value as "theSize"
	theCapacity = theSize;
	array = new T[theCapacity];
	int i = 0;
	for (auto itr = start; itr != end; ++itr, ++i) {
		array[i] = *itr;
	}
}

// Destructor
template <typename T>
Vector<T>::~Vector()
{
	delete [] array;
}

// return value at specified index
template <typename T>
T& Vector<T>::operator[](int index)
{
	return array[index];
}

// return constant value and not change anything class members
template <typename T>
const T& Vector<T>::operator[](int index) const
{
	return array[index];
}

// copy assignment
template <typename T>
const Vector<T>& Vector<T>::operator=(const Vector<T> &rhs)
{
	Vector<T> copy = rhs;
	std::swap(*this, copy);
	return *this;
}

// Move Assignemnt
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> &&rhs)
{
	std::swap(theSize, rhs.theSize);
	std::swap(theCapacity, rhs.theCapacity);
	std::swap(array, rhs.array);

	return *this;
}

// at, similar to operator[]
template <typename T>
T& Vector<T>::at(int loc)
{
	if (loc >= theSize || loc < 0) {
		throw std::out_of_range("The index you gave is not in the vector's range");
	}
	return array[loc];
}

// at, similar to operator[] const
template <typename T>
const T& Vector<T>::at(int loc) const
{
	if (loc >= theSize || loc < 0) {
		throw std::out_of_range("The index you gave is not in the vector's range");
	}
	return array[loc];
}

// front, returns a reference to the first element
template <typename T>
T& Vector<T>::front()
{
	return array[0];
}

// front, returns a const reference to the first element
template <typename T>
const T& Vector<T>::front() const
{
	return array[0];
}

// back, returns a reference to the last element
template <typename T>
const T& Vector<T>::back() const
{
	return array[theSize - 1];
}

// back, returns a const refernce to the last element
template <typename T>
T& Vector<T>::back()
{
	return array[theSize - 1];
}

// size, return the size of the container, theSize
template <typename T>
int Vector<T>::size() const
{
	return theSize;
}

// capacity, return the capacity of the current container, theCapacity
template <typename T>
int Vector<T>::capacity() const
{
	return theCapacity;
}

// empty, returns true if the container is empty, else false
template <typename T>
bool Vector<T>::empty() const
{
	return theSize == 0;
}

// clear, sets the size of the container to 0, effectively clearing the container of all values
// memory doesn't need to be reclaimed
template <typename T>
void Vector<T>::clear()
{
	theSize = 0;
}

// push_back, insert an object as the last element of the container
template <typename T>
void Vector<T>::push_back(const T& val)
{
	// first need to check if the size will be larger than the capacity
	if (theSize == theCapacity) {
		doubleCapacity();
	}
	array[theSize++] = val;
}

// pop_back, shrink the container by removing the last element
template <typename T>
void Vector<T>::pop_back()
{
	--theSize;
}

// resize, shrink or expand the size of the container and insert the given value at the end if it's an expansion
template <typename T>
void Vector<T>::resize(int num, T val)
{
	// num is the new size and val is the possible value to insert at the end
	if (num > theSize) {
		if (num > theCapacity) {
			reserve(2*num); // increase the capacity to double the size
		}
		for (int i = theSize; i < num; ++i) {
			array[i] = val;
		}
	}
	theSize = num;
}

template <typename T>
void Vector<T>::reserve(int size)
{
	if (size <= theSize) { // if the given value is smaller than the current size, do nothing
		return;
	}
	T* newArray = new T[size];

	for (int i = 0; i < theSize; ++i) {
		newArray[i] = std::move(array[i]); // make elements in array Rvalue so they can be transfered efficiently
	}

	theCapacity = size;
	std::swap(array, newArray); // swap so that array is now the newly constructed array
	delete [] newArray; // get rid of newArray
}


// print, takes reference to ostream type and delimiter as arguments and loops through array, printing each element
template <typename T>
void Vector<T>::print(std::ostream& os, char ofc) const
{
	if (theSize > 0) {
		os << array[0];
		for (int i = 1; i < theSize; i++) {
			os << ofc << array[i];
		}
	}
}

// begin, return an iterator to the first element
template <typename T>
typename Vector<T>::iterator Vector<T>::begin()
{
	return array;
}

// begin, return a const_iterator to the first element
template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const
{
	return array;
}

// end, return an iterator to the end marker, which is after the last element
template <typename T>
typename Vector<T>::iterator Vector<T>::end()
{
	return array + theSize;
}

// end, return const_iterator to the end marker
template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const
{
	return array + theSize;
}

// insert, put an element of type T in given position and push back all the elements after it by one
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(Vector<T>::iterator itr, const T& val)
{
	if (theSize == theCapacity) {
		doubleCapacity();
	}
	for (auto index = end(); index != itr; --index) {
		*index = std::move(*(index - 1));
	}
	*itr = val;
	++theSize;
	return itr;
}

// erase, delete element at the spot of the given iterator and return
template <typename T>
typename Vector<T>::iterator Vector<T>::erase(Vector<T>::iterator itr)
{
	T oldVal = *itr;
	for (auto index = itr; index != end() - 1; ++index) {
		*index = std::move(*(index + 1));
	}
	--theSize;
	return oldVal;
	/*
	 * This part confused me, I am not sure if the method is suppose to return the iterator behind the 
	 * erased one before the shift in values or after the shift in values. This implementation returns
	 * the iterator itself which is the address to the value which was after the removed value
	 */
}

// erase, delete the elements in the range of the start and end iterator, not including the end
template <typename T>
typename Vector<T>::iterator Vector<T>::erase(Vector<T>::iterator start, Vector<T>::iterator end)
{
	for (auto index = start, transfer = end; transfer != this->end(); ++index, ++transfer)
	{
		*index = std::move(*transfer);
	}
	theSize -= end - start;
}

// doubleCapacity, doubles the capacity of the array
template <typename T>
void Vector<T>::doubleCapacity()
{
	if (theCapacity > 0) {
		int newCapacity = 2*theCapacity;
		T* newArray = new T[newCapacity];

		for (int i = 0; i < theSize; ++i) {
			newArray[i] = std::move(array[i]); // make elements in array Rvalue so they can be transfered efficiently
		}

		theCapacity = newCapacity;
		std::swap(array, newArray); // swap so that array is now the newly constructed array
		delete [] newArray; // get rid of newArray
	} else {
		T* newArray = new T[1];
		theCapacity = 1;
		std::swap(array, newArray);
		delete [] newArray;
	}
}

template <typename T>
bool operator==(const Vector<T> & lhs, const Vector<T> & rhs)
{
	if (lhs.size() == rhs.size()) {
		for (int i = 0; i < rhs.size(); ++i) {
			if (lhs[i] != rhs[i]) {
				return false;
			}
		}
	} else {
		return false;
	}
	return true;
}

template <typename T>
bool operator!=(const Vector<T> & lhs, const Vector<T> & rhs)
{
	return !(lhs == rhs);
}

template <typename T>
std::ostream & operator<<(std::ostream &os, const Vector<T> &v)
{
	v.print(os);
	return os;
}


#endif
