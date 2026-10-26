class Solution {
private:
    long long dfs(vector<vector<int>>& grid, int r, int c) {
        int m = grid.size();
        int n = grid[0].size();
        
        long long current_sum = grid[r][c];
        grid[r][c] = 0; 
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] > 0) {
                current_sum += dfs(grid, nr, nc);
            }
        }
        return current_sum;
    }
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        if (m == 0) return 0;
        int n = grid[0].size();
        
        int count = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] > 0) {
                    long long total_value = dfs(grid, i, j);
                    if (total_value % k == 0) {
                        count++;
                    }
                }
            }
        }
        return count;
    }
};