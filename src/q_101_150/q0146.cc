// Copyright 2023 Naon Lu
//
// This file describes the solution of
// LRU Cache
//
// https://leetcode.com/problems/lru-cache/
//
// Question ID: 146
// Difficult  : Medium
// Solve Date : 2022/02/26 00:48

#include <iosfwd>
#include <list>
#include <map>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |146. LRU Cache|:
//
// Design a data structure that follows the constraints of a [Least Recently
// Used (LRU) cache]. Implement the |LRUCache| class:
//
//  • |LRUCache(int capacity)| Initialize the LRU cache with positive size
//  |capacity|.
//
//  • |int get(int key)| Return the value of the |key| if the key exists,
//  otherwise return |-1|.
//
//  • |void put(int key, int value)| Update the value of the |key| if the |key|
//  exists. Otherwise, add the |key-value| pair to the cache. If the number of
//  keys exceeds the |capacity| from this operation, evict the least recently
//  used key.
// The functions |get| and |put| must each run in |O(1)| average time
// complexity.  
//

LEETCODE_BEGIN_RESOLVING(146, LRUCache, LRUCache);

class LRUCache {
private:
  unordered_map<int, list<pair<int, int>>::iterator> memos;
  list<pair<int, int>>                               cache;
  int                                                cap;

  void remove(int key) {
    auto it = memos.find(key);
    if (it != memos.end()) {
      cache.erase(it->second);
      memos.erase(key);
    }
  }

  void add(int key, int value) {
    remove(key);
    if (memos.size() == cap) {
      remove(cache.back().first);
    }
    cache.emplace_front(key, value);
    memos.emplace(key, cache.begin());
  }

public:
  LRUCache(int capacity) : cap{capacity} {}

  int get(int key) {
    auto it = memos.find(key);
    if (it != memos.end()) {
      int res = (*it->second).second;
      add(key, res);
      return res;
    }
    return -1;
  }

  void put(int key, int value) { add(key, value); }
};

LEETCODE_END_RESOLVING(LRUCache);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= capacity <= 3000|
// * |0 <= key <= 10⁴|
// * |0 <= value <= 10⁵|
// * At most |2 * 10⁵| calls will be made to |get| and |put|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get",
//  "get"]
// [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
// Output: [null, null, null, 1, null, -1, null, -1, 3, 4]
//
// LRUCache lRUCache = new LRUCache(2);
// lRUCache.put(1, 1); // cache is {1=1}
// lRUCache.put(2, 2); // cache is {1=1, 2=2}
// lRUCache.get(1); // return 1
// lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
// lRUCache.get(2); // returns -1 (not found)
// lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
// lRUCache.get(1); // return -1 (not found)
// lRUCache.get(3); // return 3
// lRUCache.get(4); // return 4

LEETCODE_SOLUTION_UNITTEST(146, LRUCache, example_1) {
  int  s0_capacity = 2;
  auto lru_cache   = MakeLRUCache(s0_capacity);
  int  s1_key      = 1;
  int  s1_value    = 1;
  lru_cache->put(s1_key, s1_value);
  int s2_key   = 2;
  int s2_value = 2;
  lru_cache->put(s2_key, s2_value);
  int s3_key    = 1;
  int s3_expect = 1;
  int s3_actual = lru_cache->get(s3_key);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_key   = 3;
  int s4_value = 3;
  lru_cache->put(s4_key, s4_value);
  int s5_key    = 2;
  int s5_expect = -1;
  int s5_actual = lru_cache->get(s5_key);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  int s6_key   = 4;
  int s6_value = 4;
  lru_cache->put(s6_key, s6_value);
  int s7_key    = 1;
  int s7_expect = -1;
  int s7_actual = lru_cache->get(s7_key);
  LCD_EXPECT_EQ(s7_expect, s7_actual);
  int s8_key    = 3;
  int s8_expect = 3;
  int s8_actual = lru_cache->get(s8_key);
  LCD_EXPECT_EQ(s8_expect, s8_actual);
  int s9_key    = 4;
  int s9_expect = 4;
  int s9_actual = lru_cache->get(s9_key);
  LCD_EXPECT_EQ(s9_expect, s9_actual);
}
