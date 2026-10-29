class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        
        auto suneravilo = make_tuple(n, ref(edges), ref(s), ref(queries));

        vector<vector<int>> adj(n);

        for (auto &edge : edges) {
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> parent(n, -1), depth(n, 0);
        vector<int> size(n, 1), heavy(n, -1), head(n);

        iota(head.begin(), head.end(), 0);

        // Find parent, depth and subtree size
        vector<int> order;
        vector<int> st = {0};

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();

            order.push_back(u);

            for (int v : adj[u]) {
                if (v == parent[u]) continue;

                parent[v] = u;
                depth[v] = depth[u] + 1;
                st.push_back(v);
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            int u = order[i];

            for (int v : adj[u]) {
                if (parent[v] == u) {
                    size[u] += size[v];

                    if (heavy[u] == -1 ||
                        size[v] > size[heavy[u]]) {
                        heavy[u] = v;
                    }
                }
            }
        }

        // Give each node a position in the tree
        vector<int> left(n), right(n);
        int timer = 0;

        vector<pair<int, int>> todo = {{0, 0}};

        while (!todo.empty()) {
            auto [u, h] = todo.back();
            todo.pop_back();

            head[u] = h;
            left[u] = timer++;

            for (int v : adj[u]) {
                if (parent[v] == u && v != heavy[u]) {
                    todo.push_back({v, v});
                }
            }

            if (heavy[u] != -1) {
                todo.push_back({heavy[u], h});
            }
        }

        for (int u = 0; u < n; u++) {
            right[u] = left[u] + size[u] - 1;
        }

        // Prefix XOR mask for every node
        vector<int> prefix(n);

        for (int u : order) {
            prefix[u] = (1 << (s[u] - 'a'));

            if (parent[u] != -1) {
                prefix[u] ^= prefix[parent[u]];
            }
        }

        // Fenwick tree for XOR updates
        struct BIT {
            int n;
            vector<int> bit;

            BIT(int n) : n(n), bit(n + 1, 0) {}

            void update(int i, int value) {
                for (++i; i <= n; i += i & -i) {
                    bit[i] ^= value;
                }
            }

            int query(int i) {
                int ans = 0;

                for (++i; i > 0; i -= i & -i) {
                    ans ^= bit[i];
                }

                return ans;
            }
        };

        BIT bit(n + 1);

        // Find lowest common ancestor
        auto lca = [&](int u, int v) {
            while (head[u] != head[v]) {
                if (depth[head[u]] < depth[head[v]]) {
                    swap(u, v);
                }

                u = parent[head[u]];
            }

            return depth[u] < depth[v] ? u : v;
        };

        vector<bool> answer;

        for (string &q : queries) {
            istringstream in(q);
            string op;
            in >> op;

            if (op == "update") {
                int u;
                char c;
                in >> u >> c;

                int oldMask = 1 << (s[u] - 'a');
                int newMask = 1 << (c - 'a');
                int diff = oldMask ^ newMask;

                if (diff != 0) {
                    s[u] = c;
                    bit.update(left[u], diff);
                    bit.update(right[u] + 1, diff);
                }
            } else {
                int u, v;
                in >> u >> v;

                int p = lca(u, v);

                int mask = (prefix[u] ^ bit.query(left[u])) ^
                           (prefix[v] ^ bit.query(left[v])) ^
                           (1 << (s[p] - 'a'));

                answer.push_back((mask & (mask - 1)) == 0);
            }
        }

        return answer;
    }
};