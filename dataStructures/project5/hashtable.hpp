#ifndef HASHTABLE_HPP__
#define HASHTABLE_HPP__


// PUBLIC MEMBER FUNCTIONS

// Constructor
template <typename T>
HashTable<T>::HashTable(size_t size) :
	theSize{0}
{
	unsigned long prime = prime_below(size);
	if (prime == 0) {
		prime = default_capacity;
		std::cout << "set to default capacity" << std::endl;
	}
	table = hash_table{prime};
	std::cout << prime << std::endl;
}

// Destructor: NEED TO IMPLEMENT
template <typename T>
HashTable<T>::~HashTable()
{
}

// contains: returns true if value is in the hashtable
template <typename T>
bool HashTable<T>::contains(const T &x)
{
	auto & bucketList = table[myhash(x)];
	return std::find(std::begin(bucketList), std::end(bucketList), x) != std::end(bucketList);
}

// insert: inserts the value into the hashtable, returns true if done correctly
// returns false otherwise, copy version
template <typename T>
bool HashTable<T>::insert(const T &x)
{
	auto & bucketList = table[myhash(x)];
	if (std::find(std::begin(bucketList), std::end(bucketList), x) != std::end(bucketList)) {
		return false;
	}
	bucketList.push_back(x);
	if (++theSize > table.size()) {
		rehash();
	}
	return true;
}

// insert: move version
template <typename T>
bool HashTable<T>::insert(T &&x)
{
	auto & bucketList = table[myhash(x)];
	if (std::find(std::begin(bucketList), std::end(bucketList), x) != std::end(bucketList)) {
		return false;
	}
	bucketList.push_back(x);
	if (++theSize > table.size()) {
		rehash();
	}
	return true;
}

// remove: removes the given value and returns true if done correctly, false otherwise
template <typename T>
bool HashTable<T>::remove(const T &x)
{
	auto & bucketList = table[myhash(x)];
	auto itr = std::find(std::begin(bucketList), std::end(bucketList), x);
	if (itr == std::end(bucketList)) {
		return false;
	}
	bucketList.erase(itr);
	--theSize;
	return true;
}

// clear: remove all the elements in the hashtable
template <typename T>
void HashTable<T>::clear()
{
	makeEmpty();
}

// load: takes the filename provided and loads the contents in the file with that
// filename. We are assuming that each line of the file contains a single value
// and that T has a constructor which accepts a string.
template <typename T>
bool HashTable<T>::load(const char *filename)
{
	std::ifstream inputFile;
	inputFile.open(filename);
	if (!inputFile.is_open()) {
		return false; // return false if the file is not open
	}
	std::string line;
	while (std::getline(inputFile, line)) {
		insert(T{line}); // assuming T has a constructor which accepts a string
	}
	inputFile.close();
	return true;
}

// dump: display the contents of the hashtable
template <typename T>
void HashTable<T>::dump()
{
	for (unsigned long bucket = 0; bucket < table.size(); ++bucket) {
		auto bucketList = table[bucket];
		std::cout << "v[" << bucket << "]: ";
		for (auto element : bucketList) {
			std::cout << element << "\t";
		}
		std::cout << std::endl;
	}
}

// write_to_file: print the contents of the hashtable to a file named filename
template <typename T>
bool HashTable<T>::write_to_file(const char *filename)
{
	std::ofstream outputFile;
	outputFile.open(filename);
	if (!outputFile.is_open()) {
		return false;
	}
	for (auto bucketList : table) {
		for (auto element : bucketList) {
			outputFile << element << std::endl;
		}
	}
	outputFile.close();
	return true;
}

// size: return the size of the hashtable, not required
template <typename T>
size_t HashTable<T>::size()
{
	return theSize;
}

// num_of_buckets: returns the number of buckets in the hashtable currently
template <typename T>
size_t HashTable<T>::num_of_buckets()
{
	return table.size();
}


// PRIVATE MEMBER FUNCTION

// makeEmpty: clears the hashtable
template <typename T>
void HashTable<T>::makeEmpty()
{
	for (auto bucketList : table) {
		bucketList.clear();
	}
	theSize = 0;
}

// rehash: rehash the hashtable which will increase the size and reposition the
// elements relative to each other
template <typename T>
void HashTable<T>::rehash()
{
	hash_table oldTable = table;
	table.resize(prime_below(2*oldTable.size()));
	for (auto &bucketList : table) {
		bucketList.clear();
	}
	theSize = 0;
	for (auto &bucketList : oldTable) {
		for (auto &element : bucketList) {
			insert(element);
		}
	}
}

// myhash: the hash function for this class, it will return the index where the
// given element should be stored
template <typename T>
size_t HashTable<T>::myhash(const T &x)
{
	size_t buckets = table.size(); // normalize to size of table
	return std::hash<T>{}(x)%buckets;
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename T>
unsigned long HashTable<T>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename T>
void HashTable<T>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}


#endif
