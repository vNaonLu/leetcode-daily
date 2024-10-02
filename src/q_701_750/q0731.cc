// Copyright 2024 Naon Lu
//
// This file describes the solution of
// My Calendar II
//
// https://leetcode.com/problems/my-calendar-ii/
//
// Question ID: 731
// Difficult  : Medium
// Solve Date : 2024/09/27 20:43

#include <iosfwd>
#include <map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |731. My Calendar II|:
//
// You are implementing a program to use as your calendar. We can add a new
// event if adding the event will not cause a triple booking. A triple booking
// happens when three events have some non-empty intersection (i.e., some moment
// is common to all the three events.). The event can be represented as a pair
// of integers |start| and |end| that represents a booking on the half-open
// interval |[start, end)|, the range of real numbers |x| such that |start <= x
// < end|. Implement the |MyCalendarTwo| class:
//
//  • |MyCalendarTwo()| Initializes the calendar object.
//
//  • |boolean book(int start, int end)| Returns |true| if the event can be
//  added to the calendar successfully without causing a triple booking.
//  Otherwise, return |false| and do not add the event to the calendar.
//
//

LEETCODE_BEGIN_RESOLVING(731, MyCalendarII, MyCalendarTwo);

class MyCalendarTwo {
public:
  MyCalendarTwo() {}

  bool book(int start, int end) {
    ++ev_[start];
    --ev_[end];
    int ongoing = 0;
    for (auto &[t, change] : ev_) {
      ongoing += change;
      if (ongoing >= 3) {
        --ev_[start];
        ++ev_[end];
        return false;
      }
    }
    return true;
  }

private:
  map<int, int> ev_;
};

LEETCODE_END_RESOLVING(MyCalendarTwo);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |0 <= start < end <= 10⁹|
// * At most |1000| calls will be made to |book|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["MyCalendarTwo", "book", "book", "book", "book", "book", "book"]
// [[], [10, 20], [50, 60], [10, 40], [5, 15], [5, 10], [25, 55]]
// Output: [null, true, true, true, false, true, true]
//

LEETCODE_SOLUTION_UNITTEST(731, MyCalendarII, example_1) {
  auto my_calendar_two = MakeMyCalendarTwo();
  int  s1_start        = 10;
  int  s1_end          = 20;
  bool s1_expect       = true;
  bool s1_actual       = my_calendar_two->book(s1_start, s1_end);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int  s2_start  = 50;
  int  s2_end    = 60;
  bool s2_expect = true;
  bool s2_actual = my_calendar_two->book(s2_start, s2_end);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int  s3_start  = 10;
  int  s3_end    = 40;
  bool s3_expect = true;
  bool s3_actual = my_calendar_two->book(s3_start, s3_end);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int  s4_start  = 5;
  int  s4_end    = 15;
  bool s4_expect = false;
  bool s4_actual = my_calendar_two->book(s4_start, s4_end);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int  s5_start  = 5;
  int  s5_end    = 10;
  bool s5_expect = true;
  bool s5_actual = my_calendar_two->book(s5_start, s5_end);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  int  s6_start  = 25;
  int  s6_end    = 55;
  bool s6_expect = true;
  bool s6_actual = my_calendar_two->book(s6_start, s6_end);
  LCD_EXPECT_EQ(s6_expect, s6_actual);
}
