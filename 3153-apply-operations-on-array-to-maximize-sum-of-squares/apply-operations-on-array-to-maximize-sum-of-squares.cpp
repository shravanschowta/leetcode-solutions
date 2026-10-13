class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        constexpr int kMod = 1'000'000'007;
        constexpr int kMaxBit = 30;
        int ans = 0;
        vector<int> count(kMaxBit);

        // Count the frequency of each bit across all numbers
        for (int num : nums) {
            for (int i = 0; i < kMaxBit; ++i) {
                if ((num >> i) & 1) {
                    ++count[i];
                }
            }
        }

        // Greedily construct the k largest possible numbers
        for (int i = 0; i < k; ++i) {
            int num = 0;
            for (int j = 0; j < kMaxBit; ++j) {
                if (count[j] > 0) {
                    num |= (1 << j);
                    --count[j];
                }
            }
            long long squared = 1LL * num * num;
            ans = (ans + squared) % kMod;
        }

        return ans;
    }
};