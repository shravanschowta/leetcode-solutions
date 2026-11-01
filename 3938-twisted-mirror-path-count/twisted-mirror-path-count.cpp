class Solution {
    const int MOD = 1e9 + 7;

    // Helper function with memoization: 
    // dir = 0 means we entered coming from the left (moving right)
    // dir = 1 means we entered coming from above (moving down)
    long long solve(int i, int j, int dir, int m, int n, const vector<vector<int>>& grid, vector<vector<vector<long long>>>& memo) {
        // Base case: out of bounds
        if (i < 0 || i >= m || j < 0 || j >= n) return 0;
        
        // Base case: reached bottom-right destination
        if (i == m - 1 && j == n - 1) return 1;

        if (memo[i][j][dir] != -1) return memo[i][j][dir];

        long long ways = 0;

        if (grid[i][j] == 1) {
            // Mirror cell: reflects based on incoming direction
            if (dir == 0) {
                // Entered moving right -> redirected down to (i + 1, j)
                ways = solve(i + 1, j, 1, m, n, grid, memo);
            } else {
                // Entered moving down -> redirected right to (i, j + 1)
                ways = solve(i, j + 1, 0, m, n, grid, memo);
            }
        } else {
            // Empty cell: can choose to continue moving or branch out
            if (dir == 0) {
                // If we came from left, we can move Right or Down next
                ways = (solve(i, j + 1, 0, m, n, grid, memo) + solve(i + 1, j, 1, m, n, grid, memo)) % MOD;
            } else {
                // If we came from above, we can move Right or Down next
                ways = (solve(i, j + 1, 0, m, n, grid, memo) + solve(i + 1, j, 1, m, n, grid, memo)) % MOD;
            }
        }

        return memo[i][j][dir] = ways;
    }

public:
    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // If start or end has a mirror constraint violation inherently
        if (grid[0][0] == 1 || grid[m - 1][n - 1] == 1) return 0;

        // Memoization table: dimensions [m][n][2]
        vector<vector<vector<long long>>> memo(m, vector<vector<long long>>(n, vector<long long>(2, -1)));

        // From the start position (0,0), we can initiate by moving right (dir = 0) or down (dir = 1)
        long long ans1 = solve(0, 1, 0, m, n, grid, memo); // Moving right initially
        long long ans2 = solve(1, 0, 1, m, n, grid, memo); // Moving down initially

        return (ans1 + ans2) % MOD;
    }
};