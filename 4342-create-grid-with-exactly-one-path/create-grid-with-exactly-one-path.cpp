class Solution {
public:
    vector<string> createGrid(int m, int n) {
        // Initialize the grid filled with '#' (obstacles)
        vector<string> g(m, string(n, '#'));
        
        // Open the entire first row
        g[0] = string(n, '.');
        
        // Open the last column of every row
        for (int i = 0; i < m; ++i) {
            g[i][n - 1] = '.';
        }
        
        return g;
    }
};