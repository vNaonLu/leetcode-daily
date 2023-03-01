#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 815.
 *      Bus Routes
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   You are given an array ‘routes’ representing bus routes where
 *   ‘routes[i]’ is a bus route that the ‘iᵗʰ’ bus repeats
 *       - For example, if ‘routes[0] = [1, 5, 7]’ , this means that the
 *   ‘0ᵗʰ’ bus travels in the sequence ‘1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 ->
 *   ...’
 *   You will start at the bus stop ‘source’ (You are not on any bus
 *   initially), and you want to go to the bus stop ‘target’ . You can
 *   travel between bus stops by buses
 *   Return “the least number of buses you must take to travel from ”
 *   ‘source’ “ to ” ‘target’ . Return ‘-1’ if it is not possible.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ routes.length ≤ 500’ .
 *   • ‘1 ≤ routes[i].length ≤ 10⁵’
 *   • All the values of ‘routes[i]’ are “unique” .
 *   • ‘sum(routes[i].length) ≤ 10⁵’
 *   • ‘0 ≤ routes[i][j] < 10⁶’
 *   • ‘0 ≤ source, target < 10⁶’
 *
 */

struct q815 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  private:
    bool intersect(vector<int> &a, vector<int> &b) {
      int i = 0;
      int j = 0;
      while (i < a.size() && j < b.size()) {
        if (a[i] == b[j]) {
          return true;
        }
        if (a[i] < b[j]) {
          ++i;
        } else {
          ++j;
        }
      }
      return false;
    }

  public:
    int numBusesToDestination(vector<vector<int>> &routes, int source,
                              int target) {
      if (source == target) {
        return 0;
      }
      auto n     = routes.size();
      auto graph = vector<vector<int>>();
      for (auto &p : routes) {
        sort(p.begin(), p.end());
        graph.emplace_back();
      }

      auto seen = unordered_set<int>();
      auto targ = unordered_set<int>();
      auto path = queue<pair<int, int>>();

      for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
          if (intersect(routes[i], routes[j])) {
            graph[i].emplace_back(j);
            graph[j].emplace_back(i);
          }
        }
      }

      for (int i = 0; i < n; ++i) {
        auto find = lower_bound(routes[i].begin(), routes[i].end(), source);
        if (find != routes[i].end() && *find == source) {
          seen.emplace(i);
          path.emplace(i, 0);
        }
        find = lower_bound(routes[i].begin(), routes[i].end(), target);
        if (find != routes[i].end() && *find == target) {
          targ.emplace(i);
        }
      }

      while (!path.empty()) {
        auto [node, depth] = path.front();
        path.pop();
        if (targ.count(node)) {
          return depth + 1;
        }
        for (auto n : graph[node]) {
          if (!seen.count(n)) {
            seen.emplace(n);
            path.emplace(n, depth + 1);
          }
        }
      }

      return -1;
    }
  };

  class Solution *solution;
};

TEST_F(q815, sample_input01) {
  solution                   = new Solution();
  vector<vector<int>> routes = {
      {1, 2, 7},
      {3, 6, 7}
  };
  int source = 1;
  int target = 6;
  int exp    = 2;
  int act    = solution->numBusesToDestination(routes, source, target);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q815, sample_input02) {
  solution                   = new Solution();
  vector<vector<int>> routes = {
      { 7, 12 },
      { 4,  5, 15},
      { 6   },
      { 15, 19},
      { 9, 12, 13}
  };
  int source = 15;
  int target = 12;
  int exp    = -1;
  int act    = solution->numBusesToDestination(routes, source, target);
  EXPECT_EQ(act, exp);
  delete solution;
}