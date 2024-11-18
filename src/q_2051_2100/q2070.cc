// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Most Beautiful Item for Each Query
//
// https://leetcode.com/problems/most-beautiful-item-for-each-query/
//
// Question ID: 2070
// Difficult  : Medium
// Solve Date : 2024/11/12 19:31

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2070. Most Beautiful Item for Each Query|:
//
// You are given a 2D integer array |items| where |items[i] = [priceᵢ, beautyᵢ]|
// denotes the price and beauty of an item respectively. You are also given a
// 0-indexed integer array |queries|. For each |queries[j]|, you want to
// determine the maximum beauty of an item whose price is less than or equal to
// |queries[j]|. If no such item exists, then the answer to this query is |0|.
// Return an array |answer| of the same length as |queries| where |answer[j]| is
// the answer to the |jᵗʰ| query.
//
//

LEETCODE_BEGIN_RESOLVING(2070, MostBeautifulItemForEachQuery, Solution);

class Solution {
public:
  vector<int> maximumBeauty(vector<vector<int>> &items, vector<int> &queries) {
    sort(items.begin(), items.end());
    int         n = items.size();
    vector<int> bt(n);
    bt[0] = items[0][1];
    for (int i = 1; i < n; ++i) {
      bt[i] = max(bt[i - 1], items[i][1]);
    }
    vector<int> res;
    res.reserve(n);
    for (auto x : queries) {
      vector<int> t{x, numeric_limits<int>::max()};
      auto it = upper_bound(items.begin(), items.end(), t) - items.begin();
      if (it == 0) {
        res.emplace_back(0);
      } else {
        res.emplace_back(bt[it - 1]);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= items.length, queries.length <= 10⁵|
// * |items[i].length == 2|
// * |1 <= priceᵢ, beautyᵢ, queries[j] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: items = [[1,2],[3,2],[2,4],[5,6],[3,5]], queries = [1,2,3,4,5,6]
// Output: [2,4,5,5,6,6]
//

LEETCODE_SOLUTION_UNITTEST(2070, MostBeautifulItemForEachQuery, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> items    = {
      {1, 2},
      {3, 2},
      {2, 4},
      {5, 6},
      {3, 5}
  };
  vector<int> queries = {1, 2, 3, 4, 5, 6};
  vector<int> expect  = {2, 4, 5, 5, 6, 6};
  vector<int> actual  = solution->maximumBeauty(items, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: items = [[1,2],[1,2],[1,3],[1,4]], queries = [1]
// Output: [4]
//

LEETCODE_SOLUTION_UNITTEST(2070, MostBeautifulItemForEachQuery, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> items    = {
      {1, 2},
      {1, 2},
      {1, 3},
      {1, 4}
  };
  vector<int> queries = {1};
  vector<int> expect  = {4};
  vector<int> actual  = solution->maximumBeauty(items, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: items = [[10,1000]], queries = [5]
// Output: [0]
//

LEETCODE_SOLUTION_UNITTEST(2070, MostBeautifulItemForEachQuery, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> items    = {
      {10, 1000}
  };
  vector<int> queries = {5};
  vector<int> expect  = {0};
  vector<int> actual  = solution->maximumBeauty(items, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input:
//  [[193,732],[781,962],[864,954],[749,627],[136,746],[478,548],[640,908],[210,799],[567,715],[914,388],[487,853],[533,554],[247,919],[958,150],[193,523],[176,656],[395,469],[763,821],[542,946],[701,676]]
// [885,1445,1580,1309,205,1788,1214,1404,572,1170,989,265,153,151,1479,1180,875,276,1584]
// Output:
// [962,962,962,962,746,962,962,962,946,962,962,919,746,746,962,962,962,919,962]
//

LEETCODE_SOLUTION_UNITTEST(2070, MostBeautifulItemForEachQuery,
                           extra_testcase_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> items    = {
      {193, 732},
      {781, 962},
      {864, 954},
      {749, 627},
      {136, 746},
      {478, 548},
      {640, 908},
      {210, 799},
      {567, 715},
      {914, 388},
      {487, 853},
      {533, 554},
      {247, 919},
      {958, 150},
      {193, 523},
      {176, 656},
      {395, 469},
      {763, 821},
      {542, 946},
      {701, 676}
  };
  vector<int> queries = {885,  1445, 1580, 1309, 205, 1788, 1214,
                         1404, 572,  1170, 989,  265, 153,  151,
                         1479, 1180, 875,  276,  1584};
  vector<int> expect  = {962, 962, 962, 962, 746, 962, 962, 962, 946, 962,
                         962, 919, 746, 746, 962, 962, 962, 919, 962};
  vector<int> actual  = solution->maximumBeauty(items, queries);
  LCD_EXPECT_EQ(expect, actual);
}
