// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count Vowel Strings in Ranges
//
// https://leetcode.com/problems/count-vowel-strings-in-ranges/
//
// Question ID: 2559
// Difficult  : Medium
// Solve Date : 2025/01/02 21:24

#include <algorithm>
#include <iosfwd>
#include <ranges>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2559. Count Vowel Strings in Ranges|:
//
// You are given a 0-indexed array of strings |words| and a 2D array of integers
// |queries|. Each query |queries[i] = [lᵢ, rᵢ]| asks us to find the number of
// strings present in the range |lᵢ| to |rᵢ| (both inclusive) of |words| that
// start and end with a vowel. Return an array |ans| of size |queries.length|,
// where |ans[i]| is the answer to the |i|ᵗʰ query. Note that the vowel letters
// are |'a'|, |'e'|, |'i'|, |'o'|, and |'u'|.
//
//

LEETCODE_BEGIN_RESOLVING(2559, CountVowelStringsInRanges, Solution);

class Solution {
public:
  vector<int> vowelStrings(vector<string>      &words,
                           vector<vector<int>> &queries) {
    vector<int> prev(1);
    for (auto &s : words) {
      prev.emplace_back(prev.back() +
                        (isVowel(s.front()) && isVowel(s.back())));
    }

    vector<int> res;
    for (auto &q : queries) {
      res.emplace_back(prev[q[1] + 1] - prev[q[0]]);
    }
    return res;
  }

private:
  static bool isVowel(auto c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 10⁵|
// * |1 <= words[i].length <= 40|
// * |words[i]| consists only of lowercase English letters.
// * |sum(words[i].length) <= 3 * 10⁵|
// * |1 <= queries.length <= 10⁵|
// * |0 <= lᵢ <= rᵢ < words.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["aba","bcb","ece","aa","e"], queries = [[0,2],[1,4],[1,1]]
// Output: [2,3,0]
//

LEETCODE_SOLUTION_UNITTEST(2559, CountVowelStringsInRanges, example_1) {
  auto                solution = MakeSolution();
  vector<string>      words    = {"aba", "bcb", "ece", "aa", "e"};
  vector<vector<int>> queries  = {
      {0, 2},
      {1, 4},
      {1, 1}
  };
  vector<int> expect = {2, 3, 0};
  vector<int> actual = solution->vowelStrings(words, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["a","e","i"], queries = [[0,2],[0,1],[2,2]]
// Output: [3,2,1]
//

LEETCODE_SOLUTION_UNITTEST(2559, CountVowelStringsInRanges, example_2) {
  auto                solution = MakeSolution();
  vector<string>      words    = {"a", "e", "i"};
  vector<vector<int>> queries  = {
      {0, 2},
      {0, 1},
      {2, 2}
  };
  vector<int> expect = {3, 2, 1};
  vector<int> actual = solution->vowelStrings(words, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input:
//  ["bzmxvzjxfddcuznspdcbwiojiqf","mwguoaskvramwgiweogzulcinycosovozppl","uigevazgbrddbcsvrvnngfrvkhmqszjicpieahs","uivcdsboxnraqpokjzaayedf","yalc","bbhlbmpskgxmxosft","vigplemkoni","krdrlctodtmprpxwditvcps","gqjwokkskrb","bslxxpabivbvzkozzvdaykaatzrpe","qwhzcwkchluwdnqjwhabroyyxbtsrsxqjnfpadi","siqbezhkohmgbenbkikcxmvz","ddmaireeouzcvffkcohxus","kjzguljbwsxlrd","gqzuqcljvcpmoqlnrxvzqwoyas","vadguvpsubcwbfbaviedr","nxnorutztxfnpvmukpwuraen","imgvujjeygsiymdxp","rdzkpk","cuap","qcojjumwp","pyqzshwykhtyzdwzakjejqyxbganow","cvxuskhcloxykcu","ul","axzscbjajazvbxffrydajapweci"]
// [[4, 4],[6, 17],[10, 17],[9, 18],[17, 22],[5, 23],[2, 5],[17, 21],[5, 17],[4,
// 8],[7, 17],[16, 19],[7, 12],[9, 20],[13, 23],[1, 5],[19, 19]] Output:
// [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
//

LEETCODE_SOLUTION_UNITTEST(2559, CountVowelStringsInRanges, extra_testcase_1) {
  auto                solution = MakeSolution();
  vector<string>      words    = {"bzmxvzjxfddcuznspdcbwiojiqf",
                                  "mwguoaskvramwgiweogzulcinycosovozppl",
                                  "uigevazgbrddbcsvrvnngfrvkhmqszjicpieahs",
                                  "uivcdsboxnraqpokjzaayedf",
                                  "yalc",
                                  "bbhlbmpskgxmxosft",
                                  "vigplemkoni",
                                  "krdrlctodtmprpxwditvcps",
                                  "gqjwokkskrb",
                                  "bslxxpabivbvzkozzvdaykaatzrpe",
                                  "qwhzcwkchluwdnqjwhabroyyxbtsrsxqjnfpadi",
                                  "siqbezhkohmgbenbkikcxmvz",
                                  "ddmaireeouzcvffkcohxus",
                                  "kjzguljbwsxlrd",
                                  "gqzuqcljvcpmoqlnrxvzqwoyas",
                                  "vadguvpsubcwbfbaviedr",
                                  "nxnorutztxfnpvmukpwuraen",
                                  "imgvujjeygsiymdxp",
                                  "rdzkpk",
                                  "cuap",
                                  "qcojjumwp",
                                  "pyqzshwykhtyzdwzakjejqyxbganow",
                                  "cvxuskhcloxykcu",
                                  "ul",
                                  "axzscbjajazvbxffrydajapweci"};
  vector<vector<int>> queries  = {
      { 4,  4},
      { 6, 17},
      {10, 17},
      { 9, 18},
      {17, 22},
      { 5, 23},
      { 2,  5},
      {17, 21},
      { 5, 17},
      { 4,  8},
      { 7, 17},
      {16, 19},
      { 7, 12},
      { 9, 20},
      {13, 23},
      { 1,  5},
      {19, 19}
  };
  vector<int> expect = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  vector<int> actual = solution->vowelStrings(words, queries);
  LCD_EXPECT_EQ(expect, actual);
}
