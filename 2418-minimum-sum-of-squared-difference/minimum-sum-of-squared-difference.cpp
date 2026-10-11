class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        vector<int> d(n);
        long long total_diff = 0;
        int max_val = 0;
        long long k = (long long)k1 + k2;
        
        for (int i = 0; i < n; ++i) {
            d[i] = abs(nums1[i] - nums2[i]);
            total_diff += d[i];
            max_val = max(max_val, d[i]);
        }
        
        // If we have enough operations to reduce all differences to 0
        if (total_diff <= k) return 0;
        
        // Binary search for the optimal maximum difference threshold
        int left = 0, right = max_val;
        while (left < right) {
            int mid = left + (right - left) / 2;
            long long ops_needed = 0;
            for (int v : d) {
                if (v > mid) {
                    ops_needed += (v - mid);
                }
            }
            if (ops_needed <= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        // Reduce all differences to at most `left`
        for (int i = 0; i < n; ++i) {
            if (d[i] > left) {
                k -= (d[i] - left);
                d[i] = left;
            }
        }
        
        // Distribute any remaining budget of `k` by decrementing elements equal to `left`
        for (int i = 0; i < n && k > 0; ++i) {
            if (d[i] == left) {
                d[i]--;
                k--;
            }
        }
        
        // Calculate the final sum of squared differences
        long long ans = 0;
        for (int v : d) {
            ans += (long long)v * v;
        }
        
        return ans;
    }
};