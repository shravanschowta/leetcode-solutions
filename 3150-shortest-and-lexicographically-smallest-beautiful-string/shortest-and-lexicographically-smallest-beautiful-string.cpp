class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.length();
        string result = "";
        int minLen = n + 1;
        
        int onesCount = 0;
        int left = 0;

        for (int right = 0; right < n; ++right) {
            if (s[right] == '1') {
                onesCount++;
            }

            while (onesCount == k) {
                int currentLen = right - left + 1;
                string currentSub = s.substr(left, currentLen);


                if (currentLen < minLen) {
                    minLen = currentLen;
                    result = currentSub;
                } else if (currentLen == minLen) {
                    result = min(result, currentSub);
                }

                if (s[left] == '1') {
                    onesCount--;
                }
                left++;
            }
        }

        return result;
    }
};