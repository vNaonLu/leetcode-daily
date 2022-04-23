#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 1705.
 *       Maximum Number of Eaten Apples
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   There is a special kind of apple tree that grows apples every day for
 *   ‘n’ days. On the ‘iᵗʰ’ day, the tree grows ‘apples[i]’ apples that
 *   will rot after ‘days[i]’ days, that is on day ‘i + days[i]’ the apples
 *   will be rotten and cannot be eaten. On some days, the apple tree does
 *   not grow any apples, which are denoted by ‘apples[i] = 0’ and ‘days[i]
 *   = 0’
 *   You decided to eat “at most” one apple a day (to keep the doctors
 *   away). Note that you can keep eating after the first ‘n’
 *   Given two integer arrays ‘days’ and ‘apples’ of length ‘n’ , return
 *   “the maximum number of apples you can eat.” 
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘n = apples.length = days.length’
 *   • ‘1 ≤ n ≤ 2 × 10⁴’
 *   • ‘0 ≤ apples[i], days[i] ≤ 2 × 10⁴’
 *   • ‘days[i] = 0’ if and only if ‘apples[i] = 0’ .
 *
 */

struct q1705 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   private:
    using day_count = pair<int, int>;

   public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
      priority_queue<day_count, vector<day_count>, greater<day_count>> pq;
      int res = 0,
          curr_day = 0,
          n = apples.size();
      while (curr_day < n || pq.empty() == false) {
        if (curr_day < n && apples[curr_day] > 0) {
          pq.emplace(curr_day + days[curr_day], apples[curr_day]);
        }

        while (pq.empty() == false) {
          auto [rot_day, remain] = pq.top(); pq.pop();
          if (rot_day > curr_day) {
            if (remain > 0) {
              pq.emplace(rot_day, --remain);
              ++res;
              break;
            }
          }
        }

        ++curr_day;
      }
      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q1705, sample_input01) {
  solution = new Solution();
  vector<int> apples = {1, 2, 3, 5, 2};
  vector<int> days = {3, 2, 1, 4, 2};
  int exp = 7;
  int act = solution->eatenApples(apples, days);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1705, sample_input02) {
  solution = new Solution();
  vector<int> apples = {3, 0, 0, 0, 0, 2};
  vector<int> days = {3, 0, 0, 0, 0, 2};
  int exp = 5;
  int act = solution->eatenApples(apples, days);
  EXPECT_EQ(act, exp);
  delete solution;
}