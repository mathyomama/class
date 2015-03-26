#ifndef QUEUE_H_
#define QUEUE_H_

/*
 * This is the Queue header file for the project 3 of COP4530. The Queue class
 * will be implemented by adapting a container class via composition. The default
 * container will be the deque. The following will define the class and member 
 * functions and adaptee container.
 */

#include <iostream>
#include <deque>


namespace cop4530 {

	template <typename T, typename Container = std::deque<T>>
	class Queue {
		public:
			// Constructors
			Queue();
			Queue(const Queue &rhs); // copy constructor
			Queue(Queue &&rhs); // move constructor

			// Destructor
			~Queue();

			// Assignment
			Queue& operator=(const Queue &rhs); // copy assignment
			Queue& operator=(Queue &&rhs); // move assignment

			// public member functions
			T& back(); // return the last element in the queue
			const T& back() const; // constant version of the above function
			bool empty() const; // return true if the queue is empty; false otherwise
			T& front(); // return the first element in the queue
			const T& front() const; // the constant version of the above function
			void pop(); // remove the first element in the queue and discard it
			void push(const T& val); // add an element to the back of the queue
			void push(T&& val); // the move version of the above function
			int size();

		protected:
			// The adaptee class in the form of an object
			Container c;
	};

	// Inclusion of the implementation file
#include "Queue.hpp"

} // This ends namespace cop4350

#endif
