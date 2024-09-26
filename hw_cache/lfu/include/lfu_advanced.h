#pragma once

#include <unordered_map>
#include <list>
#include <utility>


template <typename ValueT, typename KeyT = int>
class LFUCache
{
  using CounterT = unsigned;

  struct Node
  {
    KeyT key;
    ValueT value;
    CounterT count;
    typename std::list<KeyT>::iterator iter;
  };

private:
  size_t capacity_;
  CounterT minCount_ = 1;

  std::unordered_map<KeyT, Node> keyToNode_;
  std::unordered_map<CounterT, std::list<KeyT>> countToKeys_;

private:
  void touch(Node &node)
  {
    // update node count
    CounterT prevCount = node.count;
    CounterT newCount = ++node.count;

    // remove node from prevCount
    countToKeys_[prevCount].erase(node.iter);
    if (countToKeys_[prevCount].empty())
    {
      countToKeys_.erase(prevCount);
      // if it was the minCount_ that got erased,
      // update minCount_
      if (minCount_ == prevCount)
        ++minCount_;
    }

    // insert the key to the front of newCount list
    countToKeys_[newCount].push_front(node.key);
    node.iter = countToKeys_[newCount].begin();
  }

public:
  LFUCache(size_t capacity) : capacity_(capacity) {}

  bool full() const { return keyToNode_.size() == capacity_; }

  // returns true if cache hit, false if cache miss
  template <typename F>
  bool lookup_update(KeyT key, F slow_get_page)
  {
    if (!capacity_)
      return false;

    auto map_it = keyToNode_.find(key);
    if (map_it == keyToNode_.end()) // miss
    {
      if (full())
      {
        // if there are multiple keys with the same count,
        // remove least recently used one
        KeyT keyToEvict = countToKeys_[minCount_].back();
        countToKeys_[minCount_].pop_back();
        keyToNode_.erase(keyToEvict);
      }
      // insert new node
      minCount_ = 1;
      countToKeys_[minCount_].push_front(key);
      keyToNode_[key] = Node{key, slow_get_page(key), 1, countToKeys_[1].begin()};
      return false;
    }
    // hit
    touch(map_it->second);
    return true;
  }
};
