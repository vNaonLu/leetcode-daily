// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Random Pick with Weight
//
// https://leetcode.com/problems/random-pick-with-weight/
//
// Question ID: 528
// Difficult  : Medium
// Solve Date : 2022/07/26 19:19

#include <iosfwd>
#include <random>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |528. Random Pick with Weight|:
//
// You are given a 0-indexed array of positive integers |w| where |w[i]|
// describes the weight of the |iᵗʰ| index. You need to implement the function
// |pickIndex()|, which randomly picks an index in the range |[0, w.length - 1]|
// (inclusive) and returns it. The probability of picking an index |i| is |w[i]
// / sum(w)|.
//
//  • For example, if |w = [1, 3]|, the probability of picking index |0| is |1 /
//  (1 + 3) = 0.25| (i.e., |25%|), and the probability of picking index |1| is
//  |3 / (1 + 3) = 0.75| (i.e., |75%|).
//

LEETCODE_BEGIN_RESOLVING(528, RandomPickWithWeight, Solution);

class Solution {
private:
  mt19937_64                         rng;
  uniform_int_distribution<uint32_t> U_dist;
  vector<int>                        prefix;

public:
  Solution(vector<int> &w) : rng{random_device{}()}, prefix{w} {
    for (auto it = prefix.begin() + 1; it != prefix.end(); ++it) {
      *it += *(it - 1);
    }

    U_dist.param(
        uniform_int_distribution<uint32_t>::param_type(0, prefix.back() - 1));
  }

  int pickIndex() {
    auto t = U_dist(rng);

    return distance(prefix.begin(),
                    upper_bound(prefix.begin(), prefix.end(), t));
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= w.length <= 10⁴|
// * |1 <= w[i] <= 10⁵|
// * |pickIndex| will be called at most |10⁴| times.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["Solution","pickIndex"]
// [[[1]],[]]
// Output: [null,0]
//
// Solution solution = new Solution([1]);
// solution.pickIndex(); // return 0. The only option is to return 0 since there
// is only one element in w.

LEETCODE_SOLUTION_UNITTEST(528, RandomPickWithWeight, example_1) {
  vector<int> s0_w      = {1};
  auto        solution  = MakeSolution(s0_w);
  int         s1_expect = 0;
  int         s1_actual = solution->pickIndex();
  LCD_EXPECT_EQ(s1_expect, s1_actual);
}

// [Example #2]
//  Input:
//  ["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
// [[[1,3]],[],[],[],[],[]]
// Output: [null,1,1,1,1,0]
//
// Solution solution = new Solution([1, 3]);
// solution.pickIndex(); // return 1. It is returning the second element (index
// = 1) that has a probability of 3/4. solution.pickIndex(); // return 1
// solution.pickIndex(); // return 1
// solution.pickIndex(); // return 1
// solution.pickIndex(); // return 0. It is returning the first element (index =
// 0) that has a probability of 1/4. Since this is a randomization problem,
// multiple answers are allowed. All of the following outputs can be considered
// correct: [null,1,1,1,1,0] [null,1,1,1,1,1] [null,1,1,1,0,0] [null,1,1,1,0,1]
// [null,1,0,1,0,0]
// ......
// and so on.

LEETCODE_SOLUTION_UNITTEST(528, RandomPickWithWeight, example_2) {
  vector<int>        s0_w = {1, 3};
  auto               solution  = MakeSolution(s0_w);
  unordered_set<int> must_in = {0, 1};
  int                s1_actual = solution->pickIndex();
  EXPECT_TRUE(must_in.count(s1_actual));
  int s2_actual = solution->pickIndex();
  EXPECT_TRUE(must_in.count(s2_actual));
  int s3_actual = solution->pickIndex();
  EXPECT_TRUE(must_in.count(s3_actual));
  int s4_actual = solution->pickIndex();
  EXPECT_TRUE(must_in.count(s4_actual));
  int s5_actual = solution->pickIndex();
  EXPECT_TRUE(must_in.count(s5_actual));
}
