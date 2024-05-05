#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void depthFirstSearch(const vector<vector<int>>& matrx) {
    int numVertices = matrx.size();

    vector<bool> visited(numVertices, false);
    stack<int> dfsStack;

    dfsStack.push(0);

    cout << "result: ";

    while (!dfsStack.empty()) {
        int currentVertex = dfsStack.top();
        dfsStack.pop();

        if (!visited[currentVertex]) {
            cout << currentVertex << " ";
            visited[currentVertex] = true;

            for (int neighbor = 0; neighbor < numVertices; ++neighbor) {
                if (matrx[currentVertex][neighbor] != 0 && !visited[neighbor]) {
                    dfsStack.push(neighbor);
                }
            }
        }
    }

    cout << endl;
    
}

int main() {
    vector<vector<int>> adjacencyMatrix = {
        {0, 6, 5, 6, 7, 5, 8, 8, 2},
        {6, 0, 2, 5, 1, 4, 4, 3, 2},
        {5, 2, 0, 0, 6, 7, 5, 4, 2},
        {6, 5, 0, 0, 2, 4, 1, 7, 4},
        {7, 1, 6, 2, 0, 8, 0, 9, 5},
        {5, 4, 7, 4, 8, 0, 9, 8, 0},
        {8, 4, 5, 1, 0, 9, 0, 7, 5},
        {8, 3, 4, 7, 9, 8, 7, 0, 7},
        {2, 2, 2, 4, 5, 0, 5, 7, 0}
    };

    depthFirstSearch(adjacencyMatrix);

    return 0;
}
