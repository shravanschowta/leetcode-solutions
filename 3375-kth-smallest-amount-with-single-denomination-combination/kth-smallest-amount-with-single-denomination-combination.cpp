class Solution {
private:
    // Helper function to calculate Greatest Common Divisor
    long long gcd(long long a, long long b) {
        return std::gcd(a, b);
    }

    // Helper function to calculate Least Common Multiple avoiding overflow
    long long lcm(long long a, long long b) {
        if (a == 0 || b == 0) return 0;
        return (a / gcd(a, b)) * b;
    }

    // Counts numbers <= target that are divisible by at least one coin
    long long countMultiples(long long target, const vector<int>& coins) {
        int n = coins.size();
        long long count = 0;

        // Iterate through all 2^n - 1 non-empty subsets using a bitmask
        for (int mask = 1; mask < (1 << n); ++mask) {
            long long currentLcm = 1;
            int bitsCount = 0;
            bool overflow = false;

            for (int i = 0; i < n; ++i) {
                if ((mask >> i) & 1) {
                    bitsCount++;
                    currentLcm = lcm(currentLcm, coins[i]);
                    // If LCM exceeds target, this subset contributes 0 multiples
                    if (currentLcm > target) {
                        overflow = true;
                        break;
                    }
                }
            }

            if (overflow) continue;

            // Apply Inclusion-Exclusion Principle
            if (bitsCount % 2 == 1) {
                count += target / currentLcm;
            } else {
                count -= target / currentLcm;
            }
        }

        return count;
    }

public:
    long long findKthSmallest(vector<int>& coins, int k) {
        long long low = 1;
        long long high = (long long)*min_element(coins.begin(), coins.end()) * k;
        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            if (countMultiples(mid, coins) >= k) {
                ans = mid;
                high = mid - 1; // Try to find a smaller valid value
            } else {
                low = mid + 1;  // Not enough multiples, look higher
            }
        }

        return ans;
    }
};