// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Magnetic Force Between Two Balls
//
// https://leetcode.com/problems/magnetic-force-between-two-balls/
//
// Question ID: 1552
// Difficult  : Medium
// Solve Date : 2022/07/17 14:37

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1552. Magnetic Force Between Two Balls|:
//
// In the universe Earth C-137, Rick discovered a special form of magnetic force
// between two balls if they are put in his new invented basket. Rick has |n|
// empty baskets, the |iᵗʰ| basket is at |position[i]|, Morty has |m| balls and
// needs to distribute the balls into the baskets such that the minimum magnetic
// force between any two balls is maximum. Rick stated that magnetic force
// between two different balls at positions |x| and |y| is ||x - y||. Given the
// integer array |position| and the integer |m|. Return the required force.
//

LEETCODE_BEGIN_RESOLVING(1552, MagneticForceBetweenTwoBalls, Solution);

class Solution {
private:
  bool helper(vector<int> &ps, int F, int m) {
    auto prev = ps.front();
    --m;

    for (auto it = ps.begin(); it != ps.end(); ++it) {
      while (it != ps.end() && *it - prev < F) {
        ++it;
      }

      if (it == ps.end()) {
        break;
      }

      prev = *it;
      --m;
    }

    return m <= 0;
  }

public:
  int maxDistance(vector<int> &position, int m) {
    sort(position.begin(), position.end());

    int L = 1, R = position.back();
    while (L <= R) {
      int mid = L + (R - L) / 2;

      if (helper(position, mid, m)) {
        L = mid + 1;
      } else {
        R = mid - 1;
      }
    }

    return L - 1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == position.length|
// * |2 <= n <= 10⁵|
// * |1 <= position[i] <= 10⁹|
// * All integers in |position| are distinct.
// * |2 <= m <= position.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: position = [1,2,3,4,7], m = 3
// Output: 3
//
// Distributing the 3 balls into baskets 1, 4 and 7 will make the magnetic force
// between ball pairs [3, 3, 6]. The minimum magnetic force is 3. We cannot
// achieve a larger minimum magnetic force than 3.

LEETCODE_SOLUTION_UNITTEST(1552, MagneticForceBetweenTwoBalls, example_1) {
  auto        solution = MakeSolution();
  vector<int> position = {1, 2, 3, 4, 7};
  int         m        = 3;
  int         expect   = 3;
  int         actual   = solution->maxDistance(position, m);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: position = [5,4,3,2,1,1000000000], m = 2
// Output: 999999999
//
// We can use baskets 1 and 1000000000.

LEETCODE_SOLUTION_UNITTEST(1552, MagneticForceBetweenTwoBalls, example_2) {
  auto        solution = MakeSolution();
  vector<int> position = {5, 4, 3, 2, 1, 1000000000};
  int         m        = 2;
  int         expect   = 999999999;
  int         actual   = solution->maxDistance(position, m);
  LCD_EXPECT_EQ(expect, actual);
}
