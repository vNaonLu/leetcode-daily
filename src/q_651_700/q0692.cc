// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Top K Frequent Words
//
// https://leetcode.com/problems/top-k-frequent-words/
//
// Question ID: 692
// Difficult  : Medium
// Solve Date : 2022/05/09 17:55

#include <algorithm>
#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |692. Top K Frequent Words|:
//
// Given an array of strings |words| and an integer |k|, return the |k| most
// frequent strings. Return the answer sorted by the frequency from highest to
// lowest. Sort the words with the same frequency by their lexicographical
// order.  
//

LEETCODE_BEGIN_RESOLVING(692, TopKFrequentWords, Solution);

class Solution {
public:
  vector<string> topKFrequent(vector<string> &words, int k) {
    auto memo = unordered_map<string, int>();
    auto res  = vector<string>();
    for (auto &s : words) {
      auto find = memo.find(s);
      if (find == memo.end()) {
        res.emplace_back(s);
        memo[s] = 1;
      } else {
        ++find->second;
      }
    }
    sort(res.begin(), res.end(), [&](auto &x, auto &y) {
      return memo[x] == memo[y] ? x < y : memo[x] > memo[y];
    });
    res.erase(res.begin() + k, res.end());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 500|
// * |1 <= words[i].length <= 10|
// * |words[i]| consists of lowercase English letters.
// * |k| is in the range |[1, The number of unique words[i]]|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["i","love","leetcode","i","love","coding"], k = 2
// Output: ["i","love"]
//
// "i" and "love" are the two most frequent words.
// Note that "i" comes before "love" due to a lower alphabetical order.

LEETCODE_SOLUTION_UNITTEST(692, TopKFrequentWords, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"i", "love", "leetcode", "i", "love", "coding"};
  int            k        = 2;
  vector<string> expect   = {"i", "love"};
  vector<string> actual   = solution->topKFrequent(words, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words =
//  ["the","day","is","sunny","the","the","the","sunny","is","is"], k = 4
// Output: ["the","is","sunny","day"]
//
// "the", "is", "sunny" and "day" are the four most frequent words, with the
// number of occurrence being 4, 3, 2 and 1 respectively.

LEETCODE_SOLUTION_UNITTEST(692, TopKFrequentWords, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"the", "day", "is",    "sunny", "the",
                             "the", "the", "sunny", "is",    "is"};
  int            k        = 4;
  vector<string> expect   = {"the", "is", "sunny", "day"};
  vector<string> actual   = solution->topKFrequent(words, k);
  LCD_EXPECT_EQ(expect, actual);
}
