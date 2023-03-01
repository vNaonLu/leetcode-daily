#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/**
 * The file is generated by LeetCodeDailyTools
 *
 * 502.
 *      IPO
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Suppose LeetCode will start its “IPO” soon. In order to sell a good
 *   price of its shares to Venture Capital, LeetCode would like to work on
 *   some projects to increase its capital before the “IPO” . Since it has
 *   limited resources, it can only finish at most ‘k’ distinct projects
 *   before the “IPO” . Help LeetCode design the best way to maximize its
 *   total capital after finishing at most ‘k’ distinct
 *   You are given ‘n’ projects where the ‘iᵗʰ’ project has a pure profit
 *   ‘profits[i]’ and a minimum capital of ‘capital[i]’ is needed to start
 *   Initially, you have ‘w’ capital. When you finish a project, you will
 *   obtain its pure profit and the profit will be added to your total
 *   Pick a list of “at most” ‘k’ distinct projects from given projects to
 *   “maximize your final capital” , and return “the final maximized
 *   capital”
 *   The answer is guaranteed to fit in a 32-bit signed integer.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ k ≤ 10⁵’
 *   • ‘0 ≤ w ≤ 10⁹’
 *   • ‘n = profits.length’
 *   • ‘n = capital.length’
 *   • ‘1 ≤ n ≤ 10⁵’
 *   • ‘0 ≤ profits[i] ≤ 10⁴’
 *   • ‘0 ≤ capital[i] ≤ 10⁹’
 *
 * see more details: https://leetcode.com/problems/ipo/
 */

struct q502 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  public:
    int findMaximizedCapital(int k, int w, vector<int> &profits,
                             vector<int> &capital) {
      priority_queue<pair<int, int>> max_heap;
      priority_queue<pair<int, int>, vector<pair<int, int>>,
                     greater<pair<int, int>>>
          min_heap;
      for (int i = 0; i < profits.size(); ++i) {
        min_heap.emplace(capital[i], profits[i]);
      }

      while (k > 0) {
        while (!min_heap.empty() && min_heap.top().first <= w) {
          auto p = min_heap.top();
          min_heap.pop();
          max_heap.emplace(p.second, p.first);
        }
        if (!max_heap.empty()) {
          w += max_heap.top().first;
          max_heap.pop();
          --k;
        } else {
          break;
        }
      }
      return w;
    }
  };

  class Solution *solution;
};

TEST_F(q502, sample_input01) {
  solution            = new Solution();
  int         k       = 2;
  int         w       = 0;
  vector<int> profits = {1, 2, 3};
  vector<int> capital = {0, 1, 1};
  int         exp     = 4;
  int         act     = solution->findMaximizedCapital(k, w, profits, capital);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q502, sample_input02) {
  solution            = new Solution();
  int         k       = 3;
  int         w       = 0;
  vector<int> profits = {1, 2, 3};
  vector<int> capital = {0, 1, 2};
  int         exp     = 6;
  int         act     = solution->findMaximizedCapital(k, w, profits, capital);
  EXPECT_EQ(act, exp);
  delete solution;
}