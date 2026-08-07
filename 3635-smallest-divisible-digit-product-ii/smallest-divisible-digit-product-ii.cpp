
class Solution {
    // Structure to represent prime factor counts for 2, 3, 5, 7
    struct Factors {
        int c2 = 0, c3 = 0, c5 = 0, c7 = 0;

        bool isSatisfied() const {
            return c2 <= 0 && c3 <= 0 && c5 <= 0 && c7 <= 0;
        }

        // Returns the minimal digits required to satisfy factors
        string getMinDigits() const {
            int t2 = max(0, c2), t3 = max(0, c3);
            int t5 = max(0, c5), t7 = max(0, c7);

            string res = "";
            // Greedy packing into single-digit numbers 9 down to 2
            while (t3 >= 2) { res += '9'; t3 -= 2; }
            while (t2 >= 3) { res += '8'; t2 -= 3; }
            while (t7 >= 1) { res += '7'; t7 -= 1; }
            if (t2 >= 1 && t3 >= 1) { res += '6'; t2--; t3--; }
            while (t5 >= 1) { res += '5'; t5 -= 1; }
            while (t2 >= 2) { res += '4'; t2 -= 2; }
            while (t3 >= 1) { res += '3'; t3 -= 1; }
            while (t2 >= 1) { res += '2'; t2 -= 1; }

            sort(res.begin(), res.end());
            return res;
        }
    };

    Factors getFactors(long long t) {
        Factors f;
        while (t % 2 == 0) { f.c2++; t /= 2; }
        while (t % 3 == 0) { f.c3++; t /= 3; }
        while (t % 5 == 0) { f.c5++; t /= 5; }
        while (t % 7 == 0) { f.c7++; t /= 7; }
        if (t > 1) return {-1, -1, -1, -1}; // Invalid prime factor
        return f;
    }

    void removeDigitFactors(Factors& f, int digit) {
        if (digit == 2) f.c2--;
        else if (digit == 3) f.c3--;
        else if (digit == 4) f.c2 -= 2;
        else if (digit == 5) f.c5--;
        else if (digit == 6) { f.c2--; f.c3--; }
        else if (digit == 7) f.c7--;
        else if (digit == 8) f.c2 -= 3;
        else if (digit == 9) f.c3 -= 2;
    }

public:
    string smallestNumber(string num, long long t) {
        Factors req = getFactors(t);
        if (req.c2 == -1) return "-1"; // t contains prime factor > 7

        int n = num.length();

        // Step 1: Precalculate product factors of num's prefixes
        vector<Factors> prefix_factors(n + 1);
        prefix_factors[0] = req;

        int first_zero = -1;
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                first_zero = i;
                break;
            }
            prefix_factors[i + 1] = prefix_factors[i];
            removeDigitFactors(prefix_factors[i + 1], num[i] - '0');
        }

        // Case A: num itself is valid (no zeros and satisfies factors)
        if (first_zero == -1 && prefix_factors[n].isSatisfied()) {
            return num;
        }

        // Step 2: Try matching prefix up to length i, then change digit at i
        int max_prefix = (first_zero == -1) ? n - 1 : first_zero;

        for (int i = max_prefix; i >= 0; --i) {
            int start_digit = (num[i] - '0') + 1;

            for (int d = start_digit; d <= 9; ++d) {
                Factors cur = prefix_factors[i];
                removeDigitFactors(cur, d);

                string min_suffix = cur.getMinDigits();
                int rem_len = n - 1 - i;

                if (min_suffix.length() <= rem_len) {
                    string ans = num.substr(0, i) + to_string(d);
                    int ones = rem_len - min_suffix.length();
                    ans += string(ones, '1') + min_suffix;
                    return ans;
                }
            }
        }

        // Step 3: If no answer of same length, expand to length n + 1
        string min_digits = req.getMinDigits();
        int target_len = max((int)num.length() + 1, (int)min_digits.length());
        int ones = target_len - min_digits.length();

        return string(ones, '1') + min_digits;
    }
};