#include <iostream>
#include <vector>
using namespace std;

class Graph {
private:
    int V; // Number of vertices
    vector<vector<int>> adjMatrix;

public:
    Graph(int vertices) : V(vertices) {
        // Initialize adjacency matrix with zeros
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int from, int to, int weight) {
        // Add edge in both directions (undirected graph)
        adjMatrix[from][to] = weight;
        adjMatrix[to][from] = weight;  // For undirected graph
    }

    void printGraph() {
        cout << "\nAdjacency Matrix Representation:\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\nEdges with weights:\n";
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                if (adjMatrix[i][j] != 0) {
                    cout << "Node" << i+1 << " ===== " 
                         << adjMatrix[i][j] << " ===== Node" 
                         << j+1 << endl;
                }
            }
        }
    }
        void displayVertices() {
        cout << "\nVertices in the graph:\n";
        for (int i = 0; i < V; i++) {
            cout << "Node" << i+1;
            // Print adjacent vertices with their weights
            cout << " -> Adjacent nodes: ";
            bool hasAdjacent = false;
            for (int j = 0; j < V; j++) {
                if (adjMatrix[i][j] != 0) {
                    if (hasAdjacent) cout << ", ";
                    cout << "Node" << j+1 << "(weight: " << adjMatrix[i][j] << ")";
                    hasAdjacent = true;
                }
            }
            if (!hasAdjacent) cout << "None";
            cout << endl;
        }
    }
};

int main() {
    // Create a graph with 5 nodes (0-4 representing nodes 1-5)
    Graph g(5);

    // Add edges with weights as per your diagram
    g.addEdge(0, 1, 5);  // node1 - node2 weight 5
    g.addEdge(0, 2, 3);  // node1 - node3 weight 3
    g.addEdge(1, 3, 2);  // node2 - node4 weight 2
    g.addEdge(2, 4, 4);  // node3 - node5 weight 4
    g.addEdge(3, 2, 3);  // node4 - node3 weight 3

    // Print the graph
    g.printGraph();
    g.displayVertices();

    return 0;
}