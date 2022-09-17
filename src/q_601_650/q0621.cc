#include <gtest/gtest.h>
#include <iostream>
#include <leetcode/anyorder.hpp>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 621.
 *      Task Scheduler
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given a characters array ‘tasks’ , representing the tasks a CPU needs
 *   to do, where each letter represents a different task. Tasks could be
 *   done in any order. Each task is done in one unit of time. For each
 *   unit of time, the CPU could complete either one task or just be
 *   However, there is a non-negative integer ‘n’ that represents the
 *   cooldown period betweentwo “same tasks” (the same letter in the
 *   array), that is that there must be at least ‘n’ units of time between
 *   any two same
 *   Return “the least number of units of times that the CPU will take to
 *   finish all the given tasks” .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ task.length ≤ 10⁴’
 *   • ‘tasks[i]’ is upper-case English letter.
 *   • The integer ‘n’ is in the range ‘[0, 100]’ .
 *
 */

struct q621 : public ::testing::Test {
  // Leetcode answer here
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

  class Solution *solution;
};

TEST_F(q621, sample_input01) {
  solution           = new Solution();
  vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
  int          n     = 2;
  int          exp   = 8;
  EXPECT_EQ(solution->leastInterval(tasks, n), exp);
  delete solution;
}

TEST_F(q621, sample_input02) {
  solution           = new Solution();
  vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
  int          n     = 0;
  int          exp   = 6;
  EXPECT_EQ(solution->leastInterval(tasks, n), exp);
  delete solution;
}

TEST_F(q621, sample_input03) {
  solution           = new Solution();
  vector<char> tasks = {'A', 'A', 'A', 'A', 'A', 'A',
                        'B', 'C', 'D', 'E', 'F', 'G'};
  int          n     = 2;
  int          exp   = 16;
  EXPECT_EQ(solution->leastInterval(tasks, n), exp);
  delete solution;
}