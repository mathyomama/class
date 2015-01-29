#ifndef SortedBGPTable_H
#define SortedBGPTable_H

#include <unordered_map>
#include <string>
#include <vector>

/*
 * This is the class for holding the sorted table.
 */

class SortedBGPTable {
	public:
		//type definition to make the code more concise
		typedef std::unordered_map<std::string, std::vector<std::string>> BGPTable;

		//Constructor
		explicit SortedBGPTable(std::string& key, std::vector<std::string>& value);

		SortedBGPTable::BGPTable insert_neighbor(std::string neighbor_str, char delim);
		SortedBGPTable::BGPTable insert_neighbor(std::vector<std::string> neighbor_arr);

	private:
		SortedBGPTable::BGPTable table;
};


#endif
