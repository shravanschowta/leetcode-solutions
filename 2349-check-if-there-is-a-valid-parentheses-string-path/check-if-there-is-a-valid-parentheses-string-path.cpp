class Solution {
private:
    int m, n;
    vector<vector<vector<int>>> memo;

    bool dfs(int i, int j, int k, const vector<vector<char>>& grid) {
        k += (grid[i][j] == '(' ? 1 : -1);
        if (k < 0) return false;
        int remaining_steps = (m - 1 - i) + (n - 1 - j);
        if (k > remaining_steps) return false;
        if (i == m - 1 && j == n - 1) {
            return k == 0;
        }
        if (memo[i][j][k] != -1) {
            return memo[i][j][k];
        }

        bool down = false, right = false;
        if (i + 1 < m) down = dfs(i + 1, j, k, grid);
        if (j + 1 < n) right = dfs(i, j + 1, k, grid);

        return memo[i][j][k] = (down || right);
    }

public:
    bool hasValidPath(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();

        if ((m + n) % 2 == 0 || grid[0][0] == ')' || grid[m - 1][n - 1] == '(') {
            return false;
        }
        memo = vector<vector<vector<int>>>(m, vector<vector<int>>(n, vector<int>(m + n, -1)));

        return dfs(0, 0, 0, grid);
    }
};