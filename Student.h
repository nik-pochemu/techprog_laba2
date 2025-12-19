#pragma once
#include <iostream>

class Student {
    char* name;
    int* scores;
    int scoreCount;

public:
    Student();
    Student(const char* n, int cnt);
    Student(const Student& s);
    ~Student();

    Student& operator=(const Student& s);

    double avg() const;

    const char* getName() const;
    int getScore(int index) const;
    int getScoreCount() const;

    void setName(const char* newName);
    void setMarks(const int* newMarks, int count);
    void clear();

    friend std::ostream& operator<<(std::ostream& os, const Student& s);
    friend std::istream& operator>>(std::istream& is, Student& s);
};