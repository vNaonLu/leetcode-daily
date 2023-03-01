// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Design Underground System
//
// https://leetcode.com/problems/design-underground-system/
//
// Question ID: 1396
// Difficult  : Medium
// Solve Date : 2022/04/24 14:23

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1396. Design Underground System|:
//
// An underground railway system is keeping track of customer travel times
// between different stations. They are using this data to calculate the average
// time it takes to travel from one station to another. Implement the
// |UndergroundSystem| class:
//
//  • |void checkIn(int id, string stationName, int t)|
//
//
//    • A customer with a card ID equal to |id|, checks in at the station
//    |stationName| at time |t|.
//
//    • A customer can only be checked into one place at a time.
//
//
//
//  • |void checkOut(int id, string stationName, int t)|
//
//
//    • A customer with a card ID equal to |id|, checks out from the station
//    |stationName| at time |t|.
//
//
//
//  • |double getAverageTime(string startStation, string endStation)|
//
//
//    • Returns the average time it takes to travel from |startStation| to
//    |endStation|.
//
//    • The average time is computed from all the previous traveling times from
//    |startStation| to |endStation| that happened directly, meaning a check in
//    at |startStation| followed by a check out from |endStation|.
//
//    • The time it takes to travel from |startStation| to |endStation| may be
//    different from the time it takes to travel from |endStation| to
//    |startStation|.
//
//    • There will be at least one customer that has traveled from
//    |startStation| to |endStation| before |getAverageTime| is called.
//
//
// You may assume all calls to the |checkIn| and |checkOut| methods are
// consistent. If a customer checks in at time |t₁| then checks out at time
// |t₂|, then |t₁ < t₂|. All events happen in chronological order.  
//

LEETCODE_BEGIN_RESOLVING(1396, DesignUndergroundSystem, UndergroundSystem);

class UndergroundSystem {
private:
  unordered_map<string, unordered_map<string, pair<int, int>>> station_count;
  unordered_map<int, pair<string, int>>                        person;

public:
  UndergroundSystem() {}

  void checkIn(int id, string stationName, int t) {
    person.emplace(id, make_pair(stationName, t));
  }

  void checkOut(int id, string stationName, int t) {
    auto x = person.find(id);
    if (x != person.end()) {
      auto &map         = station_count[x->second.first];
      auto &[time, cnt] = map[stationName];
      time += t - x->second.second;
      ++cnt;
      person.erase(x);
    }
  }

  double getAverageTime(string startStation, string endStation) {
    auto start_find = station_count.find(startStation);
    if (start_find != station_count.end()) {
      auto end_find = start_find->second.find(endStation);
      if (end_find != start_find->second.end()) {
        auto &[t, cnt] = end_find->second;

        return (double)t / (double)cnt;
      }
    }

    return 0.0;
  }
};

LEETCODE_END_RESOLVING(UndergroundSystem);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= id, t <= 10⁶|
// * |1 <= stationName.length, startStation.length, endStation.length <= 10|
// * All strings consist of uppercase and lowercase English letters and digits.
// * There will be at most |2 * 10⁴| calls in total to |checkIn|, |checkOut|,
// and |getAverageTime|.
// * Answers within |10⁻⁵| of the actual value will be accepted.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input:
//  ["UndergroundSystem","checkIn","checkIn","checkIn","checkOut","checkOut","checkOut","getAverageTime","getAverageTime","checkIn","getAverageTime","checkOut","getAverageTime"]
// [[],[45,"Leyton",3],[32,"Paradise",8],[27,"Leyton",10],[45,"Waterloo",15],[27,"Waterloo",20],[32,"Cambridge",22],["Paradise","Cambridge"],["Leyton","Waterloo"],[10,"Leyton",24],["Leyton","Waterloo"],[10,"Waterloo",38],["Leyton","Waterloo"]]
// Output:
// [null,null,null,null,null,null,null,14.00000,11.00000,null,11.00000,null,12.00000]
//
// UndergroundSystem undergroundSystem = new UndergroundSystem();
// undergroundSystem.checkIn(45, "Leyton", 3);
// undergroundSystem.checkIn(32, "Paradise", 8);
// undergroundSystem.checkIn(27, "Leyton", 10);
// undergroundSystem.checkOut(45, "Waterloo", 15); // Customer 45 "Leyton" ->
// "Waterloo" in 15-3 = 12 undergroundSystem.checkOut(27, "Waterloo", 20); //
// Customer 27 "Leyton" -> "Waterloo" in 20-10 = 10
// undergroundSystem.checkOut(32, "Cambridge", 22); // Customer 32 "Paradise" ->
// "Cambridge" in 22-8 = 14 undergroundSystem.getAverageTime("Paradise",
// "Cambridge"); // return 14.00000. One trip "Paradise" -> "Cambridge", (14) /
// 1 = 14 undergroundSystem.getAverageTime("Leyton", "Waterloo"); //
// return 11.00000. Two trips "Leyton" -> "Waterloo", (10 + 12) / 2 = 11
// undergroundSystem.checkIn(10, "Leyton", 24);
// undergroundSystem.getAverageTime("Leyton", "Waterloo"); // return 11.00000
// undergroundSystem.checkOut(10, "Waterloo", 38); // Customer 10 "Leyton" ->
// "Waterloo" in 38-24 = 14 undergroundSystem.getAverageTime("Leyton",
// "Waterloo"); // return 12.00000. Three trips "Leyton" -> "Waterloo", (10 + 12
// + 14) / 3 = 12

LEETCODE_SOLUTION_UNITTEST(1396, DesignUndergroundSystem, example_1) {
  auto   underground_system = MakeUndergroundSystem();
  int    s1_id              = 45;
  string s1_stationName     = "Leyton";
  int    s1_t               = 3;
  underground_system->checkIn(s1_id, s1_stationName, s1_t);
  int    s2_id          = 32;
  string s2_stationName = "Paradise";
  int    s2_t           = 8;
  underground_system->checkIn(s2_id, s2_stationName, s2_t);
  int    s3_id          = 27;
  string s3_stationName = "Leyton";
  int    s3_t           = 10;
  underground_system->checkIn(s3_id, s3_stationName, s3_t);
  int    s4_id          = 45;
  string s4_stationName = "Waterloo";
  int    s4_t           = 15;
  underground_system->checkOut(s4_id, s4_stationName, s4_t);
  int    s5_id          = 27;
  string s5_stationName = "Waterloo";
  int    s5_t           = 20;
  underground_system->checkOut(s5_id, s5_stationName, s5_t);
  int    s6_id          = 32;
  string s6_stationName = "Cambridge";
  int    s6_t           = 22;
  underground_system->checkOut(s6_id, s6_stationName, s6_t);
  string s7_startStation = "Paradise";
  string s7_endStation   = "Cambridge";
  double s7_expect       = 14.00000;
  double s7_actual =
      underground_system->getAverageTime(s7_startStation, s7_endStation);
  LCD_EXPECT_EQ(s7_expect, s7_actual);
  string s8_startStation = "Leyton";
  string s8_endStation   = "Waterloo";
  double s8_expect       = 11.00000;
  double s8_actual =
      underground_system->getAverageTime(s8_startStation, s8_endStation);
  LCD_EXPECT_EQ(s8_expect, s8_actual);
  int    s9_id          = 10;
  string s9_stationName = "Leyton";
  int    s9_t           = 24;
  underground_system->checkIn(s9_id, s9_stationName, s9_t);
  string s10_startStation = "Leyton";
  string s10_endStation   = "Waterloo";
  double s10_expect       = 11.00000;
  double s10_actual =
      underground_system->getAverageTime(s10_startStation, s10_endStation);
  LCD_EXPECT_EQ(s10_expect, s10_actual);
  int    s11_id          = 10;
  string s11_stationName = "Waterloo";
  int    s11_t           = 38;
  underground_system->checkOut(s11_id, s11_stationName, s11_t);
  string s12_startStation = "Leyton";
  string s12_endStation   = "Waterloo";
  double s12_expect       = 12.00000;
  double s12_actual =
      underground_system->getAverageTime(s12_startStation, s12_endStation);
  LCD_EXPECT_EQ(s12_expect, s12_actual);
}

// [Example #2]
//  Input:
//  ["UndergroundSystem","checkIn","checkOut","getAverageTime","checkIn","checkOut","getAverageTime","checkIn","checkOut","getAverageTime"]
// [[],[10,"Leyton",3],[10,"Paradise",8],["Leyton","Paradise"],[5,"Leyton",10],[5,"Paradise",16],["Leyton","Paradise"],[2,"Leyton",21],[2,"Paradise",30],["Leyton","Paradise"]]
// Output: [null,null,null,5.00000,null,null,5.50000,null,null,6.66667]
//
// UndergroundSystem undergroundSystem = new UndergroundSystem();
// undergroundSystem.checkIn(10, "Leyton", 3);
// undergroundSystem.checkOut(10, "Paradise", 8); // Customer 10 "Leyton" ->
// "Paradise" in 8-3 = 5 undergroundSystem.getAverageTime("Leyton", "Paradise");
// // return 5.00000, (5) / 1 = 5 undergroundSystem.checkIn(5, "Leyton", 10);
// undergroundSystem.checkOut(5, "Paradise", 16); // Customer 5 "Leyton" ->
// "Paradise" in 16-10 = 6 undergroundSystem.getAverageTime("Leyton",
// "Paradise"); // return 5.50000, (5 + 6) / 2 = 5.5
// undergroundSystem.checkIn(2, "Leyton", 21);
// undergroundSystem.checkOut(2, "Paradise", 30); // Customer 2 "Leyton" ->
// "Paradise" in 30-21 = 9 undergroundSystem.getAverageTime("Leyton",
// "Paradise"); // return 6.66667, (5 + 6 + 9) / 3 = 6.66667

LEETCODE_SOLUTION_UNITTEST(1396, DesignUndergroundSystem, example_2) {
  auto   underground_system = MakeUndergroundSystem();
  int    s1_id              = 10;
  string s1_stationName     = "Leyton";
  int    s1_t               = 3;
  underground_system->checkIn(s1_id, s1_stationName, s1_t);
  int    s2_id          = 10;
  string s2_stationName = "Paradise";
  int    s2_t           = 8;
  underground_system->checkOut(s2_id, s2_stationName, s2_t);
  string s3_startStation = "Leyton";
  string s3_endStation   = "Paradise";
  double s3_expect       = 5.00000;
  double s3_actual =
      underground_system->getAverageTime(s3_startStation, s3_endStation);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int    s4_id          = 5;
  string s4_stationName = "Leyton";
  int    s4_t           = 10;
  underground_system->checkIn(s4_id, s4_stationName, s4_t);
  int    s5_id          = 5;
  string s5_stationName = "Paradise";
  int    s5_t           = 16;
  underground_system->checkOut(s5_id, s5_stationName, s5_t);
  string s6_startStation = "Leyton";
  string s6_endStation   = "Paradise";
  double s6_expect       = 5.50000;
  double s6_actual =
      underground_system->getAverageTime(s6_startStation, s6_endStation);
  LCD_EXPECT_EQ(s6_expect, s6_actual);
  int    s7_id          = 2;
  string s7_stationName = "Leyton";
  int    s7_t           = 21;
  underground_system->checkIn(s7_id, s7_stationName, s7_t);
  int    s8_id          = 2;
  string s8_stationName = "Paradise";
  int    s8_t           = 30;
  underground_system->checkOut(s8_id, s8_stationName, s8_t);
  string s9_startStation = "Leyton";
  string s9_endStation   = "Paradise";
  double s9_expect       = 6.6666666666666666666666666667;
  double s9_actual =
      underground_system->getAverageTime(s9_startStation, s9_endStation);
  LCD_EXPECT_EQ(s9_expect, s9_actual);
}
