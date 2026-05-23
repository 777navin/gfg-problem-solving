/*
========================================================
File Name: 23-05-2026_GFG_Painting_The_Fence.cpp
========================================================

Date: 23-05-2026
Problem Name: Painting the Fence
Platform: GeeksforGeeks
Problem Link:
https://www.geeksforgeeks.org/problems/painting-the-fence3727/1

Difficulty: Medium
Tags:
Dynamic Programming, Recursion, Memoization,
Tabulation, Space Optimization

========================================================
Problem Summary
========================================================

Given:
- n fences
- k colors

Find the number of ways to paint the fences such that
NOT MORE THAN 2 adjacent fences have the same color.

Return total possible ways.

--------------------------------------------------------
Example
--------------------------------------------------------

Input:
n = 3
k = 2

Output:
6

Explanation:
Possible ways:
RRB
RBR
RBB
BRR
BRB
BBR

AAA type patterns are NOT allowed.

========================================================
Core Recurrence Relation
========================================================

f(n) = (k - 1) * (f(n-1) + f(n-2))

Why?

Case 1:
Last two fences have different colors
-> Depends on f(n-1)

Case 2:
Last two fences have same colors
-> Previous fence must differ
-> Depends on f(n-2)

========================================================
APPROACH 1 : Pure Recursion
========================================================

Intuition:
Try solving smaller subproblems recursively.

Approach:
Use recurrence directly.

Base Cases:
f(1) = k
f(2) = k * k

Dry Run:
n = 3, k = 2

f(3)
= (2-1) * (f(2) + f(1))
= 1 * (4 + 2)
= 6

Time Complexity:
O(2^N)

Space Complexity:
O(N) recursion stack

Drawback:
Repeated calculations.

========================================================
APPROACH 2 : Memoization (Top Down DP)
========================================================

Intuition:
Store already computed states.

Approach:
Use DP array.

Time Complexity:
O(N)

Space Complexity:
O(N)

Better because:
Avoids repeated recursive calls.

========================================================
APPROACH 3 : Tabulation (Bottom Up DP)
========================================================

Intuition:
Build answers iteratively.

Approach:
Start from smaller states and move upward.

Time Complexity:
O(N)

Space Complexity:
O(N)

Advantages:
No recursion overhead.

========================================================
APPROACH 4 : Space Optimized DP
========================================================

Intuition:
Only previous 2 states are needed.

Approach:
Use variables instead of DP array.

Time Complexity:
O(N)

Space Complexity:
O(1)

Best Approach:
Most optimal for interviews and CP.

========================================================
Comparison Table
========================================================

Method                 TC          SC
-----------------------------------------
Recursion              O(2^N)      O(N)
Memoization            O(N)        O(N)
Tabulation             O(N)        O(N)
Space Optimized        O(N)        O(1)

========================================================
Final Recommended Solution
========================================================
Space Optimized DP

========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    static const int MOD = 1000000007;

    /*
    ========================================================
    APPROACH 1 : RECURSION
    ========================================================
    */

    long long solveRec(int n, int k) {

        // Edge Cases
        if(n <= 0 || k <= 0)
            return 0;

        // Base Case
        if(n == 1)
            return k;

        // Base Case
        if(n == 2)
            return 1LL * k * k;

        // Recurrence Relation
        return (1LL * (k - 1) *
               (solveRec(n - 1, k) +
                solveRec(n - 2, k))) % MOD;
    }

    /*
    ========================================================
    APPROACH 2 : MEMOIZATION
    ========================================================
    */

    long long solveMemo(int n, int k, vector<long long>& dp) {

        if(n <= 0 || k <= 0)
            return 0;

        if(n == 1)
            return k;

        if(n == 2)
            return 1LL * k * k;

        if(dp[n] != -1)
            return dp[n];

        dp[n] = (1LL * (k - 1) *
                (solveMemo(n - 1, k, dp) +
                 solveMemo(n - 2, k, dp))) % MOD;

        return dp[n];
    }

    /*
    ========================================================
    APPROACH 3 : TABULATION
    ========================================================
    */

    long long solveTab(int n, int k) {

        if(n <= 0 || k <= 0)
            return 0;

        if(n == 1)
            return k;

        vector<long long> dp(n + 1, 0);

        dp[1] = k;
        dp[2] = 1LL * k * k;

        for(int i = 3; i <= n; i++) {

            dp[i] = (1LL * (k - 1) *
                    (dp[i - 1] + dp[i - 2])) % MOD;
        }

        return dp[n];
    }

    /*
    ========================================================
    APPROACH 4 : SPACE OPTIMIZED DP
    ========================================================
    */

    long long solveSpaceOptimized(int n, int k) {

        // Edge Cases
        if(n <= 0 || k <= 0)
            return 0;

        // Base Cases
        if(n == 1)
            return k;

        if(n == 2)
            return 1LL * k * k;

        long long prev2 = k;
        long long prev1 = 1LL * k * k;

        for(int i = 3; i <= n; i++) {

            long long curr =
            (1LL * (k - 1) * (prev1 + prev2)) % MOD;

            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }

    /*
    ========================================================
    GFG REQUIRED FUNCTION
    ========================================================
    */

    long long countWays(int n, int k) {

        // Recommended Approach
        return solveSpaceOptimized(n, k);
    }
};

/*
========================================================
Driver Code (GFG Style)
========================================================
*/

int main() {

    int testCases;
    cin >> testCases;

    while(testCases--) {

        int n, k;
        cin >> n >> k;

        Solution obj;

        cout << obj.countWays(n, k) << endl;
    }

    return 0;
}
