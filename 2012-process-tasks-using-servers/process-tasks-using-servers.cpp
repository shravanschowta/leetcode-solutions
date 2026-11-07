class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> idle;
        for (int i = 0; i < n; ++i) {
            idle.push({servers[i], i});
        }
        
        // Min-heap for busy servers: (free_time, weight, index)
        priority_queue<pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>>>, greater<pair<long long, pair<int, int>>>> busy;
        
        vector<int> ans(m);
        long long current_time = 0;
        
        for (int j = 0; j < m; ++j) {
            // Ensure time is at least the current task's arrival time j
            current_time = max(current_time, (long long)j);
            
            // Free up all servers that have finished their jobs by current_time
            while (!busy.empty() && busy.top().first <= current_time) {
                auto [free_time, server_info] = busy.top();
                busy.pop();
                idle.push(server_info);
            }
            
            // If no servers are idle, fast-forward time to when the next server becomes free
            if (idle.empty()) {
                current_time = busy.top().first;
                while (!busy.empty() && busy.top().first <= current_time) {
                    auto [free_time, server_info] = busy.top();
                    busy.pop();
                    idle.push(server_info);
                }
            }
            
            // Assign the task to the best available server
            auto [weight, index] = idle.top();
            idle.pop();
            
            ans[j] = index;
            busy.push({current_time + tasks[j], {weight, index}});
        }
        
        return ans;
    }
};