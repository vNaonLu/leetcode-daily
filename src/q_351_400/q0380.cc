// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Insert Delete GetRandom O(1)
//
// https://leetcode.com/problems/insert-delete-getrandom-o1/
//
// Question ID: 380
// Difficult  : Medium
// Solve Date : 2021/10/21 13:14

#include <iosfwd>
#include <set>
#include <unordered_set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |380. Insert Delete GetRandom O(1)|:
//
// Implement the |RandomizedSet| class:
//
//  • |RandomizedSet()| Initializes the |RandomizedSet| object.
//
//  • |bool insert(int val)| Inserts an item |val| into the set if not present.
//  Returns |true| if the item was not present, |false| otherwise.
//
//  • |bool remove(int val)| Removes an item |val| from the set if present.
//  Returns |true| if the item was present, |false| otherwise.
//
//  • |int getRandom()| Returns a random element from the current set of
//  elements (it's guaranteed that at least one element exists when this method
//  is called). Each element must have the same probability of being returned.
// You must implement the functions of the class such that each function works
// in average  |O(1)| time complexity.  
//

LEETCODE_BEGIN_RESOLVING(380, InsertDeleteGetRandomO1, RandomizedSet);

class RandomizedSet {
private:
  unordered_set<int> data;

public:
  RandomizedSet() {
    data.clear();
    srand(time(nullptr));
  }
  bool insert(int val) {
    if (data.count(val))
      return false;
    data.insert(val);
    return true;
  }
  bool remove(int val) {
    if (!data.count(val))
      return false;
    data.erase(val);
    return true;
  }
  int getRandom() {
    int  idx = rand() % data.size();
    auto res = data.begin();
    while (idx-- > 0)
      ++res;
    return *res;
  }
};

LEETCODE_END_RESOLVING(RandomizedSet);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |-2³¹ <= val <= 2³¹ - 1|
// * At most |2 * | |10⁵| calls will be made to |insert|, |remove|, and
// |getRandom|.
// * There will be at least one element in the data structure when |getRandom|
// is called.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["RandomizedSet", "insert", "remove", "insert", "getRandom",
//  "remove", "insert", "getRandom"]
// [[], [1], [2], [2], [], [1], [2], []]
// Output: [null, true, false, true, 2, true, false, 2]
//
// RandomizedSet randomizedSet = new RandomizedSet();
// randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was
// inserted successfully. randomizedSet.remove(2); // Returns false as 2 does
// not exist in the set. randomizedSet.insert(2); // Inserts 2 to the set,
// returns true. Set now contains [1,2]. randomizedSet.getRandom(); //
// getRandom() should return either 1 or 2 randomly. randomizedSet.remove(1); //
// Removes 1 from the set, returns true. Set now contains [2].
// randomizedSet.insert(2); // 2 was already in the set, so return false.
// randomizedSet.getRandom(); // Since 2 is the only number in the set,
// getRandom() will always return 2.

LEETCODE_SOLUTION_UNITTEST(380, InsertDeleteGetRandomO1, example_1) {
  GTEST_SKIP() << "Random Output";
  auto randomized_set = MakeRandomizedSet();
  int  s1_val         = 1;
  bool s1_expect      = true;
  bool s1_actual      = randomized_set->insert(s1_val);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int  s2_val    = 2;
  bool s2_expect = false;
  bool s2_actual = randomized_set->remove(s2_val);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int  s3_val    = 2;
  bool s3_expect = true;
  bool s3_actual = randomized_set->insert(s3_val);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_expect = 2;
  int s4_actual = randomized_set->getRandom();
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int  s5_val    = 1;
  bool s5_expect = true;
  bool s5_actual = randomized_set->remove(s5_val);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  int  s6_val    = 2;
  bool s6_expect = false;
  bool s6_actual = randomized_set->insert(s6_val);
  LCD_EXPECT_EQ(s6_expect, s6_actual);
  int s7_expect = 2;
  int s7_actual = randomized_set->getRandom();
  LCD_EXPECT_EQ(s7_expect, s7_actual);
}
