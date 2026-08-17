class Solution {
    vector<vector<int>> memo;
    vector<int> pref;

    // Helper to get range sum in O(1)
    int getSum(int l, int r) {
        return pref[r + 1] - pref[l];
    }

    int solve(int i, int j) {
        // Base case: Single element or invalid range
        if (i >= j) return 0;

        // Return memoized result if available
        if (memo[i][j] != -1) return memo[i][j];

        int maxScore = 0;

        // Try all possible split points k
        for (int k = i; k < j; ++k) {
            int leftSum = getSum(i, k);
            int rightSum = getSum(k + 1, j);

            if (leftSum < rightSum) {
                // Bob keeps the left side
                maxScore = max(maxScore, leftSum + solve(i, k));
            } else if (rightSum < leftSum) {
                // Bob keeps the right side
                maxScore = max(maxScore, rightSum + solve(k + 1, j));
            } else {
                // Equal sums: Alice chooses the side that maximizes her score
                int takeLeft = leftSum + solve(i, k);
                int takeRight = rightSum + solve(k + 1, j);
                maxScore = max(maxScore, max(takeLeft, takeRight));
            }
        }

        return memo[i][j] = maxScore;
    }

public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        
        // Compute prefix sums
        pref.assign(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + stoneValue[i];
        }

        // Initialize memoization table with -1
        memo.assign(n, vector<int>(n, -1));

        return solve(0, n - 1);
    }
};