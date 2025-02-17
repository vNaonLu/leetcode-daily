// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Design a Number Container System
//
// https://leetcode.com/problems/design-a-number-container-system/
//
// Question ID: 2349
// Difficult  : Medium
// Solve Date : 2025/02/08 13:46

#include <iosfwd>
#include <map>
#include <set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2349. Design a Number Container System|:
//
// Design a number container system that can do the following:
//
//  • Insert or Replace a number at the given index in the system.
//
//  • Return the smallest index for the given number in the system.
// Implement the |NumberContainers| class:
//
//  • |NumberContainers()| Initializes the number container system.
//
//  • |void change(int index, int number)| Fills the container at |index| with
//  the |number|. If there is already a number at that |index|, replace it.
//
//  • |int find(int number)| Returns the smallest index for the given |number|,
//  or |-1| if there is no index that is filled by |number| in the system.
//
//

LEETCODE_BEGIN_RESOLVING(2349, DesignANumberContainerSystem, NumberContainers);

class NumberContainers {
public:
  NumberContainers() {}

  void change(int index, int number) {
    auto nit = num_to_ind_.find(number);
    if (nit == num_to_ind_.end()) {
      nit = num_to_ind_.emplace(number, set<int>()).first;
    }

    nit->second.insert(index);
    if (auto [it, ok] = slot_.try_emplace(index, nit); !ok) {
      if (it->second->first == number) {
        return;
      }
      it->second->second.erase(index);
      if (it->second->second.empty()) {
        num_to_ind_.erase(it->second);
      }
      it->second = nit;
    }
  }

  int find(int number) {
    if (auto it = num_to_ind_.find(number); it != num_to_ind_.end()) {
      return *it->second.begin();
    }
    return -1;
  }

private:
  map<int, set<int>>                        num_to_ind_;
  map<int, decltype(num_to_ind_)::iterator> slot_;
};

LEETCODE_END_RESOLVING(NumberContainers);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= index, number <= 10⁹|
// * At most |10⁵| calls will be made in total to |change| and |find|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["NumberContainers", "find", "change", "change", "change", "change",
//  "find", "change", "find"]
// [[], [10], [2, 10], [1, 10], [3, 10], [5, 10], [10], [1, 20], [10]]
// Output: [null, -1, null, null, null, null, 1, null, 2]
//

LEETCODE_SOLUTION_UNITTEST(2349, DesignANumberContainerSystem, example_1) {
  auto number_containers = MakeNumberContainers();
  int  s1_number         = 10;
  int  s1_expect         = -1;
  int  s1_actual         = number_containers->find(s1_number);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int s2_index  = 2;
  int s2_number = 10;
  number_containers->change(s2_index, s2_number);
  int s3_index  = 1;
  int s3_number = 10;
  number_containers->change(s3_index, s3_number);
  int s4_index  = 3;
  int s4_number = 10;
  number_containers->change(s4_index, s4_number);
  int s5_index  = 5;
  int s5_number = 10;
  number_containers->change(s5_index, s5_number);
  int s6_number = 10;
  int s6_expect = 1;
  int s6_actual = number_containers->find(s6_number);
  LCD_EXPECT_EQ(s6_expect, s6_actual);
  int s7_index  = 1;
  int s7_number = 20;
  number_containers->change(s7_index, s7_number);
  int s8_number = 10;
  int s8_expect = 2;
  int s8_actual = number_containers->find(s8_number);
  LCD_EXPECT_EQ(s8_expect, s8_actual);
}

// [Extra Testcase #1]
//  Input: ["NumberContainers","change","find","change","find","find","find"]
// [[],[1,10],[10],[1,20],[10],[20],[30]]
// Output: [null,null,1,null,-1,1,-1]
//

LEETCODE_SOLUTION_UNITTEST(2349, DesignANumberContainerSystem,
                           extra_testcase_1) {
  auto number_containers = MakeNumberContainers();
  int  s1_index          = 1;
  int  s1_number         = 10;
  number_containers->change(s1_index, s1_number);
  int s2_number = 10;
  int s2_expect = 1;
  int s2_actual = number_containers->find(s2_number);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int s3_index  = 1;
  int s3_number = 20;
  number_containers->change(s3_index, s3_number);
  int s4_number = 10;
  int s4_expect = -1;
  int s4_actual = number_containers->find(s4_number);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int s5_number = 20;
  int s5_expect = 1;
  int s5_actual = number_containers->find(s5_number);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  int s6_number = 30;
  int s6_expect = -1;
  int s6_actual = number_containers->find(s6_number);
  LCD_EXPECT_EQ(s6_expect, s6_actual);
}

// [Extra Testcase #2]
//  Input: ["NumberContainers","change","change","find","change","find"]
// [[],[1,10],[1,10],[10],[1,20],[10]]
// Output: [null,null,null,1,null,-1]
//

LEETCODE_SOLUTION_UNITTEST(2349, DesignANumberContainerSystem,
                           extra_testcase_2) {
  auto number_containers = MakeNumberContainers();
  int  s1_index          = 1;
  int  s1_number         = 10;
  number_containers->change(s1_index, s1_number);
  int s2_index  = 1;
  int s2_number = 10;
  number_containers->change(s2_index, s2_number);
  int s3_number = 10;
  int s3_expect = 1;
  int s3_actual = number_containers->find(s3_number);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_index  = 1;
  int s4_number = 20;
  number_containers->change(s4_index, s4_number);
  int s5_number = 10;
  int s5_expect = -1;
  int s5_actual = number_containers->find(s5_number);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
}
