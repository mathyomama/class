/*
 * Spell checker program
 */

#include <iostream>
#include "hashtable.h"


using namespace std;
using namespace cop4530;

void menu()
{
	cout << "\n\n";
	cout << "l - Load Dictionary From File" << endl;
	cout << "a - Add Word" << endl;
	cout << "r - Remove Word" << endl;
	cout << "c - Clear HashTable" << endl;
	cout << "f - Find Word" << endl;
	cout << "d - Dump HashTable" << endl;
	cout << "s - HashTable Size" << endl;
	cout << "w - Write to File" << endl;
	cout << "x - Exit program" << endl;
	cout << "\nEnter choice : ";
}

void spell_check(string dictionary, string input, string output) {
}

void menu_program() {
	string hash_size;
	cout << "Enter preferred hash table capacity: ";
	cin >> hash_size;
	HashTable dict{stoi(hash_size)};
	
}

void print_usage(string name) {
	cout << "USAGE: " << name << " <dict_file> <file_to_check> <output_file>" << endl;
}

int main(int argc, char* argv[]) {
	if (argc == 4) {
		spell_check(argv[1], argv[2], argv[3]);
	} else if (argc == 1) {
		menu_program();
	} else {
		print_usage(argv[0]);
	}

	return 0;
}
