class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        // Min-heap to store busy servers: pairs of {free_time, server_id}
        priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, greater<pair<int, int>>> busy_heap;
        
        // Set to store available (idle) server IDs
        set<int> idle_servers;
        for (int i = 0; i < k; ++i) {
            idle_servers.insert(i);
        }

        vector<int> request_count(k, 0);
        int n = arrival.size();

        for (int i = 0; i < n; ++i) {
            int arrival_time = arrival[i];
            int processing_time = load[i];

            // 1. Free up servers whose tasks are completed by the current arrival time
            while (!busy_heap.empty() && busy_heap.top().first <= arrival_time) {
                idle_servers.insert(busy_heap.top().second);
                busy_heap.pop();
            }

            // If no servers are available, drop the request
            if (idle_servers.empty()) {
                continue;
            }

            // 2. Find the preferred server using lower_bound for index >= (i % k)
            int preferred = i % k;
            auto it = idle_servers.lower_bound(preferred);

            // If no server >= preferred exists, wrap around to the beginning of the set
            if (it == idle_servers.end()) {
                it = idle_servers.begin();
            }

            int assigned_server = *it;

            // 3. Assign the request to the selected server
            idle_servers.erase(it);
            request_count[assigned_server]++;
            busy_heap.push({arrival_time + processing_time, assigned_server});
        }

        // 4. Find the maximum number of requests handled by any server
        int max_requests = 0;
        for (int count : request_count) {
            max_requests = max(max_requests, count);
        }

        // 5. Collect all servers that handled the maximum number of requests
        vector<int> result;
        for (int i = 0; i < k; ++i) {
            if (request_count[i] == max_requests) {
                result.push_back(i);
            }
        }

        return result;
    }
};