class Solution {
public:
    vector<string> braceExpansionII(string expression) {
        int i = 0;
        unordered_set<string> result = parse(expression, i);
        vector<string> res(result.begin(), result.end());
        sort(res.begin(), res.end());
        return res;
    }

private:
    unordered_set<string> parse(const string& s, int& i) {
        unordered_set<string> current;
        current.insert("");
        
        while (i < s.size() && s[i] != '}') {
            if (s[i] == ',') {
                i++;
                unordered_set<string> next = parse(s, i);
                current.insert(next.begin(), next.end());
            } else if (s[i] == '{') {
                i++;
                unordered_set<string> inner = parse(s, i);
                i++; // skip '}'
                unordered_set<string> next;
                for (const string& prefix : current) {
                    for (const string& suffix : inner) {
                        next.insert(prefix + suffix);
                    }
                }
                current = next;
            } else {
                string word = "";
                while (i < s.size() && isalpha(s[i])) {
                    word += s[i++];
                }
                unordered_set<string> next;
                for (const string& prefix : current) {
                    next.insert(prefix + word);
                }
                current = next;
            }
        }
        return current;
    }
};