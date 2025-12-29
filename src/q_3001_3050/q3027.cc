// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find the Number of Ways to Place People II
//
// https://leetcode.com/problems/find-the-number-of-ways-to-place-people-ii/
//
// Question ID: 3027
// Difficult  : Hard
// Solve Date : 2025/09/03 20:10

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3027. Find the Number of Ways to Place People II|:
//
// You are given a 2D array |points| of size |n x 2| representing integer
// coordinates of some points on a 2D-plane, where |points[i] = [xᵢ, yᵢ]|. We
// define the right direction as positive x-axis (increasing x-coordinate) and
// the left direction as negative x-axis (decreasing x-coordinate). Similarly,
// we define the up direction as positive y-axis (increasing y-coordinate) and
// the down direction as negative y-axis (decreasing y-coordinate) You have to
// place |n| people, including Alice and Bob, at these points such that there is
// exactly one person at every point. Alice wants to be alone with Bob, so Alice
// will build a rectangular fence with Alice's position as the upper left corner
// and Bob's position as the lower right corner of the fence (Note that the
// fence might not enclose any area, i.e. it can be a line). If any person other
// than Alice and Bob is either inside the fence or on the fence, Alice will be
// sad. Return the number of pairs of points where you can place Alice and Bob,
// such that Alice does not become sad on building the fence. Note that Alice
// can only build a fence with Alice's position as the upper left corner, and
// Bob's position as the lower right corner. For example, Alice cannot build
// either of the fences in the picture below with four corners |(1, 1)|, |(1,
// 3)|, |(3, 1)|, and |(3, 3)|, because:
//
//  • With Alice at |(3, 3)| and Bob at |(1, 1)|, Alice's position is not the
//  upper left corner and Bob's position is not the lower right corner of the
//  fence.
//
//  • With Alice at |(1, 3)| and Bob at |(1, 1)|, Bob's position is not the
//  lower right corner of the fence.
// ![img](https://assets.leetcode.com/uploads/2024/01/04/example0alicebob-1.png)
//
//

LEETCODE_BEGIN_RESOLVING(3027, FindTheNumberOfWaysToPlacePeopleII, Solution);

class Solution {
public:
  int numberOfPairs(vector<vector<int>> &P) {
    sort(P.begin(), P.end(), cmp);
    int n = P.size(), ans = 0;
    for (int i = 0; i < n - 1; i++) {
      int y = numeric_limits<int>::max(), yi = P[i][1];
      for (int j = i + 1; j < n; j++) {
        const int yj = P[j][1];
        if (yj >= yi && y > yj) {
          ans++;
          y = yj;
          if (yi == yj)
            break;
        }
      }
    }
    return ans;
  }

private:
  static bool cmp(const vector<int> &p, const vector<int> &q) {
    return (p[0] == q[0]) ? p[1] < q[1] : p[0] > q[0];
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 1000|
// * |points[i].length == 2|
// * |-10⁹ <= points[i][0], points[i][1] <= 10⁹|
// * All |points[i]| are distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: points = [[1,1],[2,2],[3,3]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3027, FindTheNumberOfWaysToPlacePeopleII,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {1, 1},
      {2, 2},
      {3, 3}
  };
  int expect = 0;
  int actual = solution->numberOfPairs(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: points = [[6,2],[4,4],[2,6]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3027, FindTheNumberOfWaysToPlacePeopleII,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {6, 2},
      {4, 4},
      {2, 6}
  };
  int expect = 2;
  int actual = solution->numberOfPairs(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: points = [[3,1],[1,3],[1,1]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3027, FindTheNumberOfWaysToPlacePeopleII,
                           example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {3, 1},
      {1, 3},
      {1, 1}
  };
  int expect = 2;
  int actual = solution->numberOfPairs(points);
  LCD_EXPECT_EQ(expect, actual);
}
