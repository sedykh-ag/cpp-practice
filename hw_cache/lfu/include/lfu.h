#include <list>
#include <unordered_map>
#include <cstddef>
#include <algorithm>
#include <cassert>
#include <tuple>

#pragma once


template <typename ValueT, typename KeyT = int>
class LFUCache
{
private:
  using CounterT = unsigned;
  using ListItem = std::tuple<KeyT, ValueT, CounterT>;
  using ListIt = typename std::list<ListItem>::iterator;

  size_t capacity_;

  std::list<ListItem> list_;
  std::unordered_map<KeyT, ListIt> map_;

private:
  static bool cmp(const ListItem &a, const ListItem &b)
  {
    return std::get<2>(a) < std::get<2>(b);
  }

public:
  LFUCache(size_t capacity) : capacity_(capacity) {}

  bool full() const { return list_.size() == capacity_; }

  // returns true if cache hit, false if cache miss
  template <typename F>
  bool lookup_update(KeyT key, F slow_get_page)
  {
    if (!capacity_)
      return false;

    auto map_it = map_.find(key);
    if (map_it == map_.end()) // miss
    {
      if (full())
      {
        auto min_elem_it = std::min_element(list_.rbegin(), list_.rend(), cmp);
        assert(min_elem_it != list_.rend());
        auto tuple = *min_elem_it;
        KeyT key = std::get<0>(tuple);
        map_.erase(key);
        list_.erase(std::prev(min_elem_it.base()));
      }
      list_.emplace_front(key, slow_get_page(key), 1);
      map_.emplace(key, list_.begin());
      return false;
    }
    // hit
    auto &tuple = *(map_it->second);
    std::get</* CounterT */2>(tuple) += 1;
    std::get</* ValueT */ 1>(tuple) = slow_get_page(key);
    return true;
  }

  void print()
  {
    for (const ListItem &tuple : list_)
    {
      int value = std::get<1>(tuple);
      int counter = std::get<2>(tuple);
      std::cout << value << ", " << counter << " | ";
    }
    std::cout << std::endl;
  }
};
