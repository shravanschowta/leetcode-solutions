class Solution {
public:
    int numberOfSets(int n, int k) {
        long long MOD = 1e9 + 7;
        int total = n + k - 1;
        int r = 2 * k;
        
        // We need to compute Combination C(total, r) % MOD
        // C(total, r) = total! / (r! * (total - r)!)
        if (r > total) return 0;
        
        vector<long long> inv(r + 1, 0);
        inv[1] = 1;
        for (int i = 2; i <= r; ++i) {
            inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
        }
        
        long long res = 1;
        for (int i = 1; i <= r; ++i) {
            res = res * (total - i + 1) % MOD;
            res = res * inv[i] % MOD;
        }
        
        return res;
    }
};