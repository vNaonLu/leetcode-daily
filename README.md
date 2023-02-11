# Daily LeetCode in C++

[![githubbuild](https://github.com/vNaonLu/Daily_LeetCode/actions/workflows/test.yml/badge.svg)](https://github.com/vNaonLu/Daily_LeetCode/actions)

This repository collects some of my LeetCode solutions for **free** questions since 2021/09/06.The remain questions is still being solved so the current project may not contain the solutions you are looking for. Please check the chapter [Getting Started](#getting-started) for more details.

Here is my [LeetCode account](https://leetcode.com/naon/) if you are interested.


## Getting Started
See [Activity](#activity) to check the recent solution resolution status, including the historical statistics and the recent submissions.
All solutions are stored in `src` and more information can be found at [Find Solution](#finding-solution).
See [Installation](#installation) if you are interested in how to build the project or want to add some testcases for some solutions.

## Activity
![progress](./assets/progress.svg)
More information about full activity can be found at:

- Submissions in 2023: [docs/2023.md](./docs/2023.md)
- Submissions in 2022: [docs/2022.md](./docs/2022.md)
- Submissions in 2021: [docs/2021.md](./docs/2021.md)

## Finding Solution
Solutions can be found in the directories in `./src` by its question identifier. For instance, the solution for [1. Two Sum](https://leetcode.com/problems/two-sum/) is stored in [`./src/q1_50/q0001.cc`](./src/q1_50/q0001.cc). The source usually contains a structure which is named by question identifier and inherits from the google test structure `testing::Test` and several testcases:
```cpp
#include <gtest/gtest.h>
#include <iostream>

// ...

struct q1 : public ::testing::Test {
  class Solution {
  public:
    vector<int> twoSum(vector<int> &nums, int target) {
      // some solution...
    }
  };
// ...
};

TEST_F(q1, sample_input01) {
// some test input...
}
// ...
```
The approach is always appeared in the `struct` block. Or you can simply use the script `repo_manager.py` to cat the exist solution via:
```sh
$ repo_manager.py -c <question id>
```
But the script probably won't work as it is very rough currently.

## Installation
It is not necessary to build or install this project if you just want specific solutions, but you can still build and run this project. There has a python scripts named `repo_manager.py` in the root, which is a tool to automatically add/delete the solution in this project, generate the solution template or update the readme or log. However the script may too rough to use since I haven't tested it in other environment.
Before running to build project, please check below dependencies exist in the build environment:
 - Compiler supports `C++17`.
 - CMake above `3.11`.
 - Unix-like OS.

Then you can build the project easily by

``` sh
# Clone this project and change workspace to the project root.
$ git clone https://github.com/vNaonLu/daily-leetcode
$ cd daily-leetcode
# Configure the cmake build files and build it.
$ cmake -S . -B build -DENABLE_LEETCODE_TEST=ON
$ cmake --build build
# Run the leetcode test by GTest interface.
$ ./build/leetcode_test
```
