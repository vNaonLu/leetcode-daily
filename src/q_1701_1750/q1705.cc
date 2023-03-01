// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Number of Eaten Apples
//
// https://leetcode.com/problems/maximum-number-of-eaten-apples/
//
// Question ID: 1705
// Difficult  : Medium
// Solve Date : 2022/02/17 21:55

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1705. Maximum Number of Eaten Apples|:
//
// There is a special kind of apple tree that grows apples every day for |n|
// days. On the |iᵗʰ| day, the tree grows |apples[i]| apples that will rot after
// |days[i]| days, that is on day |i + days[i]| the apples will be rotten and
// cannot be eaten. On some days, the apple tree does not grow any apples, which
// are denoted by |apples[i] == 0| and |days[i] == 0|. You decided to eat at
// most one apple a day (to keep the doctors away). Note that you can keep
// eating after the first |n| days. Given two integer arrays |days| and |apples|
// of length |n|, return the maximum number of apples you can eat.  
//

LEETCODE_BEGIN_RESOLVING(1705, MaximumNumberOfEatenApples, Solution);

class Solution {
private:
  using day_count = pair<int, int>;

public:
  int eatenApples(vector<int> &apples, vector<int> &days) {
    priority_queue<day_count, vector<day_count>, greater<day_count>> pq;
    int res = 0, curr_day = 0, n = apples.size();
    while (curr_day < n || pq.empty() == false) {
      if (curr_day < n && apples[curr_day] > 0) {
        pq.emplace(curr_day + days[curr_day], apples[curr_day]);
      }

      while (pq.empty() == false) {
        auto [rot_day, remain] = pq.top();
        pq.pop();
        if (rot_day > curr_day) {
          if (remain > 0) {
            pq.emplace(rot_day, --remain);
            ++res;
            break;
          }
        }
      }

      ++curr_day;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == apples.length == days.length|
// * |1 <= n <= 2 * 10⁴|
// * |0 <= apples[i], days[i] <= 2 * 10⁴|
// * |days[i] = 0| if and only if |apples[i] = 0|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: apples = [1,2,3,5,2], days = [3,2,1,4,2]
// Output: 7
//
// You can eat 7 apples:
// - On the first day, you eat an apple that grew on the first day.
// - On the second day, you eat an apple that grew on the second day.
// - On the third day, you eat an apple that grew on the second day. After this
// day, the apples that grew on the third day rot.
// - On the fourth to the seventh days, you eat apples that grew on the fourth
// day.

LEETCODE_SOLUTION_UNITTEST(1705, MaximumNumberOfEatenApples, example_1) {
  auto        solution = MakeSolution();
  vector<int> apples   = {1, 2, 3, 5, 2};
  vector<int> days     = {3, 2, 1, 4, 2};
  int         expect   = 7;
  int         actual   = solution->eatenApples(apples, days);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: apples = [3,0,0,0,0,2], days = [3,0,0,0,0,2]
// Output: 5
//
// You can eat 5 apples:
// - On the first to the third day you eat apples that grew on the first day.
// - Do nothing on the fouth and fifth days.
// - On the sixth and seventh days you eat apples that grew on the sixth day.

LEETCODE_SOLUTION_UNITTEST(1705, MaximumNumberOfEatenApples, example_2) {
  auto        solution = MakeSolution();
  vector<int> apples   = {3, 0, 0, 0, 0, 2};
  vector<int> days     = {3, 0, 0, 0, 0, 2};
  int         expect   = 5;
  int         actual   = solution->eatenApples(apples, days);
  LCD_EXPECT_EQ(expect, actual);
}
