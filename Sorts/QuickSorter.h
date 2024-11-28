#pragma once

#include "ISorter.h"
#include <algorithm> 

template <typename T, typename Comparator>
class QuickSorter : public ISorter<T, Comparator> {
private:
    void QuickSortImpl(SharedPtr<Sequence<T>> sequence, int low, int high, Comparator comp) {
        if (low < high) {
            int partitionIndex = Partition(sequence, low, high, comp);
            QuickSortImpl(sequence, low, partitionIndex - 1, comp);
            QuickSortImpl(sequence, partitionIndex + 1, high, comp);
        }
    }

    int Partition(SharedPtr<Sequence<T>> sequence, int low, int high, Comparator comp) {
        int mid = low + (high - low) / 2;
        if (comp(sequence->Get(high), sequence->Get(low))) std::swap(sequence->Get(low), sequence->Get(high));
        if (comp(sequence->Get(mid), sequence->Get(low))) std::swap(sequence->Get(low), sequence->Get(mid));
        if (comp(sequence->Get(high), sequence->Get(mid))) std::swap(sequence->Get(mid), sequence->Get(high));
        T pivot = sequence->Get(mid);

        std::swap(sequence->Get(mid), sequence->Get(high));


        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (comp(sequence->Get(j), pivot)) {
                i++;
                std::swap(sequence->Get(i), sequence->Get(j));
            }
        }
        std::swap(sequence->Get(i + 1), sequence->Get(high));
        return (i + 1);
    }

public:
    void Sort(SharedPtr<Sequence<T>> sequence, Comparator comp) override {
        if (sequence->GetLength() <= 1) return;
        QuickSortImpl(sequence, 0, sequence->GetLength() - 1, comp);
    }
};