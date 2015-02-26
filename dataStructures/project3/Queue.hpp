#ifndef QUEUE_HPP_
#define QUEUE_HPP_

/*
 * The following is the Queue implementation.
 */


// zero parameter constructor
template <typename T, class Container>
Queue<T, Container>::Queue() :
	c{}
{
}

// copy constructor
template <typename T, class Container>
Queue<T, Container>::Queue(const Queue<T, Container> &rhs) :
	c{rhs.c}
{
}

// move constructor
template <typename T, class Container>
Queue<T, Container>::Queue(Queue<T, Container> &&rhs) :
	c{std::move(rhs.c)}
{
}

// destructor
template <typename T, class Container>
Queue<T, Container>::~Queue()
{
	delete c;
}

// copy assignment
template <typename T, class Container>
Queue<T, Container>& Queue<T, Container>::operator=(const Queue<T, Container> &rhs)
{
	Queue<T, Container> copy = rhs;
	std::swap(*this, copy);
	return *this;
}

// move assignment
template <typename T, class Container>
Queue<T, Container>& Queue<T, Container>::operator=(Queue<T, Container> &&rhs)
{
	std::swap(c, rhs.c);
}

// back, returns the last element of the queue
template <typename T, class Container>
T& Queue<T, Container>::back()
{
	return c.back();
}

// back, returns the last element of the queue, constant version
template <typename T, class Container>
const T& Queue<T, Container>::back() const
{
	return c.back();
}

// front, returns the first element of the queue
template <typename T, class Container>
T& Queue<T, Container>::front()
{
	return c.front();
}

// front, returns the first element of the queue, constant version
template <typename T, class Container>
const T& Queue<T, Container>::front() const
{
	return c.front();
}

// pop, execute the adaptee version of pop_front which should discard the first element
template <typename T, class Container>
void Queue<T, Container>::pop()
{
	c.pop_front();
}

// push, executes the adaptee version of push_back which should add the value to the back
template <typename T, class Container>
void Queue<T, Container>::push(const T& val)
{
	c.push_back(val);
}

// push, the move version
template <typename T, class Container>
void Queue<T, Container>::push(T&& val)
{
	c.push_back(val); // This implementation is relying on the adoptee class to have a move version
}

template <typename T, class Container>
int Queue<T, Container>::size()
{
	return c.size();
}

#endif
