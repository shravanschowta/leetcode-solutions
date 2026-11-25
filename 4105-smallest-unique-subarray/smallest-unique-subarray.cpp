class Solution {
private:
    static constexpr long long BASE1 = 1000003LL;
    static constexpr long long MOD1  = 1000000007LL;
    static constexpr long long BASE2 = 1000033LL;
    static constexpr long long MOD2  = 1000000009LL;

    vector<long long> pow1, pow2;

    static uint64_t pack(long long h1, long long h2) {
        return (static_cast<uint64_t>(h1) << 32) | static_cast<uint32_t>(h2);
    }

    bool hasUniqueOfLength(const vector<int>& nums, int len) {
        int n = static_cast<int>(nums.size());
        if (len == n) return true;

        long long h1 = 0, h2 = 0;
        for (int i = 0; i < len; ++i) {
            h1 = (h1 * BASE1 + nums[i]) % MOD1;
            h2 = (h2 * BASE2 + nums[i]) % MOD2;
        }

        unordered_map<uint64_t, int> freq;
        freq.reserve(n - len + 1);
        freq[pack(h1, h2)] = 1;

        long long p1 = pow1[len - 1];
        long long p2 = pow2[len - 1];

        for (int i = len; i < n; ++i) {
            long long outVal = nums[i - len];
            long long inVal = nums[i];

            h1 = (h1 - (outVal * p1) % MOD1 + MOD1) % MOD1;
            h1 = (h1 * BASE1 + inVal) % MOD1;

            h2 = (h2 - (outVal * p2) % MOD2 + MOD2) % MOD2;
            h2 = (h2 * BASE2 + inVal) % MOD2;

            ++freq[pack(h1, h2)];
        }

        for (const auto& [_, cnt] : freq) {
            if (cnt == 1) return true;
        }
        return false;
    }

public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        pow1.assign(n + 1, 1);
        pow2.assign(n + 1, 1);

        for (int i = 1; i <= n; ++i) {
            pow1[i] = (pow1[i - 1] * BASE1) % MOD1;
            pow2[i] = (pow2[i - 1] * BASE2) % MOD2;
        }

        int lo = 1, hi = n, ans = n;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (hasUniqueOfLength(nums, mid)) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return ans;
    }
};