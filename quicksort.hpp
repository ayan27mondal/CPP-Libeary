#ifndef __QUICKSORT_HPP__
#define __QUICKSORT_HPP__

#include <vector>
#include <algorithm>

template <typename T>
int partition(std::vector<T>& a, int p, int r)
{
    T x = a[r];
    int i = p - 1;
    for (int j = p; j < r; ++j)
    {
        if (a[j] <= x)
        {
            ++i;
            std::swap(a[i], a[j]);
        }
    }
    std::swap(a[i + 1], a[r]);
    return i + 1;
}

template <typename T>
void quickSort(std::vector<T>& a, int p, int r)
{
    if (p < r)
    {
        int q = partition(a, p, r);
        quickSort(a, p, q - 1);
        quickSort(a, q + 1, r);
    }
}

template <typename T>
void quickSort(std::vector<T>& a)
{
    quickSort(a, 0, static_cast<int>(a.size()) - 1);
}

#endif