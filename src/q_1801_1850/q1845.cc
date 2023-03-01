// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Seat Reservation Manager
//
// https://leetcode.com/problems/seat-reservation-manager/
//
// Question ID: 1845
// Difficult  : Medium
// Solve Date : 2022/05/12 18:19

#include <iosfwd>
#include <queue>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1845. Seat Reservation Manager|:
//
// Design a system that manages the reservation state of |n| seats that are
// numbered from |1| to |n|. Implement the |SeatManager| class:
//
//  • |SeatManager(int n)| Initializes a |SeatManager| object that will manage
//  |n| seats numbered from |1| to |n|. All seats are initially available.
//
//  • |int reserve()| Fetches the smallest-numbered unreserved seat, reserves
//  it, and returns its number.
//
//  • |void unreserve(int seatNumber)| Unreserves the seat with the given
//  |seatNumber|.
//  
//

LEETCODE_BEGIN_RESOLVING(1845, SeatReservationManager, SeatManager);

class SeatManager {
private:
  std::priority_queue<int, vector<int>, greater<int>> seat;

public:
  SeatManager(int n) {
    for (int i = 1; i <= n; ++i) {
      seat.emplace(i);
    }
  }

  int reserve() {
    auto res = seat.top();
    seat.pop();

    return res;
  }

  void unreserve(int seatNumber) { seat.emplace(seatNumber); }
};

LEETCODE_END_RESOLVING(SeatManager);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁵|
// * |1 <= seatNumber <= n|
// * For each call to |reserve|, it is guaranteed that there will be at least
// one unreserved seat.
// * For each call to |unreserve|, it is guaranteed that |seatNumber| will be
// reserved.
// * At most |10⁵| calls in total will be made to |reserve| and |unreserve|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["SeatManager", "reserve", "reserve", "unreserve", "reserve",
//  "reserve", "reserve", "reserve", "unreserve"]
// [[5], [], [], [2], [], [], [], [], [5]]
// Output: [null, 1, 2, null, 2, 3, 4, 5, null]
//
// SeatManager seatManager = new SeatManager(5); // Initializes a SeatManager
// with 5 seats. seatManager.reserve(); // All seats are available, so return
// the lowest numbered seat, which is 1. seatManager.reserve(); // The available
// seats are [2,3,4,5], so return the lowest of them, which is 2.
// seatManager.unreserve(2); // Unreserve seat 2, so now the available seats are
// [2,3,4,5]. seatManager.reserve(); // The available seats are [2,3,4,5], so
// return the lowest of them, which is 2. seatManager.reserve(); // The
// available seats are [3,4,5], so return the lowest of them, which is 3.
// seatManager.reserve(); // The available seats are [4,5], so return the lowest
// of them, which is 4. seatManager.reserve(); // The only available seat is
// seat 5, so return 5. seatManager.unreserve(5); // Unreserve seat 5, so now
// the available seats are [5].

LEETCODE_SOLUTION_UNITTEST(1845, SeatReservationManager, example_1) {
  int  s0_n         = 5;
  auto seat_manager = MakeSeatManager(s0_n);
  int  s1_expect    = 1;
  int  s1_actual    = seat_manager->reserve();
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int s2_expect = 2;
  int s2_actual = seat_manager->reserve();
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int s3_seatNumber = 2;
  seat_manager->unreserve(s3_seatNumber);
  int s4_expect = 2;
  int s4_actual = seat_manager->reserve();
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int s5_expect = 3;
  int s5_actual = seat_manager->reserve();
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  int s6_expect = 4;
  int s6_actual = seat_manager->reserve();
  LCD_EXPECT_EQ(s6_expect, s6_actual);
  int s7_expect = 5;
  int s7_actual = seat_manager->reserve();
  LCD_EXPECT_EQ(s7_expect, s7_actual);
  int s8_seatNumber = 5;
  seat_manager->unreserve(s8_seatNumber);
}
