
// Date: 19-04-2026
// Language: C++

#include <bits/stdc++.h>
using namespace std;

/*
====================================================
1. RECURSION
====================================================

Intuition:
From every cell, move to:
1. Down      -> (row+1, col)
2. Diagonal  -> (row+1, col+1)

Take minimum path sum.

Time Complexity: O(2^n)
Space Complexity: O(n)
*/

class Solution1 {
public:
    int solve(vector<vector<int>>& triangle, int row, int col) {
        if (row == triangle.size() - 1)
            return triangle[row][col];

        int down = triangle[row][col] + solve(triangle, row + 1, col);
        int diag = triangle[row][col] + solve(triangle, row + 1, col + 1);

        return min(down, diag);
    }

    int minimumTotal(vector<vector<int>>& triangle) {
        return solve(triangle, 0, 0);
    }
};

/*
====================================================
2. MEMOIZATION
====================================================

Intuition:
Store repeated states in dp[row][col].

Time Complexity: O(n^2)
Space Complexity: O(n^2) + O(n)
*/

class Solution2 {
public:
    int solve(vector<vector<int>>& triangle, int row, int col,
              vector<vector<int>>& dp) {

        if (row == triangle.size() - 1)
            return triangle[row][col];

        if (dp[row][col] != -1)
            return dp[row][col];

        int down = triangle[row][col] + solve(triangle, row + 1, col, dp);
        int diag = triangle[row][col] + solve(triangle, row + 1, col + 1, dp);

        return dp[row][col] = min(down, diag);
    }

    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();

        vector<vector<int>> dp(n, vector<int>(n, -1));

        return solve(triangle, 0, 0, dp);
    }
};

/*
====================================================
3. TABULATION
====================================================

Intuition:
Start from second last row and move upward.

Time Complexity: O(n^2)
Space Complexity: O(n^2)
*/

class Solution3 {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();

        vector<vector<int>> dp = triangle;

        for (int row = n - 2; row >= 0; row--) {
            for (int col = 0; col <= row; col++) {
                dp[row][col] += min(dp[row + 1][col],
                                    dp[row + 1][col + 1]);
            }
        }

        return dp[0][0];
    }
};

/*
====================================================
4. SPACE OPTIMIZED
====================================================

Intuition:
Need only next row values.

Time Complexity: O(n^2)
Space Complexity: O(n)
*/

class Solution4 {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();

        vector<int> dp = triangle[n - 1];

        for (int row = n - 2; row >= 0; row--) {
            for (int col = 0; col <= row; col++) {
                dp[col] = triangle[row][col] +
                          min(dp[col], dp[col + 1]);
            }
        }

        return dp[0];
    }
};

/*
====================================================
MAIN FUNCTION
====================================================
*/

int main() {
    vector<vector<int>> triangle = {
        {2},
        {3, 4},
        {6, 5, 7},
        {4, 1, 8, 3}
    };

    Solution1 obj1;
    Solution2 obj2;
    Solution3 obj3;
    Solution4 obj4;

    cout << "Recursion: " << obj1.minimumTotal(triangle) << endl;
    cout << "Memoization: " << obj2.minimumTotal(triangle) << endl;
    cout << "Tabulation: " << obj3.minimumTotal(triangle) << endl;
    cout << "Space Optimized: " << obj4.minimumTotal(triangle) << endl;

    return 0;
}
