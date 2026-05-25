/*
Date: 25-05-2026

Problem Name:
Largest Square Formed In A Matrix

Platform:
GeeksforGeeks (GFG)

Difficulty:
Medium

Tags:
Dynamic Programming, Matrix, Recursion, Memoization, Tabulation, Space Optimization

Problem Summary:
Given a binary matrix mat[][] consisting of 0s and 1s,
find the size of the largest square sub-matrix containing only 1s.

Return the side length of the largest square.

------------------------------------------------------------

Methods to Solve:

1. Pure Recursion
2. Memoization (Top Down DP)
3. Tabulation (Bottom Up DP)
4. Space Optimized DP (Optimal)

============================================================

1. PURE RECURSION
------------------------------------------------------------

Intuition:
For every cell:
- Try expanding square using:
    right
    down
    diagonal

If current cell is 1:
answer = 1 + min(right, down, diagonal)

Approach:
- Recursively calculate largest square possible
- Track maximum answer globally

Dry Run:
Matrix:
1 1
1 1

At (0,0):
right = 1
down = 1
diagonal = 1

ans = 1 + min(1,1,1)
    = 2

Largest square size = 2

Time Complexity:
Exponential

Space Complexity:
O(n+m)

Why Better Than Previous:
- Helps derive recurrence relation

When To Use:
- Learning recursion and DP transitions

============================================================

2. MEMOIZATION (TOP DOWN DP)
------------------------------------------------------------

Intuition:
Same states repeat multiple times.

Store answers in DP table.

Approach:
- Use recursion + memoization

Time Complexity:
O(n*m)

Space Complexity:
O(n*m)

Why Better:
Avoids recomputation.

When To Use:
- Easy conversion from recursion

============================================================

3. TABULATION (BOTTOM UP DP)
------------------------------------------------------------

DP Relation:

If mat[i][j] == 1

dp[i][j] =
1 + min(
    dp[i][j+1],
    dp[i+1][j],
    dp[i+1][j+1]
)

Approach:
- Build DP table from bottom-right

Time Complexity:
O(n*m)

Space Complexity:
O(n*m)

Why Better:
No recursion stack.

============================================================

4. SPACE OPTIMIZED DP (OPTIMAL)
------------------------------------------------------------

Intuition:
Current row depends only on:
- current row
- next row

Use 1D arrays.

Approach:
- Maintain currentRow and nextRow

Time Complexity:
O(n*m)

Space Complexity:
O(m)

Why Better:
Most optimized solution.

============================================================

COMPARISON TABLE
------------------------------------------------------------

Method                  TC              SC
------------------------------------------------------------
Recursion               Exponential     O(n+m)
Memoization             O(n*m)          O(n*m)
Tabulation              O(n*m)          O(n*m)
Space Optimized DP      O(n*m)          O(m)

============================================================

FINAL RECOMMENDED SOLUTION:
Space Optimized Dynamic Programming

Reason:
- Optimal TC
- Minimal SC
- Clean implementation

============================================================
*/

class Solution {
public:

    /*
    --------------------------------------------------------
    METHOD 1 : PURE RECURSION
    --------------------------------------------------------
    */

    int solveRec(vector<vector<int>>& mat,
                 int i,
                 int j,
                 int n,
                 int m,
                 int &maxi) {

        // Base Case
        if(i >= n || j >= m) {
            return 0;
        }

        // Explore all directions
        int right = solveRec(mat, i, j + 1, n, m, maxi);

        int diagonal = solveRec(mat,
                                i + 1,
                                j + 1,
                                n,
                                m,
                                maxi);

        int down = solveRec(mat,
                            i + 1,
                            j,
                            n,
                            m,
                            maxi);

        // If current cell contains 1
        if(mat[i][j] == 1) {

            int ans = 1 + min(right,
                              min(diagonal, down));

            maxi = max(maxi, ans);

            return ans;
        }

        return 0;
    }

    /*
    --------------------------------------------------------
    METHOD 2 : MEMOIZATION
    --------------------------------------------------------
    */

    int solveMemo(vector<vector<int>>& mat,
                  int i,
                  int j,
                  int n,
                  int m,
                  vector<vector<int>>& dp,
                  int &maxi) {

        if(i >= n || j >= m) {
            return 0;
        }

        if(dp[i][j] != -1) {
            return dp[i][j];
        }

        int right = solveMemo(mat,
                              i,
                              j + 1,
                              n,
                              m,
                              dp,
                              maxi);

        int diagonal = solveMemo(mat,
                                 i + 1,
                                 j + 1,
                                 n,
                                 m,
                                 dp,
                                 maxi);

        int down = solveMemo(mat,
                             i + 1,
                             j,
                             n,
                             m,
                             dp,
                             maxi);

        if(mat[i][j] == 1) {

            dp[i][j] = 1 + min(right,
                               min(diagonal, down));

            maxi = max(maxi, dp[i][j]);

            return dp[i][j];
        }

        return dp[i][j] = 0;
    }

    /*
    --------------------------------------------------------
    METHOD 3 : TABULATION
    --------------------------------------------------------
    */

    int solveTab(vector<vector<int>>& mat,
                 int n,
                 int m) {

        vector<vector<int>> dp(n + 1,
                               vector<int>(m + 1, 0));

        int maxi = 0;

        for(int i = n - 1; i >= 0; i--) {

            for(int j = m - 1; j >= 0; j--) {

                int right = dp[i][j + 1];

                int diagonal = dp[i + 1][j + 1];

                int down = dp[i + 1][j];

                if(mat[i][j] == 1) {

                    dp[i][j] = 1 + min(right,
                                       min(diagonal, down));

                    maxi = max(maxi, dp[i][j]);
                }
            }
        }

        return maxi;
    }

    /*
    --------------------------------------------------------
    METHOD 4 : SPACE OPTIMIZED DP (OPTIMAL)
    --------------------------------------------------------
    */

    int solveSpaceOptimized(vector<vector<int>>& mat,
                            int n,
                            int m) {

        vector<int> nextRow(m + 1, 0);

        int maxi = 0;

        for(int i = n - 1; i >= 0; i--) {

            vector<int> currentRow(m + 1, 0);

            for(int j = m - 1; j >= 0; j--) {

                int right = currentRow[j + 1];

                int diagonal = nextRow[j + 1];

                int down = nextRow[j];

                if(mat[i][j] == 1) {

                    currentRow[j] =
                        1 + min(right,
                                min(diagonal, down));

                    maxi = max(maxi, currentRow[j]);
                }
            }

            nextRow = currentRow;
        }

        return maxi;
    }

    /*
    --------------------------------------------------------
    MAIN FUNCTION (GFG FORMAT)
    --------------------------------------------------------
    */

    int maxSquare(int n, int m, vector<vector<int>> mat) {

        // Recommended Optimal Approach
        return solveSpaceOptimized(mat, n, m);
    }
};
