#pragma once

#include "ISorter.h"

template <typename T, typename Comparator>
class BubbleSorter : public ISorter<T, Comparator> {
public:
    void Sort(SharedPtr<Sequence<T>> sequence, Comparator comp) override {
        int n = sequence->GetLength();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (comp(sequence->Get(j + 1), sequence->Get(j))) {
                    T temp = sequence->Get(j);
                    sequence->Set(j, sequence->Get(j + 1));
                    sequence->Set(j + 1, temp);
                }
            }
        }
    }
};