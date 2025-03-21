// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find All Possible Recipes from Given Supplies
//
// https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies/
//
// Question ID: 2115
// Difficult  : Medium
// Solve Date : 2025/03/21 15:45

#include <iosfwd>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2115. Find All Possible Recipes from Given Supplies|:
//
// You have information about |n| different recipes. You are given a string
// array |recipes| and a 2D string array |ingredients|. The |iᵗʰ| recipe has the
// name |recipes[i]|, and you can create it if you have all the needed
// ingredients from |ingredients[i]|. A recipe can also be an ingredient for
// other recipes, i.e., |ingredients[i]| may contain a string that is in
// |recipes|. You are also given a string array |supplies| containing all the
// ingredients that you initially have, and you have an infinite supply of all
// of them. Return a list of all the recipes that you can create. You may return
// the answer in any order. Note that two recipes may contain each other in
// their ingredients.
//
//

LEETCODE_BEGIN_RESOLVING(2115, FindAllPossibleRecipesFromGivenSupplies,
                         Solution);

class Solution {
public:
  vector<string> findAllRecipes(vector<string>         &recipes,
                                vector<vector<string>> &ingredients,
                                vector<string>         &supplies) {
    unordered_set<string> available_supplies(supplies.begin(), supplies.end());
    unordered_map<string, vector<string>> recipe_to_ingredients;
    unordered_map<string, int>            visited;
    vector<string>                        result;

    for (size_t i = 0; i < recipes.size(); i++) {
      recipe_to_ingredients[recipes[i]] = ingredients[i];
    }

    function<bool(string)> can_make = [&](string recipe) {
      if (visited.count(recipe)) {
        return visited[recipe] == 1;
      }

      if (available_supplies.count(recipe)) {
        return true;
      }

      if (!recipe_to_ingredients.count(recipe)) {
        return false;
      }

      visited[recipe] = 0;

      for (const string &ingredient : recipe_to_ingredients[recipe]) {
        if (!can_make(ingredient)) {
          visited[recipe] = -1;
          return false;
        }
      }

      visited[recipe] = 1;
      result.push_back(recipe);
      return true;
    };

    for (const string &recipe : recipes) {
      can_make(recipe);
    }

    return result;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == recipes.length == ingredients.length|
// * |1 <= n <= 100|
// * |1 <= ingredients[i].length, supplies.length <= 100|
// * |1 <= recipes[i].length, ingredients[i][j].length, supplies[k].length <=
// 10|
// * |recipes[i], ingredients[i][j]|, and |supplies[k]| consist only of
// lowercase English letters.
// * All the values of |recipes| and |supplies| combined are unique.
// * Each |ingredients[i]| does not contain any duplicate values.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: recipes = ["bread"], ingredients = [["yeast","flour"]], supplies =
//  ["yeast","flour","corn"]
// Output: ["bread"]
//

LEETCODE_SOLUTION_UNITTEST(2115, FindAllPossibleRecipesFromGivenSupplies,
                           example_1) {
  auto                   solution    = MakeSolution();
  vector<string>         recipes     = {"bread"};
  vector<vector<string>> ingredients = {
      {"yeast", "flour"}
  };
  vector<string> supplies = {"yeast", "flour", "corn"};
  vector<string> expect   = {"bread"};
  vector<string> actual =
      solution->findAllRecipes(recipes, ingredients, supplies);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: recipes = ["bread","sandwich"], ingredients =
//  [["yeast","flour"],["bread","meat"]], supplies = ["yeast","flour","meat"]
// Output: ["bread","sandwich"]
//

LEETCODE_SOLUTION_UNITTEST(2115, FindAllPossibleRecipesFromGivenSupplies,
                           example_2) {
  auto                   solution    = MakeSolution();
  vector<string>         recipes     = {"bread", "sandwich"};
  vector<vector<string>> ingredients = {
      {"yeast", "flour"},
      {"bread",  "meat"}
  };
  vector<string> supplies = {"yeast", "flour", "meat"};
  vector<string> expect   = {"bread", "sandwich"};
  vector<string> actual =
      solution->findAllRecipes(recipes, ingredients, supplies);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: recipes = ["bread","sandwich","burger"], ingredients =
//  [["yeast","flour"],["bread","meat"],["sandwich","meat","bread"]], supplies =
//  ["yeast","flour","meat"]
// Output: ["bread","sandwich","burger"]
//

LEETCODE_SOLUTION_UNITTEST(2115, FindAllPossibleRecipesFromGivenSupplies,
                           example_3) {
  auto                   solution    = MakeSolution();
  vector<string>         recipes     = {"bread", "sandwich", "burger"};
  vector<vector<string>> ingredients = {
      {"yeast", "flour"},
      {"bread", "meat"},
      {"sandwich", "meat", "bread"}
  };
  vector<string> supplies = {"yeast", "flour", "meat"};
  vector<string> expect   = {"bread", "sandwich", "burger"};
  vector<string> actual =
      solution->findAllRecipes(recipes, ingredients, supplies);
  EXPECT_ANYORDER_EQ(expect, actual);
}
