// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Design HashMap
//
// https://leetcode.com/problems/design-hashmap/
//
// Question ID: 706
// Difficult  : Easy
// Solve Date : 2021/09/20 08:00

#include <iosfwd>
#include <set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |706. Design HashMap|:
//
// Design a HashMap without using any built-in hash table libraries.
// Implement the |MyHashMap| class:
//
//  • |MyHashMap()| initializes the object with an empty map.
//
//  • |void put(int key, int value)| inserts a |(key, value)| pair into the
//  HashMap. If the |key| already exists in the map, update the corresponding
//  |value|.
//
//  • |int get(int key)| returns the |value| to which the specified |key| is
//  mapped, or |-1| if this map contains no mapping for the |key|.
//
//  • |void remove(key)| removes the |key| and its corresponding |value| if the
//  map contains the mapping for the |key|.
//  
//

LEETCODE_BEGIN_RESOLVING(706, DesignHashMap, MyHashMap);

class MyHashMap {
private:
  int data_[1000001];

public:
  MyHashMap() { memset(data_, -1, sizeof(data_)); }

  void put(int key, int value) { data_[key] = value; }

  int get(int key) { return data_[key]; }

  void remove(int key) { data_[key] = -1; }
};

LEETCODE_END_RESOLVING(MyHashMap);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= key, value <= 10⁶|
// * At most |10⁴| calls will be made to |put|, |get|, and |remove|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["MyHashMap", "put", "put", "get", "get", "put", "get", "remove",
//  "get"]
// [[], [1, 1], [2, 2], [1], [3], [2, 1], [2], [2], [2]]
// Output: [null, null, null, 1, -1, null, 1, null, -1]
//
// MyHashMap myHashMap = new MyHashMap();
// myHashMap.put(1, 1); // The map is now [[1,1]]
// myHashMap.put(2, 2); // The map is now [[1,1], [2,2]]
// myHashMap.get(1); // return 1, The map is now [[1,1], [2,2]]
// myHashMap.get(3); // return -1 (i.e., not found), The map is now [[1,1],
// [2,2]] myHashMap.put(2, 1); // The map is now [[1,1], [2,1]] (i.e., update
// the existing value) myHashMap.get(2); // return 1, The map is now [[1,1],
// [2,1]] myHashMap.remove(2); // remove the mapping for 2, The map is now
// [[1,1]] myHashMap.get(2); // return -1 (i.e., not found), The map is now
// [[1,1]]

LEETCODE_SOLUTION_UNITTEST(706, DesignHashMap, example_1) {
  auto my_hash_map = MakeMyHashMap();
  int  s1_key      = 1;
  int  s1_value    = 1;
  my_hash_map->put(s1_key, s1_value);
  int s2_key   = 2;
  int s2_value = 2;
  my_hash_map->put(s2_key, s2_value);
  int s3_key    = 1;
  int s3_expect = 1;
  int s3_actual = my_hash_map->get(s3_key);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_key    = 3;
  int s4_expect = -1;
  int s4_actual = my_hash_map->get(s4_key);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int s5_key   = 2;
  int s5_value = 1;
  my_hash_map->put(s5_key, s5_value);
  int s6_key    = 2;
  int s6_expect = 1;
  int s6_actual = my_hash_map->get(s6_key);
  LCD_EXPECT_EQ(s6_expect, s6_actual);
  int s7_key = 2;
  my_hash_map->remove(s7_key);
  int s8_key    = 2;
  int s8_expect = -1;
  int s8_actual = my_hash_map->get(s8_key);
  LCD_EXPECT_EQ(s8_expect, s8_actual);
}
