class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {

        // Number of nodes in the graph.
        // Nodes are numbered from 0 to n-1.
        int n = graph.size();


        // Create a mask where all n bits are 1.
        // This represents the state where every node has been visited.
        int all_nodes = (1 << n) - 1;


        // dist[mask][node] stores the shortest distance to reach
        // 'node' after visiting exactly the nodes represented by 'mask'.
        vector<vector<int>> dist(1 << n, vector<int>(n, INT_MAX));


        // BFS queue stores the current state as {mask, current_node}.
        // mask = nodes visited, current_node = where we currently are.
        queue<pair<int, int>> q;


        // We can start from any node, so add every node as a starting state.
        // Starting at node i means only node i has been visited, with distance 0.
        for (int i = 0; i < n; i++) {

            // Set bit i to 1 to indicate that node i has been visited.
            // Example: i = 2 → 1 << 2 = 0100.
            int mask = 1 << i;

            // Starting states have distance 0 because no edge was traversed.
            // Add this starting state to the BFS queue.
            dist[mask][i] = 0;
            q.push({mask, i});
        }


        // BFS processes states level by level: distance 0, then 1, then 2...
        // Since every edge costs 1, the first time we reach a state is shortest.
        while (!q.empty()) {

            // Get the next state from the front of the queue.
            // The state tells us which nodes are visited and our current node.
            auto [mask, current_node] = q.front();
            q.pop();


            // If every node has been visited, we have completed our goal.
            // BFS guarantees this is the shortest possible path.
            if (mask == all_nodes) {
                return dist[mask][current_node];
            }


            // Try moving from the current node to each of its neighbors.
            // Every move costs exactly 1 edge.
            for (int nbr : graph[current_node]) {

                // Set the bit corresponding to nbr to mark it as visited.
                // OR keeps all previously visited nodes while adding nbr.
                int new_mask = mask | (1 << nbr);


                // Check whether this (new_mask, nbr) state was visited before.
                // INT_MAX means we have not reached this state yet.
                if (dist[new_mask][nbr] == INT_MAX) {

                    // Reaching nbr requires one more edge than the current state.
                    // Because BFS processes by distance, this is the shortest distance.
                    dist[new_mask][nbr] = dist[mask][current_node] + 1;


                    // Add the newly discovered state to the BFS queue.
                    // It will be processed later to explore its neighbors.
                    q.push({new_mask, nbr});
                }
            }
        }


        // The graph is connected in this problem, so this should never be reached.
        // Return -1 as a safety fallback if no valid path exists.
        return -1;
    }
};