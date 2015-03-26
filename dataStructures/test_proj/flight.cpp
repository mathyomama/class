#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include "flight.h"
#include "Queue.h"


// zero parameter constructor
Flight::Flight() :
	table{}, positions{}, size{0}
{
}

// constructor from input file
Flight::Flight(std::string inputFile) :
	table{}, positions{}, size{}
{
	add_table(inputFile);
}

// add table function, should only be when the object has no entries
void Flight::add_table(std::string inputFile)
{
	// Check if the flight table has already been made. Don't make one if there are entries
	if (size > 0) {
		std::cout << "The following flight table is already filled, sorry." << std::endl;
		return;
	}

	std::ifstream ifs{inputFile};
	std::string line;
	std::getline(ifs, line);
	size = std::stoi(line);
	
	// first put the destinations into the orderingTable
	Flight::dest destination {};
	for (int i = 0; i < size; ++i) {
		std::getline(ifs, destination);
		positions.insert({i, destination});
	}

	// next put the costs into the flightTable
	for (int i = 0; i < size; ++i) {
		Flight::destCost destinationCostPairs {};
		std::getline(ifs, line);
		std::istringstream iss{line};
		for (int j = 0; j < size; ++j) {
			std::string strval;
			iss >> strval;
			Flight::cost value = std::stoi(strval);
			destinationCostPairs.insert({positions[j], value});
		}
		table.insert({positions[i], destinationCostPairs});
	}
}

// function to determine what the shortest route is based on hops/layover count
Flight::route Flight::find_min_hop_route(dest beginning, dest end)
{
	Flight::route shortestRoute; // The final answer
	cop4530::Queue<Flight::route> flightQ {}; // The queue to be used
	std::set<Flight::dest> visited; // Set of visited places
	Flight::route currentRoute;
	currentRoute.destinations.push_back(beginning);
	currentRoute.totalCost = 0;
	if (beginning == end) {
		return currentRoute;
	}
	flightQ.push(currentRoute);
	bool notFound = true;
	while (notFound) {
		Flight::route old = flightQ.front();
		Flight::dest current = old.destinations.back();
		flightQ.pop();
		for (int i = 0; i < size; ++i) {
			Flight::dest pos = positions[i];
			if (visited.find(pos) != visited.end()) { // skip if the place has already been visited
				continue;
			}
			Flight::cost val = table[current][pos];
			if (val > 0) { // check if the cost is greater than zero, meaning there is a connection
				if (pos == end) { // check if the end destination has been found
					old.destinations.push_back(pos);
					old.totalCost += val;
					shortestRoute = old;
					notFound = false;
					break;
				}
				Flight::route newer = old;
				newer.destinations.push_back(pos);
				newer.totalCost += val;
				flightQ.push(newer);
			}
		}
	}

	return shortestRoute;
}

// return the city given the position from the input file
Flight::dest Flight::get_city_by_value(int val)
{
	return positions[val];
}

// return the number of cities in the table
int Flight::get_size()
{
	return size;
}

// return the unordered_map of flight to cost pairs for the given city
Flight::destCost Flight::get_directFlights(Flight::dest city)
{
	return table[city];
}

// return true if the city is in the table, false otherwise
bool Flight::city_in_table(Flight::dest city) {
	if (table.count(city) == 1) {
		return true;
	} else {
		return false;
	}
}
