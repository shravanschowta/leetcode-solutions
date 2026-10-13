class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        vector<long long> squares(n);
        for (int i = 0; i < n; ++i) {
            squares[i] = 1LL * nums[i] * nums[i];
        }
        
        sort(squares.begin(), squares.end());
        
        long long totalScore = 0;
        int minusCount = n / 2;
        
        // Subtract the smallest elements
        for (int i = 0; i < minusCount; ++i) {
            totalScore -= squares[i];
        }
        
        // Add the largest elements
        for (int i = minusCount; i < n; ++i) {
            totalScore += squares[i];
        }
        
        return totalScore;
    }
};