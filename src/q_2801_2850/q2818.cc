// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Apply Operations to Maximize Score
//
// https://leetcode.com/problems/apply-operations-to-maximize-score/
//
// Question ID: 2818
// Difficult  : Hard
// Solve Date : 2025/03/29 13:37

#include <cmath>
#include <iosfwd>
#include <stack>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2818. Apply Operations to Maximize Score|:
//
// You are given an array |nums| of |n| positive integers and an integer |k|.
// Initially, you start with a score of |1|. You have to maximize your score by
// applying the following operation at most |k| times:
//
//  • Choose any non-empty subarray |nums[l, ..., r]| that you haven't chosen
//  previously.
//
//  • Choose an element |x| of |nums[l, ..., r]| with the highest prime score.
//  If multiple such elements exist, choose the one with the smallest index.
//
//  • Multiply your score by |x|.
// Here, |nums[l, ..., r]| denotes the subarray of |nums| starting at index |l|
// and ending at the index |r|, both ends being inclusive. The prime score of an
// integer |x| is equal to the number of distinct prime factors of |x|. For
// example, the prime score of |300| is |3| since |300 = 2 * 2 * 3 * 5 * 5|.
// Return the maximum possible score after applying at most |k| operations.
// Since the answer may be large, return it modulo |10^{9 }+ 7|.
//
//

LEETCODE_BEGIN_RESOLVING(2818, ApplyOperationsToMaximizeScore, Solution);

class Solution {
public:
  int maximumScore(vector<int> &nums, int k) {
    const int n = nums.size();
    isPrime.resize(N + 1, true);
    Sieve();
    vector<int> score(n), left(n), right(n);
    for (int i = 0; i < n; i++) {
      score[i] = prime_score(nums[i]);
    }
    stack<int> st;
    for (int i = 0; i < n; i++) {
      while (!st.empty() && score[i] > score[st.top()])
        st.pop();
      left[i] = st.empty() ? -1 : st.top();
      st.push(i);
    }
    while (!st.empty())
      st.pop();
    for (int i = n - 1; i >= 0; i--) {
      while (!st.empty() && score[i] >= score[st.top()])
        st.pop();
      right[i] = st.empty() ? n : st.top();
      st.push(i);
    }
    vector<pair<int, int>> num_idx(n);
    for (int i = 0; i < n; i++) {
      num_idx[i] = {nums[i], i};
    }
    stable_sort(num_idx.rbegin(), num_idx.rend());
    long long ans = 1;
    for (int i = 0; i < n && k > 0; i++) {
      auto [x, idx] = num_idx[i];
      int exp =
          min((long long)(idx - left[idx]) * (right[idx] - idx), (long long)k);
      ans = (ans * modPow(x, exp) % mod);
      k -= exp;
    }
    return ans;
  }

private:
  void Sieve() {
    if (!prime.empty())
      return;
    isPrime[0] = isPrime[1] = false;
    const int n_sqrt        = sqrt(N);
    for (int i = 2; i <= n_sqrt; i++) {
      if (isPrime[i]) {
        prime.push_back(i);
        for (int j = i * i; j <= N; j += i)
          isPrime[j] = false;
      }
    }
    for (int i = n_sqrt + 1; i <= N; i++) {
      if (isPrime[i])
        prime.push_back(i);
    }
  }
  int prime_score(int x) {
    if (x <= N && isPrime[x])
      return 1;
    int xsqrt = sqrt(x);
    int cnt   = 0;
    for (int p : prime) {
      if (p > xsqrt)
        break;
      if (x % p != 0)
        continue;
      while (x % p == 0)
        x /= p;
      cnt++;
    }
    cnt += (x > 1);
    return cnt;
  }
  long long modPow(long long x, int exp) {
    long long res = 1;
    while (exp > 0) {
      if (exp & 1)
        res = (res * x) % mod;
      x = (x * x) % mod;
      exp >>= 1;
    }
    return res;
  }

  inline static const int N   = sqrt(100000);
  inline static const int mod = 1e9 + 7;
  vector<bool>            isPrime;
  vector<int>             prime;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length == n <= 10⁵|
// * |1 <= nums[i] <= 10⁵|
// * |1 <= k <= min(n * (n + 1) / 2, 10⁹)|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [8,3,9,3,8], k = 2
// Output: 81
//

LEETCODE_SOLUTION_UNITTEST(2818, ApplyOperationsToMaximizeScore, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {8, 3, 9, 3, 8};
  int         k        = 2;
  int         expect   = 81;
  int         actual   = solution->maximumScore(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [19,12,14,6,10,18], k = 3
// Output: 4788
//

LEETCODE_SOLUTION_UNITTEST(2818, ApplyOperationsToMaximizeScore, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {19, 12, 14, 6, 10, 18};
  int         k        = 3;
  int         expect   = 4788;
  int         actual   = solution->maximumScore(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
