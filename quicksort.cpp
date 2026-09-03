#include <iostream>
#include <vector>
using namespace std;

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int Partition(vector<int> &a, int p, int r)
{
    int x = a[r];
    int i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (a[j] <= x)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[r]);
    return i + 1;
}

void QuickSort(vector<int> &a, int p, int r)
{
    if (p < r)
    {
        int q = Partition(a, p, r);
        QuickSort(a, p, q - 1);
        QuickSort(a, q + 1, r);
    }
}

template <typename T>
ostream &operator<<(ostream &out, const vector<T> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        out << v[i] << " ";
    }
    out << endl;
    return out;
}

int main()
{
    int n, x;
    vector<int> arr;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> x;
        arr.push_back(x);
    }
    QuickSort(arr, 0, arr.size() - 1);
    cout << arr;
    return 0;
}