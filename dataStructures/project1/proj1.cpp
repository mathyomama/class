#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <set>
#include <utility>
#include <list>
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
	// First part parses the input and passes it to the SortedBGPTable data structure
	std::string line;
	std::vector<int> arr;
	SortedBGPTable proj_table;
	while (std::getline(std::cin, line)) {
		arr = SortedBGPTable::parse_BGP_input(line);
		proj_table.insert_neighbor(arr);
	}

	// This creates a list of sorted AS's
	std::list<SortedBGPTable::ASPair> proj_sorted_list{proj_table.sorted_table()};

	// This outputs the desired information to stdout or cout
	for (auto x : proj_sorted_list) {
		std::cout << x.first << " " << x.second.size() << " ";
		auto i = x.second.begin();
		std::cout << *i;
		for (++i; i != x.second.end(); i++) {
			std::cout << "|" << *i;
		}
		std::cout << std::endl;
	}
	
	return 0;
}
