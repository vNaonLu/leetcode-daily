// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count the Number of Computer Unlocking Permutations
//
// https://leetcode.com/problems/count-the-number-of-computer-unlocking-permutations/
//
// Question ID: 3577
// Difficult  : Medium
// Solve Date : 2025/12/10 19:55

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3577. Count the Number of Computer Unlocking Permutations|:
//
// You are given an array |complexity| of length |n|.
// There are |n| locked computers in a room with labels from 0 to |n - 1|, each
// with its own unique password. The password of the computer |i| has a
// complexity |complexity[i]|. The password for the computer labeled 0 is
// already decrypted and serves as the root. All other computers must be
// unlocked using it or another previously unlocked computer, following this
// information:
//
//  • You can decrypt the password for the computer |i| using the password for
//  computer |j|, where |j| is any integer less than |i| with a lower
//  complexity. (i.e. |j < i| and |complexity[j] < complexity[i]|)
//
//  • To decrypt the password for computer |i|, you must have already unlocked a
//  computer |j| such that |j < i| and |complexity[j] < complexity[i]|.
// Find the number of permutations of |[0, 1, 2, ..., (n - 1)]| that represent a
// valid order in which the computers can be unlocked, starting from computer 0
// as the only initially unlocked one. Since the answer may be large, return it
// modulo 10⁹ + 7. Note that the password for the computer with label 0 is
// decrypted, and not the computer with the first position in the permutation.
//
//

LEETCODE_BEGIN_RESOLVING(3577, CountTheNumberOfComputerUnlockingPermutations,
                         Solution);

class Solution {
public:
  int countPermutations(vector<int> &complexity) {
    int x0   = complexity[0];
    int x1   = *min_element(complexity.begin() + 1, complexity.end());
    int kMod = 1e9 + 7;
    int n    = complexity.size();

    if (x0 >= x1) {
      return 0;
    }

    int64_t res = 1;
    for (int i = 1; i <= n - 1; ++i) {
      res *= i;
      if (res >= kMod) {
        res %= kMod;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= complexity.length <= 10⁵|
// * |1 <= complexity[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: complexity = [1,2,3]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3577, CountTheNumberOfComputerUnlockingPermutations,
                           example_1) {
  auto        solution   = MakeSolution();
  vector<int> complexity = {1, 2, 3};
  int         expect     = 2;
  int         actual     = solution->countPermutations(complexity);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: complexity = [3,3,3,4,4,4]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3577, CountTheNumberOfComputerUnlockingPermutations,
                           example_2) {
  auto        solution   = MakeSolution();
  vector<int> complexity = {3, 3, 3, 4, 4, 4};
  int         expect     = 0;
  int         actual     = solution->countPermutations(complexity);
  LCD_EXPECT_EQ(expect, actual);
}
