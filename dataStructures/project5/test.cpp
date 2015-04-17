/*
 * Test program for hashtable.h
 * Author: Michael Duckett
 */

#include <iostream>
#include <cstdarg>
#include "hashtable.h"
#include <ctime>


using namespace cop4530;
using namespace std;


void run_test(bool (*test)(), std::string test_name) {
	std::cout << "Running test: " << test_name << std::endl;
	if (!test()) {
		std::cout << test_name << " FAILED" << std::endl;
	} else {
		std::cout << test_name << " SUCCESSFUL" << std::endl;
	}
	std::cout << std::endl;
}

void print_fail(const std::string &fmt, ...) {
	va_list args;
	va_start(args, fmt);
	std::cout << "\t[FAILED] ";
	vprintf(fmt.c_str(), args);
	std::cout << std::endl;
	va_end(args);
}

void test_intro(std::string intro) {
	std::cout << "\tTesting " << intro << "..." << std::endl;
}

// A test which uses integers as keys
bool test_int() {
	// create a hashtable of default size
	test_intro("initializaiton and insertion");
	HashTable<int> intHash{};
	bool check_insert = true;
	for (int i = 0; i < 101; ++i) {
		if (!intHash.insert(i)) {
			print_fail("Insert: could not insert %d.", i);
			check_insert = false;
		}
	}
	if (intHash.size() != 101) {
		print_fail("Insert: The size is not correct.");
		check_insert = false;
	}

	// check contains
	bool check_contains = true;
	for (int i = 0; i < 101; ++i) {
		if (!intHash.contains(i)) {
			print_fail("Contains: hashtable does not contain %d.", i);
			check_insert = false;
		}
	}

	// check remove
	test_intro("remove");
	bool check_remove = true;
	for (int i = 0; i < 51; ++i) {
		intHash.remove(i);
		if (intHash.contains(i)) {
			print_fail("Remove: contains %d.", i);
			check_remove = false;
		}
	}
	if (intHash.size() != 50) {
		print_fail("Remove: the size is not correct.");
		check_remove = false;
	}

	// check clear
	test_intro("clear");
	bool check_clear = true;
	intHash.clear();
	if (intHash.size() != 0) {
		intHash.dump();
		print_fail("Clear: the size is not correct.");
		check_clear = false;
	}

	return check_insert && check_contains && check_remove && check_clear;
}

// Test which uses strings as keys, tests the load and write functions as well.
bool test_string() {
	// check insert
	HashTable<std::string> strHash{10}; // create a hashtable of size 10, initially
	test_intro("insert");
	bool check_insert = true;
	std::string test_str{"astronaut"};
	if (!strHash.insert(test_str)) {
		print_fail("Insert: could not insert '%s' into hashtable.", test_str.c_str());
		check_insert = false;
	}
	if (strHash.insert(test_str)){
		print_fail("Insert: inserted '%s' when already in string.", test_str.c_str());
		check_insert = false;
	}
	if (strHash.size() != 1) {
		print_fail("Insert: size is not 1.");
		check_insert = false;
	}

	// check remove
	test_intro("remove");
	bool check_remove = true;
	if (!strHash.remove(test_str)) {
		print_fail("Remove: could not remove '%s' from hashtable.", test_str.c_str());
		check_remove = false;
	}
	
	// check load
	test_intro("load");
	bool check_load = true;
	char input[20] = "test.input";
	if (!strHash.load(input)) {
		print_fail("Load: could not load from '%s' correctly.", input);
		check_load = false;
	}

	// check write_to_file
	test_intro("write_to_file");
	bool check_write = true;
	char output[20] = "test.output";
	if (!strHash.write_to_file("test.output")) {
		print_fail("Write_to_file: could not write to '%s' correctly.", output);
		check_write = false;
	}

	// examine dump
	std::cout << "\tdumping for examination..." << std::endl;
	strHash.dump();

	// check clear
	test_intro("clear");
	bool check_clear = true;
	strHash.clear();
	if (strHash.size() != 0) {
		print_fail("Clear: could not clear hashtable.");
		check_clear = false;
	}

	return check_insert && check_remove && check_load && check_write && check_clear;
}

bool test_big_load() {
	// test size and time of program
	test_intro("big hashtable time");
	bool check_big = true;
	HashTable<int> big_hash{1000100};
	for (int limit = 10; limit < 10000000; limit *= 10) {
		std::cout << "\ttesting " << limit << " values:" << std::endl;
		// insertion
		clock_t start = clock();
		for (int j = 0; j < limit; ++j) {
			if (!big_hash.insert(j)) {
				print_fail("Big Test: could not insert %d into large hashtable.", j);
				check_big = false;
				break;
			}
		}
		std::cout << "\tinsertion:" << (float)(clock() - start)/CLOCKS_PER_SEC << "s" << std::endl;

		// traversal
		start = clock();
		for (int j = 0; j < limit; ++j) {
			if (!big_hash.contains(j)) {
				print_fail("Big Test: could not find %d in large hashtable." , j);
				check_big = false;
				break;
			}
		}
		std::cout << "\ttraversal:" << (float)(clock() - start)/CLOCKS_PER_SEC << "s" << std::endl;

		// removal
		start = clock();
		for (int j = 0; j < limit; ++j) {
			if (!big_hash.remove(j)) {
				print_fail("Big Test: could not remove %d in large hashtable." , j);
				check_big = false;
				break;
			}
		}
		std::cout << "\tremoval:" << (float)(clock() - start)/CLOCKS_PER_SEC << "s" << std::endl;
	}

	return check_big;
}

int main(int argc, char *argv[]) {
	run_test(&test_int, "TEST_INT");
	run_test(&test_string, "TEST_STRING");
	run_test(&test_big_load, "TEST_BIG_LOAD");

	return 0;
}
