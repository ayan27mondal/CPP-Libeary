#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include <vector>
#include <queue>
#include <iostream>
#include <climits>

class Graph
{
private:
    struct Node
    {
        int _data;
        int _dist;
        int _start;
        int _finish;
        int _colour; // 0=white, 1=gray, 2=black
        Node* _parent;
        std::vector<int> _adj;

        explicit Node(int data) : _data(data), _dist(INT_MAX), _start(0), _finish(0), _colour(0), _parent(nullptr) {}
    };

    int _num_nodes;
    std::vector<Node*> _nodes;

    void clearNodes()
    {
        for (auto* n : _nodes) delete n;
        _nodes.clear();
    }

    void dfsVisit(Node* u, int& time, std::vector<int>& result)
    {
        u->_colour = 1;
        u->_start = ++time;

        for (int v_idx : u->_adj)
        {
            Node* v = _nodes[v_idx];
            if (v->_colour == 0)
            {
                v->_parent = u;
                dfsVisit(v, time, result);
            }
        }

        u->_colour = 2;
        u->_finish = ++time;
        result.push_back(u->_data);
    }

public:
    explicit Graph(int size = 0) : _num_nodes(size)
    {
        _nodes.reserve(size);
        for (int i = 0; i < size; ++i)
            _nodes.push_back(new Node(i));
    }

    ~Graph()
    {
        clearNodes();
    }

    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;

    Graph(Graph&& other) noexcept : _num_nodes(other._num_nodes), _nodes(std::move(other._nodes))
    {
        other._num_nodes = 0;
    }

    Graph& operator=(Graph&& other) noexcept
    {
        if (this != &other)
        {
            clearNodes();
            _num_nodes = other._num_nodes;
            _nodes = std::move(other._nodes);
            other._num_nodes = 0;
        }
        return *this;
    }

    void addEdge(int u, int v)
    {
        if (u >= 0 && u < _num_nodes && v >= 0 && v < _num_nodes)
        {
            _nodes[u]->_adj.push_back(v);
        }
    }

    void bfs(int start, std::vector<int>& result)
    {
        if (start < 0 || start >= _num_nodes) return;

        for (auto* n : _nodes)
        {
            n->_colour = 0;
            n->_dist = INT_MAX;
            n->_parent = nullptr;
        }

        Node* s = _nodes[start];
        s->_colour = 1;
        s->_dist = 0;

        std::queue<Node*> q;
        q.push(s);

        while (!q.empty())
        {
            Node* u = q.front();
            q.pop();
            result.push_back(u->_data);

            for (int v_idx : u->_adj)
            {
                Node* v = _nodes[v_idx];
                if (v->_colour == 0)
                {
                    v->_colour = 1;
                    v->_dist = u->_dist + 1;
                    v->_parent = u;
                    q.push(v);
                }
            }
            u->_colour = 2;
        }
    }

    void dfs(std::vector<int>& result)
    {
        for (auto* n : _nodes)
        {
            n->_colour = 0;
            n->_parent = nullptr;
            n->_start = 0;
            n->_finish = 0;
        }

        int time = 0;
        for (auto* n : _nodes)
        {
            if (n->_colour == 0)
                dfsVisit(n, time, result);
        }
    }

    void printGraph() const
    {
        for (int i = 0; i < _num_nodes; ++i)
        {
            std::cout << i << " -> ";
            for (int v : _nodes[i]->_adj)
                std::cout << v << " ";
            std::cout << std::endl;
        }
    }
};

#endif