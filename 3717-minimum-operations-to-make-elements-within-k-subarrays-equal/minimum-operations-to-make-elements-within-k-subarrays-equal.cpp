class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        vector<long long> minOps = getWindowCosts(nums, x);
        
        // DP table: dp[i][rem] = min cost using 'rem' windows from index 'i' to n-1
        vector<vector<long long>> memo(n + 1, vector<long long>(k + 1, -1));
        
        auto dp = [&](auto& self, int i, int rem) -> long long {
            if (rem == 0) return 0;
            if (i > n - rem * x) return 1e18; // Not enough elements left
            if (memo[i][rem] != -1) return memo[i][rem];
            
            // Option 1: Skip index i
            long long skip = self(self, i + 1, rem);
            
            // Option 2: Pick subarray of size x starting at index i
            long long pick = minOps[i] + self(self, i + x, rem - 1);
            
            return memo[i][rem] = min(skip, pick);
        };
        
        return dp(dp, 0, k);
    }

private:
    vector<long long> getWindowCosts(const vector<int>& nums, int x) {
        int n = nums.size();
        vector<long long> minOps(n, 1e18);
        multiset<long long> lower, upper;
        long long lowerSum = 0, upperSum = 0;
        
        auto balance = [&]() {
            if (lower.size() < upper.size()) {
                long long val = *upper.begin();
                upper.erase(upper.begin());
                lower.insert(val);
                upperSum -= val;
                lowerSum += val;
            } else if (lower.size() - upper.size() > 1) {
                long long val = *lower.rbegin();
                lower.erase(lower.find(val)); // Erase only one instance
                upper.insert(val);
                lowerSum -= val;
                upperSum += val;
            }
        };
        
        for (int i = 0; i < n; ++i) {
            // Insert new element
            if (lower.empty() || nums[i] <= *lower.rbegin()) {
                lower.insert(nums[i]);
                lowerSum += nums[i];
            } else {
                upper.insert(nums[i]);
                upperSum += nums[i];
            }
            balance();
            
            // Remove element sliding out of the window
            if (i >= x) {
                long long outNum = nums[i - x];
                auto it = lower.find(outNum);
                if (it != lower.end()) {
                    lower.erase(it); // Erase single instance via iterator
                    lowerSum -= outNum;
                } else {
                    it = upper.find(outNum);
                    if (it != upper.end()) {
                        upper.erase(it); // Erase single instance via iterator
                        upperSum -= outNum;
                    }
                }
                balance();
            }
            
            // Record cost once window size reaches x
            if (i >= x - 1) {
                long long median = *lower.rbegin();
                long long ops = (median * lower.size() - lowerSum) + (upperSum - median * upper.size());
                minOps[i - x + 1] = ops; // Store at the start index of the window
            }
        }
        return minOps;
    }
};