// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Provinces
//
// https://leetcode.com/problems/number-of-provinces/
//
// Question ID: 547
// Difficult  : Medium
// Solve Date : 2021/09/24 15:56

#include <iosfwd>
#include <stack>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |547. Number of Provinces|:
//
// There are |n| cities. Some of them are connected, while some are not. If city
// |a| is connected directly with city |b|, and city |b| is connected directly
// with city |c|, then city |a| is connected indirectly with city |c|. A
// province is a group of directly or indirectly connected cities and no other
// cities outside of the group. You are given an |n x n| matrix |isConnected|
// where |isConnected[i][j] = 1| if the |iᵗʰ| city and the |jᵗʰ| city are
// directly connected, and |isConnected[i][j] = 0| otherwise. Return the total
// number of provinces.  
//

LEETCODE_BEGIN_RESOLVING(547, NumberOfProvinces, Solution);

class Solution {
public:
  int findCircleNum(vector<vector<int>> &isConnected) {
    int n = isConnected.size();
    for (int i = 0; i < n; ++i) {
      if (isConnected[i][i] == 1) {
        stack<int> dir;
        dir.push(i);
        while (!dir.empty()) {
          auto cur = dir.top();
          dir.pop();
          for (int j = 0; j < n; ++j) {
            if (cur == j)
              continue;
            if (isConnected[cur][j] == 1) {
              isConnected[j][cur] = 0;
              isConnected[cur][j] = 0;
              isConnected[j][j]   = 0;
              dir.push(j);
            }
          }
        }
      }
    }
    int res = 0;
    for (int i = 0; i < n; ++i) {
      if (isConnected[i][i] == 1)
        ++res;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 200|
// * |n == isConnected.length|
// * |n == isConnected[i].length|
// * |isConnected[i][j]| is |1| or |0|.
// * |isConnected[i][i] == 1|
// * |isConnected[i][j] == isConnected[j][i]|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(547, NumberOfProvinces, example_1) {
  auto                solution    = MakeSolution();
  vector<vector<int>> isConnected = {
      {1, 1, 0},
      {1, 1, 0},
      {0, 0, 1}
  };
  int expect = 2;
  int actual = solution->findCircleNum(isConnected);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(547, NumberOfProvinces, example_2) {
  auto                solution    = MakeSolution();
  vector<vector<int>> isConnected = {
      {1, 0, 0},
      {0, 1, 0},
      {0, 0, 1}
  };
  int expect = 3;
  int actual = solution->findCircleNum(isConnected);
  LCD_EXPECT_EQ(expect, actual);
}
