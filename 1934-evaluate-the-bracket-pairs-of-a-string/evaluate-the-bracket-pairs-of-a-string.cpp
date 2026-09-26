class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;
        for (const auto& pair : knowledge) {
            mp[pair[0]] = pair[1];
        }

        string result = "";
        int n = s.length();
        
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                int j = i + 1;
                while (j < n && s[j] != ')') {
                    j++;
                }
                string key = s.substr(i + 1, j - (i + 1));
                if (mp.find(key) != mp.end()) {
                    result += mp[key];
                } else {
                    result += "?";
                }
                i = j;
            } else {
                result += s[i];
            }
        }
        
        return result;
    }
};