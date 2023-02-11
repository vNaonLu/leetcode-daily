# Daily LeetCode in C++

[![githubbuild](https://github.com/vNaonLu/Daily_LeetCode/actions/workflows/test.yml/badge.svg)](https://github.com/vNaonLu/Daily_LeetCode/actions)

This repository collects some of my LeetCode solutions for **free** questions since 2021/09/06.The remain questions is still being solved so the current project may not contain the solutions you are looking for. Please check the chapter [Getting Started](#getting-started) for more details.

Here is my [LeetCode account](https://leetcode.com/naon/) if you are interested.


## Getting Started
See [Status](#status) to check the recent solution resolution status, including the historical statistics and the recent submissions.
All solutions are stored in `src` and more information can be found at [Find Solution](#finding-solution).
See [Installation](#installation) if you are interested in how to build the project or want to add some testcases for some solutions.

## Status
<div style="min-height: 186px;height: 186px;width: min-content;padding-top: 1rem;padding-bottom: 0.75rem;background-color: #404040;border-radius: 0.5rem">
   <div style="diplay: flex; flex-direction: row; font-weight: 500; padding-left: 13px; padding-right: 13px">
       <span style="color: #eff2f699;">Solved </span>
       <span style="color: #ffa116;">Free Problems</span>
   </div>
   <div style="margin-left: 2rem;margin-right: 2rem;align-items: center;display: flex;">
      <div style="min-width: 100px;justify-content: center;display: flex;margin-right: 2rem;margin-top: 1.5rem;">
           <div style="z-index: 0;max-width: 100pxmax-height: 100px;position: relative;">
               <img src="/vNaonLu/daily-leetcode/raw/master/assets/progress.svg">
               <div style="text-align: center;position: absolute;transform: translate(-50%, -50%);top: 50%;left: 50%;">
                   <div>
                       <div style="font-size: 24px;font-weight: 500;color: #ffffff;">869</div>
                       <div style="font-size: .75rem;line-height: 1rem;color: #eff2f699;">Solved</div>
                   </div>
               </div>
           </div>
      </div>
      <div style="max-width: 228px;flex-direction: column;display: flex;width: 100%;">
           <div style="margin-top: 0rem;">
              <div style="font-size: .75rem;line-height: 1rem;align-items: flex-end;width: 100%;display: flex;">
                  <div style="width: 53px;color: #eff2f699;">Easy</div>
                  <div style="display: flex;flex: 1 1 0%;align-items: center;">
                      <span style="line-height: 20pxfont-weight: 500font-size: 1rem;margin-right: 5px;color: #ffffff;">317</span>
                      <span style="color: #747474;font-weight: 500font-size: .75remfont-height: 1rem;color: #ebebf54d;">/522</span>
                  </div>
                  <div style="display: inline;">
                      <span>
                          <span style="color: #eff2f699;">Complete</span>
                          <span style="margin-left: 0.375rem;color: #ffffff;">60.73%</span>
                      </span>
                  </div>
              </div>
              <div style="border-radius: 9999px;width: 228px;height: 0.25rem;position: relative;">
                  <div style="background-color: #747474;width: 100%;height: 100%;position: absolute;"></div>
                  <div style="background-color: #ffa116;width: 60.7280%;height: 100%;position: absolute;border-radius: 9999px;"></div>
              </div>
           </div>
           <div style="margin-top: 1rem;">
              <div style="font-size: .75rem;line-height: 1rem;align-items: flex-end;width: 100%;display: flex;">
                  <div style="width: 53px;color: #eff2f699;">Medium</div>
                  <div style="display: flex;flex: 1 1 0%;align-items: center;">
                      <span style="line-height: 20pxfont-weight: 500font-size: 1rem;margin-right: 5px;color: #ffffff;">457</span>
                      <span style="color: #747474;font-weight: 500font-size: .75remfont-height: 1rem;color: #ebebf54d;">/1049</span>
                  </div>
                  <div style="display: inline;">
                      <span>
                          <span style="color: #eff2f699;">Complete</span>
                          <span style="margin-left: 0.375rem;color: #ffffff;">43.57%</span>
                      </span>
                  </div>
              </div>
              <div style="border-radius: 9999px;width: 228px;height: 0.25rem;position: relative;">
                  <div style="background-color: #747474;width: 100%;height: 100%;position: absolute;"></div>
                  <div style="background-color: #ffa116;width: 43.5653%;height: 100%;position: absolute;border-radius: 9999px;"></div>
              </div>
           </div>
           <div style="margin-top: 1rem;">
              <div style="font-size: .75rem;line-height: 1rem;align-items: flex-end;width: 100%;display: flex;">
                  <div style="width: 53px;color: #eff2f699;">Hard</div>
                  <div style="display: flex;flex: 1 1 0%;align-items: center;">
                      <span style="line-height: 20pxfont-weight: 500font-size: 1rem;margin-right: 5px;color: #ffffff;">95</span>
                      <span style="color: #747474;font-weight: 500font-size: .75remfont-height: 1rem;color: #ebebf54d;">/459</span>
                  </div>
                  <div style="display: inline;">
                      <span>
                          <span style="color: #eff2f699;">Complete</span>
                          <span style="margin-left: 0.375rem;color: #ffffff;">20.70%</span>
                      </span>
                  </div>
              </div>
              <div style="border-radius: 9999px;width: 228px;height: 0.25rem;position: relative;">
                  <div style="background-color: #747474;width: 100%;height: 100%;position: absolute;"></div>
                  <div style="background-color: #ffa116;width: 20.6972%;height: 100%;position: absolute;border-radius: 9999px;"></div>
              </div>
           </div>
      </div>
   </div>
</div>

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
