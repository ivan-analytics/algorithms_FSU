
template <typename K, typename V>
HashTable<K,V>::HashTable(size_t size) {
    size = prime_below(size);
    if (size <= 0)
        size = default_capacity;
    buckets.resize(size);
    current_size = 0;
}

template <typename K, typename V>
HashTable<K,V>::~HashTable() {
    clear();
}

template <typename K, typename V>
bool HashTable<K,V>::contains(const K & k) const {
    auto & whichList = buckets[myhash(k)];
    for (auto & pair : whichList) {
        if (pair.first == k)
            return true;
    }
    return false;
}

template <typename K, typename V>
bool HashTable<K,V>::match(const std::pair<K,V> & kv) const {
    auto & whichList = buckets[myhash(kv.first)];
    for (auto & pair : whichList) {
        if (pair == kv)
            return true;
    }
    return false;
}

template <typename K, typename V>
bool HashTable<K,V>::insert(const std::pair<K,V> & kv) {
    auto & whichList = buckets[myhash(kv.first)];
    for (auto & pair : whichList) {
        if (pair.first == kv.first) {
            if (pair.second == kv.second)
                return false;
            else {
                pair.second = kv.second;
                return true;
            }
        }
    }
    whichList.push_back(kv);
    if (++current_size > buckets.size())
        rehash();
    return true;
}

template <typename K, typename V>
bool HashTable<K,V>::insert(std::pair<K,V> && kv) {
    auto & whichList = buckets[myhash(kv.first)];
    for (auto & pair : whichList) {
        if (pair.first == kv.first) {
            if (pair.second == kv.second)
                return false;
            else {
                pair.second = std::move(kv.second);
                return true;
            }
        }
    }
    whichList.push_back(std::move(kv));
    if (++current_size > buckets.size())
        rehash();
    return true;
}

template <typename K, typename V>
bool HashTable<K,V>::remove(const K & k) {
    auto & whichList = buckets[myhash(k)];
    for (auto itr = whichList.begin(); itr != whichList.end(); ++itr) {
        if (itr->first == k) {
            whichList.erase(itr);
            --current_size;
            return true;
        }
    }
    return false;
}

template <typename K, typename V>
void HashTable<K,V>::clear() {
    makeEmpty();
}

template <typename K, typename V>
bool HashTable<K,V>::load(const char *filename) {
    std::ifstream infile(filename);
    if (!infile)
        return false;
    K key;
    V val;
    while (infile >> key >> val) {
        insert(std::make_pair(key, val));
    }
    infile.close();
    return true;
}

template <typename K, typename V>
void HashTable<K,V>::dump() const {
    for (size_t i = 0; i < buckets.size(); ++i) {
        std::cout << "v[" << i << "]:";
        for (auto & kv : buckets[i]) {
            std::cout << " " << kv.first << " " << kv.second << " :";
        }
        std::cout << std::endl;
    }
}

template <typename K, typename V>
size_t HashTable<K,V>::size() const {
    return current_size;
}

template <typename K, typename V>
bool HashTable<K,V>::write_to_file(const char *filename) const {
    std::ofstream outfile(filename);
    if (!outfile)
        return false;
    for (auto & whichList : buckets) {
        for (auto & kv : whichList) {
            outfile << kv.first << " " << kv.second << std::endl;
        }
    }
    outfile.close();
    return true;
}

template <typename K, typename V>
void HashTable<K,V>::makeEmpty() {
    for (auto & whichList : buckets)
        whichList.clear();
    current_size = 0;
}

template <typename K, typename V>
void HashTable<K,V>::rehash() {
    std::vector< std::list< std::pair<K,V> > > oldBuckets = buckets;

    // Create new double-sized, empty table
    buckets.resize(prime_below(2 * buckets.size()));
    for (auto & thisList : buckets)
        thisList.clear();

    // Copy elements from oldBuckets to new buckets
    current_size = 0;
    for (auto & whichList : oldBuckets)
        for (auto & kv : whichList)
            insert(std::move(kv));
}

template <typename K, typename V>
size_t HashTable<K,V>::myhash(const K &k) const {
    static std::hash<K> hf;
    return hf(k) % buckets.size();
}

// Returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K,V>::prime_below (unsigned long n)
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

// Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K,V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.size();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i * 2 ; j < n; j += i)
          vprimes[j] = 0;
    }
}
