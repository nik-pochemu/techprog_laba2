#include "Group.h"
#include <iostream>
#include <cstring>

using namespace std;

Group::Group() : students(nullptr), count(0), number(0), size_subjects(0), subjects(nullptr) {
    cout << "[Group] Конструктор без параметров\n";
}

Group::Group(int num, int n, const char* subs[], int size) : number(num), count(n), size_subjects(size) {
    cout << "[Group] Конструктор с параметрами\n";

    subjects = new char* [size_subjects];
    for (int i = 0; i < size_subjects; i++) {
        subjects[i] = new char[strlen(subs[i]) + 1];
        strcpy_s(subjects[i], strlen(subs[i]) + 1, subs[i]);
    }

    students = new Student[count];
    for (int i = 0; i < count; i++) {
        cout << "=== Ввод студента " << i + 1 << " ===\n";
        cin >> students[i];
    }
}

Group::Group(const Group& g) : number(g.number), count(g.count), size_subjects(g.size_subjects) {
    subjects = new char* [size_subjects];
    for (int i = 0; i < size_subjects; i++) {
        subjects[i] = new char[strlen(g.subjects[i]) + 1];
        strcpy_s(subjects[i], strlen(g.subjects[i]) + 1, g.subjects[i]);
    }

    students = new Student[count];
    for (int i = 0; i < count; i++)
        students[i] = g.students[i];
}

Group::~Group() {
    delete[] students;
    for (int i = 0; i < size_subjects; i++)
        delete[] subjects[i];
    delete[] subjects;
}

double Group::getAverageScore() const {
    int sum = 0, cnt = 0;
    for (int i = 0; i < count; i++)
        for (int j = 0; j < students[i].getScoreCount(); j++) {
            sum += students[i].getScore(j);
            cnt++;
        }
    return cnt ? double(sum) / cnt : 0.0;
}

void Group::addStudent(const Student& s) {
    Student* tmp = new Student[count + 1];
    for (int i = 0; i < count; i++) tmp[i] = students[i];
    tmp[count++] = s;
    delete[] students;
    students = tmp;
}

void Group::removeStudent(int index) {
    if (index < 0 || index >= count) return;

    Student* tmp = new Student[count - 1];
    for (int i = 0, j = 0; i < count; i++)
        if (i != index) tmp[j++] = students[i];

    delete[] students;
    students = tmp;
    count--;
}

int Group::getNumber() const { return number; }
int Group::getCount() const { return count; }
int Group::getSize() const { return size_subjects; }
char** Group::getSubjects() { return subjects; }
Student& Group::getStudent(int i) { return students[i]; }

void Group::setNumber(int n) { number = n; }

void Group::setSubjects(char** newSubjects, int size) {
    for (int i = 0; i < size_subjects; i++)
        delete[] subjects[i];
    delete[] subjects;

    size_subjects = size;
    subjects = new char* [size_subjects];
    for (int i = 0; i < size_subjects; i++) {
        subjects[i] = new char[strlen(newSubjects[i]) + 1];
        strcpy_s(subjects[i], strlen(newSubjects[i]) + 1, newSubjects[i]);
    }
}

void Group::print() const {
    cout << "Группа №" << number << "\n";
    for (int i = 0; i < count; i++)
        cout << i + 1 << ") " << students[i] << "\n";
    cout << "Средний балл группы: " << getAverageScore() << "\n";
}