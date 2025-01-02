#include <iostream>
using namespace std;

void BFS(int graph[7][7], int n, int start) {
    bool visited[7] = {false};
    int queue[7], front = 0, rear = 0;

    cout << "BFS traversal: ";
    queue[rear++] = start;
    visited[start] = true;

    while (front < rear) {
        int node = queue[front++];
        cout << char('a' + node) << " ";

        for (int i = 0; i < n; ++i) {
            if (graph[node][i] == 1 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = true;
            }
        }
    }
    cout << endl;
}

void DFS(int graph[7][7], int n, int start) {
    bool visited[7] = {false};
    int stack[7], top = -1;

    cout << "DFS traversal: ";
    stack[++top] = start;

    while (top >= 0) {
        int node = stack[top--];

        if (!visited[node]) {
            cout << char('a' + node) << " ";
            visited[node] = true;
        }

        for (int i = n - 1; i >= 0; --i) {
            if (graph[node][i] == 1 && !visited[i]) {
                stack[++top] = i;
            }
        }
    }
    cout << endl;
}

int main() {
    int n = 7;
    int graph[7][7] = {
        {0, 1, 0, 1, 1, 0, 1},
        {0, 0, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 1},
        {1, 0, 1, 0, 0, 1, 1},
        {0, 1, 0, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 1, 0, 0}
    };

    cout << "Enter the starting vertex: ";
    char startVertex;
    cin >> startVertex;
    int start = startVertex - 'a';

    if (start < 0 || start >= n) {
        cout << "Not" << endl;
        return 1;
    }

    BFS(graph, n, start);
    DFS(graph, n, start);

    return 0;
}
