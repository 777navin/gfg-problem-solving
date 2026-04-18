// Problem: Minimum Jumps
// Date: 18-04-2026
// Language: C++

/*
Intuition:
Each element tells the maximum jump length from that position.
We need minimum jumps to reach the last index.

Instead of trying all paths recursively, use a greedy approach.
Track the farthest position reachable in current jump range.
When current range ends, take one more jump.

Approach:
1. If array has only one element, return 0.
2. If first element is 0, return -1 (cannot move).
3. Maintain:
   - maxReach = farthest index reachable
   - steps = remaining steps in current jump
   - jumps = number of jumps taken
4. Traverse array:
   - Update maxReach
   - Use one step
   - If steps become 0:
       -> take another jump
       -> if current index >= maxReach, return -1
       -> reset steps = maxReach - i
5. Return jumps when last index is reached.

Time Complexity:
O(n)

Space Complexity:
O(1)
*/

class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();

        if (n == 1) return 0;
        if (arr[0] == 0) return -1;

        int maxReach = arr[0];
        int steps = arr[0];
        int jumps = 1;

        for (int i = 1; i < n; i++) {
            if (i == n - 1)
                return jumps;

            maxReach = max(maxReach, i + arr[i]);
            steps--;

            if (steps == 0) {
                jumps++;

                if (i >= maxReach)
                    return -1;

                steps = maxReach - i;
            }
        }

        return -1;
    }
};
