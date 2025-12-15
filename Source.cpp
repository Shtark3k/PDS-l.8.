#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int MAX_N = 100;

int adj[MAX_N][MAX_N];
bool visited[MAX_N];
int dfsNumber[MAX_N];
int dfsCounter = 0;
int n, m;

int Stack[MAX_N];
int topIndex = -1;

void push(int v)
{
    topIndex++;
    Stack[topIndex] = v;
}

int pop()
{
    int v = Stack[topIndex];
    topIndex--;
    return v;
}

bool isEmpty()
{
    return topIndex == -1;
}

void printStack()
{
    cout << "[ ";
    for (int i = 0; i <= topIndex; i++)
    {
        cout << Stack[i] + 1 << " ";
    }
    cout << "]";
}

void DFS(int start)
{
    push(start);

    while (!isEmpty())
    {
        int v = pop();

        if (!visited[v])
        {
            visited[v] = true;
            dfsCounter++;
            dfsNumber[v] = dfsCounter;

            cout << "Current: " << v + 1
                << " | DFS-number: " << dfsNumber[v]
                << " | Stack: ";
            printStack();
            cout << "\n";

            for (int u = n - 1; u >= 0; u--)
            {
                if (adj[v][u] == 1 && !visited[u])
                {
                    push(u);
                }
            }
        }
    }
}

int main()
{
    string file;
    cout << "Enter input file name: ";
    cin >> file;

    ifstream fin(file);

    if (!fin.is_open())
    {
        cerr << "Error: cannot open file!\n";
        return 1;
    }

    fin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
        dfsNumber[i] = 0;

        for (int j = 0; j < n; j++)
        {
            adj[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++)
    {
        int u, v;
        fin >> u >> v;
        adj[u - 1][v - 1] = 1;
    }

    fin.close();

    int start;
    cout << "Enter start vertex: ";
    cin >> start;
    start--;

    cout << "\nDFS traversal protocol:\n";
    DFS(start);

    return 0;
}