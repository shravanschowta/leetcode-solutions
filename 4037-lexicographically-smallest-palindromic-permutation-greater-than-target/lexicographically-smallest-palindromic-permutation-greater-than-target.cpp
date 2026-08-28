class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.length();
        vector<int> count(26, 0);
        for (char c : s) count[c - 'a']++;

        // 1. Feasibility check
        int oddCount = 0;
        char middleChar = 0;
        for (int i = 0; i < 26; ++i) {
            if (count[i] % 2 != 0) {
                oddCount++;
                middleChar = 'a' + i;
            }
        }
        if (oddCount > 1) return "";

        int halfLen = n / 2;
        vector<int> avail(26, 0);
        for (int i = 0; i < 26; ++i) avail[i] = count[i] / 2;

        // Step 1: Try matching target[0 ... halfLen-1] greedily
        string prefix = "";
        int matched = 0;
        for (int i = 0; i < halfLen; ++i) {
            int c = target[i] - 'a';
            if (avail[c] > 0) {
                avail[c]--;
                prefix.push_back(target[i]);
                matched++;
            } else {
                break;
            }
        }

        // Helper to check if full palindrome formed from current prefix beats target
        auto isStrictlyGreater = [&](const string& halfPrefix, const vector<int>& rem) {
            string full = halfPrefix;
            for (int c = 0; c < 26; ++c) {
                full.append(rem[c], 'a' + c);
            }
            string rev = full;
            reverse(rev.begin(), rev.end());
            if (n % 2 != 0) full += middleChar;
            full += rev;
            return full > target;
        };

        // Step 2: Check if exact prefix match works (if we matched all halfLen characters)
        if (matched == halfLen) {
            if (isStrictlyGreater(prefix, avail)) {
                string rev = prefix;
                reverse(rev.begin(), rev.end());
                return (n % 2 != 0) ? prefix + middleChar + rev : prefix + rev;
            }
        }

        // Step 3: Backtrack from matched length to find a pivot position p where we pick char > target[p]
        for (int p = matched; p >= 0; --p) {
            if (p < matched) {
                // Return character at position p back to available pool
                avail[prefix.back() - 'a']++;
                prefix.pop_back();
            }

            char tChar = (p < halfLen) ? target[p] : 'a' - 1;
            
            // Try placing smallest character > target[p]
            for (int c = tChar - 'a' + 1; c < 26; ++c) {
                if (avail[c] > 0) {
                    prefix.push_back('a' + c);
                    avail[c]--;

                    // Fill remaining positions with smallest available chars
                    for (int remC = 0; remC < 26; ++remC) {
                        prefix.append(avail[remC], 'a' + remC);
                    }

                    string rev = prefix;
                    reverse(rev.begin(), rev.end());
                    return (n % 2 != 0) ? prefix + middleChar + rev : prefix + rev;
                }
            }
        }

        return "";
    }
};