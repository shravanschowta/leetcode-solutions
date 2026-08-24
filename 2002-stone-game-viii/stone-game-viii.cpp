class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();
        
        // Compute prefix sums in-place
        vector<long long> pref(n);
        pref[0] = stones[0];
        for (int i = 1; i < n; ++i) {
            pref[i] = pref[i - 1] + stones[i];
        }

        // Base case: at the last index (n-1), the score diff is just pref[n-1]
        long long maxDiff = pref[n - 1];

        // Iterate backwards from n-2 down to 1
        // The first player must take x > 1 stones, so index must be >= 1.
        for (int i = n - 2; i >= 1; --i) {
            maxDiff = max(maxDiff, pref[i] - maxDiff);
        }

        return maxDiff;
    }
};