// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Search Suggestions System
//
// https://leetcode.com/problems/search-suggestions-system/
//
// Question ID: 1268
// Difficult  : Medium
// Solve Date : 2022/06/19 13:18

#include <algorithm>
#include <array>
#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1268. Search Suggestions System|:
//
// You are given an array of strings |products| and a string |searchWord|.
// Design a system that suggests at most three product names from |products|
// after each character of |searchWord| is typed. Suggested products should have
// common prefix with |searchWord|. If there are more than three products with a
// common prefix return the three lexicographically minimums products. Return a
// list of lists of the suggested products after each character of |searchWord|
// is typed.
//

LEETCODE_BEGIN_RESOLVING(1268, SearchSuggestionsSystem, Solution);

class Solution {
private:
  struct Trie {
    array<unique_ptr<Trie>, 26> next;
    bool                        is_end = {false};
    vector<string>              suggested;
  };

  template <typename iterator>
  unique_ptr<Trie> build_trie(iterator beg, iterator end) {
    auto res = make_unique<Trie>();
    while (beg != end) {
      auto &sv = *beg++;
      Trie *p  = res.get();

      for (auto &c : sv) {
        auto &next = p->next[c - 'a'];
        if (nullptr == next) {
          next = make_unique<Trie>();
        }
        if (next->suggested.size() < 3) {
          next->suggested.emplace_back(sv);
        }
        p = next.get();
      }

      p->is_end = true;
    }

    return res;
  }

public:
  vector<vector<string>> suggestedProducts(vector<string> &products,
                                           string          searchWord) {
    vector<vector<string>> res;
    sort(products.begin(), products.end());
    auto dict = build_trie(products.begin(), products.end());
    auto p    = dict.get();

    for (auto &c : searchWord) {
      auto next = p->next[c - 'a'].get();
      if (nullptr != next) {
        res.emplace_back(next->suggested);
      } else
        break;
      p = next;
    }
    res.resize(searchWord.size());

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= products.length <= 1000|
// * |1 <= products[i].length <= 3000|
// * |1 <= sum(products[i].length) <= 2 * 10⁴|
// * All the strings of |products| are unique.
// * |products[i]| consists of lowercase English letters.
// * |1 <= searchWord.length <= 1000|
// * |searchWord| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: products = ["mobile","mouse","moneypot","monitor","mousepad"],
//  searchWord = "mouse"
// Output:
// [["mobile","moneypot","monitor"],["mobile","moneypot","monitor"],["mouse","mousepad"],["mouse","mousepad"],["mouse","mousepad"]]
//
// products sorted lexicographically =
// ["mobile","moneypot","monitor","mouse","mousepad"]. After typing m and mo all
// products match and we show user ["mobile","moneypot","monitor"]. After typing
// mou, mous and mouse the system suggests ["mouse","mousepad"].

LEETCODE_SOLUTION_UNITTEST(1268, SearchSuggestionsSystem, example_1) {
  auto                   solution   = MakeSolution();
  vector<string>         products   = {"mobile", "mouse", "moneypot", "monitor",
                                       "mousepad"};
  string                 searchWord = "mouse";
  vector<vector<string>> expect     = {
      {"mobile", "moneypot", "monitor"},
      {"mobile", "moneypot", "monitor"},
      {"mouse", "mousepad"},
      {"mouse", "mousepad"},
      {"mouse", "mousepad"}
  };
  vector<vector<string>> actual =
      solution->suggestedProducts(products, searchWord);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: products = ["havana"], searchWord = "havana"
// Output: [["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
//
// The only word "havana" will be always suggested while typing the search word.

LEETCODE_SOLUTION_UNITTEST(1268, SearchSuggestionsSystem, example_2) {
  auto                   solution   = MakeSolution();
  vector<string>         products   = {"havana"};
  string                 searchWord = "havana";
  vector<vector<string>> expect     = {{"havana"}, {"havana"}, {"havana"},
                                       {"havana"}, {"havana"}, {"havana"}};
  vector<vector<string>> actual =
      solution->suggestedProducts(products, searchWord);
  LCD_EXPECT_EQ(expect, actual);
}
