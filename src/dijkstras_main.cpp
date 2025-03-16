#include "dijkstras.h"
#include <iostream>

using namespace std;

void run_dijkstra(const string& filename, int source) {
    // Load the graph from file
    Graph G;
    try {
        file_to_graph(filename, G);
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
        return;
    }

    // Run Dijkstra's algorithm
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    // Print shortest paths from the source
    for (int destination = 0; destination < G.numVertices; destination++) {
        vector<int> path = extract_shortest_path(distances, previous, destination);

        // Print path
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i < path.size() - 1) cout << " ";
        }
        cout << endl;

        // Print total cost
        cout << "Total cost is " << (distances[destination] == INF ? "INF" : to_string(distances[destination])) << endl;
    }
}

// g++ dijkstras.cpp dijkstras_main.cpp -o dijkstras_main
// ./dijkstras_main
int main() {
    run_dijkstra("small.txt", 0);
    return 0;
}
