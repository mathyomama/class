#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include "SortedBGPTable.h"


/*
 * This will split the given string a certain number of times if given a count greater than zero or until the
 * string has been exhausted
 */
std::vector<std::string> &split_line(const std::string &str, char delim, std::vector<std::string> &arr) {
	std::stringstream iss(str);
	std::string elem;
	for (unsigned int i = 0; i < 7; i++){
		std::getline(iss, elem, delim);
		arr.push_back(elem);
	}
	return arr;
}

std::vector<std::string> split_line(const std::string &str, char delim) {
	std::vector<std::string> arr;
	split_line(str, delim, arr);
	return arr;
}

int main() {
	std::string line;
	std::vector<int> arr;
	SortedBGPTable proj_table;
	while (std::getline(std::cin, line)) {
		arr = SortedBGPTable::parse_BGP_input(line);
		proj_table.insert_neighbor(arr);
	}

	SortedBGPTable::neighbors small_array = proj_table[701];
	for (auto x : small_array) {
		std::cout << x.first << " " <<  x.second << std::endl;
	}
	
	return 0;
}
