// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Median from Data Stream
//
// https://leetcode.com/problems/find-median-from-data-stream/
//
// Question ID: 295
// Difficult  : Hard
// Solve Date : 2022/11/12 21:03

#include <iosfwd>
#include <queue>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |295. Find Median from Data Stream|:
//
// The median is the middle value in an ordered integer list. If the size of the
// list is even, there is no middle value, and the median is the mean of the two
// middle values.
//
//  • For example, for |arr = [2,3,4]|, the median is |3|.
//
//  • For example, for |arr = [2,3]|, the median is |(2 + 3) / 2 = 2.5|.
// Implement the MedianFinder class:
//
//  • |MedianFinder()| initializes the |MedianFinder| object.
//
//  • |void addNum(int num)| adds the integer |num| from the data stream to the
//  data structure.
//
//  • |double findMedian()| returns the median of all elements so far. Answers
//  within |10⁻⁵| of the actual answer will be accepted.
//

LEETCODE_BEGIN_RESOLVING(295, FindMedianFromDataStream, MedianFinder);

class MedianFinder {
private:
  priority_queue<int>                            max_heap_;
  priority_queue<int, vector<int>, greater<int>> min_heap_;

public:
  MedianFinder() {}

  void addNum(int num) {
    if (max_heap_.empty() || (max_heap_.top() > num)) {
      max_heap_.emplace(num);
    } else {
      min_heap_.emplace(num);
    }

    if (max_heap_.size() > min_heap_.size() + 1) {
      min_heap_.emplace(max_heap_.top());
      max_heap_.pop();
    } else if (max_heap_.size() + 1 < min_heap_.size()) {
      max_heap_.emplace(min_heap_.top());
      min_heap_.pop();
    }
  }

  double findMedian() {
    if (max_heap_.size() == min_heap_.size()) {
      return max_heap_.empty() ? 0 : (max_heap_.top() + min_heap_.top()) / 2.0;
    } else {
      return max_heap_.size() > min_heap_.size() ? max_heap_.top()
                                                 : min_heap_.top();
    }
  }
};

LEETCODE_END_RESOLVING(MedianFinder);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |-10⁵ <= num <= 10⁵|
// * There will be at least one element in the data structure before calling
// |findMedian|.
// * At most |5 * 10⁴| calls will be made to |addNum| and |findMedian|.
// * If all integer numbers from the stream are in the range |[0, 100]|, how
// would you optimize your solution?
// * If |99%| of all integer numbers from the stream are in the range |[0,
// 100]|, how would you optimize your solution?
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["MedianFinder", "addNum", "addNum", "findMedian", "addNum",
//  "findMedian"]
// [[], [1], [2], [], [3], []]
// Output: [null, null, null, 1.5, null, 2.0]
//
// MedianFinder medianFinder = new MedianFinder();
// medianFinder.addNum(1); // arr = [1]
// medianFinder.addNum(2); // arr = [1, 2]
// medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
// medianFinder.addNum(3); // arr[1, 2, 3]
// medianFinder.findMedian(); // return 2.0

LEETCODE_SOLUTION_UNITTEST(295, FindMedianFromDataStream, example_1) {
  auto median_finder = MakeMedianFinder();
  int  s1_num        = 1;
  median_finder->addNum(s1_num);
  int s2_num = 2;
  median_finder->addNum(s2_num);
  double s3_expect = 1.5;
  double s3_actual = median_finder->findMedian();
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_num = 3;
  median_finder->addNum(s4_num);
  double s5_expect = 2.0;
  double s5_actual = median_finder->findMedian();
  LCD_EXPECT_EQ(s5_expect, s5_actual);
}
