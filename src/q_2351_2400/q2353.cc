// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Design a Food Rating System
//
// https://leetcode.com/problems/design-a-food-rating-system/
//
// Question ID: 2353
// Difficult  : Medium
// Solve Date : 2023/12/17 15:49

#include <iosfwd>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2353. Design a Food Rating System|:
//
// Design a food rating system that can do the following:
//
//  • Modify the rating of a food item listed in the system.
//
//  • Return the highest-rated food item for a type of cuisine in the system.
// Implement the |FoodRatings| class:
//
//  • |FoodRatings(String[] foods, String[] cuisines, int[] ratings)|
//  Initializes the system. The food items are described by |foods|, |cuisines|
//  and |ratings|, all of which have a length of |n|.
//
//
//    • |foods[i]| is the name of the |iᵗʰ| food,
//
//    • |cuisines[i]| is the type of cuisine of the |iᵗʰ| food, and
//
//    • |ratings[i]| is the initial rating of the |iᵗʰ| food.
//
//
//
//  • |void changeRating(String food, int newRating)| Changes the rating of the
//  food item with the name |food|.
//
//  • |String highestRated(String cuisine)| Returns the name of the food item
//  that has the highest rating for the given type of |cuisine|. If there is a
//  tie, return the item with the lexicographically smaller name.
// Note that a string |x| is lexicographically smaller than string |y| if |x|
// comes before |y| in dictionary order, that is, either |x| is a prefix of |y|,
// or if |i| is the first position such that |x[i] != y[i]|, then |x[i]| comes
// before |y[i]| in alphabetic order.
//
//

LEETCODE_BEGIN_RESOLVING(2353, DesignAFoodRatingSystem, FoodRatings);

class FoodRatings {
public:
  FoodRatings(vector<string> &foods, vector<string> &cuisines,
              vector<int> &ratings) {
    int n = foods.size();
    for (int i = 0; i < n; ++i) {
      string food    = foods[i];
      string cuisine = cuisines[i];
      int    rating  = ratings[i];
      mp[food]       = {-rating, cuisine};
      rated[cuisine].emplace(-rating, food);
    }
  }

  void changeRating(string food, int newRating) {
    string &cuisine    = mp[food].second;
    int     old_rating = mp[food].first;
    rated[cuisine].erase({old_rating, food});
    rated[cuisine].emplace(-newRating, food);
    mp[food] = {-newRating, cuisine};
  }

  string highestRated(string cuisine) { return rated[cuisine].begin()->second; }

private:
  unordered_map<string, set<pair<int, string>>> rated;
  unordered_map<string, pair<int, string>>      mp;
};

LEETCODE_END_RESOLVING(FoodRatings);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 2 * 10⁴|
// * |n == foods.length == cuisines.length == ratings.length|
// * |1 <= foods[i].length, cuisines[i].length <= 10|
// * |foods[i]|, |cuisines[i]| consist of lowercase English letters.
// * |1 <= ratings[i] <= 10⁸|
// * All the strings in |foods| are distinct.
// * |food| will be the name of a food item in the system across all calls to
// |changeRating|.
// * |cuisine| will be a type of cuisine of at least one food item in the system
// across all calls to |highestRated|.
// * At most |2 * 10⁴| calls in total will be made to |changeRating| and
// |highestRated|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["FoodRatings", "highestRated", "highestRated", "changeRating",
//  "highestRated", "changeRating", "highestRated"]
// [[["kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"], ["korean",
// "japanese", "japanese", "greek", "japanese", "korean"], [9, 12, 8, 15, 14,
// 7]], ["korean"], ["japanese"], ["sushi", 16], ["japanese"], ["ramen", 16],
// ["japanese"]] Output: [null, "kimchi", "ramen", null, "sushi", null, "ramen"]
//
// FoodRatings foodRatings = new FoodRatings(["kimchi", "miso", "sushi",
// "moussaka", "ramen", "bulgogi"], ["korean", "japanese", "japanese", "greek",
// "japanese", "korean"], [9, 12, 8, 15, 14, 7]);
// foodRatings.highestRated("korean"); // return "kimchi"
//  // "kimchi" is the highest rated korean food with a rating of 9.
// foodRatings.highestRated("japanese"); // return "ramen"
//  // "ramen" is the highest rated japanese food with a rating of 14.
// foodRatings.changeRating("sushi", 16); // "sushi" now has a rating of 16.
// foodRatings.highestRated("japanese"); // return "sushi"
//  // "sushi" is the highest rated japanese food with a rating of 16.
// foodRatings.changeRating("ramen", 16); // "ramen" now has a rating of 16.
// foodRatings.highestRated("japanese"); // return "ramen"
//  // Both "sushi" and "ramen" have a rating of 16.
//  // However, "ramen" is lexicographically smaller than "sushi".

LEETCODE_SOLUTION_UNITTEST(2353, DesignAFoodRatingSystem, example_1) {
  vector<string> s0_foods    = {"kimchi",   "miso",  "sushi",
                                "moussaka", "ramen", "bulgogi"};
  vector<string> s0_cuisines = {"korean", "japanese", "japanese",
                                "greek",  "japanese", "korean"};
  vector<int>    s0_ratings  = {9, 12, 8, 15, 14, 7};
  auto   food_ratings = MakeFoodRatings(s0_foods, s0_cuisines, s0_ratings);
  string s1_cuisine   = "korean";
  string s1_expect    = "kimchi";
  string s1_actual    = food_ratings->highestRated(s1_cuisine);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  string s2_cuisine = "japanese";
  string s2_expect  = "ramen";
  string s2_actual  = food_ratings->highestRated(s2_cuisine);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  string s3_food      = "sushi";
  int    s3_newRating = 16;
  food_ratings->changeRating(s3_food, s3_newRating);
  string s4_cuisine = "japanese";
  string s4_expect  = "sushi";
  string s4_actual  = food_ratings->highestRated(s4_cuisine);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  string s5_food      = "ramen";
  int    s5_newRating = 16;
  food_ratings->changeRating(s5_food, s5_newRating);
  string s6_cuisine = "japanese";
  string s6_expect  = "ramen";
  string s6_actual  = food_ratings->highestRated(s6_cuisine);
  LCD_EXPECT_EQ(s6_expect, s6_actual);
}
