// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Count Tested Devices After Test Operations
//
// https://leetcode.com/problems/count-tested-devices-after-test-operations/
//
// Question ID: 2960
// Difficult  : Easy
// Solve Date : 2024/02/10 11:50

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2960. Count Tested Devices After Test Operations|:
//
// You are given a 0-indexed integer array |batteryPercentages| having length
// |n|, denoting the battery percentages of |n| 0-indexed devices. Your task is
// to test each device |i| in order from |0| to |n - 1|, by performing the
// following test operations:
//
//  • If |batteryPercentages[i]| is greater than |0|:
//
//
//    • Increment the count of tested devices.
//
//    • Decrease the battery percentage of all devices with indices |j| in the
//    range |[i + 1, n - 1]| by |1|, ensuring their battery percentage never
//    goes below |0|, i.e, |batteryPercentages[j] = max(0, batteryPercentages[j]
//    - 1)|.
//
//    • Move to the next device.
//
//
//
//  • Otherwise, move to the next device without performing any test.
// Return an integer denoting the number of devices that will be tested after
// performing the test operations in order.
//
//

LEETCODE_BEGIN_RESOLVING(2960, CountTestedDevicesAfterTestOperations, Solution);

class Solution {
public:
  int countTestedDevices(vector<int> &batteryPercentages) {
    int res = 0;
    for (auto x : batteryPercentages) {
      if (x - res > 0) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n == batteryPercentages.length <= 100 |
// * |0 <= batteryPercentages[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: batteryPercentages = [1,1,2,1,3]
// Output: 3
//
// Performing the test operations in order starting from device 0:
// At device 0, batteryPercentages[0] > 0, so there is now 1 tested device, and
// batteryPercentages becomes [1,0,1,0,2]. At device 1, batteryPercentages[1] ==
// 0, so we move to the next device without testing. At device 2,
// batteryPercentages[2] > 0, so there are now 2 tested devices, and
// batteryPercentages becomes [1,0,1,0,1]. At device 3, batteryPercentages[3] ==
// 0, so we move to the next device without testing. At device 4,
// batteryPercentages[4] > 0, so there are now 3 tested devices, and
// batteryPercentages stays the same. So, the answer is 3.

LEETCODE_SOLUTION_UNITTEST(2960, CountTestedDevicesAfterTestOperations,
                           example_1) {
  auto        solution           = MakeSolution();
  vector<int> batteryPercentages = {1, 1, 2, 1, 3};
  int         expect             = 3;
  int         actual = solution->countTestedDevices(batteryPercentages);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: batteryPercentages = [0,1,2]
// Output: 2
//
// Performing the test operations in order starting from device 0:
// At device 0, batteryPercentages[0] == 0, so we move to the next device
// without testing. At device 1, batteryPercentages[1] > 0, so there is now 1
// tested device, and batteryPercentages becomes [0,1,1]. At device 2,
// batteryPercentages[2] > 0, so there are now 2 tested devices, and
// batteryPercentages stays the same. So, the answer is 2.

LEETCODE_SOLUTION_UNITTEST(2960, CountTestedDevicesAfterTestOperations,
                           example_2) {
  auto        solution           = MakeSolution();
  vector<int> batteryPercentages = {0, 1, 2};
  int         expect             = 2;
  int         actual = solution->countTestedDevices(batteryPercentages);
  LCD_EXPECT_EQ(expect, actual);
}
