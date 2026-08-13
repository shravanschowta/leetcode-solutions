struct Node {
    int len = 0;
    int max_len = 0;
    int pref_len = 0;
    int suff_len = 0;
    char pref_char = 0;
    char suff_char = 0;
};

class Solution {
    vector<Node> tree;

    Node merge(const Node& L, const Node& R) {
        Node res;
        res.len = L.len + R.len;
        res.pref_char = L.pref_char;
        res.suff_char = R.suff_char;
        
        res.max_len = max(L.max_len, R.max_len);
        res.pref_len = L.pref_len;
        res.suff_len = R.suff_len;

        // If characters across the middle boundary match
        if (L.suff_char == R.pref_char) {
            res.max_len = max(res.max_len, L.suff_len + R.pref_len);

            // Left side is entirely uniform -> prefix extends into right side
            if (L.pref_len == L.len) {
                res.pref_len = L.len + R.pref_len;
            }
            // Right side is entirely uniform -> suffix extends into left side
            if (R.suff_len == R.len) {
                res.suff_len = R.len + L.suff_len;
            }
        }
        return res;
    }

    void build(const string& s, int i, int l, int r) {
        if (l == r) {
            tree[i] = {1, 1, 1, 1, s[l], s[l]}; // len, max_len, pref_len, suff_len, pref_char, suff_char
            return;
        }
        int mid = (l + r) / 2;
        build(s, 2 * i + 1, l, mid);
        build(s, 2 * i + 2, mid + 1, r);
        tree[i] = merge(tree[2 * i + 1], tree[2 * i + 2]);
    }

    void update(int i, int l, int r, int idx, char c) {
        if (l == r) {
            tree[i] = {1, 1, 1, 1, c, c};
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update(2 * i + 1, l, mid, idx, c);
        else            update(2 * i + 2, mid + 1, r, idx, c);

        tree[i] = merge(tree[2 * i + 1], tree[2 * i + 2]);
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.length();
        tree.resize(4 * n);
        
        build(s, 0, 0, n - 1);

        int q = queryIndices.size();
        vector<int> ans(q);

        for (int i = 0; i < q; ++i) {
            update(0, 0, n - 1, queryIndices[i], queryCharacters[i]);
            ans[i] = tree[0].max_len;
        }

        return ans;
    }
};