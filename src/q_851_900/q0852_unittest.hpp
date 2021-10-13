
#ifndef Q852_UNITTEST_H__
#define Q852_UNITTEST_H__
#include <gtest/gtest.h>

#include "q0852.hpp"
using namespace std;

TEST(q852, sample_input01){
  l852::Solution solver;
  vector<int> arr = {0, 1, 0};
  int exp = 1;
  EXPECT_EQ(solver.peakIndexInMountainArray(arr), exp);
}

TEST(q852, sample_input02){
  l852::Solution solver;
  vector<int> arr = {0, 2, 1, 0};
  int exp = 1;
  EXPECT_EQ(solver.peakIndexInMountainArray(arr), exp);
}

TEST(q852, sample_input03){
  l852::Solution solver;
  vector<int> arr = {0, 10, 5, 2};
  int exp = 1;
  EXPECT_EQ(solver.peakIndexInMountainArray(arr), exp);
}

TEST(q852, sample_input04){
  l852::Solution solver;
  vector<int> arr = {3, 4, 5, 1};
  int exp = 2;
  EXPECT_EQ(solver.peakIndexInMountainArray(arr), exp);
}

TEST(q852, sample_input05){
  l852::Solution solver;
  vector<int> arr = {24, 69, 100, 99, 79, 78, 67, 36, 26, 19};
  int exp = 2;
  EXPECT_EQ(solver.peakIndexInMountainArray(arr), exp);
}

#endif