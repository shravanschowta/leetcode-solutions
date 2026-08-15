class Solution {
private:
    int maxScoreDiff(const std::vector<int>& nums, int i, int j, std::vector<std::vector<int>>& memo) {
        // Base case: only one element left
        if (i == j) {
            return nums[i];
        }
        
        // Return cached result if already computed
        if (memo[i][j] != -1) {
            return memo[i][j];
        }
        
        // Choice 1: Take nums[i]
        int takeLeft = nums[i] - maxScoreDiff(nums, i + 1, j, memo);
        
        // Choice 2: Take nums[j]
        int takeRight = nums[j] - maxScoreDiff(nums, i, j - 1, memo);
        
        // Pick the best outcome for the current player
        return memo[i][j] = max(takeLeft, takeRight);
    }

public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> memo(n,vector<int>(n, -1));
        
        return maxScoreDiff(nums, 0, n - 1, memo) >= 0;
    }
};