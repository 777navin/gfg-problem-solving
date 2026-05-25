/*
========================================================
Date: 25-05-2026

Problem Name: Edit Distance
Platform: GeeksforGeeks (GFG)

Difficulty: Medium

Tags:
Dynamic Programming, Strings, Recursion, Memoization,
Tabulation, Space Optimization

========================================================
PROBLEM SUMMARY
========================================================

Given two strings str1 and str2, find the minimum number
of operations required to convert str1 into str2.

Allowed Operations:
1. Insert a character
2. Delete a character
3. Replace a character

Each operation costs 1.

--------------------------------------------------------
Example:
Input:
str1 = "geek"
str2 = "gesek"

Output:
1

Explanation:
Insert 's' into "geek"

========================================================
METHODS TO SOLVE
========================================================

1. Pure Recursion (Brute Force)
2. Memoization (Top-Down DP)
3. Tabulation (Bottom-Up DP)
4. Space Optimized DP (Optimal)

========================================================
1) PURE RECURSION (BRUTE FORCE)
========================================================

INTUITION:
Try all possible operations at every mismatch:
- Insert
- Delete
- Replace

APPROACH:
If characters match:
    move both pointers

Else:
    take minimum of:
    1 + insert
    1 + delete
    1 + replace

DRY RUN:
str1 = "cat"
str2 = "cut"

c == c
a != u

Options:
Replace a -> u

Result = 1

TIME COMPLEXITY:
O(3^(N+M))

SPACE COMPLEXITY:
O(N+M) recursion stack

WHY BAD?
Repeated subproblems cause huge recomputation.

========================================================
2) MEMOIZATION (TOP-DOWN DP)
========================================================

INTUITION:
Store already computed states.

STATE:
dp[i][j]
Minimum operations needed to convert:
str1[i...] -> str2[j...]

TIME COMPLEXITY:
O(N*M)

SPACE COMPLEXITY:
O(N*M) + recursion stack

WHY BETTER?
Avoids repeated recursive calculations.

========================================================
3) TABULATION (BOTTOM-UP DP)
========================================================

INTUITION:
Build answers from smaller substrings.

STATE:
dp[i][j]

Meaning:
Minimum operations needed to convert:
first i chars of str1
to
first j chars of str2

TRANSITION:
If chars match:
    dp[i][j] = dp[i-1][j-1]

Else:
    dp[i][j] =
        1 + min(
            insert,
            delete,
            replace
        )

TIME COMPLEXITY:
O(N*M)

SPACE COMPLEXITY:
O(N*M)

========================================================
4) SPACE OPTIMIZED DP (OPTIMAL)
========================================================

INTUITION:
Current row only depends on:
- previous row
- current row left element

So we only need 2 arrays.

TIME COMPLEXITY:
O(N*M)

SPACE COMPLEXITY:
O(M)

WHY BEST?
Same efficiency with much lower memory usage.

========================================================
COMPARISON TABLE
========================================================

Method                 TC              SC
------------------------------------------------
Recursion              Exponential     O(N+M)
Memoization            O(N*M)          O(N*M)
Tabulation             O(N*M)          O(N*M)
Space Optimized DP     O(N*M)          O(M)

========================================================
FINAL RECOMMENDED SOLUTION
========================================================

Use:
SPACE OPTIMIZED DYNAMIC PROGRAMMING

Reason:
- Optimal memory usage
- Fast execution
- Industry standard DP solution

========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
    ========================================================
    METHOD 1: PURE RECURSION
    ========================================================
    */

    int solveRec(string &s1, string &s2, int i, int j) {

        // If s1 finished
        if(i == s1.length())
            return s2.length() - j;

        // If s2 finished
        if(j == s2.length())
            return s1.length() - i;

        // Characters match
        if(s1[i] == s2[j])
            return solveRec(s1, s2, i + 1, j + 1);

        // Insert
        int insertOp = 1 + solveRec(s1, s2, i, j + 1);

        // Delete
        int deleteOp = 1 + solveRec(s1, s2, i + 1, j);

        // Replace
        int replaceOp = 1 + solveRec(s1, s2, i + 1, j + 1);

        return min({insertOp, deleteOp, replaceOp});
    }

    /*
    ========================================================
    METHOD 2: MEMOIZATION
    ========================================================
    */

    int solveMem(string &s1, string &s2,
                 int i, int j,
                 vector<vector<int>> &dp) {

        if(i == s1.length())
            return s2.length() - j;

        if(j == s2.length())
            return s1.length() - i;

        if(dp[i][j] != -1)
            return dp[i][j];

        if(s1[i] == s2[j]) {
            return dp[i][j] =
                solveMem(s1, s2, i + 1, j + 1, dp);
        }

        int insertOp =
            1 + solveMem(s1, s2, i, j + 1, dp);

        int deleteOp =
            1 + solveMem(s1, s2, i + 1, j, dp);

        int replaceOp =
            1 + solveMem(s1, s2, i + 1, j + 1, dp);

        return dp[i][j] =
            min({insertOp, deleteOp, replaceOp});
    }

    /*
    ========================================================
    METHOD 3: TABULATION
    ========================================================
    */

    int solveTab(string &s1, string &s2) {

        int n = s1.length();
        int m = s2.length();

        vector<vector<int>> dp(n + 1,
                               vector<int>(m + 1, 0));

        // Base cases
        for(int i = 0; i <= n; i++)
            dp[i][m] = n - i;

        for(int j = 0; j <= m; j++)
            dp[n][j] = m - j;

        for(int i = n - 1; i >= 0; i--) {

            for(int j = m - 1; j >= 0; j--) {

                if(s1[i] == s2[j]) {
                    dp[i][j] = dp[i + 1][j + 1];
                }
                else {

                    int insertOp = 1 + dp[i][j + 1];

                    int deleteOp = 1 + dp[i + 1][j];

                    int replaceOp = 1 + dp[i + 1][j + 1];

                    dp[i][j] =
                        min({insertOp, deleteOp, replaceOp});
                }
            }
        }

        return dp[0][0];
    }

    /*
    ========================================================
    METHOD 4: SPACE OPTIMIZED DP (OPTIMAL)
    ========================================================
    */

    int solveSpaceOptimized(string &s1, string &s2) {

        int n = s1.length();
        int m = s2.length();

        vector<int> next(m + 1, 0);
        vector<int> curr(m + 1, 0);

        // Base case initialization
        for(int j = 0; j <= m; j++) {
            next[j] = m - j;
        }

        for(int i = n - 1; i >= 0; i--) {

            curr[m] = n - i;

            for(int j = m - 1; j >= 0; j--) {

                if(s1[i] == s2[j]) {
                    curr[j] = next[j + 1];
                }
                else {

                    int insertOp = 1 + curr[j + 1];

                    int deleteOp = 1 + next[j];

                    int replaceOp = 1 + next[j + 1];

                    curr[j] =
                        min({insertOp, deleteOp, replaceOp});
                }
            }

            next = curr;
        }

        return next[0];
    }

    /*
    ========================================================
    GFG DRIVER FUNCTION
    ========================================================
    */

    int editDistance(string s1, string s2) {

        // Recommended Optimal Solution
        return solveSpaceOptimized(s1, s2);
    }
};

/*
========================================================
SAMPLE TESTING
========================================================

Input:
s1 = "horse"
s2 = "ros"

Output:
3

Explanation:
horse -> rorse (replace h with r)
rorse -> rose  (remove r)
rose  -> ros   (remove e)

========================================================
*/
