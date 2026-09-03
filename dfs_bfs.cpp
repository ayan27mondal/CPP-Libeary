// #ifndef __DFS_BFS_HPP__
// #define __DFS_BFS_HPP__

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

template <typename T>
ostream &operator<<(ostream &out, const vector<T> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        out << v[i] << ' ';
    }
    out << '\n';
    return out;
}

int inf = 10000000;
int tm = 0;

class Graph
{
private:
    class node
    {
    public:
        int _data;
        node(const int &data) : _data(data) {}
        int _dist;
        int _start;
        int _finish;
        int _colour;
        node *_parent;
    };
    int num_nodes;
    vector<pair<node, vector<node>>> arr;

public:
    Graph(int size, vector<pair<int, vector<int>>> adj)
    {
        num_nodes = size;
        vector<node> list;
        for (int i = 0; i < num_nodes; i++)
        {
            for (int j = 0; j < adj[i].second.size(); j++)
            {
                list.push_back(node(adj[i].second[j]));
            }
            arr.push_back(make_pair(i, list));
            list.clear();
        }
    }

    void printgraph()
    {
        for (int i = 0; i < num_nodes; i++)
        {
            cout << i << " -> ";
            vector<node> u = arr[i].second;
            for (int j = 0; j < u.size(); j++)
            {
                cout << arr[i].second[j]._data;
            }
            cout << endl;
        }
    }

    void BFS(int n)
    {
        node *s = &arr[n].first;
        for (int i = 0; i < num_nodes; i++)
        {
            if (i != n)
            {
                node *u = &arr[i].first;
                u->_colour = 0; // white
                u->_dist = inf;
                u->_parent = NULL;
            }
        }
        s->_colour = 1; // grey
        s->_dist = 0;
        s->_parent = NULL;

        queue<node *> q;
        q.push(&arr[n].first);
        while (!q.empty())
        {
            node *u = q.front();
            q.pop();
            cout << u->_data << " ";
            for (int i = 0; i < arr[u->_data].second.size(); i++)
            {
                if (arr[arr[u->_data].second[i]._data].first._colour == 0)
                {
                    arr[arr[u->_data].second[i]._data].first._colour = 1;
                    arr[arr[u->_data].second[i]._data].first._dist = arr[u->_data].first._dist + 1;
                    arr[arr[u->_data].second[i]._data].first._parent = &arr[u->_data].first;
                    q.push(&arr[arr[u->_data].second[i]._data].first);
                }
            }
            arr[u->_data].first._colour = 2; // black
        }
        cout << endl;
    }

    void DFS()
    {
        for (int i = 0; i < num_nodes; i++)
        {
            node *u = &arr[i].first;
            u->_colour = 0; // white
            u->_parent = NULL;
            u->_start = 0;
            u->_finish = 0;
        }

        for (int i = 0; i < num_nodes; i++)
        {
            node *u = &arr[i].first;
            if (u->_colour == 0)
            {
                DFSVisit(u);
            }
        }
    }

    void DFSVisit(node *u)
    {
        tm++;
        u->_start = tm;
        u->_colour = 1; // grey

        for (int i = 0; i < arr[u->_data].second.size(); i++)
        {
            if (arr[arr[u->_data].second[i]._data].first._colour == 0)
            {
                arr[arr[u->_data].second[i]._data].first._colour = 1;
                arr[arr[u->_data].second[i]._data].first._parent = &arr[u->_data].first;
                DFSVisit(&arr[arr[u->_data].second[i]._data].first);
            }
        }
        u->_colour = 2;
        cout << u->_data << " ";
        tm++;
        u->_finish = tm;
    }
};

int main()
{
    int n;
    cin >> n;
    vector<int> list;
    vector<pair<int, vector<int>>> v;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        for (int j = 0; j < x; j++)
        {
            int y;
            cin >> y;
            list.push_back(y);
        }
        v.push_back(make_pair(i, list));
        list.clear();
    }

    Graph g(n, v);
    g.BFS(0);
    g.DFS();
}

// #endif