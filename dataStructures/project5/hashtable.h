#ifndef HASHTABLE_H__
#define HASHTABLE_H__


#include <vector>
#include <list>
#include <fstream>


namespace cop4530 {

template <typename T>
class HashTable {
	public:
		// constructor and destructor
		explicit HashTable(size_t size=101); // default size is 101, a prime number
		~HashTable();

		// public member functions on HashTable
		bool contains(const T &x); // returns true if value is in hashtable
		bool insert(const T &x); // inserts value into hashtable, copy version
		bool insert(T &&x); // move version
		bool remove(const T &x); // removes value from hashtable
		void clear(); // delete all elements in the hashtable
		bool load(const char *filename); // load the contents of the file with name filename into hashtable
		void dump(); // display all entries in the hash table
		bool write_to_file(const char *filename); // write all the values in the hashtable to a file named filename
		size_t size(); // return the current size of the hashtable, not required

	private:
		// private static constant member variables used in helper functions
		static const unsigned int default_capacity = 11; // provided by instructor
		static const unsigned int max_prime = 1301081; // provided by instructor

		// private member functions
		void makeEmpty(); // delete all elements in the hash table
		void rehash(); // rehash the hashtable, for when the hashtable becomes too large
		size_t myhash(const T &x); // the hash function, returns the index of the vector entry where x should be stored

		// used when improper size is given (for example
		// size is 0 or negatiave)
		unsigned long prime_below(unsigned long); // provided by instructor
		void setPrimes(std::vector<unsigned long> &); // provided by instructor

		// typedef for ease
		typedef std::vector<std::list<T>> hash_table;
		// private member variables
		size_t theSize;
		hash_table table;
};

// include the implementation file
#include "hashtable.hpp"

}

#endif
