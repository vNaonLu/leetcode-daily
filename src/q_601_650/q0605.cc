// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Can Place Flowers
//
// https://leetcode.com/problems/can-place-flowers/
//
// Question ID: 605
// Difficult  : Easy
// Solve Date : 2022/01/18 18:15

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |605. Can Place Flowers|:
//
// You have a long flowerbed in which some of the plots are planted, and some
// are not. However, flowers cannot be planted in adjacent plots. Given an
// integer array |flowerbed| containing |0|'s and |1|'s, where |0| means empty
// and |1| means not empty, and an integer |n|, return if |n| new flowers can be
// planted in the |flowerbed| without violating the no-adjacent-flowers rule.  
//

LEETCODE_BEGIN_RESOLVING(605, CanPlaceFlowers, Solution);

class Solution {
public:
  bool canPlaceFlowers(vector<int> &flowerbed, int n) {
    int count = 0;
    for (int i = 0; i < flowerbed.size(); ++i) {
      if (flowerbed[i] == 0 && (i == 0 || flowerbed[i - 1] == 0) &&
          (i == flowerbed.size() - 1 || flowerbed[i + 1] == 0)) {
        flowerbed[i] = 1;
        ++count;
      }
    }
    return count >= n;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= flowerbed.length <= 2 * 10⁴|
// * |flowerbed[i]| is |0| or |1|.
// * There are no two adjacent flowers in |flowerbed|.
// * |0 <= n <= flowerbed.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: flowerbed = [1,0,0,0,1], n = 1
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(605, CanPlaceFlowers, example_1) {
  auto        solution  = MakeSolution();
  vector<int> flowerbed = {1, 0, 0, 0, 1};
  int         n         = 1;
  bool        expect    = true;
  bool        actual    = solution->canPlaceFlowers(flowerbed, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: flowerbed = [1,0,0,0,1], n = 2
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(605, CanPlaceFlowers, example_2) {
  auto        solution  = MakeSolution();
  vector<int> flowerbed = {1, 0, 0, 0, 1};
  int         n         = 2;
  bool        expect    = false;
  bool        actual    = solution->canPlaceFlowers(flowerbed, n);
  LCD_EXPECT_EQ(expect, actual);
}
