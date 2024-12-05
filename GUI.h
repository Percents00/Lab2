// GUI.h
#ifndef GUI_H
#define GUI_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QSpinBox>
#include <fstream>
#include <sstream>
#include <chrono>
#include <random>

#include "ArraySequence.h"
#include "Sorts/ISorter.h"
#include "Sorts/BubbleSorter.h"
#include "Sorts/QuickSorter.h"
#include "Sorts/HeapSorter.h"
#include "Students.h"



class GUI : public QWidget {
    Q_OBJECT

private:
    std::vector<std::string> firstNames;
    std::vector<std::string> lastNames;
    std::random_device rd;
    std::mt19937 generator{rd()};
    SharedPtr<Sequence<Student>> students;
    QTextEdit *inputTextEdit;
    QTextEdit *outputTextEdit;
    QComboBox *sorterComboBox;
    QComboBox *comparatorComboBox;
    QLabel *timeLabel;
    std::map<std::string, ISorter<Student, std::function<bool(const Student&, const Student&)>>*> sorters;

    std::string generateRandomString(int length) {
        std::uniform_int_distribution<> distrib('a', 'z');
        std::string str;
        for (int i = 0; i < length; ++i) {
            str += static_cast<char>(distrib(generator));
        }
        return str;
    }

    Student generateRandomStudent() {
        if (firstNames.empty() || lastNames.empty()) {
            std::cerr << "Error: First or last names not loaded." << std::endl;
            return Student{};
        }


        std::uniform_int_distribution<> yearDistrib(1990, 2005);
        std::uniform_int_distribution<> idDistrib(1000, 9999);
        std::uniform_int_distribution<> firstNameDistrib(0, firstNames.size() - 1);
        std::uniform_int_distribution<> lastNameDistrib(0, lastNames.size() - 1);


        return {
            firstNames[firstNameDistrib(generator)],
            lastNames[lastNameDistrib(generator)],
            yearDistrib(generator),
            idDistrib(generator)
        };
    }

    void loadStudentsFromText(const QString& text) {
        std::stringstream ss(text.toStdString());
        students = SharedPtr<Sequence<Student>>(new ArraySequence<Student>());
        Student s;
        while (ss >> s) {
            students = students->Append(s);

        }

        std::cout << "Loaded " << students->GetLength() << " students." << std::endl;
    }

    bool loadNamesFromFile(const std::string& filename, std::vector<std::string>& names) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        std::string name;
        while (std::getline(file, name)) {
            names.push_back(name);

        }
        file.close();
        return true;
    }

    template<typename Comparator>
    void sortAndDisplay(Comparator comp, const std::string& sorterName) {
        if (!students) {
            outputTextEdit->setPlainText("Error: No data loaded.");
            return;
        }



        auto start = std::chrono::high_resolution_clock::now();
        sorters.at(sorterName)->Sort(students, comp);
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        timeLabel->setText(QString("Sorting time: %1 ms").arg(duration.count()));


        std::stringstream ss;
        for (int i = 0; i < students->GetLength(); ++i) {
            ss << students->Get(i) << "\n";
        }
        outputTextEdit->setPlainText(QString::fromStdString(ss.str()));
    }


    void runComparisons(std::function<bool(const Student&, const Student&)> comp) {

        if (!students || students->GetLength() == 0) {
            outputTextEdit->setPlainText("Error: No data loaded.");
            return;
        }


        std::vector<std::pair<std::string, long long>> timings;
        std::vector<std::string> sortersToCompare = {"Bubble Sort", "Quick Sort", "Heap Sort"};

        std::stringstream finalOutput;

        for (const auto& sorterName : sortersToCompare) {
             SharedPtr<Sequence<Student>> copied_students = students->Copy();
            try {
                auto start = std::chrono::high_resolution_clock::now();
                sorters.at(sorterName)->Sort(copied_students, comp);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

                timings.push_back({sorterName, duration.count()});

                if (sorterName == sortersToCompare.back()) {

                    for (int i = 0; i < copied_students->GetLength(); ++i) {
                        finalOutput << copied_students->Get(i) << "\n";
                    }

                }


            } catch (const std::exception& e) {
                 outputTextEdit->append(QString("Error during %1 sort: %2\n").arg(QString::fromStdString(sorterName), QString::fromStdString(e.what())));
            }
        }

        std::stringstream timingsOutput;
        for (const auto& timing : timings) {
            timingsOutput << timing.first << ": " << timing.second << " ms\n";
        }
        timeLabel->setText(QString::fromStdString(timingsOutput.str()));

        outputTextEdit->setPlainText(QString::fromStdString(finalOutput.str()));

    }



public:
    GUI(QWidget *parent = nullptr) : QWidget(parent), students(nullptr) {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        resize(800, 600);



        inputTextEdit = new QTextEdit();
        mainLayout->addWidget(new QLabel("Input data (one student per line):"));
        mainLayout->addWidget(inputTextEdit);

        if (!loadNamesFromFile("first_names.txt", firstNames)) {
            std::cerr << "Error loading first names from file." << std::endl;
        }
        if (!loadNamesFromFile("last_names.txt", lastNames)) {
            std::cerr << "Error loading last names from file." << std::endl;
        }


        QPushButton* loadFromFileButton = new QPushButton("Load from File");
        mainLayout->addWidget(loadFromFileButton);
        connect(loadFromFileButton, &QPushButton::clicked, this, &GUI::loadFromFile);

        sorters["Bubble Sort"] = new BubbleSorter<Student, std::function<bool(const Student&, const Student&)>>{};
        sorters["Quick Sort"] = new QuickSorter<Student, std::function<bool(const Student&, const Student&)>>{};
        sorters["Heap Sort"] = new HeapSorter<Student, std::function<bool(const Student&, const Student&)>>{};

        sorterComboBox = new QComboBox();
        for (const auto& pair : sorters) {
            sorterComboBox->addItem(QString::fromStdString(pair.first));
        }
        mainLayout->addWidget(new QLabel("Sorter:"));
        mainLayout->addWidget(sorterComboBox);


        comparatorComboBox = new QComboBox();
        comparatorComboBox->addItem("By First Name");
        comparatorComboBox->addItem("By Last Name");
        comparatorComboBox->addItem("By Birth Year");
        comparatorComboBox->addItem("By ID");
        mainLayout->addWidget(new QLabel("Comparator:"));
        mainLayout->addWidget(comparatorComboBox);


        QPushButton *sortButton = new QPushButton("Sort");
        mainLayout->addWidget(sortButton);


        connect(sortButton, &QPushButton::clicked, this, &GUI::sortStudents);


        outputTextEdit = new QTextEdit();
        outputTextEdit->setReadOnly(true);

        mainLayout->addWidget(new QLabel("Output:"));
        mainLayout->addWidget(outputTextEdit);


        timeLabel = new QLabel("");
        mainLayout->addWidget(timeLabel);


        setLayout(mainLayout);
        setWindowTitle("Student Sorter");


        QHBoxLayout *generateLayout = new QHBoxLayout();
        generateLayout->addWidget(new QLabel("Number of students:"));

        QSpinBox *numStudentsSpinBox = new QSpinBox();
        numStudentsSpinBox->setMinimum(1);
        numStudentsSpinBox->setMaximum(99999);
        numStudentsSpinBox->setValue(500);
        generateLayout->addWidget(numStudentsSpinBox);

        QPushButton *generateButton = new QPushButton("Generate");
        generateLayout->addWidget(generateButton);

        mainLayout->addLayout(generateLayout);


        connect(generateButton, &QPushButton::clicked, this, [this, numStudentsSpinBox]() {
             generateStudents(numStudentsSpinBox->value());
        });

        QPushButton *compareButton = new QPushButton("Sort and Compare");
        mainLayout->addWidget(compareButton);
        connect(compareButton, &QPushButton::clicked, this, &GUI::compareSorts);

    }

    ~GUI() {
        for (auto const& [key, val] : sorters)
            delete val;
    }

public slots:

    void compareSorts() {

        QString selectedComparator = comparatorComboBox->currentText();

        if (!students || students->GetLength() == 0) {
            outputTextEdit->setPlainText("Error: No data loaded.");
            return;
        }


        std::function<bool(const Student&, const Student&)> comparator;
        if (selectedComparator == "By First Name") {
            comparator = CompareStudentsByFirstName{};
        } else if (selectedComparator == "By Last Name") {
            comparator = CompareStudentsByLastName{};
        } else if (selectedComparator == "By Birth Year") {
            comparator = CompareStudentsByBirthYear{};
        } else if (selectedComparator == "By ID") {
            comparator = CompareStudentsById{};
        } else {
            outputTextEdit->setPlainText("Error: Invalid comparator selected.");
            return;
        }


        runComparisons(comparator);

    }

    void generateStudents(int numStudents) {
        students = SharedPtr<Sequence<Student>>(new ArraySequence<Student>());
        for (int i = 0; i < numStudents; ++i) {
            students = students->Append(generateRandomStudent());
        }

        std::stringstream ss;
        for (int i = 0; i < students->GetLength(); ++i) {
            ss << students->Get(i) << "\n";
        }
        inputTextEdit->setPlainText(QString::fromStdString(ss.str()));
    }

    void loadFromFile() {
        QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt);;All Files (*)");
        if (fileName.isEmpty()) {
            return;
        }



        std::ifstream inputFile(fileName.toStdString());

        if (inputFile.is_open()) {
            std::stringstream ss;
            ss << inputFile.rdbuf();
            inputFile.close();


            loadStudentsFromText(QString::fromStdString(ss.str()));

            inputTextEdit->setPlainText(QString::fromStdString(ss.str()));

        }

        if (!inputFile.is_open()) {
            outputTextEdit->setPlainText("Error opening file.");
            return;
        }

        std::stringstream ss;
        ss << inputFile.rdbuf();
        inputFile.close();

        loadStudentsFromText(QString::fromStdString(ss.str()));


    }

    void sortStudents() {


        QString selectedSorter = sorterComboBox->currentText();
        QString selectedComparator = comparatorComboBox->currentText();

        if (!students || students->GetLength() == 0) {
            outputTextEdit->setPlainText("Error: No data loaded.");
            return;
        }

        std::function<bool(const Student&, const Student&)> comparator;

        if (selectedComparator == "By First Name") {
            comparator = CompareStudentsByFirstName{};
        } else if (selectedComparator == "By Last Name") {
            comparator = CompareStudentsByLastName{};
        } else if (selectedComparator == "By Birth Year") {
            comparator = CompareStudentsByBirthYear{};
        } else if (selectedComparator == "By ID") {
            comparator = CompareStudentsById{};
        } else {
            outputTextEdit->setPlainText("Error: Invalid comparator selected.");
            return;
        }



        try {
            if (selectedSorter == "All") {
                runComparisons(comparator);
            } else {
                sortAndDisplay(comparator, selectedSorter.toStdString());
            }
        }  catch (const std::out_of_range& e) {
            outputTextEdit->setPlainText(QString("Error: Sorter '%1' not found.").arg(selectedSorter));
            std::cerr << "Error: " << e.what() << std::endl;
        }

    }

    void onSorterSelected(int index) {
        QString selectedSorter = sorterComboBox->itemText(index);
        std::cout << "Selected sorter: " << selectedSorter.toStdString() << std::endl;
    }
};

#endif // GUI_H
