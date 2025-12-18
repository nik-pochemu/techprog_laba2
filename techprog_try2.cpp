#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <windows.h>
#include <limits> 
using namespace std;

// ----------- КЛАСС STUDENT -----------------

class Student {
    char* name;
    int* scores;
    int scoreCount;

public:
    Student() : name(nullptr), scores(nullptr), scoreCount(0) {
        cout << "[Student] Конструктор без параметров\n";
    }

    Student(const char* n, int cnt) : scoreCount(cnt) {
        cout << "[Student] Конструктор с параметрами\n";

        name = new char[strlen(n) + 1];
        strcpy_s(name, strlen(n) + 1, n);

        scores = new int[scoreCount];
        cout << "Введите " << scoreCount << " оценок: ";
        for (int i = 0; i < scoreCount; i++)
            cin >> scores[i];
    }

    Student(const Student& s) {
        cout << "[Student] Конструктор копирования\n";
        scoreCount = s.scoreCount;

        name = new char[strlen(s.name) + 1];
        strcpy_s(name, strlen(s.name) + 1, s.name);

        scores = new int[scoreCount];
        for (int i = 0; i < scoreCount; i++)
            scores[i] = s.scores[i];
    }

    void clear() {
        // очистка имени
        if (name) {
            delete[] name;
            name = nullptr;
        }

        // очистка оценок
        if (scores) {
            delete[] scores;
            scores = nullptr;
        }

        scoreCount = 0;
    }


    ~Student() {
        cout << "[Student] Деструктор вызван\n";
        clear();
    }

    Student& operator=(const Student& s) {
        if (this == &s) return *this;

        delete[] name;
        delete[] scores;

        scoreCount = s.scoreCount;
        name = new char[strlen(s.name) + 1];
        strcpy_s(name, strlen(s.name) + 1, s.name);

        scores = new int[scoreCount];
        for (int i = 0; i < scoreCount; i++)
            scores[i] = s.scores[i];

        return *this;
    }

    double avg() const {
        if (scoreCount == 0) return 0.0;
        double sum = 0;
        for (int i = 0; i < scoreCount; i++) sum += scores[i];
        return sum / scoreCount;
    }

    const char* getName() const { return name; }
    int getScore(int index) const {
        if (index < 0 || index >= scoreCount) {
            return 0; // или выброс исключения, если разрешено
        }
        return scores[index];
    }
    int getScoreCount() const {
        return scoreCount;
    }
    void setName(const char* newName) {
        if (name) {
            delete[] name;
        }
        name = new char[strlen(newName) + 1];
        strcpy_s(name, strlen(newName) + 1, newName);
    }
    void setMarks(const int* newMarks, int count) {
        if (scores) {
            delete[] scores;
        }
        scoreCount = count;
        scores = new int[scoreCount];
        for (int i = 0; i < scoreCount; i++) {
            scores[i] = newMarks[i];
        }



    }

    friend ostream& operator<<(ostream& os, const Student& s) {
        os << "Имя: " << s.name << " | оценки: ";
        for (int i = 0; i < s.scoreCount; i++) os << s.scores[i] << " ";
        os << " | средний балл: " << s.avg();
        return os;
    }

    friend istream& operator>>(istream& is, Student& s) {
        char temp[256];
        cout << "Введите ФИО: ";
        is.ignore();
        is.getline(temp, 255);

        delete[] s.name;
        s.name = new char[strlen(temp) + 1];
        strcpy_s(s.name, strlen(temp) + 1, temp);

        cout << "Введите количество оценок: ";
        is >> s.scoreCount;

        delete[] s.scores;
        s.scores = new int[s.scoreCount];

        cout << "Введите оценки: ";
        for (int i = 0; i < s.scoreCount; i++) is >> s.scores[i];

        return is;
    }
};


// --------------- КЛАСС GROUP --------------------

class Group {
    Student* students;
    int count;
    int number;
    int size_subjects;
    char** subjects;

public:
    Group() {
        students = nullptr;
        count = 0;
        number = 0;
        size_subjects = 0;
        subjects = nullptr;
        cout << "[Group] Конструктор без параметров\n";
    }

    Group(int num, int n, const char* subjects[], const int size_subjects) : number(num), count(n) {
        cout << "[Group] Конструктор с параметрами\n";
        this->subjects = new char* [sizeof(size_subjects)];
        for (int i = 0; i < size_subjects; i++) {
            this->subjects[i] = new char[strlen(subjects[i]) + 1];
            strcpy_s(this->subjects[i], strlen(subjects[i]) + 1, subjects[i]);
        }
        students = new Student[count];
        for (int i = 0; i < count; i++) {
            cout << "=== Ввод студента " << i + 1 << " ===\n";
            cin >> students[i];
        }
        this->size_subjects = size_subjects;
    }

    Group(const Group& g) {
        cout << "[Group] Конструктор копирования\n";
        number = g.number;
        count = g.count;

        subjects = new char* [size_subjects];
        for (int i = 0; i < size_subjects; i++) {
            subjects[i] = new char[strlen(g.subjects[i]) + 1];
            strcpy_s(subjects[i], strlen(g.subjects[i]) + 1, g.subjects[i]);
        }


        students = new Student[count];
        for (int i = 0; i < count; i++) students[i] = g.students[i];
    }

    ~Group() {
        cout << "[Group] Деструктор вызван\n";
        delete[] students;
        for (int i = 0; i < size_subjects; i++) {
            delete subjects[i];
        }
        delete[] subjects;
    }

    double getAverageScore() const {
        int totalSum = 0;
        int totalCount = 0;

        for (int i = 0; i < count; i++) {
            for (int j = 0; j < students[i].getScoreCount(); j++) {
                totalSum += students[i].getScore(j);
                totalCount++;
            }
        }

        if (totalCount == 0) return 0.0;

        return static_cast<double>(totalSum) / totalCount;
    }


    void addStudent(const Student& newStudent) {
        Student* temp = new Student[count + 1];

        // копируем старых
        for (int i = 0; i < count; ++i) {
            temp[i] = students[i];   // ⚠️ нужен корректный operator=
        }

        // добавляем нового
        temp[count] = newStudent;

        delete[] students;
        students = temp;
        count++;
    }

    void removeStudent(int index) {
        if (index < 0 || index >= count) {
            return;
        }

        // очищаем удаляемого
        students[index].clear();

        Student* temp = nullptr;

        if (count - 1 > 0) {
            temp = new Student[count - 1];

            for (int i = 0, j = 0; i < count; ++i) {
                if (i == index) continue;
                temp[j++] = students[i];
            }
        }

        delete[] students;
        students = temp;
        count--;
    }
    int getNumber() const { return number; }
    int getCount() const { return count; }
    int getSize() const { return size_subjects; }
    char** getSubjects() { return subjects; }
    Student& getStudent(int i) { return students[i]; }

    void setNumber(int n) { number = n; }
    void setSizeSubjects(int size) { size_subjects = size; }
    void setCount(int newcount) { count = newcount; }
    void setSubjects(char** newSubjects, int size) {
        if (subjects) {
            for (int i = 0; i < size_subjects; ++i) {
                delete[]subjects[i];
            }
            delete[] subjects;
            subjects = nullptr;
            size_subjects = 0;
        }
        size_subjects = size;
        subjects = new char* [size_subjects];
        for (int i = 0; i < size_subjects; ++i) {
            int len = strlen(newSubjects[i]);
            subjects[i] = new char[len + 1];
            strcpy_s(subjects[i], len + 1, newSubjects[i]);
        }
    }
    void print() const {
        cout << "Группа №" << number << " (" << count << " студентов):\n";
        for (int i = 0; i < count; i++) cout << i + 1 << ") " << students[i] << "\n";
        cout << "Количество предметов группы: " << size_subjects << endl;
        for (int i = 0; i < size_subjects; i++) {
            cout << "Предмет: " << i + 1 << ":" << subjects[i] << endl;
        }
        cout << "Средний балл группы: " << getAverageScore() << endl;
    }
};


void sortGroups(Group** groups, int left, int right){
    int i = left;
    int j = right;

    int pivot = groups[(left + right) / 2]->getNumber();
    while (i <= j) {
        while (groups[i]->getNumber() < pivot) {
            i++;
        }
        while (groups[j]->getNumber() > pivot) {
            j--;
        }

        if (i <= j) {
            Group* temp = groups[i];
            groups[i] = groups[j];
            groups[j] = temp;
            i++;
            j--;
        }

        if (left < j) sortGroups(groups, left, j);
        if (i < right) sortGroups(groups, i, right);
    }
}




void menu() {
    Group** groups = nullptr;
    int groupCount = 0;
    int size_subjects = 0;
    char* subjects = new char[64];
    char* newname = new char[64];
    int* marks = new int[64];

    while (true) {
        cout << "\n===== МЕНЮ =====\n"
            << "1. Добавить группу\n"
            << "2. Удалить группу\n"
            << "3. Показать все группы\n"
            << "4. Показать студентов со ср.баллом > 4.0\n"
            << "5. Обработать файл (поменять местами слова)\n"
            << "6. Редактировать группу\n"
            << "7. Редактировать студента\n"
            << "8. Удалить студента\n"
            << "9. Добавить студента\n"
            << "0. Выход\n"
            << "Выбор: ";

        int choice;
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {

        case 1: {
            int gnum, cnt;
            cout << "Введите номер группы: ";
            cin >> gnum;
            cout << "Введите количество предметов: ";
            cin >> size_subjects;
            cin.ignore();
            char** subjects = new char* [size_subjects];
            for (int i = 0; i < size_subjects; i++) {
                char buffer[256];
                cout << "Введите название предметов " << i + 1 << ": ";
                cin.getline(buffer, 256);
                subjects[i] = new char[strlen(buffer) + 1];
                strcpy_s(subjects[i], strlen(buffer) + 1, buffer);
            }

            cout << "Введите число студентов: ";
            cin >> cnt;

            Group** tmp = new Group * [groupCount + 1];
            for (int i = 0; i < groupCount; i++) tmp[i] = groups[i];
            tmp[groupCount] = new Group(gnum, cnt, (const char **) subjects, size_subjects);

            delete[] groups;
            groups = tmp;
            groupCount++;
            sortGroups(groups, 0, groupCount - 1);
            cout << "Группа добавлена\n";
            delete[] subjects;
            break;
        }

        case 2: {
            cout << "Введите номер группы (1.." << groupCount << "): ";
            int num; cin >> num;
            cin.ignore();
            int idx = -1;
            for (int i = 0; i < groupCount; i++) {
                if (groups[i]->getNumber() == num) idx = i;
            }
            if (idx == -1) {
                cout << "index error" << endl;
                break;
            }

            delete groups[idx];

            Group** tmp = new Group * [groupCount - 1];
            for (int i = 0, j = 0; i < groupCount; i++) {
                if (i == idx - 1) continue;
                tmp[j++] = groups[i];
            }

            delete[] groups;
            groups = tmp;
            groupCount--;

            cout << "Группа удалена\n";
            break;
        }

        case 3: {
            for (int i = 0; i < groupCount; i++)
                groups[i]->print();
            break;
        }

        case 4: {
            for (int i = 0; i < groupCount; i++) {
                Group* g = groups[i];
                for (int k = 0; k < g->getCount(); k++) {
                    if (g->getStudent(k).avg() > 4.0) {
                        cout << "[ГРУППА " << g->getNumber() << "] "
                            << g->getStudent(k) << "\n";
                    }
                }
            }
            break;
        }

        case 5:
        {
            // === ЧТЕНИЕ ФАЙЛА В ДИНАМИЧЕСКИЙ БУФЕР ===
            ifstream fin("data.txt", ios::binary);
            if (!fin) {
                cout << "Не удалось открыть файл\n";
                break;
            }

            fin.seekg(0, ios::end);
            long size = fin.tellg();
            fin.seekg(0, ios::beg);

            char* buffer = new char[size + 1];
            fin.read(buffer, size);
            buffer[size] = '\0';
            fin.close();

            // === ПОТОК ДЛЯ СЛОВ ===
            stringstream ss(buffer);

            const int WORD_SIZE = 256;
            char* w1 = new char[WORD_SIZE];
            char* w2 = new char[WORD_SIZE];

            bool hasFirst = false;

            // === ОБРАБОТКА СЛОВ ПО ПАРАМ ===
            while (true) {
                if (!hasFirst) {
                    if (!(ss >> w1)) break;
                    hasFirst = true;
                }

                if (!(ss >> w2)) {
                    cout << w1; // нечётное слово — выводим как есть
                    break;
                }

                cout << w2 << " " << w1;

                if (!ss.eof()) cout << " ";

                hasFirst = false;
            }

            cout << endl;

            // === ОЧИСТКА ПАМЯТИ ===
            delete[] buffer;
            delete[] w1;
            delete[] w2;

            break;
        }


        case 6:
        {
           /* cout << "Введите номер группы (1.." << groupCount << "): ";
            int num; cin >> num;
            cin.ignore();
            int idx = -1;
            for (int i = 0; i < groupCount; i++) {
                if (groups[i]->getNumber() == num) idx = i;
            }
            if (idx == -1) {
                cout << "index error" << endl;
                break;
            }*/


            cout << "Введите индекс группы (1.." << groupCount << "): ";
            int idx; cin >> idx;
            if (idx < 1 || idx > groupCount) {
                cout << "Ошибка индекса\n"; break;
            }
            int newgnum, newcnt;
            cout << "Введите новый номер группы: ";
            cin >> newgnum;
            cout << "Введите количество предметов: ";
            cin >> size_subjects;
            cin.ignore();
            char** subjects = new char* [size_subjects];
            for (int i = 0; i < size_subjects; i++) {
                char buffer[256];
                cout << "Введите название предметов " << i + 1 << ": ";
                cin.getline(buffer, 256);
                subjects[i] = new char[strlen(buffer) + 1];
                strcpy_s(subjects[i], strlen(buffer) + 1, buffer);
            }
            for (int i = 0, j = 0; i < groupCount; i++) {
                if (i == idx - 1) {
                    groups[i]->setNumber(newgnum);
                    groups[i]->setSubjects(subjects, size_subjects);
                    break;
                }

            }
            cout << "Группа обновлена\n";
            delete[] subjects;
            break;
        }

        case 7:
        {
            cout << "Введите индекс группы (1.." << groupCount << "): ";
            int idx; cin >> idx;
            cin.ignore();
            if (idx < 1 || idx > groupCount) {
                cout << "Ошибка индекса\n"; break;
            }
            cout << "Введите индекс студента (1.." << groupCount << "): ";
            int idxs; cin >> idxs;
            cin.ignore();
            Group* g = groups[idx-1];
            if (idxs < 1 || idxs > g->getCount()) {
                cout << "Ошибка индекса\n"; break;
            }
            cout << "Введите новое имя студента: ";
            cin.getline(newname, 256);
            cin.ignore();
            int scoreCount;
            cout << "Введите количество оценок студента: ";
            cin >> scoreCount;
            cout << "Введите оценки студента : ";
            for (int i = 0; i < scoreCount; i++) cin >> marks[i];
            for (int i = 0; i < g->getCount(); i++) {
                if (i == idxs - 1) {
                    Student& s = g->getStudent(i);
                    s.setName(newname);
                    s.setMarks(marks, scoreCount);
                }
            }

            cout << "Студент обновлен\n";
            
            break;
        }

        case 8:
        {
            cout << "Введите индекс группы (1.." << groupCount << "): ";
            int idx; cin >> idx;
            cin.ignore();
            if (idx < 1 || idx > groupCount) {
                cout << "Ошибка индекса\n"; break;
            }
            cout << "Введите индекс студента (1.." << groupCount << "): ";
            int idxs; cin >> idxs;
            cin.ignore();
            Group* g = groups[idx - 1];
            if (idxs < 1 || idxs > g->getCount()) {
                cout << "Ошибка индекса\n"; break;
            }
            g->removeStudent(idxs - 1);
            cout << "Студент удалён\n";
            break;
        }

        case 9:
        {
            cout << "Введите индекс группы (1.." << groupCount << "): ";
            int idx; cin >> idx;
            cin.ignore();
            if (idx < 1 || idx > groupCount) {
                cout << "Ошибка индекса\n"; break;
            }
            Group* g = groups[idx - 1];
            cout << "Введите имя студента: ";
            cin.getline(newname, 256);
            int scoreCount;
            cout << "Введите количество оценок студента: ";
            cin >> scoreCount;
            /*cout << "Введите оценки студента : ";
            for (int i = 0; i < scoreCount; i++) cin >> marks[i];*/
            Student s(newname, scoreCount);
            g->addStudent(s);
            cout << "Студент добавлен\n";
            break;
            
        }



        default:
            cout << "Неверный ввод\n";
        }
    }
    delete[] subjects;
    delete[] newname;
    delete[] marks;
    for (int i = 0; i < groupCount; i++) delete groups[i];
    delete[] groups;
}


// ---------------- MAIN ------------------

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    try {
        menu();
    }
    catch (exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
   
} 