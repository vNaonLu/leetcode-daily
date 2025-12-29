// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Total Damage With Spell Casting
//
// https://leetcode.com/problems/maximum-total-damage-with-spell-casting/
//
// Question ID: 3186
// Difficult  : Medium
// Solve Date : 2025/10/11 16:47

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3186. Maximum Total Damage With Spell Casting|:
//
// A magician has various spells.
// You are given an array |power|, where each element represents the damage of a
// spell. Multiple spells can have the same damage value. It is a known fact
// that if a magician decides to cast a spell with a damage of |power[i]|, they
// cannot cast any spell with a damage of |power[i] - 2|, |power[i] - 1|,
// |power[i] + 1|, or |power[i] + 2|. Each spell can be cast only once. Return
// the maximum possible total damage that a magician can cast.
//
//

LEETCODE_BEGIN_RESOLVING(3186, MaximumTotalDamageWithSpellCasting, Solution);

class Solution {
public:
  long long maximumTotalDamage(vector<int> &power) {
    unordered_map<int, long long> freq;
    for (int p : power)
      freq[p]++;
    vector<int> keys;
    for (auto &[k, _] : freq)
      keys.push_back(k);
    sort(keys.begin(), keys.end());
    int               n = keys.size();
    vector<long long> dp(n);
    dp[0] = freq[keys[0]] * keys[0];
    for (int i = 1; i < n; i++) {
      long long take = freq[keys[i]] * keys[i];
      int prev = upper_bound(keys.begin(), keys.begin() + i, keys[i] - 3) -
                 keys.begin() - 1;
      if (prev >= 0)
        take += dp[prev];
      dp[i] = max(dp[i - 1], take);
    }
    return dp[n - 1];
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= power.length <= 10⁵|
// * |1 <= power[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: power = [1,1,3,4]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(3186, MaximumTotalDamageWithSpellCasting,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> power    = {1, 1, 3, 4};
  long long   expect   = 6;
  long long   actual   = solution->maximumTotalDamage(power);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: power = [7,1,6,6]
// Output: 13
//

LEETCODE_SOLUTION_UNITTEST(3186, MaximumTotalDamageWithSpellCasting,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> power    = {7, 1, 6, 6};
  long long   expect   = 13;
  long long   actual   = solution->maximumTotalDamage(power);
  LCD_EXPECT_EQ(expect, actual);
}
