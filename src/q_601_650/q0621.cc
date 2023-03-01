// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Task Scheduler
//
// https://leetcode.com/problems/task-scheduler/
//
// Question ID: 621
// Difficult  : Medium
// Solve Date : 2021/11/08 18:26

#include <iosfwd>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |621. Task Scheduler|:
//
// Given a characters array |tasks|, representing the tasks a CPU needs to do,
// where each letter represents a different task. Tasks could be done in any
// order. Each task is done in one unit of time. For each unit of time, the CPU
// could complete either one task or just be idle. However, there is a
// non-negative integer  |n| that represents the cooldown period between two
// same tasks (the same letter in the array), that is that there must be at
// least |n| units of time between any two same tasks. Return the least number
// of units of times that the CPU will take to finish all the given tasks.  
//

LEETCODE_BEGIN_RESOLVING(621, TaskScheduler, Solution);

class Solution {
private:
  template <typename Iterator>
  priority_queue<int> toFreqPriorityQueue(Iterator beg, Iterator end) {
    auto freq = unordered_map<char, int>();
    auto pq   = priority_queue<int>();
    while (beg != end) {
      ++freq[*beg++];
    }
    for (auto &p : freq) {
      pq.emplace(p.second);
    }
    return pq;
  }

public:
  int leastInterval(vector<char> &tasks, int n) {
    auto pq  = toFreqPriorityQueue(tasks.begin(), tasks.end());
    auto res = (int)0;
    while (!pq.empty()) {
      auto tmp = vector<int>();
      auto cnt = (int)n + 1;
      /// at most (n + 1) loop for 1 circle
      while (!pq.empty() && cnt > 0) {
        if (pq.top() > 1) {
          tmp.emplace_back(pq.top() - 1);
        }
        pq.pop();
        ++res;
        --cnt;
      }

      if (cnt > 0 && tmp.size() > 0) {
        /// idle
        res += cnt;
      }

      for (auto x : tmp) {
        pq.emplace(x);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= task.length <= 10⁴|
// * |tasks[i]| is upper-case English letter.
// * The integer |n| is in the range |[0, 100]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: tasks = ["A","A","A","B","B","B"], n = 2
// Output: 8
//
// A -> B -> idle -> A -> B -> idle -> A -> B
// There is at least 2 units of time between any two same tasks.

LEETCODE_SOLUTION_UNITTEST(621, TaskScheduler, example_1) {
  auto         solution = MakeSolution();
  vector<char> tasks    = {'A', 'A', 'A', 'B', 'B', 'B'};
  int          n        = 2;
  int          expect   = 8;
  int          actual   = solution->leastInterval(tasks, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: tasks = ["A","A","A","B","B","B"], n = 0
// Output: 6
//
// On this case any permutation of size 6 would work since n = 0.
// ["A","A","A","B","B","B"]
// ["A","B","A","B","A","B"]
// ["B","B","B","A","A","A"]
// ...
// And so on.

LEETCODE_SOLUTION_UNITTEST(621, TaskScheduler, example_2) {
  auto         solution = MakeSolution();
  vector<char> tasks    = {'A', 'A', 'A', 'B', 'B', 'B'};
  int          n        = 0;
  int          expect   = 6;
  int          actual   = solution->leastInterval(tasks, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
// Output: 16
//
// One possible solution is
// A -> B -> C -> A -> D -> E -> A -> F -> G -> A -> idle -> idle -> A -> idle
// -> idle -> A

LEETCODE_SOLUTION_UNITTEST(621, TaskScheduler, example_3) {
  auto         solution = MakeSolution();
  vector<char> tasks    = {'A', 'A', 'A', 'A', 'A', 'A',
                           'B', 'C', 'D', 'E', 'F', 'G'};
  int          n        = 2;
  int          expect   = 16;
  int          actual   = solution->leastInterval(tasks, n);
  LCD_EXPECT_EQ(expect, actual);
}
