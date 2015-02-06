#ifndef SortedBGPTable_H
#define SortedBGPTable_H

#include <map>
#include <unordered_map>
#include <string>
#include <vector>

/*
 * This is the class for holding the sorted table.
 */

class SortedBGPTable {
	public:
		//type definition to make the code more concise
		typedef std::map<int, int> neighbors;
		typedef std::unordered_map<int, neighbors> BGPTable;

		//Constructor
		explicit SortedBGPTable();

		neighbors & operator[](int key);
		const SortedBGPTable::BGPTable & insert_neighbor(std::vector<int> & neighbor_arr);
		static std::vector<int> parse_BGP_input(const std::string & neighbor_str);

	private:
		BGPTable table;
};


#endif
