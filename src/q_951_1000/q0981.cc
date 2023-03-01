// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Time Based Key-Value Store
//
// https://leetcode.com/problems/time-based-key-value-store/
//
// Question ID: 981
// Difficult  : Medium
// Solve Date : 2022/07/29 18:41

#include <iosfwd>
#include <map>
#include <set>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |981. Time Based Key-Value Store|:
//
// Design a time-based key-value data structure that can store multiple values
// for the same key at different time stamps and retrieve the key's value at a
// certain timestamp. Implement the |TimeMap| class:
//
//  • |TimeMap()| Initializes the object of the data structure.
//
//  • |void set(String key, String value, int timestamp)| Stores the key |key|
//  with the value |value |at the given time |timestamp|.
//
//  • |String get(String key, int timestamp)| Returns a value such that |set|
//  was called previously, with |timestamp_prev <= timestamp|. If there are
//  multiple such values, it returns the value associated with the largest
//  |timestamp_prev|. If there are no values, it returns |""|.
//

LEETCODE_BEGIN_RESOLVING(981, TimeBasedKeyValueStore, TimeMap);

class TimeMap {
private:
  unordered_map<string, map<int, string>> data;

public:
  TimeMap() {}

  void set(string key, string value, int timestamp) {
    auto &find      = data[key];
    find[timestamp] = value;
  }

  string get(string key, int timestamp) {
    auto find = data.find(key);
    if (find != data.end()) {
      auto tm_find = find->second.upper_bound(timestamp);
      if (tm_find != find->second.begin()) {
        return (--tm_find)->second;
      }
    }

    return "";
  }
};

LEETCODE_END_RESOLVING(TimeMap);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= key.length, value.length <= 100|
// * |key| and |value| consist of lowercase English letters and digits.
// * |1 <= timestamp <= 10⁷|
// * All the timestamps |timestamp| of |set| are strictly increasing.
// * At most |2 * 10⁵| calls will be made to |set| and |get|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["TimeMap", "set", "get", "get", "set", "get", "get"]
// [[], ["foo", "bar", 1], ["foo", 1], ["foo", 3], ["foo", "bar2", 4], ["foo",
// 4], ["foo", 5]] Output: [null, null, "bar", "bar", null, "bar2", "bar2"]
//
// TimeMap timeMap = new TimeMap();
// timeMap.set("foo", "bar", 1); // store the key "foo" and value "bar" along
// with timestamp = 1. timeMap.get("foo", 1); // return "bar" timeMap.get("foo",
// 3); // return "bar", since there is no value corresponding to foo at
// timestamp 3 and timestamp 2, then the only value is at timestamp 1 is "bar".
// timeMap.set("foo", "bar2", 4); // store the key "foo" and value "bar2" along
// with timestamp = 4. timeMap.get("foo", 4); // return "bar2"
// timeMap.get("foo", 5); // return "bar2"

LEETCODE_SOLUTION_UNITTEST(981, TimeBasedKeyValueStore, example_1) {
  auto   time_map     = MakeTimeMap();
  string s1_key       = "foo";
  string s1_value     = "bar";
  int    s1_timestamp = 1;
  time_map->set(s1_key, s1_value, s1_timestamp);
  string s2_key       = "foo";
  int    s2_timestamp = 1;
  string s2_expect    = "bar";
  string s2_actual    = time_map->get(s2_key, s2_timestamp);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  string s3_key       = "foo";
  int    s3_timestamp = 3;
  string s3_expect    = "bar";
  string s3_actual    = time_map->get(s3_key, s3_timestamp);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  string s4_key       = "foo";
  string s4_value     = "bar2";
  int    s4_timestamp = 4;
  time_map->set(s4_key, s4_value, s4_timestamp);
  string s5_key       = "foo";
  int    s5_timestamp = 4;
  string s5_expect    = "bar2";
  string s5_actual    = time_map->get(s5_key, s5_timestamp);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  string s6_key       = "foo";
  int    s6_timestamp = 5;
  string s6_expect    = "bar2";
  string s6_actual    = time_map->get(s6_key, s6_timestamp);
  LCD_EXPECT_EQ(s6_expect, s6_actual);
}
