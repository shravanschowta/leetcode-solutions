class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        
        // Initialize closestSum with the first valid triplet sum
        int closestSum = nums[0] + nums[1] + nums[2];
        
        for (int i = 0; i < n - 2; ++i) {
            // Skip duplicate fixed elements
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            
            int start = i + 1;
            int end = n - 1;
            
            while (start < end) {
                int currentSum = nums[i] + nums[start] + nums[end];
                
                // If we hit target exactly, distance is 0—return immediately
                if (currentSum == target) {
                    return currentSum;
                }
                
                // Update closestSum if currentSum is closer to target
                if (abs(currentSum - target) < abs(closestSum - target)) {
                    closestSum = currentSum;
                }
                
                // Move pointers conditionally based on comparison to target
                if (currentSum < target) {
                    start++;
                } else {
                    end--;
                }
            }
        }
        
        return closestSum;
    }
};