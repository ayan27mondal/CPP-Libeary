#include "graph.hpp"

int main()
{
    int n;
    std::cin >> n;

    Graph g(n);

    for (int i = 0; i < n; ++i)
    {
        int x;
        std::cin >> x;
        for (int j = 0; j < x; ++j)
        {
            int y;
            std::cin >> y;
            g.addEdge(i, y);
        }
    }

    std::vector<int> bfs_result, dfs_result;
    g.bfs(0, bfs_result);
    g.dfs(dfs_result);

    std::cout << "BFS: ";
    for (int v : bfs_result) std::cout << v << " ";
    std::cout << std::endl;

    std::cout << "DFS: ";
    for (int v : dfs_result) std::cout << v << " ";
    std::cout << std::endl;

    return 0;
}