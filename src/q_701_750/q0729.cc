// Copyright 2023 Naon Lu
//
// This file describes the solution of
// My Calendar I
//
// https://leetcode.com/problems/my-calendar-i/
//
// Question ID: 729
// Difficult  : Medium
// Solve Date : 2022/05/15 13:05

#include <iosfwd>
#include <map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |729. My Calendar I|:
//
// You are implementing a program to use as your calendar. We can add a new
// event if adding the event will not cause a double booking. A double booking
// happens when two events have some non-empty intersection (i.e., some moment
// is common to both events.). The event can be represented as a pair of
// integers |start| and |end| that represents a booking on the half-open
// interval |[start, end)|, the range of real numbers |x| such that |start <= x
// < end|. Implement the |MyCalendar| class:
//
//  • |MyCalendar()| Initializes the calendar object.
//
//  • |boolean book(int start, int end)| Returns |true| if the event can be
//  added to the calendar successfully without causing a double booking.
//  Otherwise, return |false| and do not add the event to the calendar.
//

LEETCODE_BEGIN_RESOLVING(729, MyCalendarI, MyCalendar);

class MyCalendar {
private:
  map<int, int> itinerary; /// end -> beg

public:
  MyCalendar() {}

  bool book(int start, int end) {
    auto find = itinerary.upper_bound(start);

    if (find == itinerary.end() || end <= find->second) {
      itinerary[end] = start;

      return true;
    }

    return false;
  }
};

LEETCODE_END_RESOLVING(MyCalendar);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= start < end <= 10⁹|
// * At most |1000| calls will be made to |book|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["MyCalendar", "book", "book", "book"]
// [[], [10, 20], [15, 25], [20, 30]]
// Output: [null, true, false, true]
//
// MyCalendar myCalendar = new MyCalendar();
// myCalendar.book(10, 20); // return True
// myCalendar.book(15, 25); // return False, It can not be booked because time
// 15 is already booked by another event. myCalendar.book(20, 30); // return
// True, The event can be booked, as the first event takes every time less than
// 20, but not including 20.

LEETCODE_SOLUTION_UNITTEST(729, MyCalendarI, example_1) {
  auto my_calendar = MakeMyCalendar();
  int  s1_start    = 10;
  int  s1_end      = 20;
  bool s1_expect   = true;
  bool s1_actual   = my_calendar->book(s1_start, s1_end);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int  s2_start  = 15;
  int  s2_end    = 25;
  bool s2_expect = false;
  bool s2_actual = my_calendar->book(s2_start, s2_end);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int  s3_start  = 20;
  int  s3_end    = 30;
  bool s3_expect = true;
  bool s3_actual = my_calendar->book(s3_start, s3_end);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
}
