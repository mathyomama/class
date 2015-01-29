#include "SortedBGPTable.h"

 SortedBGPTable::SortedBGPTable(std::string key, std::vector<std::string> value) : table{key, value} {
}

SortedBGPTable::BGPTable SortedBGPTable::insert_neighbors(std::string neighbor_str, char delim) {
	return table;
}

SortedBGPTable::BGPTable SortedBGPTable::insert_neighbor(std::vector<std::string> neighbor_arr) {
	return table;
}
