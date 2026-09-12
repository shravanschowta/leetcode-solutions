
class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        unordered_set<int> s;
        int n = digits.size();
        
        for (int i = 0; i < n; ++i) {
            // Ones place must be even
            if (digits[i] % 2 != 0) {
                continue;
            }
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    continue;
                }
                for (int k = 0; k < n; ++k) {
                    // Hundreds place cannot be 0, and indices must be unique
                    if (digits[k] == 0 || k == i || k == j) {
                        continue;
                    }
                    s.insert(digits[k] * 100 + digits[j] * 10 + digits[i]);
                }
            }
        }
        
        return s.size();
    }
};
