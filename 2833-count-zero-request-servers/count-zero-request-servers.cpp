class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        // Sort logs by time
        sort(logs.begin(), logs.end(), [](const auto& a, const auto& b) {
            return a[1] < b[1];
        });

        int m = queries.size();
        vector<vector<int>> qs(m);
        for (int i = 0; i < m; ++i) {
            qs[i] = {queries[i], i};
        }
        
        // Sort queries by time while keeping track of original indices
        sort(qs.begin(), qs.end());

        vector<int> ans(m);
        unordered_map<int, int> cnt; // Tracks server request counts in the current window
        int k = 0, j = 0;
        int num_logs = logs.size();

        for (int i = 0; i < m; ++i) {
            int q = qs[i][0];
            int idx = qs[i][1];
            int l = q - x;
            int r = q;

            // Add logs that fall within or up to time r
            while (k < num_logs && logs[k][1] <= r) {
                cnt[logs[k][0]]++;
                k++;
            }
            
            // Remove logs that are older than the left window boundary l
            while (j < num_logs && logs[j][1] < l) {
                cnt[logs[j][0]]--;
                if (cnt[logs[j][0]] == 0) {
                    cnt.erase(logs[j][0]);
                }
                j++;
            }

            // Servers with zero requests = Total servers - servers with at least one request
            ans[idx] = n - cnt.size();
        }

        return ans;
    }
};
