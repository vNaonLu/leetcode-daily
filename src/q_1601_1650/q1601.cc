// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Number of Achievable Transfer Requests
//
// https://leetcode.com/problems/maximum-number-of-achievable-transfer-requests/
//
// Question ID: 1601
// Difficult  : Hard
// Solve Date : 2023/07/02 14:24

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1601. Maximum Number of Achievable Transfer Requests|:
//
// We have |n| buildings numbered from |0| to |n - 1|. Each building has a
// number of employees. It's transfer season, and some employees want to change
// the building they reside in. You are given an array |requests| where
// |requests[i] = [fromᵢ, toᵢ]| represents an employee's request to transfer
// from building |fromᵢ| to building |toᵢ|. All buildings are full, so a list of
// requests is achievable only if for each building, the net change in employee
// transfers is zero. This means the number of employees leaving is equal to the
// number of employees moving in. For example if |n = 3| and two employees are
// leaving building |0|, one is leaving building |1|, and one is leaving
// building |2|, there should be two employees moving to building |0|, one
// employee moving to building |1|, and one employee moving to building |2|.
// Return the maximum number of achievable requests.
//
//

LEETCODE_BEGIN_RESOLVING(1601, MaximumNumberOfAchievableTransferRequests,
                         Solution);

class Solution {
public:
  int maximumRequests(int n, vector<vector<int>> &requests) {
    int res = 0;
    int rn  = requests.size();
    int rbn = 1 << rn;

    for (int i = 0; i < rbn; ++i) {
      vector<int> tmp(n, 0);
      int         t = 0;

      for (int j = 0; j < rn; ++j) {
        if (i & (1 << j)) {
          ++t;
          --tmp[requests[j][0]];
          ++tmp[requests[j][1]];
        }
      }

      bool f = true;
      for (int j = 0; j < n; ++j) {
        if (tmp[j] != 0) {
          f = false;
          break;
        }
      }

      if (f) {
        res = max(res, t);
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 20|
// * |1 <= requests.length <= 16|
// * |requests[i].length == 2|
// * |0 <= fromᵢ, toᵢ < n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5, requests = [[0,1],[1,0],[0,1],[1,2],[2,0],[3,4]]
// Output: 5
// Explantion: Let's see the requests:
// From building 0 we have employees x and y and both want to move to
// building 1. From building 1 we have employees a and b and they want to move
// to buildings 2 and 0 respectively. From building 2 we have employee z and
// they want to move to building 0. From building 3 we have employee c and they
// want to move to building 4. From building 4 we don't have any requests. We
// can achieve the requests of users x and b by swapping their places. We can
// achieve the requests of users y, a and z by swapping the places in the 3
// buildings.
//

LEETCODE_SOLUTION_UNITTEST(1601, MaximumNumberOfAchievableTransferRequests,
                           example_1) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> requests = {
      {0, 1},
      {1, 0},
      {0, 1},
      {1, 2},
      {2, 0},
      {3, 4}
  };
  int expect = 5;
  int actual = solution->maximumRequests(n, requests);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, requests = [[0,0],[1,2],[2,1]]
// Output: 3
// Explantion: Let's see the requests:
// From building 0 we have employee x and they want to stay in the same building
// 0. From building 1 we have employee y and they want to move to building 2.
// From building 2 we have employee z and they want to move to building 1.
// We can achieve all the requests.
//

LEETCODE_SOLUTION_UNITTEST(1601, MaximumNumberOfAchievableTransferRequests,
                           example_2) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> requests = {
      {0, 0},
      {1, 2},
      {2, 1}
  };
  int expect = 3;
  int actual = solution->maximumRequests(n, requests);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 4, requests = [[0,3],[3,1],[1,2],[2,0]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(1601, MaximumNumberOfAchievableTransferRequests,
                           example_3) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> requests = {
      {0, 3},
      {3, 1},
      {1, 2},
      {2, 0}
  };
  int expect = 4;
  int actual = solution->maximumRequests(n, requests);
  LCD_EXPECT_EQ(expect, actual);
}
