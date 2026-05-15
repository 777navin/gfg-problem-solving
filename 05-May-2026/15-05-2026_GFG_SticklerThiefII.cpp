/*
Date: 15-05-2026
Problem Name: Stickler Thief II (House Robber II)
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Dynamic Programming, Recursion, Memoization

Problem Summary:
You are given an array of non-negative integers representing the amount of money in each house arranged in a circle. 
You cannot rob two adjacent houses. Find the maximum amount you can rob.

Methods to Solve:
1. Brute Force (Recursion)
2. Better Approach (Recursion + Memoization)
3. Optimal Approach (Dynamic Programming with rolling variables)

---------------------------------------------------------------
Method 1: Brute Force (Recursion)
- Intuition: Try all possibilities (rob or skip each house).
- Approach: Recursive calls with index jumps.
- Dry Run: nums = [1,2,3,1]
    Case1 (exclude last): max = 4
    Case2 (exclude first): max = 3
    Answer = 4
- Time Complexity: O(2^n)
- Space Complexity: O(n) recursion stack
- Why better than previous: Base method, but inefficient.
- When to use: Small inputs only.

---------------------------------------------------------------
Method 2: Recursion + Memoization
- Intuition: Avoid recomputation by caching results.
- Approach: Use dp[i] to store max loot from i..end.
- Dry Run: nums = [1,2,3,1]
    dp[2] = 3, dp[1] = 3, dp[0] = 4
- Time Complexity: O(n)
- Space Complexity: O(n)
- Why better: Efficient, avoids exponential blowup.
- When to use: Medium inputs, educational clarity.

---------------------------------------------------------------
Method 3: Optimal DP (Iterative)
- Intuition: Rolling variables track rob/skip choices.
- Approach: Linear DP with two variables (prev1, prev2).
- Dry Run: nums = [1,2,3,1]
    Case1: [1,2,3] → max = 4
    Case2: [2,3,1] → max = 3
    Answer = 4
- Time Complexity: O(n)
- Space Complexity: O(1)
- Why better: Most efficient.
- When to use: Production/contest.

---------------------------------------------------------------
Comparison Table:
Method   | TC     | SC   | Best Use Case
Brute    | O(2^n) | O(n) | Very small inputs
Memoized | O(n)   | O(n) | Educational clarity
Optimal  | O(n)   | O(1) | Contest/production

Final Recommended Solution: Optimal DP (Iterative)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Helper function to solve linear House Robber problem
    int solveLinear(vector<int>& nums, int start, int end) {
        int prev1 = 0, prev2 = 0;
        for (int i = start; i <= end; i++) {
            int rob = nums[i] + prev2;   // Rob current house
            int skip = prev1;            // Skip current house
            int curr = max(rob, skip);
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        // Case 1: Exclude last house
        int case1 = solveLinear(nums, 0, n - 2);
        // Case 2: Exclude first house
        int case2 = solveLinear(nums, 1, n - 1);
        return max(case1, case2);
    }
};

// Driver code for GFG
int main() {
    vector<int> nums = {1,2,3,1};
    Solution obj;
    cout << obj.rob(nums) << endl; // Expected output: 4
    return 0;
}
