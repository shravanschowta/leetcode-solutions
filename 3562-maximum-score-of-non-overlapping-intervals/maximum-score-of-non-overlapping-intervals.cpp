#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& input) {
        int n = input.size();
        vector<tuple<int, int, int, int>> intervals;
        for (int i = 0; i < n; ++i) {
            intervals.emplace_back(input[i][0], input[i][1], input[i][2], i);
        }
        ranges::sort(intervals);

        // memo[i][quota] stores {weight, selected_indices}
        vector<vector<pair<long long, vector<int>>>> memo(n, vector<pair<long long, vector<int>>>(5, {-1, {}}));

        auto solve = [&](auto& self, int i, int quota) -> pair<long long, vector<int>> {
            if (i == intervals.size() || quota == 0) return {0, {}};
            if (memo[i][quota].first != -1) return memo[i][quota];

            // Option 1: Skip the current interval
            auto skip = self(self, i + 1, quota);

            // Option 2: Pick the current interval
            auto [l, r, weight, originalIndex] = intervals[i];
            
            // Binary search to find the first interval that starts strictly after 'r'
            int low = i + 1, high = intervals.size(), j = intervals.size();
            while (low < high) {
                int mid = low + (high - low) / 2;
                if (get<0>(intervals[mid]) > r) {
                    j = mid;
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }

            auto nextRes = self(self, j, quota - 1);
            vector<int> newSelected = nextRes.second;
            newSelected.push_back(originalIndex);
            ranges::sort(newSelected);
            pair<long long, vector<int>> pick = {weight + nextRes.first, newSelected};

            // Choose the option with maximum weight; break ties with lexicographically smaller indices
            if (pick.first > skip.first || (pick.first == skip.first && pick.second < skip.second)) {
                return memo[i][quota] = pick;
            }
            return memo[i][quota] = skip;
        };

        return solve(solve, 0, 4).second;
    }
};