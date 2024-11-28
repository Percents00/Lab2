#include "Students.h"

std::istream& operator>>(std::istream& is, Student& student) {
    return is >> student.firstName >> student.lastName >> student.birthYear >> student.id;
}

std::ostream& operator<<(std::ostream& os, const Student& student) {
    return os << student.firstName << " " << student.lastName << " " << student.birthYear << " " << student.id;
}