#include "ArraySequence.h"
#include "Sorts/BubbleSorter.h"
#include "Sorts/QuickSorter.h"
#include "Sorts/HeapSorter.h"
#include "Students.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>


template <typename T>
bool compareLess(const T& a, const T& b) {
    return a < b;
}

template <typename T>
bool compareGreater(const T& a, const T& b) {
    return a > b;
}


void testBubbleSort() {
    std::cout << "Testing Bubble Sort..." << std::endl;

    SharedPtr<Sequence<int>> emptySeq(new ArraySequence<int>());
    BubbleSorter<int, bool(*)(const int&, const int&)> bubbleSorter;
    bubbleSorter.Sort(emptySeq, compareLess);
    assert(emptySeq->GetLength() == 0);


    int singleData[] = {5};
    SharedPtr<Sequence<int>> singleSeq(new ArraySequence<int>(singleData, 1));
    bubbleSorter.Sort(singleSeq, compareLess);
    assert(singleSeq->GetLength() == 1 && singleSeq->Get(0) == 5);

    int sortedData[] = {1, 2, 3, 4, 5};
    SharedPtr<Sequence<int>> sortedSeq(new ArraySequence<int>(sortedData, 5));
    bubbleSorter.Sort(sortedSeq, compareLess);
    for (int i = 0; i < 5; ++i) {
        assert(sortedSeq->Get(i) == i + 1);
    }

    int reverseData[] = {5, 4, 3, 2, 1};
    SharedPtr<Sequence<int>> reverseSeq(new ArraySequence<int>(reverseData, 5));
    bubbleSorter.Sort(reverseSeq, compareLess);
    for (int i = 0; i < 5; ++i) {
        assert(reverseSeq->Get(i) == i + 1);
    }

    int randomData[] = {3, 1, 4, 5, 2};
    SharedPtr<Sequence<int>> randomSeq(new ArraySequence<int>(randomData, 5));
    bubbleSorter.Sort(randomSeq, compareLess);
    for (int i = 0; i < 5; ++i) {
        assert(randomSeq->Get(i) == i + 1);
    }

    std::cout << "Bubble Sort tests passed!" << std::endl;
}


void testQuickSort() {
    std::cout << "Testing Quick Sort..." << std::endl;
    QuickSorter<int, bool(*)(const int&, const int&)> quickSorter;

    SharedPtr<Sequence<int>> emptySeq(new ArraySequence<int>());
    quickSorter.Sort(emptySeq, compareLess);
    assert(emptySeq->GetLength() == 0);

    int singleData[] = {5};
    SharedPtr<Sequence<int>> singleSeq(new ArraySequence<int>(singleData, 1));
    quickSorter.Sort(singleSeq, compareLess);
    assert(singleSeq->GetLength() == 1 && singleSeq->Get(0) == 5);

    int sortedData[] = {1, 2, 3, 4, 5};
    SharedPtr<Sequence<int>> sortedSeq(new ArraySequence<int>(sortedData, 5));
    quickSorter.Sort(sortedSeq, compareLess);
    for (int i = 0; i < 5; ++i) {
        assert(sortedSeq->Get(i) == i + 1);
    }

    int reverseData[] = {5, 4, 3, 2, 1};
    SharedPtr<Sequence<int>> reverseSeq(new ArraySequence<int>(reverseData, 5));
    quickSorter.Sort(reverseSeq, compareLess);
    for (int i = 0; i < 5; ++i) {
        assert(reverseSeq->Get(i) == i + 1);
    }

    int randomData[] = {3, 1, 4, 5, 2};
    SharedPtr<Sequence<int>> randomSeq(new ArraySequence<int>(randomData, 5));
    quickSorter.Sort(randomSeq, compareLess);
    for (int i = 0; i < 5; ++i) {
        assert(randomSeq->Get(i) == i + 1);
    }


    int duplicateData[] = {3, 1, 4, 1, 2};
    SharedPtr<Sequence<int>> duplicateSeq(new ArraySequence<int>(duplicateData, 5));
    quickSorter.Sort(duplicateSeq, compareLess);
    assert(duplicateSeq->Get(0) == 1);
    assert(duplicateSeq->Get(1) == 1);
    assert(duplicateSeq->Get(2) == 2);
    assert(duplicateSeq->Get(3) == 3);
    assert(duplicateSeq->Get(4) == 4);


    std::cout << "Quick Sort tests passed!" << std::endl;
}

void testHeapSort() {
    std::cout << "Testing Heap Sort..." << std::endl;
    HeapSorter<int, bool(*)(const int&, const int&)> heapSorter;

    SharedPtr<Sequence<int>> emptySeq(new ArraySequence<int>());
    heapSorter.Sort(emptySeq, compareLess);
    assert(emptySeq->GetLength() == 0);

    int singleData[] = {5};
    SharedPtr<Sequence<int>> singleSeq(new ArraySequence<int>(singleData, 1));
    heapSorter.Sort(singleSeq, compareLess);
    assert(singleSeq->GetLength() == 1 && singleSeq->Get(0) == 5);

    int sortedDataAsc[] = {1, 2, 3, 4, 5};
    SharedPtr<Sequence<int>> sortedSeqAsc(new ArraySequence<int>(sortedDataAsc, 5));
    heapSorter.Sort(sortedSeqAsc, compareLess);
    for (int i = 0; i < 5; ++i) {
        assert(sortedSeqAsc->Get(i) == i + 1);
    }

    int reverseData[] = {5, 4, 3, 2, 1};
    SharedPtr<Sequence<int>> reverseSeq(new ArraySequence<int>(reverseData, 5));
    heapSorter.Sort(reverseSeq, compareLess);
    for (int i = 0; i < 5; ++i) {
        assert(reverseSeq->Get(i) == i + 1);
    }

    int randomData[] = {3, 1, 4, 5, 2};
    SharedPtr<Sequence<int>> randomSeq(new ArraySequence<int>(randomData, 5));
    heapSorter.Sort(randomSeq, compareLess);
    for (int i = 0; i < 5; ++i) {
        assert(randomSeq->Get(i) == i + 1);
    }

    int duplicateData[] = {3, 1, 4, 1, 2};
    SharedPtr<Sequence<int>> duplicateSeq(new ArraySequence<int>(duplicateData, 5));
    heapSorter.Sort(duplicateSeq, compareLess);
    assert(duplicateSeq->Get(0) == 1);
    assert(duplicateSeq->Get(1) == 1);
    assert(duplicateSeq->Get(2) == 2);
    assert(duplicateSeq->Get(3) == 3);
    assert(duplicateSeq->Get(4) == 4);

    int descendingData[] = {5, 2, 8, 1, 9, 4};
    SharedPtr<Sequence<int>> descendingSeq(new ArraySequence<int>(descendingData, 6));
    heapSorter.Sort(descendingSeq, compareGreater);
    assert(descendingSeq->Get(0) == 9);
    assert(descendingSeq->Get(1) == 8);
    assert(descendingSeq->Get(2) == 5);
    assert(descendingSeq->Get(3) == 4);
    assert(descendingSeq->Get(4) == 2);
    assert(descendingSeq->Get(5) == 1);



    std::cout << "Heap Sort tests passed!" << std::endl;
}


void testStudents() {
    std::cout << "Testing Student class and file input..." << std::endl;

    Student student1("Ivan", "Ivanov", 2000, 12345);
    std::stringstream ss;
    ss << student1;
    assert(ss.str() == "Ivan Ivanov 2000 12345");

    std::stringstream ss2("Petr Petrov 1999 67890");
    Student student2;
    ss2 >> student2;
    assert(student2.getFirstName() == "Petr");
    assert(student2.getLastName() == "Petrov");
    assert(student2.getBirthYear() == 1999);
    assert(student2.getId() == 67890);

    std::ofstream outputFile("test_students.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file!" << std::endl;
        return;
    }
    outputFile << "Anna Karenina 1998 54321\n";
    outputFile << "Boris Pasternak 2001 98765\n";
    outputFile.close();


    std::ifstream inputFile("test_students.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file!" << std::endl;
        return;
    }

    SharedPtr<Sequence<Student>> students(new ArraySequence<Student>());

    Student studentFromFile;
    while (inputFile >> studentFromFile) {
        SharedPtr<Sequence<Student>> tmp = students->Append(studentFromFile);
        students = tmp;
    }
    inputFile.close();


    assert(students->GetLength() == 2);
    assert(students->Get(0).getFirstName() == "Anna");
    assert(students->Get(1).getId() == 98765);

    std::cout << "Student tests passed!" << std::endl;
}

int main() {
    testBubbleSort();
    testQuickSort();  
    testHeapSort();
    testStudents();
    return 0;
}