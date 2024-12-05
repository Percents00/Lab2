#include <string>
#include <iostream>
#include <algorithm>


class Student {
private:
    std::string firstName;
    std::string lastName;
    int birthYear;
    int id;

public:
    Student() : firstName(""), lastName(""), birthYear(0), id(0) {}

    Student(const std::string& firstName, const std::string& lastName, int birthYear, int id)
        : firstName(firstName), lastName(lastName), birthYear(birthYear), id(id) {}

    const std::string& getFirstName() const { return firstName; }
    const std::string& getLastName() const { return lastName; }
    int getBirthYear() const { return birthYear; }
    int getId() const { return id; }

    friend std::istream& operator>>(std::istream& is, Student& student);
    friend std::ostream& operator<<(std::ostream& os, const Student& student);

    bool operator==(const Student& other) const {
        return firstName == other.firstName &&
               lastName == other.lastName &&
               birthYear == other.birthYear &&
               id == other.id;
    }

    bool operator<(const Student& other) const {
        return birthYear < other.birthYear;
    }

    bool operator>(const Student& other) const {
        return birthYear > other.birthYear;
    }


};

struct CompareStudentsById {
    bool operator()(const Student& s1, const Student& s2) const {
        return s1.getId() < s2.getId();
    }
};

struct CompareStudentsByBirthYear {
    bool operator()(const Student& s1, const Student& s2) const {
        return s1.getBirthYear() < s2.getBirthYear();
    }
};

struct CompareStudentsByLastName {
    bool operator()(const Student& s1, const Student& s2) const {
        return s1.getLastName() < s2.getLastName();
    }
};

struct CompareStudentsByFirstName {
    bool operator()(const Student& s1, const Student& s2) const {
        std::string firstName1 = s1.getFirstName();
        std::string firstName2 = s2.getFirstName();
        std::transform(firstName1.begin(), firstName1.end(), firstName1.begin(), ::tolower);
        std::transform(firstName2.begin(), firstName2.end(), firstName2.begin(), ::tolower);
        return firstName1 < firstName2;
    }
};