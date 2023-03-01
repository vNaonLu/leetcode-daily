// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Design HashSet
//
// https://leetcode.com/problems/design-hashset/
//
// Question ID: 705
// Difficult  : Easy
// Solve Date : 2022/04/21 08:32

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |705. Design HashSet|:
//
// Design a HashSet without using any built-in hash table libraries.
// Implement |MyHashSet| class:
//
//  • |void add(key)| Inserts the value |key| into the HashSet.
//
//  • |bool contains(key)| Returns whether the value |key| exists in the HashSet
//  or not.
//
//  • |void remove(key)| Removes the value |key| in the HashSet. If |key| does
//  not exist in the HashSet, do nothing.
//  
//

LEETCODE_BEGIN_RESOLVING(705, DesignHashSet, MyHashSet);

class MyHashSet {
private:
  vector<int> data_;

public:
  MyHashSet() : data_(1000001, -1) {}

  void add(int key) { data_[key] = 1; }

  void remove(int key) { data_[key] = -1; }

  bool contains(int key) { return data_[key] == 1; }
};

LEETCODE_END_RESOLVING(MyHashSet);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= key <= 10⁶|
// * At most |10⁴| calls will be made to |add|, |remove|, and |contains|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["MyHashSet", "add", "add", "contains", "contains", "add",
//  "contains", "remove", "contains"]
// [[], [1], [2], [1], [3], [2], [2], [2], [2]]
// Output: [null, null, null, true, false, null, true, null, false]
//
// MyHashSet myHashSet = new MyHashSet();
// myHashSet.add(1); // set = [1]
// myHashSet.add(2); // set = [1, 2]
// myHashSet.contains(1); // return True
// myHashSet.contains(3); // return False, (not found)
// myHashSet.add(2); // set = [1, 2]
// myHashSet.contains(2); // return True
// myHashSet.remove(2); // set = [1]
// myHashSet.contains(2); // return False, (already removed)

LEETCODE_SOLUTION_UNITTEST(705, DesignHashSet, example_1) {
  auto my_hash_set = MakeMyHashSet();
  int  s1_key      = 1;
  my_hash_set->add(s1_key);
  int s2_key = 2;
  my_hash_set->add(s2_key);
  int  s3_key    = 1;
  bool s3_expect = true;
  bool s3_actual = my_hash_set->contains(s3_key);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int  s4_key    = 3;
  bool s4_expect = false;
  bool s4_actual = my_hash_set->contains(s4_key);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int s5_key = 2;
  my_hash_set->add(s5_key);
  int  s6_key    = 2;
  bool s6_expect = true;
  bool s6_actual = my_hash_set->contains(s6_key);
  LCD_EXPECT_EQ(s6_expect, s6_actual);
  int s7_key = 2;
  my_hash_set->remove(s7_key);
  int  s8_key    = 2;
  bool s8_expect = false;
  bool s8_actual = my_hash_set->contains(s8_key);
  LCD_EXPECT_EQ(s8_expect, s8_actual);
}
