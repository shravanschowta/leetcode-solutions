class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int ans = INT_MAX;
        int sum = 0;
        // best[i] stores the minimum length of a valid subarray with sum = target in arr[0..i]
        vector<int> best(arr.size(), INT_MAX);
        
        for (int l = 0, r = 0; r < arr.size(); ++r) {
            sum += arr[r];
            
            // Shrink the window from the left if the sum exceeds the target
            while (sum > target) {
                sum -= arr[l++];
            }
            
            // If we found a valid subarray with sum equal to target
            if (sum == target) {
                // Check if there's a non-overlapping valid subarray to the left
                if (l > 0 && best[l - 1] != INT_MAX) {
                    ans = min(ans, best[l - 1] + r - l + 1);
                }
                best[r] = r - l + 1;
            }
            
            // Propagate the minimum length forward
            if (r > 0) {
                best[r] = min(best[r], best[r - 1]);
            }
        }
        
        return ans == INT_MAX ? -1 : ans;
    }
};