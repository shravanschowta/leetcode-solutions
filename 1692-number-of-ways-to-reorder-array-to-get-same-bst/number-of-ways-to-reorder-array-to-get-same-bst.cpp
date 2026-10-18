class Solution {
    long long MOD = 1e9 + 7;
    vector<vector<long long>> table;

    long long dfs(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2) return 1;

        vector<int> left, right;
        int root = nums[0];
        
        for (int i = 1; i < n; ++i) {
            if (nums[i] < root) {
                left.push_back(nums[i]);
            } else {
                right.push_back(nums[i]);
            }
        }

        long long left_ways = dfs(left);
        long long right_ways = dfs(right);

        // Ways to interleave left and right elements: C(left.size() + right.size(), left.size())
        long long ways = table[n - 1][left.size()];
        
        ways = (ways * left_ways) % MOD;
        ways = (ways * right_ways) % MOD;

        return ways;
    }

public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        
        // Initialize Pascal's triangle for binomial coefficients
        table.resize(n + 1, vector<long long>(n + 1, 1));
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                table[i][j] = (table[i - 1][j - 1] + table[i - 1][j]) % MOD;
            }
        }

        return (dfs(nums) - 1 + MOD) % MOD;
    }
};