/*  Copyright (C) 2026 cpp-knowledge-base project
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache License Version 2.0.
 */

#include <iostream>
#include <vector>

namespace {

void backtrack(const std::vector<int> &nums, size_t index, std::vector<int> &subset,
    std::vector<std::vector<int>> &result)
{
    result.push_back(subset);

    for (size_t i = index; i < nums.size(); ++i) {
        // Choose
        subset.push_back(nums[i]);

        // Explore
        backtrack(nums, i + 1, subset, result);

        // Undo choice (backtrack)
        subset.pop_back();
    }
}

} // namespace

int main()
{
    std::vector<int> nums = { 1, 2, 3 };
    std::vector<std::vector<int>> result;
    std::vector<int> subset;

    backtrack(nums, 0, subset, result);

    for (const auto &subset : result) {
        std::cout << "[ ";
        for (int x : subset) {
            std::cout << x << " ";
        }
        std::cout << "]\n";
    }

    return 0;
}
