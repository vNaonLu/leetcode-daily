// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Smallest Number in Infinite Set
//
// https://leetcode.com/problems/smallest-number-in-infinite-set/
//
// Question ID: 2336
// Difficult  : Medium
// Solve Date : 2023/04/25 18:45

#include <iosfwd>
#include <set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2336. Smallest Number in Infinite Set|:
//
// You have a set which contains all positive integers |[1, 2, 3, 4, 5, ...]|.
// Implement the |SmallestInfiniteSet| class:
//
//  • |SmallestInfiniteSet()| Initializes the SmallestInfiniteSet object to
//  contain all positive integers.
//
//  • |int popSmallest()| Removes and returns the smallest integer contained in
//  the infinite set.
//
//  • |void addBack(int num)| Adds a positive integer |num| back into the
//  infinite set, if it is not already in the infinite set.
//
//

LEETCODE_BEGIN_RESOLVING(2336, SmallestNumberInInfiniteSet,
                         SmallestInfiniteSet);

class SmallestInfiniteSet {
public:
  SmallestInfiniteSet() {}

  int popSmallest() {
    if (!q.empty()) {
      auto res = *q.begin();
      q.erase(q.begin());
      return res;
    }
    return cur++;
  }

  void addBack(int num) {
    if (num < cur) {
      q.emplace(num);
    }
  }

private:
  int      cur = 1;
  set<int> q;
};

LEETCODE_END_RESOLVING(SmallestInfiniteSet);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= num <= 1000|
// * At most |1000| calls will be made in total to |popSmallest| and |addBack|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["SmallestInfiniteSet", "addBack", "popSmallest", "popSmallest",
//  "popSmallest", "addBack", "popSmallest", "popSmallest", "popSmallest"]
// [[], [2], [], [], [], [1], [], [], []]
// Output: [null, null, 1, 2, 3, null, 1, 4, 5]
//
// SmallestInfiniteSet smallestInfiniteSet = new SmallestInfiniteSet();
// smallestInfiniteSet.addBack(2); // 2 is already in the set, so no change is
// made. smallestInfiniteSet.popSmallest(); // return 1, since 1 is the smallest
// number, and remove it from the set. smallestInfiniteSet.popSmallest(); //
// return 2, and remove it from the set. smallestInfiniteSet.popSmallest(); //
// return 3, and remove it from the set. smallestInfiniteSet.addBack(1); // 1 is
// added back to the set. smallestInfiniteSet.popSmallest(); // return 1, since
// 1 was added back to the set and
//  // is the smallest number, and remove it from the set.
// smallestInfiniteSet.popSmallest(); // return 4, and remove it from the set.
// smallestInfiniteSet.popSmallest(); // return 5, and remove it from the set.

LEETCODE_SOLUTION_UNITTEST(2336, SmallestNumberInInfiniteSet, example_1) {
  auto smallest_infinite_set = MakeSmallestInfiniteSet();
  int  s1_num                = 2;
  smallest_infinite_set->addBack(s1_num);
  int s2_expect = 1;
  int s2_actual = smallest_infinite_set->popSmallest();
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int s3_expect = 2;
  int s3_actual = smallest_infinite_set->popSmallest();
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_expect = 3;
  int s4_actual = smallest_infinite_set->popSmallest();
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int s5_num = 1;
  smallest_infinite_set->addBack(s5_num);
  int s6_expect = 1;
  int s6_actual = smallest_infinite_set->popSmallest();
  LCD_EXPECT_EQ(s6_expect, s6_actual);
  int s7_expect = 4;
  int s7_actual = smallest_infinite_set->popSmallest();
  LCD_EXPECT_EQ(s7_expect, s7_actual);
  int s8_expect = 5;
  int s8_actual = smallest_infinite_set->popSmallest();
  LCD_EXPECT_EQ(s8_expect, s8_actual);
}
