/*
 * My tests for the Queue implementation
 */

#include "Queue.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace cop4530;


void print_success(std::string msg) {
	std::cout << "SUCCESS: " << msg << std::endl;
}

void print_failed(std::string msg) {
	std::cout << "FAILED: " << msg << std::endl;
}

int main() {
	std::cout << "Begin testing" << std::endl;
	/*
	 * First we will test out ints
	 */
	Queue<int> myQ {};
	int myInt = 4;

	// test if the front element is equal to the back for one element
	myQ.push(myInt);
	if (myQ.front() == myQ.back()) {
		print_success("The front the same as the back for one element queue!");
	} else {
		print_failed("The front did NOT equal the back for a one element queue, uh oh.");
	}

	// test if successive pushes work
	for (int i = 0; i < 100; ++i) {
		myQ.push(i);
	}
	// the size should be 101
	if (myQ.size() == 101) {
		print_success("The size is 101, yay!");
	} else {
		print_failed("The size was not 101, you done messed up!");
	}
	
	// Test if front and back are working correctly
	if (myQ.front() == 4) {
		print_success("The front is 4, good.");
	} else {
		print_failed("The front is not 4, bad.");
	}
	if (myQ.back() == 99) {
		print_success("The back is 99, good.");
	} else {
		print_failed("The back is not 99, bad");
	}

	// Test the assignment operators and the pop function
	Queue<int> otherQ = myQ;
	if (otherQ.front() == 4) {
		print_success("The front is 4, awesome.");
	} else {
		print_failed("The front isn't 4.");
	}
	otherQ.pop(); // pop the four in the front
	for (int i = 0; i < 100; ++i) {
		if (otherQ.front() != i) {
			print_failed("The front isn't right for value: ");
			std::cout << i << std::endl;
			break;
		}
		otherQ.pop();
	}
	if (otherQ.size() == 0) {
		print_success("The size is 0, good job.");
	} else {
		print_failed("The size wasn't 0, something happened.");
	}

	// Performance testing
	int sizes[] {10, 100, 1000, 10000, 100000, 1000000};
	Queue<int> testQ {};
	for (int size : sizes) {
		for (int i = 0; i < size; ++i) {
			testQ.push(i);
		}

		std::clock_t start = std::clock();
		for (int i = 0; i < size; ++i) {
			testQ.pop();
		}
		std::clock_t stop = std::clock();

		std::cout << "For size, " << size << ", the execution time of popping that many elements is " << stop - start << "ms." << std::endl;
	}


	return 0;
}
