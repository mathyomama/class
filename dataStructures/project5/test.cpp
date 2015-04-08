/*
 * Test program for hashtable.h
 * Author: Michael Duckett
 */

#include <iostream>
#include "hashtable.h"


using namespace cop4530;
using namespace std;

// A test which uses integers as keys
bool test_int() {
	// create a hashtable of default size
	HashTable intHash{};
	for (int i = 0; i < 101; ++i) {
		intHash.insert(i);
	}
	bool check_size;
	if (intHash.size() != 101) {
		std::cout << "The size is not correct" << std::endl;
	}
}

bool test_string() {
}

bool test_file() {
}

int main(int argc, char *argv[]) {

	return 0;
}
