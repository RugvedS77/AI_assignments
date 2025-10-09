#include <bits/stdc++.h>
using namespace std;

class GraphColoring {
    int V;                          // number of vertices
    vector<vector<int>> adj;        // adjacency list
    vector<int> colors;             // color assignment
    int numColors;                  // max colors allowed

public:
    GraphColoring(int V, int numColors) : V(V), numColors(numColors) {
        adj.resize(V);
        colors.resize(V, 0); // 0 means uncolored
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected graph
    }

    bool isSafe(int v, int c) {
        for (int neighbor : adj[v]) {
            if (colors[neighbor] == c) return false;
        }
        return true;
    }

    bool solveUtil(int v) {
        if (v == V) return true; // all vertices colored

        for (int c = 1; c <= numColors; c++) {
            if (isSafe(v, c)) {
                colors[v] = c;
                if (solveUtil(v + 1)) return true;
                colors[v] = 0; // backtrack
            }
        }
        return false;
    }

    void solve() {
        if (!solveUtil(0)) {
            cout << "No solution exists with " << numColors << " colors.\n";
            return;
        }

        cout << "Solution found with " << numColors << " colors:\n";
        for (int v = 0; v < V; v++) {
            cout << "Vertex " << v << " ---> Color " << colors[v] << "\n";
        }
    }
};

int main() {
    int V = 4;        // number of vertices
    int numColors = 3; // number of colors allowed

    GraphColoring g(V, numColors);

    // Example: Complete graph K4
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);

    g.solve();

    return 0;
}
