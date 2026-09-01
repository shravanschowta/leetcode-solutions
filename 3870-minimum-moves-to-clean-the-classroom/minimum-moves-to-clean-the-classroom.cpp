class Solution {
public:
    int minMoves(vector<string>& classroom, int maxEnergy) {
        int m = classroom.size();
        int n = classroom[0].size();
        
        int startX = -1, startY = -1;
        vector<vector<int>> litterIdx(m, vector<int>(n, -1));
        int totalLitter = 0;
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'S') {
                    startX = i;
                    startY = j;
                } else if (classroom[i][j] == 'L') {
                    litterIdx[i][j] = totalLitter++;
                }
            }
        }
        
        // Target bitmask when all litter items are collected
        int targetMask = (1 << totalLitter) - 1;
        
        if (targetMask == 0) return 0; // No litter to collect
        
        // Initial state
        int startMask = 0;
        if (litterIdx[startX][startY] != -1) {
            startMask |= (1 << litterIdx[startX][startY]);
        }
        
        // visited[r][c][energy][mask]
        vector<vector<vector<vector<bool>>>> visited(
            m, vector<vector<vector<bool>>>(
                n, vector<vector<bool>>(
                    maxEnergy + 1, vector<bool>(1 << totalLitter, false)
                )
            )
        );
        
        // Queue stores tuple: {row, col, remaining_energy, litter_mask}
        queue<tuple<int, int, int, int>> q;
        q.push({startX, startY, maxEnergy, startMask});
        visited[startX][startY][maxEnergy][startMask] = true;
        
        int steps = 0;
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto [r, c, e, mask] = q.front();
                q.pop();
                
                if (mask == targetMask) {
                    return steps;
                }
                
                if (e == 0) continue; // Out of energy, cannot move further
                
                for (auto& dir : dirs) {
                    int nr = r + dir[0];
                    int nc = c + dir[1];
                    
                    // Check bounds and obstacles
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n || classroom[nr][nc] == 'X') {
                        continue;
                    }
                    
                    int nextEnergy = e - 1;
                    if (classroom[nr][nc] == 'R') {
                        nextEnergy = maxEnergy; // Energy reset area
                    }
                    
                    int nextMask = mask;
                    if (litterIdx[nr][nc] != -1) {
                        nextMask |= (1 << litterIdx[nr][nc]);
                    }
                    
                    if (!visited[nr][nc][nextEnergy][nextMask]) {
                        visited[nr][nc][nextEnergy][nextMask] = true;
                        q.push({nr, nc, nextEnergy, nextMask});
                    }
                }
            }
            steps++;
        }
        
        return -1; // Unable to collect all litter items
    }
};