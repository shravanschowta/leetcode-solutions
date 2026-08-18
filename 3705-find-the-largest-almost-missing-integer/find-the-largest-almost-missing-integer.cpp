class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }

        // Case 1: k == 1 -> Find max element with global frequency == 1
        if (k == 1) {
            int max_val = -1;
            for (auto& [num, count] : freq) {
                if (count == 1) {
                    max_val = max(max_val, num);
                }
            }
            return max_val;
        }

        // Case 2: k == n -> Any element appears in the only subarray of size n. Return max element.
        if (k == n) {
            int max_val = -1;
            for (int num : nums) {
                max_val = max(max_val, num);
            }
            return max_val;
        }

        // Case 3: 1 < k < n -> Only boundary elements (nums[0] and nums[n-1]) can appear in exactly 1 subarray
        int max_val = -1;
        if (freq[nums[0]] == 1) {
            max_val = max(max_val, nums[0]);
        }
        if (freq[nums[n - 1]] == 1) {
            max_val = max(max_val, nums[n - 1]);
        }

        return max_val;
    }
};