#pragma once
#include "Student.h"

class Group {
    Student* students;
    int count;
    int number;
    int size_subjects;
    char** subjects;

public:
    Group();
    Group(int num, int n, const char* subjects[], int size_subjects);
    Group(const Group& g);
    ~Group();

    double getAverageScore() const;
    void addStudent(const Student& newStudent);
    void removeStudent(int index);
    int getNumber() const;
    int getCount() const;
    int getSize() const;
    char** getSubjects();
    Student& getStudent(int i);

    void setNumber(int n);
    void setSizeSubjects(int size);
    void setCount(int newcount);
    void setSubjects(char** newSubjects, int size);

    void print() const;
};