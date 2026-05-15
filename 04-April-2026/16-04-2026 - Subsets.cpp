## Problem

Find all possible subsets of a given array of distinct positive integers.

## Intuition

Each element has two choices:

1. Include it in the current subset
2. Exclude it from the current subset

By exploring both choices recursively for every element, we can generate all possible subsets.

## Approach

* Use **Backtracking / Recursion**
* Start from index `0`
* At each index:

  * Include current element
  * Exclude current element
* When index reaches array size, store current subset
* Sort final answer for lexicographical order if needed

## C++ Code

```cpp
class Solution {
public:
    void solve(int index, vector<int>& arr, vector<int>& temp,
               vector<vector<int>>& ans) {
        
        if(index == arr.size()) {
            ans.push_back(temp);
            return;
        }

        // Include current element
        temp.push_back(arr[index]);
        solve(index + 1, arr, temp, ans);

        // Backtrack
        temp.pop_back();

        // Exclude current element
        solve(index + 1, arr, temp, ans);
    }

    vector<vector<int>> subsets(vector<int>& arr) {
        vector<vector<int>> ans;
        vector<int> temp;

        solve(0, arr, temp, ans);

        sort(ans.begin(), ans.end());
        return ans;
    }
};
```

## Time Complexity

`O(2^N * N)`
Because total subsets are `2^N` and copying subset may take `N`.

## Space Complexity

`O(N)` recursion stack + auxiliary subset storage
(Excluding output storage)
