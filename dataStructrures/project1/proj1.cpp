#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <regex>


class SortedBGPTable {
	public:
		explicit SortedBGPTable();

	private:
		std::unordered_map<std::vector<std::string>> table;
}

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

std::vector<string> &split_neighbors(const std::string &str, char delim, std::vector<std::string> &arr) {
	std::stringstream iss (str);
	std::string elem, last;
	last = "0";
	while (getline(iss, elem, delim)) {
		getline(iss, elem, delim);
		if () {
			arr.push_back(elem);
		}
	}
}

int main() {
	std::string line;
	while (std::getline(std::cin, line)) {
		std::vector<std::string> arr = split_line(line, '|');
		arr = split(arr.back(), ' ');
		std::cout << arr.back() << std::endl;
	}
	/*unordered_map<int, vector<int>> routing_set;
	
	vector<int> neighbors {496, 2001, 9001};
	pair<int, vector<int>> key_value {23, neighbors};
	routing_set.insert(key_value);

	for (auto& x: routing_set) {
		cout << x.first << ": " << x.second << endl;
	}*/

	return 0;
}
