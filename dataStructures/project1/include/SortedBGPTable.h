#ifndef SortedBGPTable_H
#define SortedBGPTable_H

#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <utility>
#include <list>

/*
 * This is the class for holding the sorted table.
 */

class SortedBGPTable {
	public:
		//type definitions to make the code more concise
		typedef std::set<int> neighbors; // set of ordered neighboring AS
		typedef std::pair<int, neighbors> ASPair; // AS node number paired with the set of neighbors
		typedef std::unordered_map<int, neighbors> BGPTable; // The unordered map of ASPairs

		//Constructor
		explicit SortedBGPTable();

		neighbors & operator[](int key);
		const SortedBGPTable::BGPTable & insert_neighbor(std::vector<int> & neighbor_arr);
		std::list<ASPair> sorted_table();
		static std::vector<int> parse_BGP_input(const std::string & neighbor_str);

	private:
		BGPTable table;
		static bool comparator(const ASPair & a, const ASPair & b);
};


#endif
