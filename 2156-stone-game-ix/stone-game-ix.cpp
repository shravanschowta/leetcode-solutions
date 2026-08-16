class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        vector<int> cnt(3, 0);
        for (int stone : stones) {
            cnt[stone % 3]++;
        }

        // Case 1: Even number of 0-stones (they cancel each other out)
        if (cnt[0] % 2 == 0) {
            return cnt[1] > 0 && cnt[2] > 0;
        }

        // Case 2: Odd number of 0-stones (flips turn advantage)
        return abs(cnt[1] - cnt[2]) > 2;
    }
};
