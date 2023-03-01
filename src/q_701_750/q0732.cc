// Copyright 2023 Naon Lu
//
// This file describes the solution of
// My Calendar III
//
// https://leetcode.com/problems/my-calendar-iii/
//
// Question ID: 732
// Difficult  : Hard
// Solve Date : 2022/10/07 10:11

#include <iosfwd>
#include <map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |732. My Calendar III|:
//
// A |k|-booking happens when |k| events have some non-empty intersection (i.e.,
// there is some time that is common to all |k| events.) You are given some
// events |[startTime, endTime)|, after each given event, return an integer |k|
// representing the maximum |k|-booking between all the previous events.
// Implement the |MyCalendarThree| class:
//
//  • |MyCalendarThree()| Initializes the object.
//
//  • |int book(int startTime, int endTime)| Returns an integer |k| representing
//  the largest integer such that there exists a |k|-booking in the calendar.
//

LEETCODE_BEGIN_RESOLVING(732, MyCalendarIII, MyCalendarThree);

class MyCalendarThree {
private:
  map<int, int> booked;
  int           res;

public:
  MyCalendarThree() {
    booked[0]       = 0;
    booked[1e9 + 1] = 0;
    res             = 0;
  }

  auto split(int x) {
    auto pair = booked.emplace(x, (--booked.upper_bound(x))->second);
    return pair.first;
  }

  int book(int start, int end) {
    auto beg = split(start);
    split(end);
    while (beg->first < end) {
      res = max(res, ++(beg->second));
      ++beg;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(MyCalendarThree);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= startTime < endTime <= 10⁹|
// * At most |400| calls will be made to |book|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["MyCalendarThree", "book", "book", "book", "book", "book", "book"]
// [[], [10, 20], [50, 60], [10, 40], [5, 15], [5, 10], [25, 55]]
// Output: [null, 1, 1, 2, 3, 3, 3]
//
// MyCalendarThree myCalendarThree = new MyCalendarThree();
// myCalendarThree.book(10, 20); // return 1
// myCalendarThree.book(50, 60); // return 1
// myCalendarThree.book(10, 40); // return 2
// myCalendarThree.book(5, 15); // return 3
// myCalendarThree.book(5, 10); // return 3
// myCalendarThree.book(25, 55); // return 3

LEETCODE_SOLUTION_UNITTEST(732, MyCalendarIII, example_1) {
  auto my_calendar_three = MakeMyCalendarThree();
  int  s1_startTime      = 10;
  int  s1_endTime        = 20;
  int  s1_expect         = 1;
  int  s1_actual         = my_calendar_three->book(s1_startTime, s1_endTime);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int s2_startTime = 50;
  int s2_endTime   = 60;
  int s2_expect    = 1;
  int s2_actual    = my_calendar_three->book(s2_startTime, s2_endTime);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int s3_startTime = 10;
  int s3_endTime   = 40;
  int s3_expect    = 2;
  int s3_actual    = my_calendar_three->book(s3_startTime, s3_endTime);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_startTime = 5;
  int s4_endTime   = 15;
  int s4_expect    = 3;
  int s4_actual    = my_calendar_three->book(s4_startTime, s4_endTime);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int s5_startTime = 5;
  int s5_endTime   = 10;
  int s5_expect    = 3;
  int s5_actual    = my_calendar_three->book(s5_startTime, s5_endTime);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  int s6_startTime = 25;
  int s6_endTime   = 55;
  int s6_expect    = 3;
  int s6_actual    = my_calendar_three->book(s6_startTime, s6_endTime);
  LCD_EXPECT_EQ(s6_expect, s6_actual);
}
