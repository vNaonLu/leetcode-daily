// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Merge Similar Items
//
// https://leetcode.com/problems/merge-similar-items/
//
// Question ID: 2363
// Difficult  : Easy
// Solve Date : 2023/02/14 19:39

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2363. Merge Similar Items|:
//
// You are given two 2D integer arrays, |items1| and |items2|, representing two
// sets of items. Each array |items| has the following properties:
//
//  • |items[i] = [valueᵢ, weightᵢ]| where |valueᵢ| represents the value and
//  |weightᵢ| represents the weight of the |iᵗʰ| item.
//
//  • The value of each item in |items| is unique.
// Return a 2D integer array |ret| where |ret[i] = [valueᵢ, weightᵢ]|, with
// |weightᵢ| being the sum of weights of all items with value |valueᵢ|. Note:
// |ret| should be returned in ascending order by value.
//

LEETCODE_BEGIN_RESOLVING(2363, MergeSimilarItems, Solution);

class Solution {
public:
  vector<vector<int>> mergeSimilarItems(vector<vector<int>> &items1,
                                        vector<vector<int>> &items2) {
    vector<vector<int>> res;
    map<int, int>       weight;
    for (auto &v : items1) {
      weight[v[0]] += v[1];
    }
    for (auto &v : items2) {
      weight[v[0]] += v[1];
    }
    for (auto [k, w] : weight) {
      res.emplace_back(vector<int>{k, w});
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= items1.length, items2.length <= 1000|
// * |items1[i].length == items2[i].length == 2|
// * |1 <= valueᵢ, weightᵢ <= 1000|
// * Each |valueᵢ| in |items1| is unique.
// * Each |valueᵢ| in |items2| is unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: items1 = [[1,1],[4,5],[3,8]], items2 = [[3,1],[1,5]]
// Output: [[1,6],[3,9],[4,5]]
//
// The item with value = 1 occurs in items1 with weight = 1 and in items2 with
// weight = 5, total weight = 1 + 5 = 6. The item with value = 3 occurs in
// items1 with weight = 8 and in items2 with weight = 1, total weight = 8 + 1
// = 9. The item with value = 4 occurs in items1 with weight = 5, total weight
// = 5. Therefore, we return [[1,6],[3,9],[4,5]].

LEETCODE_SOLUTION_UNITTEST(2363, MergeSimilarItems, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> items1   = {
      {1, 1},
      {4, 5},
      {3, 8}
  };
  vector<vector<int>> items2 = {
      {3, 1},
      {1, 5}
  };
  vector<vector<int>> expect = {
      {1, 6},
      {3, 9},
      {4, 5}
  };
  vector<vector<int>> actual = solution->mergeSimilarItems(items1, items2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: items1 = [[1,1],[3,2],[2,3]], items2 = [[2,1],[3,2],[1,3]]
// Output: [[1,4],[2,4],[3,4]]
//
// The item with value = 1 occurs in items1 with weight = 1 and in items2 with
// weight = 3, total weight = 1 + 3 = 4. The item with value = 2 occurs in
// items1 with weight = 3 and in items2 with weight = 1, total weight = 3 + 1
// = 4. The item with value = 3 occurs in items1 with weight = 2 and in items2
// with weight = 2, total weight = 2 + 2 = 4. Therefore, we return
// [[1,4],[2,4],[3,4]].

LEETCODE_SOLUTION_UNITTEST(2363, MergeSimilarItems, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> items1   = {
      {1, 1},
      {3, 2},
      {2, 3}
  };
  vector<vector<int>> items2 = {
      {2, 1},
      {3, 2},
      {1, 3}
  };
  vector<vector<int>> expect = {
      {1, 4},
      {2, 4},
      {3, 4}
  };
  vector<vector<int>> actual = solution->mergeSimilarItems(items1, items2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: items1 = [[1,3],[2,2]], items2 = [[7,1],[2,2],[1,4]]
// Output: [[1,7],[2,4],[7,1]]
// Explanation:
// The item with value = 1 occurs in items1 with weight = 3 and in items2 with
// weight = 4, total weight = 3 + 4 = 7. The item with value = 2 occurs in
// items1 with weight = 2 and in items2 with weight = 2, total weight = 2 + 2
// = 4. The item with value = 7 occurs in items2 with weight = 1, total weight
// = 1. Therefore, we return [[1,7],[2,4],[7,1]].
//

LEETCODE_SOLUTION_UNITTEST(2363, MergeSimilarItems, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> items1   = {
      {1, 3},
      {2, 2}
  };
  vector<vector<int>> items2 = {
      {7, 1},
      {2, 2},
      {1, 4}
  };
  vector<vector<int>> expect = {
      {1, 7},
      {2, 4},
      {7, 1}
  };
  vector<vector<int>> actual = solution->mergeSimilarItems(items1, items2);
  LCD_EXPECT_EQ(expect, actual);
}
