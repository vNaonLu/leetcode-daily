// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Exam Room
//
// https://leetcode.com/problems/exam-room/
//
// Question ID: 855
// Difficult  : Medium
// Solve Date : 2024/08/31 15:03

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |855. Exam Room|:
//
// There is an exam room with |n_| seats in a single row labeled from |0| to |n_
// - 1|. When a student enters the room, they must sit in the seat that
// maximizes the distance to the closest person. If there are multiple such
// seats, they sit in the seat with the lowest number. If no one is in the room,
// then the student sits at seat number |0|. Design a class that simulates the
// mentioned exam room. Implement the |ExamRoom| class:
//
//  • |ExamRoom(int n_)| Initializes the object of the exam room with the number
//  of the seats |n_|.
//
//  • |int seat()| Returns the label of the seat at which the next student will
//  set.
//
//  • |void leave(int p)| Indicates that the student sitting at seat |p| will
//  leave the room. It is guaranteed that there will be a student sitting at
//  seat |p|.
//
//

LEETCODE_BEGIN_RESOLVING(855, ExamRoom, ExamRoom);

class ExamRoom {
public:
  ExamRoom(int n_) : n_{n_} {}

  int seat() {
    if (L_.size() == 0) {
      L_.push_back(0);
      return 0;
    }
    int d = max(L_[0], n_ - 1 - L_[L_.size() - 1]);
    for (int i = 0; i < L_.size() - 1; ++i)
      d = max(d, (L_[i + 1] - L_[i]) / 2);
    if (L_[0] == d) {
      L_.insert(L_.begin(), 0);
      return 0;
    }
    for (int i = 0; i < L_.size() - 1; ++i)
      if ((L_[i + 1] - L_[i]) / 2 == d) {
        L_.insert(L_.begin() + i + 1, (L_[i + 1] + L_[i]) / 2);
        return L_[i + 1];
      }
    L_.push_back(n_ - 1);
    return n_ - 1;
  }

  void leave(int p) {
    for (int i = 0; i < L_.size(); ++i)
      if (L_[i] == p)
        L_.erase(L_.begin() + i);
  }

private:
  int         n_;
  vector<int> L_;
};

LEETCODE_END_RESOLVING(ExamRoom);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n_ <= 10⁹|
// * It is guaranteed that there is a student sitting at seat |p|.
// * At most |10⁴| calls will be made to |seat| and |leave|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["ExamRoom", "seat", "seat", "seat", "seat", "leave", "seat"]
// [[10], [], [], [], [], [4], []]
// Output: [null, 0, 9, 4, 2, null, 5]
//

LEETCODE_SOLUTION_UNITTEST(855, ExamRoom, example_1) {
  int  s0_n      = 10;
  auto exam_room = MakeExamRoom(s0_n);
  int  s1_expect = 0;
  int  s1_actual = exam_room->seat();
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int s2_expect = 9;
  int s2_actual = exam_room->seat();
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int s3_expect = 4;
  int s3_actual = exam_room->seat();
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_expect = 2;
  int s4_actual = exam_room->seat();
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int s5_p = 4;
  exam_room->leave(s5_p);
  int s6_expect = 5;
  int s6_actual = exam_room->seat();
  LCD_EXPECT_EQ(s6_expect, s6_actual);
}
