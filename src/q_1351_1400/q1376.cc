// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Time Needed to Inform All Employees
//
// https://leetcode.com/problems/time-needed-to-inform-all-employees/
//
// Question ID: 1376
// Difficult  : Medium
// Solve Date : 2022/03/18 18:26

#include <iosfwd>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1376. Time Needed to Inform All Employees|:
//
// A company has |n| employees with a unique ID for each employee from |0| to |n
// - 1|. The head of the company is the one with |headID|. Each employee has one
// direct manager given in the |manager| array where |manager[i]| is the direct
// manager of the |i-th| employee, |manager[headID] = -1|. Also, it is
// guaranteed that the subordination relationships have a tree structure. The
// head of the company wants to inform all the company employees of an urgent
// piece of news. He will inform his direct subordinates, and they will inform
// their subordinates, and so on until all employees know about the urgent news.
// The |i-th| employee needs |informTime[i]| minutes to inform all of his direct
// subordinates (i.e., After informTime[i] minutes, all his direct subordinates
// can start spreading the news). Return the number of minutes needed to inform
// all the employees about the urgent news.  
//

LEETCODE_BEGIN_RESOLVING(1376, TimeNeededToInformAllEmployees, Solution);

class Solution {
public:
  int numOfMinutes(int n, int headID, vector<int> &manager,
                   vector<int> &informTime) {
    unordered_map<int, unordered_set<int>> subordination;
    unordered_set<int>                     visited(n);
    for (int i = 0; i < manager.size(); ++i) {
      subordination[manager[i]].insert(i);
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;
    pq.emplace(informTime[headID], headID);

    while (!pq.empty()) {
      auto [time, who] = pq.top();
      pq.pop();
      if (visited.count(who))
        continue;
      visited.insert(who);

      if (visited.size() == n)
        return time;

      for (const auto &p : subordination[who]) {
        if (!visited.count(p)) {
          pq.emplace(time + informTime[p], p);
        }
      }
    }

    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁵|
// * |0 <= headID < n|
// * |manager.length == n|
// * |0 <= manager[i] < n|
// * |manager[headID] == -1|
// * |informTime.length == n|
// * |0 <= informTime[i] <= 1000|
// * |informTime[i] == 0| if employee |i| has no subordinates.
// * It is guaranteed that all the employees can be informed.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 1, headID = 0, manager = [-1], informTime = [0]
// Output: 0
//
// The head of the company is the only employee in the company.

LEETCODE_SOLUTION_UNITTEST(1376, TimeNeededToInformAllEmployees, example_1) {
  auto        solution   = MakeSolution();
  int         n          = 1;
  int         headID     = 0;
  vector<int> manager    = {-1};
  vector<int> informTime = {0};
  int         expect     = 0;
  int         actual = solution->numOfMinutes(n, headID, manager, informTime);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 6, headID = 2, manager = [2,2,-1,2,2,2], informTime =
//  [0,0,1,0,0,0]
// Output: 1
//
// The head of the company with id = 2 is the direct manager of all the
// employees in the company and needs 1 minute to inform them all. The tree
// structure of the employees in the company is shown.

LEETCODE_SOLUTION_UNITTEST(1376, TimeNeededToInformAllEmployees, example_2) {
  auto        solution   = MakeSolution();
  int         n          = 6;
  int         headID     = 2;
  vector<int> manager    = {2, 2, -1, 2, 2, 2};
  vector<int> informTime = {0, 0, 1, 0, 0, 0};
  int         expect     = 1;
  int         actual = solution->numOfMinutes(n, headID, manager, informTime);
  LCD_EXPECT_EQ(expect, actual);
}
