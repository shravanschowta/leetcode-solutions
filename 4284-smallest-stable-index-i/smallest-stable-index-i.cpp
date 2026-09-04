class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> minimum(n);
        minimum[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            minimum[i] = min(minimum[i + 1], nums[i]);
        }
        int current_max = 0;
        for (int i = 0; i < n; ++i) {
            current_max = max(current_max, nums[i]);
            if (current_max-minimum[i] <= k) {
                return i;
            }
        }
        return -1;
    }
};