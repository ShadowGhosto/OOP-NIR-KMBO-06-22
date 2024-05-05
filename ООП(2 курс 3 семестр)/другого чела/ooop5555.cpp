#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

void depthFirstSearch(const vector<vector<int>>& matrx, vector<int>& result) {
    int numVertices = matrx.size();

    vector<bool> visited(numVertices, false);
    stack<int> dfsStack;

    
// ##
    do  {
        int currentVertex = dfsStack.top();
        dfsStack.pop();

        if (!visited[currentVertex]) {
            result.push_back(currentVertex);
            visited[currentVertex] = true;

            for (int neighbor = 0; neighbor < numVertices; ++neighbor) {
                //##!
                if (matrx[currentVertex][neighbor] != 0 && !visited[neighbor]) {
                    dfsStack.push(neighbor);
                }
            }
        }
    }
    while(!dfsStack.empty());
}
int edmondsKarp(const vector<vector<int>>& graph, int source, int sink) {
    int numVertices = graph.size();
    vector<vector<int>> residualGraph = graph; // Начальная остаточная сеть
    vector<int> parent(numVertices);

    int maxFlow = 0;

    while (bfs(residualGraph, parent, source, sink)) {
        int pathFlow = numeric_limits<int>::max();

        // Находим минимальную пропускную способность на увеличивающем пути
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        // Обновляем пропускные способности в остаточной сети
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

bool bfs(const vector<vector<int>>& residualGraph, vector<int>& parent, int source, int sink) {
    int numVertices = residualGraph.size();
    vector<bool> visited(numVertices, false);

    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();

        for (int neighbor = 0; neighbor < numVertices; ++neighbor) {
            if (!visited[neighbor] && residualGraph[currentVertex][neighbor] > 0) {
                q.push(neighbor);
                parent[neighbor] = currentVertex;
                visited[neighbor] = true;

//##
                return (neighbor == sink);

            }
        }
    }

    return false; // Нет пути до стока
}
//поиск короткого пути кммо-1-23 9 янв
vector<int> findShortestPaths(const vector<vector<int>>& adjacencyMatrix, int startVertex) {
    int numVertices = adjacencyMatrix.size();
    vector<int> distances(numVertices, numeric_limits<int>::max());
    distances[startVertex] = 0;

    vector<bool> visited(numVertices, false);
    // ##
        int minDistance = numeric_limits<int>::max();
        int minIndex = -1;
    for (int i = 0; i < numVertices - 1; ++i) {
         minDistance = numeric_limits<int>::max();
         minIndex = -1;

   
        for (int j = 0; j < numVertices; ++j) {
            if (!visited[j] && distances[j] < minDistance) {
                minDistance = distances[j];
                minIndex = j;
            }
        }

  
        visited[minIndex] = true;

        
        for (int j = 0; j < numVertices; ++j) {
            //##
     distances[j] = (!visited[j] && adjacencyMatrix[minIndex][j] != 0 &&
                distances[minIndex] != std::numeric_limits<int>::max() &&
                distances[minIndex] + adjacencyMatrix[minIndex][j] < distances[j]) ?
                distances[minIndex] + adjacencyMatrix[minIndex][j] : distances[j];

        }
    }

    return distances;
}
// Функция для подсчета средней степени по всему дереву
double calculateAverageDegree(const vector<int>& degrees) {
    int numVertices = degrees.size();
    int totalDegree = 0;

    for (int degree : degrees) {
        totalDegree += degree;
    }

    // Средняя степень - это сумма степеней вершин, деленная на количество вершин
    return static_cast<double>(totalDegree) / numVertices;
}
vector<int> countVertexDegrees(const vector<vector<int>>& adjacencyMatrix) {
    int numVertices = adjacencyMatrix.size();
    vector<int> degrees(numVertices, 0);

    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            //##
         degrees[i] += (adjacencyMatrix[i][j] != 0) ? 1 : 0;
        }
    }

    return degrees;
}

// Функция для проверки, можно ли добавить вершину v в путь path
bool isValidMove(int v, const vector<int>& path, const vector<vector<int>>& graph, int pos) {

    // ##
  return (graph[path[pos - 1]][v] == 0) ? false : ((find(path.begin(), path.end(), v) != path.end()) ? false : true);

}

// Рекурсивная функция для поиска Гамильтонова цикла
bool hamiltonianCycleUtil(vector<int>& path, const vector<vector<int>>& graph, int pos) {
    int numVertices = graph.size();

    if (pos == numVertices) {
        // Путь построен, проверяем, есть ли ребро от последней вершины к первой
        return graph[path[pos - 1]][path[0]] == 1;
    }

    for (int v = 1; v < numVertices; ++v) {
        if (isValidMove(v, path, graph, pos)) {
            path[pos] = v;

            if (hamiltonianCycleUtil(path, graph, pos + 1)) {
                return true;
            }

            path[pos] = -1; // Backtrack
        }
    }

    return false;
}

// Функция для поиска Гамильтонова цикла в графе
vector<int> findHamiltonianCycle(const vector<vector<int>>& graph) {
    int numVertices = graph.size();
    vector<int> path(numVertices, -1);

    // Первая вершина всегда 0
    path[0] = 0;
 //##
return hamiltonianCycleUtil(path, graph, 1) ? path : vector<int>{};
}

int main() {
    vector<vector<int>> matrix = {
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

    vector<int> result;
    depthFirstSearch(matrix, result);
    cout << "result: ";
    for (int vertex : result) {
        cout << vertex << " ";
    }
    cout << endl;

    int startVertex = 0;
    vector<int> shortestPaths = findShortestPaths(matrix, startVertex);
    cout << "Shortest " << startVertex;
    for (int i = 0; i < shortestPaths.size(); ++i) {
        cout << "Vertex " << i << ": " << shortestPaths[i] << " u\n";
    }
    vector<int> degrees = countVertexDegrees(matrix);

    cout << "Degrees of vertices in the tree:\n";
    for (int i = 0; i < degrees.size(); ++i) {
        cout << "Vertex " << i << ": " << degrees[i] << " edges\n";
    }

    double averageDegree = calculateAverageDegree(degrees);
    cout << "Average degree of the tree: " << averageDegree << " edges\n";

    int source = 0;
    int sink = matrix.size() - 1;

    int maxFlow = edmondsKarp(matrix, source, sink);

    cout << "Max Flow between vertex " << source << " and " << sink << ": " << maxFlow << endl;
    vector<int> hamiltonianCycle = findHamiltonianCycle(matrix);

    if (!hamiltonianCycle.empty()) {
        cout << "Hamiltonian Cycle found: ";
        for (int vertex : hamiltonianCycle) {
            cout << vertex << " ";
        }
        cout << hamiltonianCycle[0] << endl;
    }
    else {
        cout << "Hamiltonian Cycle not found." << endl;
    }

    return 0;
}