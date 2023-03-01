// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Snapshot Array
//
// https://leetcode.com/problems/snapshot-array/
//
// Question ID: 1146
// Difficult  : Medium
// Solve Date : 2022/07/14 18:33

#include <iosfwd>
#include <map>
#include <set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1146. Snapshot Array|:
//
// Implement a SnapshotArray that supports the following interface:
//
//  • |SnapshotArray(int length)| initializes an array-like data structure with
//  the given length. Initially, each element equals 0.
//
//  • |void set(index, val)| sets the element at the given |index| to be equal
//  to |val|.
//
//  • |int snap()| takes a snapshot of the array and returns the |snap_id|: the
//  total number of times we called |snap()| minus |1|.
//
//  • |int get(index, snap_id)| returns the value at the given |index|, at the
//  time we took the snapshot with the given |snap_id|
//

LEETCODE_BEGIN_RESOLVING(1146, SnapshotArray, SnapshotArray);

class SnapshotArray {
private:
  int                   snap_idx = 0;
  vector<map<int, int>> data;

public:
  SnapshotArray(int length)
      : data(length,
             {
                 {0, 0}
  }),
        snap_idx{0} {}

  void set(int index, int val) { data[index][snap_idx] = val; }

  int snap() { return snap_idx++; }

  int get(int index, int snap_id) {
    return (--data[index].upper_bound(snap_id))->second;
  }
};

LEETCODE_END_RESOLVING(SnapshotArray);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= length <= 5 * 10⁴|
// * |0 <= index < length|
// * |0 <= val <= 10⁹|
// * |0 <= snap_id < |(the total number of times we call |snap()|)
// * At most |5 * 10⁴| calls will be made to |set|, |snap|, and |get|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["SnapshotArray","set","snap","set","get"]
// [[3],[0,5],[],[0,6],[0,0]]
// Output: [null,null,0,null,5]
//
// SnapshotArray snapshotArr = new SnapshotArray(3); // set the length to be 3
// snapshotArr.set(0,5); // Set array[0] = 5
// snapshotArr.snap(); // Take a snapshot, return snap_id = 0
// snapshotArr.set(0,6);
// snapshotArr.get(0,0); // Get the value of array[0] with snap_id = 0, return 5

LEETCODE_SOLUTION_UNITTEST(1146, SnapshotArray, example_1) {
  int  s0_length      = 3;
  auto snapshot_array = MakeSnapshotArray(s0_length);
  int  s1_index       = 0;
  int  s1_val         = 5;
  snapshot_array->set(s1_index, s1_val);
  int s2_expect = 0;
  int s2_actual = snapshot_array->snap();
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int s3_index = 0;
  int s3_val   = 6;
  snapshot_array->set(s3_index, s3_val);
  int s4_index   = 0;
  int s4_snap_id = 0;
  int s4_expect  = 5;
  int s4_actual  = snapshot_array->get(s4_index, s4_snap_id);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
}
