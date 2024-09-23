#include <iostream>
#include <cassert>
#include <list>

#include <ideal.h>


int slow_get_page_int(int key) { return key; }

int main()
{
  size_t cache_size;
  size_t n_elements;

  std::cin >> cache_size >> n_elements;
  assert(std::cin.good());

  std::list<int> entries{};
  for (size_t i = 0; i < n_elements; ++i)
  {
    int key;
    std::cin >> key;
    assert(std::cin.good());
    entries.push_back(key);
  }

  IdealCache<int> cache(cache_size, entries);

  unsigned hits = 0;
  for (const auto &key : entries)
  {
    if (cache.lookup_update(key, slow_get_page_int))
      hits += 1;
    // cache.print();
  }
  std::cout << hits << std::endl;
}
