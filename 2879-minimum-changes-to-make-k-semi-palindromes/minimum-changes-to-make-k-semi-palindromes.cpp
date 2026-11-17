class Solution {
public:
    int minimumChanges(string s, int k) {
        int n=s.length();
        vector<vector<int>>cost(n,vector<int>(n, 1e9)); 
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int len = j - i + 1;
                int min_c = 1e9; 
                for (int d = 1; d < len; ++d) {
                    if (len % d != 0) continue;
                    int group_len = len / d;
                    int curr_changes = 0;
                    for (int c = 0; c < d; ++c) {
                        for (int k = 0; k < group_len / 2; ++k) {
                            int left_idx = i + c + k * d;
                            int right_idx = i + c + (group_len - 1 - k) * d;
                            if (s[left_idx] != s[right_idx]) {
                                curr_changes++;
                            }
                        }
                    }
                    min_c = min(min_c, curr_changes);
                }
                cost[i][j] = min_c;
            }
        }
        
        // dp[i][j] represents the minimum changes to partition prefix s[0...i] into j parts
        vector<vector<int>> dp(n, vector<int>(k + 1, 1e9));
        
        for (int i = 0; i < n; ++i) {
            dp[i][1] = cost[0][i];
        }
        
        for (int j = 2; j <= k; ++j) {
            for (int i = j - 1; i < n; ++i) {
                for (int m = j - 2; m < i; ++m) {
                    dp[i][j] = min(dp[i][j], dp[m][j - 1] + cost[m + 1][i]);
                }
            }
        }
        
        return dp[n-1][k];
    }
};