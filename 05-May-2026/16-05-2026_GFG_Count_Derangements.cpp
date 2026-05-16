/*
Date: 16-05-2026
Problem Name: Count Derangements
Platform: GeeksforGeeks (GFG)
Difficulty: Medium
Tags: Dynamic Programming, Recursion, Combinatorics

Problem Summary:
A derangement is a permutation of n elements such that no element appears in its original position.
Given n, find the number of possible derangements.

Methods to Solve:
1. Recursive (Brute Force)
2. Dynamic Programming (Tabulation)
3. Space Optimized DP

----------------------------------------------------
Method 1: Recursive (Brute Force)
Intuition:
Use the recurrence relation D(n) = (n-1) * (D(n-1) + D(n-2)).
Approach:
Direct recursion with base cases D(1)=0, D(2)=1.
Dry Run (n=4):
D(4) = 3 * (D(3)+D(2)) = 3*(2+1)=9.
Time Complexity: O(2^n) (exponential due to overlapping calls)
Space Complexity: O(n) recursion stack
Why better than naive enumeration: avoids generating all permutations.
When to use: Small n only.

----------------------------------------------------
Method 2: Dynamic Programming (Tabulation)
Intuition:
Store results bottom-up to avoid recomputation.
Approach:
Build array dp[0..n], fill base cases, then use recurrence.
Dry Run (n=5):
dp[1]=0, dp[2]=1, dp[3]=2, dp[4]=9, dp[5]=44.
Time Complexity: O(n)
Space Complexity: O(n)
Why better: Efficient for larger n.
When to use: Moderate n values.

----------------------------------------------------
Method 3: Space Optimized DP
Intuition:
Only last two states are needed.
Approach:
Use two variables prev1, prev2 to store D(n-1), D(n-2).
Dry Run (n=5):
prev2=0, prev1=1 → D(3)=2, D(4)=9, D(5)=44.
Time Complexity: O(n)
Space Complexity: O(1)
Why better: Saves memory.
When to use: Large n.

----------------------------------------------------
Comparison Table:
Method        | TC       | SC   | Best Use Case
Recursive     | O(2^n)   | O(n) | Very small n
DP Tabulation | O(n)     | O(n) | Moderate n
Space Opt DP  | O(n)     | O(1) | Large n

Final Recommended Solution:
Use Space Optimized DP for efficiency and clarity.
*/

#include <bits/stdc++.h>
using namespace std;

class Derangement {
public:
    // Space optimized DP solution
    long long count(int n) {
        if (n == 1) return 0;
        if (n == 2) return 1;
        long long prev2 = 0, prev1 = 1, curr;
        for (int i = 3; i <= n; i++) {
            curr = (i - 1) * (prev1 + prev2);
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;  // Input number of elements
    Derangement d;
    cout << d.count(n) << "\n";  // Output derangements count
    return 0;
}
