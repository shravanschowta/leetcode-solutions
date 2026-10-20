class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        
        // Precompute prefix maximums, suffix minimums, and drop counts
        vector<int> prefMax(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefMax[i + 1] = max(prefMax[i], nums[i]);
        }
        
        vector<int> suffMin(n + 1, INT_MAX);
        for (int i = n - 1; i >= 0; i--) {
            suffMin[i] = min(nums[i], suffMin[i + 1]);
        }
        
        vector<int> prefDrop(n, 0);
        for (int i = 1; i < n; i++) {
            prefDrop[i] = prefDrop[i - 1] + (nums[i - 1] > nums[i] ? 1 : 0);
        }
        
        auto getDrops = [&](int l, int r) {
            int drops = prefDrop[r] - prefDrop[l];
            if (nums[r] > nums[l]) {
                drops++;
            }
            return drops;
        };
        
        int totalSum = 0;
        
        // Check all divisors k of n
        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;
            
            bool possible = true;
            for (int i = 0; i < n; i += k) {
                int l = i;
                int r = i + k - 1;
                
                // Check if the block can be rotated to be non-decreasing
                if (getDrops(l, r) > 1) {
                    possible = false;
                    break;
                }
                
                // Check inter-block ordering constraints
                if (l > 0 && prefMax[l] > suffMin[l]) {
                    possible = false;
                    break;
                }
            }
            
            if (possible) {
                totalSum += k;
            }
        }
        
        return totalSum;
    }
};