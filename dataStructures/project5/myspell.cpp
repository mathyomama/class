/*
 * Spell checker program
 */

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include "hashtable.h"


using namespace std;
using namespace cop4530;

/*
 * This program was provided by the instructor. It prints the menu for interactive
 * mode. 
 */
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

/*
 * This function is called when three parameters are given at the invocation of
 * the program: the dictionary filename, file-to-check filename, and the output
 * filename. First this program will load the dictionary from the dictionary file.
 * Then it will read the input file line by line and find invalid words according
 * to the dictionary provided. When an invalid word is found, ten candidate words,
 * if there are that many, will be suggested (as well as no change). Once a choice
 * is picked, the function will move on to the next invalid word on the same line.
 * Once all invalid words have been dealt with, the function will append the line
 * to the output file. This occurs for each line in the input file.
 */
void spell_check(string dictionary, string input, string output) {
	HashTable<string> dict{};
	if (!dict.load(dictionary.c_str())) {
		cout << "Cannot open file " << dictionary << endl;
		cout << "Global dictionary cannot be loaded" << endl;
		return;
	}
	ifstream ifile{input};
	if (!ifile.is_open()) {
		cout << "Word file cannot be opened" << endl;
		return;
	}
	ofstream ofile{output, ios::trunc};
	string line;
	while (getline(ifile, line)) {
		string test, corrected_line;
		for (unsigned int i = 0; i < line.size(); ++i) {
			char x = line[i]; // ith character in line
			if (isalpha(x)) { // test if the character is part of the alphabet
				test += x; // concatenate if the letter is in [:alpha:]
				if ((i + 1 < line.size() && !isalpha(line[i + 1])) || i + 1 == line.size()) {
					string test_lower = test;
					transform(test.begin(), test.end(), test_lower.begin(), ptr_fun<int, int>(tolower));
					if (!(dict.contains(test) || dict.contains(test_lower))) {
						// find ten possible replacements
						vector<string> suggestions;
						string prefix, placeholder, suffix;
						for (unsigned int n = 0; n < test.size() && suggestions.size() < 10; ++n) {
							placeholder = test[n];
							suffix = test.substr(n + 1);
							for (char character : "abcdefghijklmnopqrstuvwxyz") {
								string new_word = prefix + character + suffix;
								if (dict.contains(new_word)) {
									suggestions.push_back(new_word);
									if (suggestions.size() >= 10) {
										break;
									}
								}
							}
							prefix += placeholder;
						}
						// display output and take input
						string test_upper = test;
						transform(test.begin(), test.end(), test_upper.begin(), ptr_fun<int, int>(toupper));
						cout << corrected_line << test_upper << line.substr(i + 1) << endl;
						cout << "====================================" << endl;
						for (unsigned int j = 0; j < suggestions.size(); ++j) {
							cout << j << "): " << suggestions[j] << endl;
						}
						cout << "n (no change): " << endl;
						cout << "====================================" << endl;
						cout << "Your choice: ";
						string input;
						cin >> input;
						unsigned int choice = input[0] - '0' >= 0 ? input[0] - '0' : 11; // 11 is chosen since it is greater than 10
						switch(choice < suggestions.size()) {
							case true:
								test = suggestions[choice];
								break;
							case false:
							default:
								break;
						};
					}
					// add the corrected word to the corrected_line and clear test for the next word
					corrected_line += test;
					test.clear();
				}
			} else {
				corrected_line += x;
			}
		}
		ofile << corrected_line << endl;
	}
	ifile.close();
	ofile.close();
}

/*
 * This function is runs when the first mode is invoked on the console, i.e. when
 * not other arguments are provided (you could call this interactive mode). I
 * tried to emulate it as much as possible. It uses a switch after calling the
 * menu() function.
 */
void menu_program() {
	// Start by asking what the initial size of the hashtable should be
	cout << "Enter preferred hash table capacity: ";
	string hash_size;
	cin >> hash_size;
	HashTable<string> dict{(size_t)stoi(hash_size)};
	bool running = true;
	while (running) {
		menu();
		string input;
		string word;
		cin >> input;
		switch (input[0]) {
			// Load
			case 'l':
				cout << "Enter dictionary filename to load from: ";
				cin >> word;
				if (dict.load(word.c_str())) {
					cout << "Dictionary loaded successfully." << endl;
				} else {
					cout << "Cannot open file " << word << endl;
				}
				break;
			// Add
			case 'a':
				cout << "Enter word: ";
				cin >> word;
				cout << endl;
				if (dict.insert(word)) {
					cout << "Word " << word << " added." << endl;
				} else {
					cout << "*****: Word already exists. Could not add." << endl;
				}
				break;
			// Remove
			case 'r':
				cout << "Enter word: ";
				cin >> word;
				if (dict.insert(word)) {
					cout << "Word " << word << " deleted." << endl;
				} else {
					cout << "*****: Word not found.  Could not delete" << endl;
				}
				break;
			// Clear
			case 'c':
				dict.clear();
				break;
			// Find
			case 'f':
				cout << "Enter word: ";
				cin >> word;
				if (dict.contains(word)) {
					cout << "Word " << word << " found." << endl;
				} else {
					cout << "Word " << word << " not found." << endl;
				}
				break;
			// Dump
			case 'd':
				dict.dump();
				break;
			// Size of hashtable
			case 's':
				cout << "Size of hashtable: " << dict.size() << endl;
				break;
			// Write to file
			case 'w':
				cout << "Enter dictionary file name to write to: ";
				cin >> word;
				if (dict.write_to_file(word.c_str())) {
					cout << "Written successfully." << endl;
				} else {
					cout << "Write not successful" << endl;
				}
				break;
			// eXit interactive mode
			case 'x':
				running = false;
				break;
			// do nothing and repeat the loop
			default:
				cout << "*****Error: Invalid entry.  Try again." << endl;
				break;
		};
	}
}

/*
 * Called when an improper invocation of the program is used.
 */
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
