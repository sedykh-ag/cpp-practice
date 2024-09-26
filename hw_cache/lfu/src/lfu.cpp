#include <cstddef>
#include <iostream>
#include <cassert>

#include <lfu_advanced.h>


int slow_get_page_int(int key) { return key; }

int main()
{
  size_t cache_size;
  size_t n_elements;

  std::cin >> cache_size >> n_elements;
  assert(std::cin.good());

  LFUCache<int> cache(cache_size);

  unsigned hits = 0;
  for (size_t i = 0; i < n_elements; ++i)
  {
    int key;
    std::cin >> key;
    assert(std::cin.good());
    if (cache.lookup_update(key, slow_get_page_int)) // if cache hit
      hits += 1;
  }
  std::cout << hits << std::endl;
}
