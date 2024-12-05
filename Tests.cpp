// // Tests.cpp
// #include "ArraySequence.h"
// #include "Sorts/ISorter.h"
// #include "Sorts/BubbleSorter.h"
// #include "Sorts/QuickSorter.h"
// #include "Sorts/HeapSorter.h"
// #include "Students.h"
//
//
// #include <cassert>
// #include <iostream>
// #include <vector>
// #include <functional>
// #include <random>
// #include <chrono>
// #include <algorithm>
// #include <map>
//
//
// template <typename T, typename Comparator>
// bool isSorted(const SharedPtr<Sequence<T>>& sequence, Comparator comp) {
//     for (int i = 0; i < sequence->GetLength() - 1; ++i) {
//         if (comp(sequence->Get(i + 1), sequence->Get(i))) {
//             return false;
//         }
//     }
//     return true;
// }
//
//
//
// template <typename T, typename Sorter>
// void testSorter(Sorter& sorter, std::function<bool(const T&, const T&)> comp, const std::string& sorterName) {
//     std::cout << "Testing " << sorterName << ":\n";
//
//     std::vector<std::vector<T>> testCases;
//     std::vector<std::vector<T>> expectedAsc, expectedDesc;
//     if constexpr (std::is_same_v<T, int>) {
//         testCases = {
//                 {},
//                 {5},
//                 {3, 1, 2},
//                 {1, 2, 3},
//                 {3, 2, 1},
//                 {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5},
//                 {-500, 10000, -10, 52, 0}
//
//         };
//
//         expectedAsc = {
//                 {},
//                 {5},
//                 {1, 2, 3},
//                 {1, 2, 3},
//                 {1, 2, 3},
//                 {1, 1, 2, 3, 3, 4, 5, 5, 5, 6, 9},
//                 {-500, -10, 0, 52, 10000}
//         };
//
//         expectedDesc = {
//                 {},
//                 {5},
//                 {3, 2, 1},
//                 {3, 2, 1},
//                 {3, 2, 1},
//                 {9, 6, 5, 5, 5, 4, 3, 3, 2, 1, 1},
//                 {10000, 52, 0, -10, -500}
//
//         };
//
//     } else if constexpr (std::is_same_v<T, Student>) {
//         testCases = {
//                 {},
//                 {{"Ivan", "Ivanov", 2001, 101}},
//         };
//
//         expectedAsc = {
//             {},
//             {{"Ivan", "Ivanov", 2001, 101}},
//         };
//
//         expectedDesc = {
//                 {},
//                 {{"Ivan", "Ivanov", 2001, 101}},
//         };
//
//     }
//
//
//
//     auto compareLess = [](const T& a, const T& b) { return a < b; };
//     auto compareGreater = [](const T& a, const T& b) { return a > b; };
//     auto comparator = comp(testCases[1][0], testCases[2][0]) ? compareLess : compareGreater;
//
//
//
//
//     for (const auto& testCase : testCases) {
//         SharedPtr<Sequence<T>> seq(new ArraySequence<T>(testCase.data(), testCase.size()));
//         SharedPtr<Sequence<T>> seqCopy = seq->Copy();
//
//
//         sorter.Sort(seq, comparator);
//         assert(isSorted(seq, comparator));
//
//         std::vector<T> currentExpected;
//
//         currentExpected = comp(testCase[0], testCase[1]) ? expectedAsc[std::distance(testCases.begin(), std::find(testCases.begin(), testCases.end(), testCase))]: expectedDesc[std::distance(testCases.begin(), std::find(testCases.begin(), testCases.end(), testCase))];
//         assert(seq->GetLength() == currentExpected.size());
//         for (size_t j = 0; j < currentExpected.size(); j++) {
//             assert(seq->Get(j) == currentExpected[j]);
//         }
//
//
//
//     }
//
//
//
//
//     std::cout << "\n";
// }
//
//
//
//
//
// void testSorts() {
//     std::function<bool(int, int)> compareInts = [](int a, int b) { return a < b; };
//     std::function<bool(const Student&, const Student&)> compareStudents = [](const Student& s1, const Student& s2) { return s1.getBirthYear() < s2.getBirthYear(); };
//
//
//     using IntSorter = ISorter<int, decltype(compareInts)>;
//     using StudentSorter = ISorter<Student, decltype(compareStudents)>;
//
//     std::map<std::string, IntSorter*> intSorters;
//     std::map<std::string, StudentSorter*> studentSorters;
//
//
//     intSorters["Bubble Sort"] = new BubbleSorter<int, decltype(compareInts)>();
//     intSorters["Quick Sort"] = new QuickSorter<int, decltype(compareInts)>();
//     intSorters["Heap Sort"] = new HeapSorter<int, decltype(compareInts)>();
//
//     studentSorters["Bubble Sort"] = new BubbleSorter<Student, decltype(compareStudents)>();
//     studentSorters["Quick Sort"] = new QuickSorter<Student, decltype(compareStudents)>();
//     studentSorters["Heap Sort"] = new HeapSorter<Student, decltype(compareStudents)>();
//
//
//     for (const auto& pair : intSorters) {
//         testSorter<int>(*pair.second, compareInts, pair.first);
//         delete pair.second;
//     }
//
//
//     for (const auto& pair : studentSorters) {
//         testSorter<Student>(*pair.second, compareStudents, pair.first);
//         delete pair.second;
//     }
//
// }
//
//
//
//
// bool runAllTests() {
//     try {
//         testSorts();
//         return true;
//     } catch (const std::exception& e) {
//         std::cerr << "Test failed: " << e.what() << std::endl;
//         return false;
//     }
// }