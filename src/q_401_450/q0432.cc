// Copyright 2024 Naon Lu
//
// This file describes the solution of
// All O`one Data Structure
//
// https://leetcode.com/problems/all-oone-data-structure/
//
// Question ID: 432
// Difficult  : Hard
// Solve Date : 2024/09/29 12:24

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |432. All O`one Data Structure|:
//
// Design a data structure to store the strings' count with the ability to
// return the strings with minimum and maximum counts. Implement the |AllOne|
// class:
//
//  • |AllOne()| Initializes the object of the data structure.
//
//  • |inc(String key)| Increments the count of the string |key| by |1|. If
//  |key| does not exist in the data structure, insert it with count |1|.
//
//  • |dec(String key)| Decrements the count of the string |key| by |1|. If the
//  count of |key| is |0| after the decrement, remove it from the data
//  structure. It is guaranteed that |key| exists in the data structure before
//  the decrement.
//
//  • |getMaxKey()| Returns one of the keys with the maximal count. If no
//  element exists, return an empty string |""|.
//
//  • |getMinKey()| Returns one of the keys with the minimum count. If no
//  element exists, return an empty string |""|.
// Note that each function must run in |O(1)| average time complexity.
//
//

LEETCODE_BEGIN_RESOLVING(432, AllOOneDataStructure, AllOne);

class AllOne {
public:
  AllOne() {}

  void inc(string key) {
    int cnt = cnt_[key]++;
    if (cnt > 0) {
      freq_[cnt].erase(key);
    }
    freq_[cnt + 1].insert(key);
    if (freq_[cnt].empty()) {
      freq_.erase(cnt);
    }
  }

  void dec(string key) {
    int cnt = cnt_[key]--;
    if (cnt > 0) {
      freq_[cnt].erase(key);
    }
    if (cnt == 1) {
      cnt_.erase(key);
    } else {
      freq_[cnt - 1].insert(key);
    }
    if (freq_[cnt].empty()) {
      freq_.erase(cnt);
    }
  }

  string getMaxKey() {
    return freq_.empty() ? "" : *(freq_.rbegin()->second.begin());
  }

  string getMinKey() {
    return freq_.empty() ? "" : *(freq_.begin()->second.begin());
  }

private:
  unordered_map<string, int>      cnt_;
  map<int, unordered_set<string>> freq_;
};

LEETCODE_END_RESOLVING(AllOne);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= key.length <= 10|
// * |key| consists of lowercase English letters.
// * It is guaranteed that for each call to |dec|, |key| is existing in the data
// structure.
// * At most |5 * 10⁴| calls will be made to |inc|, |dec|, |getMaxKey|, and
// |getMinKey|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc",
//  "getMaxKey", "getMinKey"]
// [[], ["hello"], ["hello"], [], [], ["leet"], [], []]
// Output: [null, null, null, "hello", "hello", null, "hello", "leet"]
//

LEETCODE_SOLUTION_UNITTEST(432, AllOOneDataStructure, example_1) {
  auto   all_one = MakeAllOne();
  string s1_key  = "hello";
  all_one->inc(s1_key);
  string s2_key = "hello";
  all_one->inc(s2_key);
  string s3_expect = "hello";
  string s3_actual = all_one->getMaxKey();
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  string s4_expect = "hello";
  string s4_actual = all_one->getMinKey();
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  string s5_key = "leet";
  all_one->inc(s5_key);
  string s6_expect = "hello";
  string s6_actual = all_one->getMaxKey();
  LCD_EXPECT_EQ(s6_expect, s6_actual);
  string s7_expect = "leet";
  string s7_actual = all_one->getMinKey();
  LCD_EXPECT_EQ(s7_expect, s7_actual);
}
