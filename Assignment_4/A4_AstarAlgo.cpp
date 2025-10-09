#include <bits/stdc++.h>
using namespace std;

struct Node {
    pair<int, int> position;   // (row, col)
    Node* parent;              // pointer to parent node
    int g, h, f;               // costs

    Node(pair<int, int> pos, Node* par, int g_cost, int h_cost) {
        position = pos;
        parent = par;
        g = g_cost;
        h = h_cost;
        f = g + h;
    }

    // Comparator for priority queue (min-heap based on f)
    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

// Heuristic: Manhattan distance
int heuristic(pair<int,int> a, pair<int,int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

vector<pair<int,int>> astar(vector<vector<int>>& grid, pair<int,int> start, pair<int,int> goal) {
    priority_queue<Node, vector<Node>, greater<Node>> open_list;
    set<pair<int,int>> closed_set;

    Node start_node(start, nullptr, 0, heuristic(start, goal));
    open_list.push(start_node);

    while (!open_list.empty()) {
        Node current = open_list.top();
        open_list.pop();

        if (current.position == goal) {
            // Reconstruct path
            vector<pair<int,int>> path;
            Node* node_ptr = new Node(current); // copy to pointer
            while (node_ptr != nullptr) {
                path.push_back(node_ptr->position);
                node_ptr = node_ptr->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        closed_set.insert(current.position);

        // Explore 4 neighbors
        vector<pair<int,int>> directions = {{0,1},{1,0},{0,-1},{-1,0}};
        for (auto [d_row, d_col] : directions) {
            pair<int,int> neighbor_pos = {current.position.first + d_row,
                                          current.position.second + d_col};

            // Boundary check
            if (neighbor_pos.first < 0 || neighbor_pos.first >= grid.size() ||
                neighbor_pos.second < 0 || neighbor_pos.second >= grid[0].size())
                continue;

            // Skip obstacles
            if (grid[neighbor_pos.first][neighbor_pos.second] == 1)
                continue;

            // Skip visited
            if (closed_set.count(neighbor_pos))
                continue;

            int g_cost = current.g + 1;
            int h_cost = heuristic(neighbor_pos, goal);

            Node neighbor(neighbor_pos, new Node(current), g_cost, h_cost);
            open_list.push(neighbor);
        }
    }

    return {}; // No path found
}

int main() {
    // Example Grid (0 = free, 1 = blocked)
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0}
    };

    pair<int,int> start = {0, 0}; // Top-left
    pair<int,int> goal = {4, 4};  // Bottom-right

    vector<pair<int,int>> path = astar(grid, start, goal);

    if (!path.empty()) {
        cout << "Path found: ";
        for (auto [r,c] : path) {
            cout << "(" << r << "," << c << ") ";
        }
        cout << endl;
    } else {
        cout << "No path found" << endl;
    }

    return 0;
}
