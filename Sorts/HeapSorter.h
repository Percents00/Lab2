#pragma once

#include "ISorter.h"
#include <algorithm>

template <typename T, typename Comparator>
class HeapSorter : public ISorter<T, Comparator> {
private:
    void Heapify(SharedPtr<Sequence<T>> sequence, int n, int i, Comparator comp) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && comp(sequence->Get(largest), sequence->Get(left))) {
            largest = left;
        }

        if (right < n && comp(sequence->Get(largest), sequence->Get(right))) {
            largest = right;
        }


        if (largest != i) {
            std::swap(sequence->Get(i), sequence->Get(largest));
            Heapify(sequence, n, largest, comp);
        }
    }

public:
    void Sort(SharedPtr<Sequence<T>> sequence, Comparator comp) override {
        int n = sequence->GetLength();
        if (n <= 1) return;

        for (int i = n / 2 - 1; i >= 0; i--) {
            Heapify(sequence, n, i, comp);
        }

        for (int i = n - 1; i > 0; i--) {
            std::swap(sequence->Get(0), sequence->Get(i));
            Heapify(sequence, i, 0, comp);
        }
    }
};