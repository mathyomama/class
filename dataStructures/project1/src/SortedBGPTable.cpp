#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <utility>
#include <list>
#include "SortedBGPTable.h"

SortedBGPTable::SortedBGPTable() {
}

SortedBGPTable::neighbors & SortedBGPTable::operator[](int key) {
	return table[key];
}

const SortedBGPTable::BGPTable & SortedBGPTable::insert_neighbor(std::vector<int> & neighbor_arr) {
	// The incoming array should hold parsed values from the BGP input string, neighboring identical numbers and brackets should have been removed
	int len = neighbor_arr.size();
	int value1, value2; //value3;
	for (int i = 0; i < len - 1; i++) {// Each neighboring AS is inserted into its neighbors set
		value1 = neighbor_arr[i], value2 = neighbor_arr[i + 1];
		table[value1].insert(value2);
		table[value2].insert(value1);
	}
	return table;
}

std::list<SortedBGPTable::ASPair> SortedBGPTable::sorted_table() {
	// This creates a list of sorted ASPairs using the compare function from the class
	std::list<SortedBGPTable::ASPair> BGPList(std::begin(table), std::end(table));
	BGPList.sort(SortedBGPTable::comparator);
	return BGPList;
}

std::vector<int> SortedBGPTable::parse_BGP_input(const std::string & neighbor_str) {
	// This function takes an AS string and output a vector of AS which are neighbors. It filters out duplicates and AS in brackets
	std::vector<int> neighbor_arr;
	std::stringstream iss(neighbor_str);
	std::string values;
	for (int i = 0; i < 7 && getline(iss, values, '|'); i++) {} // This will set values to the 7th delimited value

	std::string prev, value;
	iss.str(values);
	getline(iss, value, ' ');
	neighbor_arr.push_back(std::stoi(value));
	prev = value;
	while (getline(iss, value, ' ')) {
		if (value[0] == '[') break; // This stops the loop when we find '[' as the first character
		if (value != prev) { // This doesn't add neighbors with the same value
			neighbor_arr.push_back(std::stoi(value));
		}
		prev = value;
	}
	return neighbor_arr;
}

bool SortedBGPTable::comparator(const SortedBGPTable::ASPair & a, const SortedBGPTable::ASPair & b) {
	// compare function which takes two ASPair types and returns true if a should come first and false if b should come first
	size_t a_size = a.second.size(), b_size = b.second.size();
	int a_key = a.first, b_key = b.first;
	if (a_size > b_size) {
		return true;// this makes the larger ASPair in size come first
	} else if (a_size < b_size) {
		return false;
	} else {
		if (a_key > b_key) {
			return false;// This makes same size ASPairs order in ascending AS key value
		} else if (a_key < b_key) {
			return true;
		} else {
			return false;
		}
	}
}
