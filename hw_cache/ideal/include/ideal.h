#pragma once

#include <list>
#include <unordered_map>
#include <map>
#include <utility>


template <typename ValueT, typename KeyT = int>
class IdealCache
{
private:
  using ListItem = std::pair<KeyT, ValueT>;
  using ListIt = typename std::list<ListItem>::iterator;

  size_t capacity_;

  std::list<ListItem> list_;
  std::unordered_map<KeyT, ListIt> map_;

  std::list<KeyT> future_;

private:
  // among cache elements + new cache candidate,
  // finds the item which occurs last in future
  // (or doesn't occur at all)
  // and returns its key
  KeyT find_latest_occurrence(KeyT new_key) const
  {
    std::map<KeyT, bool> occured;
    KeyT latest = new_key;

    for (const auto &item : list_)
      occured.emplace(item.first, false);
    occured.emplace(new_key, false);

    for (const auto &item : future_)
    {
      auto it = occured.find(item);
      if (it != occured.end())
      {
        it->second = true;
        latest = it->first;
      }
    }

    for (const auto &item : occured)
      if (item.second == false)
        return item.first; // if item didn't occur at all

    return latest;
  }

public:
  IdealCache(size_t capacity, std::list<KeyT> future)
    : capacity_(capacity), future_(future) {}

  bool full() const { return list_.size() == capacity_; }

  // returns true if cache hit, false if cache miss
  template <typename F>
  bool lookup_update(KeyT key, F slow_get_page)
  {
    future_.pop_front(); // new key is no longer "future"

    if (!capacity_)
      return false;

    auto map_it = map_.find(key);
    if (map_it == map_.end()) // miss
    {
      if (full())
      {
        KeyT latest = find_latest_occurrence(key);
        if (latest == key)
          return false; // we decided not to cache the new item

        assert(map_.find(latest) != map_.end());
        list_.erase((map_.find(latest))->second);
        map_.erase(latest);
      }
      list_.emplace_front(key, slow_get_page(key));
      map_.emplace(key, list_.begin());
      return false;
    }
    // hit
    return true;
  }

  // prints out cache contents
  void print()
  {
    std::cout << "| ";
    for (const ListItem &item : list_)
      std::cout << item.first << " | ";
    std::cout << std::endl;
  }
};
