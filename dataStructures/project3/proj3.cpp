#include <iostream>
#include <string>
#include "flight.h"


// function for asking if the client would like to look for another route
bool check_another_route(std::string msg="") {
	if (msg != "") {
		std::cout << msg << std::endl << std::endl;
	}
	std::string answer;
	while (true) {
		std::cout << "Search another route? (Y/N)";
		std::getline(std::cin, answer);
		switch(answer.front()) {
			case 'y':
			case 'Y':
				return true;
			case 'n':
			case 'N':
				return false;
			default:
				continue;
		}
	}
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "USAGE: ./proj3.x <input_file>" << std::endl;
		return 0;
	}

	std::string inputFile = argv[1];
	Flight flight_table(inputFile);
	//flight_table.add_table(inputFile);
	
	// Introduction
	int city_amount = flight_table.get_size();
	std::cout << city_amount << " cities:" << std::endl;
	for (int i = 0; i < flight_table.get_size(); ++i) {
		std::cout << "    " << flight_table.get_city_by_value(i) << std::endl;
	}
	std::cout << std::endl << "Direct flights between cities" << std::endl << "-------------------------" << std::endl;
	for (int i = 0; i < city_amount; ++i) {
		Flight::dest city = flight_table.get_city_by_value(i);
		Flight::destCost direct = flight_table.get_directFlights(city);
		std::cout << city << std::endl;
		for (int j = 0; j < city_amount; ++j) {
			Flight::dest pos = flight_table.get_city_by_value(j);
			Flight::cost val = direct[pos];
			if (val > 0) {
				std::cout << "    " << pos << ", $" << val << std::endl;
			}
		}
	}
	std::cout << "--------------------------" << std::endl << std::endl;

	// Begin input
	bool findRoute = true; // go through the loop until the client doesn't want to find a route
	while (findRoute) {
		std::cout << "Source city : ";
		Flight::dest sourceCity;
		std::getline(std::cin, sourceCity); // Need to get the whole line and not stop at a space, like in New York
		std::cout << "Destination city : ";
		Flight::dest destinationCity;
		std::getline(std::cin, destinationCity);
		std::cout << "finding min_hop route..." << std::endl;
		char msg[200] = "";
		if (!flight_table.city_in_table(sourceCity)) { // check if source city is in the flight table
			sprintf(msg, "    path not found, source city, %s, not on the map", sourceCity.c_str());
			findRoute = check_another_route(msg);
			continue;
		} else if (!flight_table.city_in_table(destinationCity)) { // check if the destination city is in the flight table
			sprintf(msg, "    path not found, destination city, %s, not on the map", destinationCity.c_str());
			findRoute = check_another_route(msg);
			continue;
		} else { // Proceed with the route finding algorithm
			Flight::route shortestRoute = flight_table.find_min_hop_route(sourceCity, destinationCity);
			std::cout << "   " << shortestRoute.destinations[0];
			for (unsigned int i = 1; i < shortestRoute.destinations.size(); ++i) {
				std::cout << " -> " <<  shortestRoute.destinations[i];
			}
			std::cout << ", $" << shortestRoute.totalCost << std::endl;
			findRoute = check_another_route(msg);
		}
	}

	return 0;
}
