#include "Student.h"
#include <cstring>

using namespace std;

Student::Student() : name(nullptr), scores(nullptr), scoreCount(0) {
    cout << "[Student] Конструктор без параметров\n";
}

Student::Student(const char* n, int cnt) : scoreCount(cnt) {
    cout << "[Student] Конструктор с параметрами\n";
    name = new char[strlen(n) + 1];
    strcpy_s(name, strlen(n) + 1, n);

    scores = new int[scoreCount];
    cout << "Введите " << scoreCount << " оценок: ";
    for (int i = 0; i < scoreCount; i++)
        cin >> scores[i];
}

Student::Student(const Student& s) {
    cout << "[Student] Конструктор копирования\n";
    scoreCount = s.scoreCount;

    name = new char[strlen(s.name) + 1];
    strcpy_s(name, strlen(s.name) + 1, s.name);

    scores = new int[scoreCount];
    for (int i = 0; i < scoreCount; i++)
        scores[i] = s.scores[i];
}

Student::~Student() {
    cout << "[Student] Деструктор вызван\n";
    clear();
}

void Student::clear() {
    delete[] name;
    delete[] scores;
    name = nullptr;
    scores = nullptr;
    scoreCount = 0;
}

Student& Student::operator=(const Student& s) {
    if (this == &s) return *this;
    clear();

    scoreCount = s.scoreCount;
    name = new char[strlen(s.name) + 1];
    strcpy_s(name, strlen(s.name) + 1, s.name);

    scores = new int[scoreCount];
    for (int i = 0; i < scoreCount; i++)
        scores[i] = s.scores[i];

    return *this;
}

double Student::avg() const {
    if (scoreCount == 0) return 0.0;
    double sum = 0;
    for (int i = 0; i < scoreCount; i++)
        sum += scores[i];
    return sum / scoreCount;
}

const char* Student::getName() const { return name; }

int Student::getScore(int index) const {
    if (index < 0 || index >= scoreCount) return 0;
    return scores[index];
}

int Student::getScoreCount() const { return scoreCount; }

void Student::setName(const char* newName) {
    delete[] name;
    name = new char[strlen(newName) + 1];
    strcpy_s(name, strlen(newName) + 1, newName);
}

void Student::setMarks(const int* newMarks, int count) {
    delete[] scores;
    scoreCount = count;
    scores = new int[scoreCount];
    for (int i = 0; i < scoreCount; i++)
        scores[i] = newMarks[i];
}

ostream& operator<<(ostream& os, const Student& s) {
    os << "Имя: " << s.name << " | оценки: ";
    for (int i = 0; i < s.scoreCount; i++)
        os << s.scores[i] << " ";
    os << " | средний балл: " << s.avg();
    return os;
}

istream& operator>>(istream& is, Student& s) {
    char temp[256];
    cout << "Введите ФИО: ";
    is.ignore();
    is.getline(temp, 255);

    s.setName(temp);

    cout << "Введите количество оценок: ";
    is >> s.scoreCount;

    delete[] s.scores;
    s.scores = new int[s.scoreCount];

    cout << "Введите оценки: ";
    for (int i = 0; i < s.scoreCount; i++)
        is >> s.scores[i];

    return is;
}