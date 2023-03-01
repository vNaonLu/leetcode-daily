// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Naming a Company
//
// https://leetcode.com/problems/naming-a-company/
//
// Question ID: 2306
// Difficult  : Hard
// Solve Date : 2023/02/09 14:55

#include <iosfwd>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2306. Naming a Company|:
//
// You are given an array of strings |ideas| that represents a list of names to
// be used in the process of naming a company. The process of naming a company
// is as follows:
//
//  1. Choose 2 distinct names from |ideas|, call them |idea^{A}| and
//  |idea^{B}|.
//
//  2. Swap the first letters of |idea^{A}| and |idea^{B}| with each other.
//
//  3. If both of the new names are not found in the original |ideas|, then the
//  name |idea^{A} idea^{B}| (the concatenation of |idea^{A}| and |idea^{B}|,
//  separated by a space) is a valid company name.
//
//  4. Otherwise, it is not a valid name.
// Return the number of distinct valid names for the company.
//

LEETCODE_BEGIN_RESOLVING(2306, NamingACompany, Solution);

class Solution {
public:
  long long distinctNames(vector<string> &ideas) {
    int64_t                       res = 0;
    vector<unordered_set<string>> arr(26);
    for (auto &s : ideas) {
      arr[s[0] - 'a'].emplace(s.substr(1));
    }
    for (int i = 0; i < 25; ++i) {
      for (int j = i + 1; j < 26; ++j) {
        unordered_set<string> tmp;
        tmp.insert(arr[i].begin(), arr[i].end());
        tmp.insert(arr[j].begin(), arr[j].end());
        res += (arr[i].size() - tmp.size()) * (arr[j].size() - tmp.size());
      }
    }
    return res * 2;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= ideas.length <= 5 * 10⁴|
// * |1 <= ideas[i].length <= 10|
// * |ideas[i]| consists of lowercase English letters.
// * All the strings in |ideas| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ideas = ["coffee","donuts","time","toffee"]
// Output: 6
//
// The following selections are valid:
// - ("coffee", "donuts"): The company name created is "doffee conuts".
// - ("donuts", "coffee"): The company name created is "conuts doffee".
// - ("donuts", "time"): The company name created is "tonuts dime".
// - ("donuts", "toffee"): The company name created is "tonuts doffee".
// - ("time", "donuts"): The company name created is "dime tonuts".
// - ("toffee", "donuts"): The company name created is "doffee tonuts".
// Therefore, there are a total of 6 distinct company names.
// The following are some examples of invalid selections:
// - ("coffee", "time"): The name "toffee" formed after swapping already exists
// in the original array.
// - ("time", "toffee"): Both names are still the same after swapping and exist
// in the original array.
// - ("coffee", "toffee"): Both names formed after swapping already exist in the
// original array.

LEETCODE_SOLUTION_UNITTEST(2306, NamingACompany, example_1) {
  auto           solution = MakeSolution();
  vector<string> ideas    = {"coffee", "donuts", "time", "toffee"};
  long           expect   = 6;
  long           actual   = solution->distinctNames(ideas);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: ideas = ["lack","back"]
// Output: 0
//
// There are no valid selections. Therefore, 0 is returned.

LEETCODE_SOLUTION_UNITTEST(2306, NamingACompany, example_2) {
  auto           solution = MakeSolution();
  vector<string> ideas    = {"lack", "back"};
  long           expect   = 0;
  long           actual   = solution->distinctNames(ideas);
  LCD_EXPECT_EQ(expect, actual);
}
