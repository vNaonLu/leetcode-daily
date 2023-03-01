// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Statistics from a Large Sample
//
// https://leetcode.com/problems/statistics-from-a-large-sample/
//
// Question ID: 1093
// Difficult  : Medium
// Solve Date : 2022/05/13 18:33

#include <iosfwd>
#include <limits>
#include <set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"
#include "test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1093. Statistics from a Large Sample|:
//
// You are given a large sample of integers in the range |[0, 255]|. Since the
// sample is so large, it is represented by an array |count| where |count[k]| is
// the number of times that |k| appears in the sample. Calculate the following
// statistics:
//
//  • |minimum|: The minimum element in the sample.
//
//  • |maximum|: The maximum element in the sample.
//
//  • |mean|: The average of the sample, calculated as the total sum of all
//  elements divided by the total number of elements.
//
//  • |median|:
//
//
//    • If the sample has an odd number of elements, then the |median| is the
//    middle element once the sample is sorted.
//
//    • If the sample has an even number of elements, then the |median| is the
//    average of the two middle elements once the sample is sorted.
//
//
//
//  • |mode|: The number that appears the most in the sample. It is guaranteed
//  to be unique.
// Return the statistics of the sample as an array of floating-point numbers
// |[minimum, maximum, mean, median, mode]|. Answers within |10⁻⁵| of the actual
// answer will be accepted.  
//

LEETCODE_BEGIN_RESOLVING(1093, StatisticsFromALargeSample, Solution);

inline static constexpr double kError = 1E-5;

class Solution {
public:
  vector<double> sampleStats(vector<int> &count) {
    vector<double>         res(5, 0);
    vector<pair<int, int>> seq_set;
    int                    max_appear = 0, num = 0;
    res.front() = std::numeric_limits<double>::max();
    for (int i = 0; i < count.size(); ++i) {
      if (count[i] > 0) {
        seq_set.emplace_back(i, count[i]);
        num += count[i];
        res[0] = min<double>(res[0], i);
        res[1] = max<double>(res[1], i);
        res[2] += static_cast<double>(i) * static_cast<double>(count[i]);

        if (max_appear < count[i]) {
          res[4]     = i;
          max_appear = count[i];
        }
      }
    }

    res[2] /= static_cast<double>(num);

    if (num & 1) {
      int median = 0, target = (num + 1) / 2;
      for (auto &[x, cnt] : seq_set) {
        median += cnt;
        if (median >= target) {
          res[3] = x;
          break;
        }
      }
    } else {
      int  median = 0, target = num / 2;
      auto beg = seq_set.begin();
      while (beg != seq_set.end()) {
        auto &[x, cnt] = *(beg++);
        median += cnt;
        if (median > target) {
          res[3] = x;
          break;
        } else if (median == target) {
          res[3] =
              (static_cast<double>(x) + static_cast<double>((*beg).first)) /
              2.0;
          break;
        }
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |count.length == 256|
// * |0 <= count[i] <= 10⁹|
// * |1 <= sum(count) <= 10⁹|
// * The mode of the sample that |count| represents is unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: count =
//  [0,1,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
// Output: [1.00000,3.00000,2.37500,2.50000,3.00000]
//
// The sample represented by count is [1,2,2,2,3,3,3,3].
// The minimum and maximum are 1 and 3 respectively.
// The mean is (1+2+2+2+3+3+3+3) / 8 = 19 / 8 = 2.375.
// Since the size of the sample is even, the median is the average of the two
// middle elements 2 and 3, which is 2.5. The mode is 3 as it appears the most
// in the sample.

LEETCODE_SOLUTION_UNITTEST(1093, StatisticsFromALargeSample, example_1) {
  auto        solution = MakeSolution();
  vector<int> count    = {
      0, 1, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  vector<double> expect = {1.00000, 3.00000, 2.37500, 2.50000, 3.00000};
  vector<double> actual = solution->sampleStats(count);
  LCD_ASSERT_EQ(expect.size(), actual.size());
  for (size_t i = 0; i < expect.size(); ++i) {
    EXPECT_NEAR(expect[i], actual[i], kError);
  }
}

// [Example #2]
//  Input: count =
//  [0,4,3,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
// Output: [1.00000,4.00000,2.18182,2.00000,1.00000]
//
// The sample represented by count is [1,1,1,1,2,2,2,3,3,4,4].
// The minimum and maximum are 1 and 4 respectively.
// The mean is (1+1+1+1+2+2+2+3+3+4+4) / 11 = 24 / 11 = 2.18181818... (for
// display purposes, the output shows the rounded number 2.18182). Since the
// size of the sample is odd, the median is the middle element 2. The mode is 1
// as it appears the most in the sample.

LEETCODE_SOLUTION_UNITTEST(1093, StatisticsFromALargeSample, example_2) {
  auto        solution = MakeSolution();
  vector<int> count    = {
      0, 4, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  vector<double> expect = {1.00000, 4.00000, 2.18182, 2.00000, 1.00000};
  vector<double> actual = solution->sampleStats(count);
  LCD_ASSERT_EQ(expect.size(), actual.size());
  for (size_t i = 0; i < expect.size(); ++i) {
    EXPECT_NEAR(expect[i], actual[i], kError);
  }
}
