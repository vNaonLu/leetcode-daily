// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Data Stream as Disjoint Intervals
//
// https://leetcode.com/problems/data-stream-as-disjoint-intervals/
//
// Question ID: 352
// Difficult  : Hard
// Solve Date : 2022/02/21 23:08

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |352. Data Stream as Disjoint Intervals|:
//
// Given a data stream input of non-negative integers |a₁, a₂, ..., aₙ|,
// summarize the numbers seen so far as a list of disjoint intervals. Implement
// the |SummaryRanges| class:
//
//  • |SummaryRanges()| Initializes the object with an empty stream.
//
//  • |void addNum(int value)| Adds the integer |value| to the stream.
//
//  • |int[][] getIntervals()| Returns a summary of the integers in the stream
//  currently as a list of disjoint intervals |[startᵢ, endᵢ]|. The answer
//  should be sorted by |startᵢ|.
//  
//

LEETCODE_BEGIN_RESOLVING(352, DataStreamAsDisjointIntervals, SummaryRanges);

class SummaryRanges {
private:
  vector<bool> memos;
  int          max_value;

public:
  SummaryRanges()
      : memos(10001, false), max_value{numeric_limits<int>::min()} {}

  void addNum(int val) {
    memos[val] = true;
    max_value  = max(max_value, val);
  }

  vector<vector<int>> getIntervals() {
    vector<vector<int>> res;
    for (int i = 0; i <= max_value + 1; ++i) {
      if (memos[i] == false)
        continue;
      int beg = i;

      while (memos[i] && i <= max_value + 1) {
        ++i;
      }

      if (beg != -1 && memos[i] == false) {
        res.emplace_back(vector<int>{beg, i - 1});
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(SummaryRanges);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= value <= 10⁴|
// * At most |3 * 10⁴| calls will be made to |addNum| and |getIntervals|.
// * At most |10²| calls will be made to  |getIntervals|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals",
//  "addNum", "getIntervals", "addNum", "getIntervals", "addNum",
//  "getIntervals"]
// [[], [1], [], [3], [], [7], [], [2], [], [6], []]
// Output: [null, null, [[1, 1]], null, [[1, 1], [3, 3]], null, [[1, 1], [3, 3],
// [7, 7]], null, [[1, 3], [7, 7]], null, [[1, 3], [6, 7]]]
//
// SummaryRanges summaryRanges = new SummaryRanges();
// summaryRanges.addNum(1); // arr = [1]
// summaryRanges.getIntervals(); // return [[1, 1]]
// summaryRanges.addNum(3); // arr = [1, 3]
// summaryRanges.getIntervals(); // return [[1, 1], [3, 3]]
// summaryRanges.addNum(7); // arr = [1, 3, 7]
// summaryRanges.getIntervals(); // return [[1, 1], [3, 3], [7, 7]]
// summaryRanges.addNum(2); // arr = [1, 2, 3, 7]
// summaryRanges.getIntervals(); // return [[1, 3], [7, 7]]
// summaryRanges.addNum(6); // arr = [1, 2, 3, 6, 7]
// summaryRanges.getIntervals(); // return [[1, 3], [6, 7]]

LEETCODE_SOLUTION_UNITTEST(352, DataStreamAsDisjointIntervals, example_1) {
  auto summary_ranges = MakeSummaryRanges();
  int  s1_value       = 1;
  summary_ranges->addNum(s1_value);
  vector<vector<int>> s2_expect = {
      {1, 1}
  };
  vector<vector<int>> s2_actual = summary_ranges->getIntervals();
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int s3_value = 3;
  summary_ranges->addNum(s3_value);
  vector<vector<int>> s4_expect = {
      {1, 1},
      {3, 3}
  };
  vector<vector<int>> s4_actual = summary_ranges->getIntervals();
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int s5_value = 7;
  summary_ranges->addNum(s5_value);
  vector<vector<int>> s6_expect = {
      {1, 1},
      {3, 3},
      {7, 7}
  };
  vector<vector<int>> s6_actual = summary_ranges->getIntervals();
  LCD_EXPECT_EQ(s6_expect, s6_actual);
  int s7_value = 2;
  summary_ranges->addNum(s7_value);
  vector<vector<int>> s8_expect = {
      {1, 3},
      {7, 7}
  };
  vector<vector<int>> s8_actual = summary_ranges->getIntervals();
  LCD_EXPECT_EQ(s8_expect, s8_actual);
  int s9_value = 6;
  summary_ranges->addNum(s9_value);
  vector<vector<int>> s10_expect = {
      {1, 3},
      {6, 7}
  };
  vector<vector<int>> s10_actual = summary_ranges->getIntervals();
  LCD_EXPECT_EQ(s10_expect, s10_actual);
}
