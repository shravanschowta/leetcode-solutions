class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
    int n = static_cast<int>(items.size());
        vector<int> free_cnt(n, 0);

        for (int i = 0; i < n; ++i) {
            int fi = items[i][0];
            for (int j = 0; j < n; ++j) {
                if (i != j && items[j][0] % fi == 0) {
                    ++free_cnt[i];
                }
            }
        }

        vector<int> dp(budget + 1, 0);

        for (int i = 0; i < n; ++i) {
            int price = items[i][1];
            int bonus = free_cnt[i];   
            if (price > budget) continue;

            // 1. First purchase of item i: gain 1 copy + bonus free copies (at most once)
            for (int b = budget; b >= price; --b) {
                dp[b] = max(dp[b], dp[b - price] + 1 + bonus);
            }

            // 2. Subsequent purchases of item i: gain 1 copy each (unlimited)
            for (int b = price; b <= budget; ++b) {
                dp[b] = max(dp[b], dp[b - price] + 1);
            }
        }
        return dp[budget];
                
    }
};