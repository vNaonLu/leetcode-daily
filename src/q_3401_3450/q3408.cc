// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Design Task Manager
//
// https://leetcode.com/problems/design-task-manager/
//
// Question ID: 3408
// Difficult  : Medium
// Solve Date : 2025/09/18 10:35

#include <iosfwd>
#include <queue>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3408. Design Task Manager|:
//
//

LEETCODE_BEGIN_RESOLVING(3408, DesignTaskManager, TaskManager);

class TaskManager {
  using int2 = pair<int, int>;
  unordered_map<int, int2> mp;
  priority_queue<int2>     pq;

public:
  TaskManager(vector<vector<int>> &tasks) {
    mp.reserve(tasks.size());
    for (auto &t : tasks) {
      int u = t[0], i = t[1], p = t[2];
      mp[i] = {p, u};
      pq.emplace(p, i);
    }
  }

  void add(int userId, int taskId, int priority) {
    mp[taskId] = {priority, userId};
    pq.emplace(priority, taskId);
  }

  void edit(int taskId, int newPriority) {
    mp[taskId].first = newPriority;
    pq.emplace(newPriority, taskId);
  }

  void rmv(int taskId) { mp[taskId].first = -1; }

  int execTop() {
    while (!pq.empty()) {
      auto [p, i] = pq.top();
      if (mp.count(i) && mp[i].first == p) {
        pq.pop();
        int u = mp[i].second;
        mp.erase(i); // Remove task after execution
        return u;
      }
      pq.pop(); // Remove
    }
    return -1; // No valid tasks to execute
  }
};
LEETCODE_END_RESOLVING(TaskManager);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= tasks.length <= 10⁵|
// * |0 <= userId <= 10⁵|
// * |0 <= taskId <= 10⁵|
// * |0 <= priority <= 10⁹|
// * |0 <= newPriority <= 10⁹|
// * At most |2 * 10⁵| calls will be made in total to |add|, |edit|, |rmv|, and
// |execTop| methods.
// * The input is generated such that |taskId| will be valid.
///////////////////////////////////////////////////////////////////////////////

LEETCODE_SOLUTION_UNITTEST(3408, DesignTaskManager, example_1) {
  GTEST_SKIP() << "Unittest Not Implemented";
}
