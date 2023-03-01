// Copyright 2023 Naon Lu
//
// This file describes the solution of
// LFU Cache
//
// https://leetcode.com/problems/lfu-cache/
//
// Question ID: 460
// Difficult  : Hard
// Solve Date : 2023/01/29 11:28

#include <iosfwd>
#include <list>
#include <map>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |460. LFU Cache|:
//
// Design and implement a data structure for a [Least Frequently Used (LFU)]
// cache. Implement the |LFUCache| class:
//
//  • |LFUCache(int capacity)| Initializes the object with the |capacity| of the
//  data structure.
//
//  • |int get(int key)| Gets the value of the |key| if the |key| exists in the
//  cache. Otherwise, returns |-1|.
//
//  • |void put(int key, int value)| Update the value of the |key| if present,
//  or inserts the |key| if not already present. When the cache reaches its
//  |capacity|, it should invalidate and remove the least frequently used key
//  before inserting a new item. For this problem, when there is a tie (i.e.,
//  two or more keys with the same frequency), the least recently used |key|
//  would be invalidated.
// To determine the least frequently used key, a use counter is maintained for
// each key in the cache. The key with the smallest use counter is the least
// frequently used key. When a key is first inserted into the cache, its use
// counter is set to |1| (due to the |put| operation). The use counter for a key
// in the cache is incremented either a |get| or |put| operation is called on
// it. The functions |get|and |put|must each run in |O(1)| average time
// complexity.
//

LEETCODE_BEGIN_RESOLVING(460, LFUCache, LFUCache);

class LFUCache {
private:
  int                                     cap;
  int                                     min_freq;
  unordered_map<int, pair<int, int>>      key_val;
  unordered_map<int, list<int>>           freq_list;
  unordered_map<int, list<int>::iterator> pos;

  unordered_map<int, pair<int, int>>::iterator access(int key) {
    auto iter = key_val.find(key);
    if (iter == key_val.end()) {
      return iter;
    }
    freq_list[iter->second.second].erase(pos[key]);
    ++iter->second.second;
    freq_list[iter->second.second].emplace_back(key);
    pos[key] = --freq_list[iter->second.second].end();
    if (freq_list[min_freq].empty()) {
      ++min_freq;
    }
    return iter;
  }

public:
  LFUCache(int capacity) : cap{capacity}, min_freq{0} {}

  int get(int key) {
    auto iter = access(key);
    return iter == key_val.end() ? -1 : iter->second.first;
  }

  void put(int key, int value) {
    if (!cap) {
      return;
    }
    auto iter = access(key);
    if (iter != key_val.end()) {
      iter->second.first = value;
    } else {
      if (key_val.size() == cap) {
        int del = freq_list[min_freq].front();
        key_val.erase(del);
        pos.erase(del);
        freq_list[min_freq].pop_front();
      }
      key_val[key] = {value, 1};
      freq_list[1].emplace_back(key);
      pos[key] = --freq_list[1].end();
      min_freq = 1;
    }
  }
};

LEETCODE_END_RESOLVING(LFUCache);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= capacity<= 10⁴|
// * |0 <= key <= 10⁵|
// * |0 <= value <= 10⁹|
// * At most |2 * 10⁵|calls will be made to |get| and |put|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get",
//  "get", "get"]
// [[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
// Output: [null, null, null, 1, null, -1, 3, null, -1, 3, 4]
//
// // cnt(x) = the use counter for key x
// // cache=[] will show the last used order for tiebreakers (leftmost element
// is most recent) LFUCache lfu = new LFUCache(2); lfu.put(1, 1); //
// cache=[1,_], cnt(1)=1 lfu.put(2, 2); // cache=[2,1], cnt(2)=1, cnt(1)=1
// lfu.get(1); // return 1
//  // cache=[1,2], cnt(2)=1, cnt(1)=2
// lfu.put(3, 3); // 2 is the LFU key because cnt(2)=1 is the smallest,
// invalidate 2.
//  // cache=[3,1], cnt(3)=1, cnt(1)=2
// lfu.get(2); // return -1 (not found)
// lfu.get(3); // return 3
//  // cache=[3,1], cnt(3)=2, cnt(1)=2
// lfu.put(4, 4); // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
//  // cache=[4,3], cnt(4)=1, cnt(3)=2
// lfu.get(1); // return -1 (not found)
// lfu.get(3); // return 3
//  // cache=[3,4], cnt(4)=1, cnt(3)=3
// lfu.get(4); // return 4
//  // cache=[4,3], cnt(4)=2, cnt(3)=3

LEETCODE_SOLUTION_UNITTEST(460, LFUCache, example_1) {
  int  s0_capacity = 2;
  auto lfu_cache   = MakeLFUCache(s0_capacity);
  int  s1_key      = 1;
  int  s1_value    = 1;
  lfu_cache->put(s1_key, s1_value);
  int s2_key   = 2;
  int s2_value = 2;
  lfu_cache->put(s2_key, s2_value);
  int s3_key    = 1;
  int s3_expect = 1;
  int s3_actual = lfu_cache->get(s3_key);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_key   = 3;
  int s4_value = 3;
  lfu_cache->put(s4_key, s4_value);
  int s5_key    = 2;
  int s5_expect = -1;
  int s5_actual = lfu_cache->get(s5_key);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  int s6_key    = 3;
  int s6_expect = 3;
  int s6_actual = lfu_cache->get(s6_key);
  LCD_EXPECT_EQ(s6_expect, s6_actual);
  int s7_key   = 4;
  int s7_value = 4;
  lfu_cache->put(s7_key, s7_value);
  int s8_key    = 1;
  int s8_expect = -1;
  int s8_actual = lfu_cache->get(s8_key);
  LCD_EXPECT_EQ(s8_expect, s8_actual);
  int s9_key    = 3;
  int s9_expect = 3;
  int s9_actual = lfu_cache->get(s9_key);
  LCD_EXPECT_EQ(s9_expect, s9_actual);
  int s10_key    = 4;
  int s10_expect = 4;
  int s10_actual = lfu_cache->get(s10_key);
  LCD_EXPECT_EQ(s10_expect, s10_actual);
}
