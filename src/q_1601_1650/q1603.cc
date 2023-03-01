// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Design Parking System
//
// https://leetcode.com/problems/design-parking-system/
//
// Question ID: 1603
// Difficult  : Easy
// Solve Date : 2022/04/25 18:43

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1603. Design Parking System|:
//
// Design a parking system for a parking lot. The parking lot has three kinds of
// parking spaces: big, medium, and small, with a fixed number of slots for each
// size. Implement the |ParkingSystem| class:
//
//  • |ParkingSystem(int big, int medium, int small)| Initializes object of the
//  |ParkingSystem| class. The number of slots for each parking space are given
//  as part of the constructor.
//
//  • |bool addCar(int carType)| Checks whether there is a parking space of
//  |carType| for the car that wants to get into the parking lot. |carType| can
//  be of three kinds: big, medium, or small, which are represented by |1|, |2|,
//  and |3| respectively. A car can only park in a parking space of its
//  |carType|. If there is no space available, return |false|, else park the car
//  in that size space and return |true|.
//  
//

LEETCODE_BEGIN_RESOLVING(1603, DesignParkingSystem, ParkingSystem);

class ParkingSystem {
private:
  vector<int> space;

public:
  ParkingSystem(int big, int medium, int small) : space{big, medium, small} {}

  bool addCar(int carType) {
    if (space[carType - 1] > 0) {
      --space[carType - 1];

      return true;
    }

    return false;
  }
};

LEETCODE_END_RESOLVING(ParkingSystem);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= big, medium, small <= 1000|
// * |carType| is |1|, |2|, or |3|
// * At most |1000| calls will be made to |addCar|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["ParkingSystem", "addCar", "addCar", "addCar", "addCar"]
// [[1, 1, 0], [1], [2], [3], [1]]
// Output: [null, true, true, false, false]
//
// ParkingSystem parkingSystem = new ParkingSystem(1, 1, 0);
// parkingSystem.addCar(1); // return true because there is 1 available slot for
// a big car parkingSystem.addCar(2); // return true because there is 1
// available slot for a medium car parkingSystem.addCar(3); // return false
// because there is no available slot for a small car parkingSystem.addCar(1);
// // return false because there is no available slot for a big car. It is
// already occupied.

LEETCODE_SOLUTION_UNITTEST(1603, DesignParkingSystem, example_1) {
  int  s0_big         = 1;
  int  s0_medium      = 1;
  int  s0_small       = 0;
  auto parking_system = MakeParkingSystem(s0_big, s0_medium, s0_small);
  int  s1_carType     = 1;
  bool s1_expect      = true;
  bool s1_actual      = parking_system->addCar(s1_carType);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int  s2_carType = 2;
  bool s2_expect  = true;
  bool s2_actual  = parking_system->addCar(s2_carType);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int  s3_carType = 3;
  bool s3_expect  = false;
  bool s3_actual  = parking_system->addCar(s3_carType);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int  s4_carType = 1;
  bool s4_expect  = false;
  bool s4_actual  = parking_system->addCar(s4_carType);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
}
