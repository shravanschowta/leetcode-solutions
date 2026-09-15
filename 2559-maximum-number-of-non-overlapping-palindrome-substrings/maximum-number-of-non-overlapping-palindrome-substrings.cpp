class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();
        
        // dp[i][j] will be true if the substring s[i...j] is a palindrome
        vector<vector<bool>> dp(n, vector<bool>(n, true));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                dp[i][j] = (s[i] == s[j]) && dp[i + 1][j - 1];
            }
        }
        
        vector<int> memo(n, -1);
        
        // Lambda function for DFS with memoization
        auto dfs = [&](auto& self, int i) -> int {
            if (i >= n) return 0;
            if (memo[i] != -1) return memo[i];
            
            // Option 1: Skip the current character
            int res = self(self, i + 1);
            
            // Option 2: Try to form a palindrome starting at i with length >= k
            for (int j = i + k - 1; j < n; ++j) {
                if (dp[i][j]) {
                    // Greedily pick the shortest valid palindrome starting at i
                    res = max(res, 1 + self(self, j + 1));
                    break; 
                }
            }
            
            return memo[i] = res;
        };
        
        return dfs(dfs, 0);
    }
};