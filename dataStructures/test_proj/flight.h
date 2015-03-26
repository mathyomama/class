#ifndef FLIGHT_H_
#define FLIGHT_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

class Flight {
	public:
		typedef std::string dest; // a destination
		typedef int cost; // the cost is an unsigned integer
		typedef std::unordered_map<dest, cost> destCost; // destination cost pairing
		typedef std::unordered_map<int, dest> orderingTable; // mapping between the position on the table and the destination name, a vector could be used with the indices as the positions, but this feels safer
		typedef std::unordered_map<dest, destCost> flightTable; // The whole flight table
		typedef struct route { // route data which is used in the route finding algorithm
			std::vector<std::string> destinations; // array of destinations with the start being at position 0 and the end being in the last position
			cost totalCost; // cost of trip
		} route;

		// Constructors
		Flight();
		Flight(std::string inputFile); // constructor with input file

		// Member variables
		void add_table(std::string inputFile); // a table is constructed from an input file
		route find_min_hop_route(dest beginning, dest end); // function for finding the route with the smallest amount of layovers
		dest get_city_by_value(int i); // return the city given the integer which refers to it
		int get_size(); // get the size or the number of cities or nodes
		destCost get_directFlights(dest city); // get the direct flight costs mapping
		bool city_in_table(dest city); // determine if the city is in the flight table

	private:
		flightTable table;
		orderingTable positions;
		int size;
};


#endif
