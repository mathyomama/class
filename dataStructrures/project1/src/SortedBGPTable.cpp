#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "SortedBGPTable.h"

SortedBGPTable::SortedBGPTable() {
}

SortedBGPTable::neighbors & SortedBGPTable::operator[](int key) {
	return table[key];
}

const SortedBGPTable::BGPTable & SortedBGPTable::insert_neighbor(std::vector<int> & neighbor_arr) {
	// The incoming array should hold parsed values from the BGP input string, neighboring identical numbers and brackets should have been removed
	int len = neighbor_arr.size();
	int value1, value2, value3;
	for (int i = 1; i < len; i += 2) { //Set up to iterate over every other element
		value1 = neighbor_arr[i - 1], value2 = neighbor_arr[i];
		table[value1][value2]++;
		table[value2][value1]++;
		// If the current index isn't the last one then we can add the next values to the table as well
		if (i != len - 1) {
			value3 = neighbor_arr[i + 1];
			table[value1][value3]++;
			table[value2][value3]++;
			table[value3][value1]++;
			table[value3][value2]++;
		}
	}
	return table;
}

std::vector<int> SortedBGPTable::parse_BGP_input(const std::string & neighbor_str) {
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
