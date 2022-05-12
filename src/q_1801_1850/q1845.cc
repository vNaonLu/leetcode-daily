#include <gtest/gtest.h>
#include <iostream>
#include <queue>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 1845.
 *       Seat Reservation Manager
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Design a system that manages the reservation state of ‘n’ seats that
 *   are numbered from ‘1’ to ‘n’
 *   Implement the ‘SeatManager’
 *       -  ‘SeatManager(int n)’ Initializes a ‘SeatManager’ object that
 *   will manage ‘n’ seats numbered from ‘1’ to ‘n’ . All seats are
 *   initially
 *       -  ‘int reserve()’ Fetches the “smallest-numbered” unreserved
 *   seat, reserves it, and returns its
 *       -  ‘void unreserve(int seatNumber)’ Unreserves the seat with the
 *   given ‘seatNumber’ .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ n ≤ 10⁵’
 *   • ‘1 ≤ seatNumber ≤ n’
 *   • For each call to ‘reserve’ , it is guaranteed that there will be at least one unreserved seat.
 *   • For each call to ‘unreserve’ , it is guaranteed that ‘seatNumber’ will be reserved.
 *   • At most ‘10⁵’ calls “in total” will be made to ‘reserve’ and ‘unreserve’ .
 *
 */

struct q1845 : public ::testing::Test {
  // Leetcode answer here
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

    void unreserve(int seatNumber) {
      seat.emplace(seatNumber);
    }
  };

  /**
   * Your SeatManager object will be instantiated and called as such:
   * SeatManager* obj = new SeatManager(n);
   * int param_1 = obj->reserve();
   * obj->unreserve(seatNumber);
   */

  class SeatManager *seat_manager;
};

TEST_F(q1845, sample_input01) {
  int n = 5;
  seat_manager = new SeatManager(n);
  EXPECT_EQ(seat_manager->reserve(), 1);
  EXPECT_EQ(seat_manager->reserve(), 2);
  seat_manager->unreserve(2);
  EXPECT_EQ(seat_manager->reserve(), 2);
  EXPECT_EQ(seat_manager->reserve(), 3);
  EXPECT_EQ(seat_manager->reserve(), 4);
  EXPECT_EQ(seat_manager->reserve(), 5);
  seat_manager->unreserve(5);
  delete seat_manager;
}