// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Employees to Be Invited to a Meeting
//
// https://leetcode.com/problems/maximum-employees-to-be-invited-to-a-meeting/
//
// Question ID: 2127
// Difficult  : Hard
// Solve Date : 2025/01/26 12:31

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2127. Maximum Employees to Be Invited to a Meeting|:
//
// A company is organizing a meeting and has a list of |n| employees, waiting to
// be invited. They have arranged for a large circular table, capable of seating
// any number of employees. The employees are numbered from |0| to |n - 1|. Each
// employee has a favorite person and they will attend the meeting only if they
// can sit next to their favorite person at the table. The favorite person of an
// employee is not themself. Given a 0-indexed integer array |favorite|, where
// |favorite[i]| denotes the favorite person of the |iᵗʰ| employee, return the
// maximum number of employees that can be invited to the meeting.
//
//

LEETCODE_BEGIN_RESOLVING(2127, MaximumEmployeesToBeInvitedToAMeeting, Solution);

class Solution {
public:
  int maximumInvitations(vector<int> &favorites) {
    int          n = favorites.size();
    vector<int>  inDegree(n, 0), chainLengths(n, 0);
    vector<bool> visited(n, false);

    for (int fav : favorites) {
      inDegree[fav]++;
    }

    queue<int> q;
    for (int i = 0; i < n; ++i) {
      if (inDegree[i] == 0) {
        q.push(i);
      }
    }

    while (!q.empty()) {
      int node = q.front();
      q.pop();
      visited[node] = true;

      int next           = favorites[node];
      chainLengths[next] = chainLengths[node] + 1;
      if (--inDegree[next] == 0) {
        q.push(next);
      }
    }

    int maxCycle = 0, totalChains = 0;
    for (int i = 0; i < n; ++i) {
      if (!visited[i]) {
        int current = i, cycleLength = 0;
        while (!visited[current]) {
          visited[current] = true;
          current          = favorites[current];
          cycleLength++;
        }

        if (cycleLength == 2) {
          totalChains += 2 + chainLengths[i] + chainLengths[favorites[i]];
        } else {
          maxCycle = max(maxCycle, cycleLength);
        }
      }
    }

    return max(maxCycle, totalChains);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == favorite.length|
// * |2 <= n <= 10⁵|
// * |0 <= favorite[i] <= n - 1|
// * |favorite[i] != i|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: favorite = [2,2,1,2]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2127, MaximumEmployeesToBeInvitedToAMeeting,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> favorite = {2, 2, 1, 2};
  int         expect   = 3;
  int         actual   = solution->maximumInvitations(favorite);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: favorite = [1,2,0]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2127, MaximumEmployeesToBeInvitedToAMeeting,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> favorite = {1, 2, 0};
  int         expect   = 3;
  int         actual   = solution->maximumInvitations(favorite);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: favorite = [3,0,1,4,1]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2127, MaximumEmployeesToBeInvitedToAMeeting,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> favorite = {3, 0, 1, 4, 1};
  int         expect   = 4;
  int         actual   = solution->maximumInvitations(favorite);
  LCD_EXPECT_EQ(expect, actual);
}
