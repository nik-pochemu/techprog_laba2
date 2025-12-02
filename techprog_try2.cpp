#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <windows.h>
#include <limits> 
#ifdef max
#undef max
#endif
using namespace std;

// ======================= КЛАСС STUDENT =========================

class Student {
    char* name;
    int* scores;
    int scoreCount;

public:
    Student() : name(nullptr), scores(nullptr), scoreCount(0) {
        name = new char[1];
        name[0] = '\0';
        scores = nullptr;
        scoreCount = 0;
        cout << "[Student] Конструктор без параметров\n";
    }

    Student(const char* n, int cnt) : name(nullptr), scores(nullptr), scoreCount(0) {
        cout << "[Student] Конструктор с параметрами\n";

        if (n) {
            name = new char[strlen(n) + 1];
            strcpy_s(name, strlen(n) + 1, n);
        }
        else {
            name = new char[1];
            name[0] = '\0';
        }

        scoreCount = cnt;
        if (scoreCount > 0) {
            scores = new int[scoreCount];
            cout << "Введите " << scoreCount << " оценок: ";
            for (int i = 0; i < scoreCount; i++)
                cin >> scores[i];
            // удаляем остаток строки после ввода чисел
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            scores = nullptr;
        }
    }

    Student(const Student& s) : name(nullptr), scores(nullptr), scoreCount(0) {
        cout << "[Student] Конструктор копирования\n";
        scoreCount = s.scoreCount;

        if (s.name) {
            name = new char[strlen(s.name) + 1];
            strcpy_s(name, strlen(s.name) + 1, s.name);
        }
        else {
            name = new char[1];
            name[0] = '\0';
        }

        if (scoreCount > 0 && s.scores) {
            scores = new int[scoreCount];
            for (int i = 0; i < scoreCount; i++)
                scores[i] = s.scores[i];
        }
        else {
            scores = nullptr;
        }
    }

    ~Student() {
        cout << "[Student] Деструктор вызван для " << (name ? name : "(null)") << "\n";
        delete[] name;
        delete[] scores;
    }

    Student& operator=(const Student& s) {
        if (this == &s) return *this;

        delete[] name;
        delete[] scores;

        scoreCount = s.scoreCount;

        if (s.name) {
            name = new char[strlen(s.name) + 1];
            strcpy_s(name, strlen(s.name) + 1, s.name);
        }
        else {
            name = new char[1];
            name[0] = '\0';
        }

        if (scoreCount > 0 && s.scores) {
            scores = new int[scoreCount];
            for (int i = 0; i < scoreCount; i++)
                scores[i] = s.scores[i];
        }
        else {
            scores = nullptr;
        }

        return *this;
    }

    double avg() const {
        if (scoreCount == 0 || scores == nullptr) return 0.0;
        double sum = 0;
        for (int i = 0; i < scoreCount; i++) sum += scores[i];
        return sum / scoreCount;
    }

    const char* getName() const { return name ? name : ""; }
    int getScoreCount() const { return scoreCount; }

    void setName(const char* newName) {
        delete[] name;
        if (newName) {
            name = new char[strlen(newName) + 1];
            strcpy_s(name, strlen(newName) + 1, newName);
        }
        else {
            name = new char[1];
            name[0] = '\0';
        }
    }

    void setScores(int* arr, int cnt) {
        delete[] scores;
        scoreCount = cnt;
        if (cnt > 0 && arr != nullptr) {
            scores = new int[cnt];
            for (int i = 0; i < cnt; i++) scores[i] = arr[i];
        }
        else {
            scores = nullptr;
        }
    }

    friend ostream& operator<<(ostream& os, const Student& s) {
        os << (s.name ? s.name : "") << " | Оценки: ";
        for (int i = 0; i < s.scoreCount; i++) {
            if (s.scores) os << s.scores[i] << " ";
            else os << "0 ";
        }
        os << "| Средний: " << s.avg();
        return os;
    }
    friend istream& operator>>(istream& is, Student& s) {
        char temp[256];
        cout << "Введите ФИО: ";
        // аккуратно удаляем остаток строки и затем читаем строку
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        is.getline(temp, 255);

        s.setName(temp);

        cout << "Введите количество оценок: ";
        int cnt;
        is >> cnt;
        if (cnt < 0) cnt = 0;

        delete[] s.scores;
        s.scoreCount = cnt;
        if (cnt > 0) {
            s.scores = new int[cnt];
            cout << "Введите оценки: ";
            for (int i = 0; i < cnt; i++) is >> s.scores[i];
            // удаляем остаток строки после ввода чисел
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            s.scores = nullptr;
            // убрать остаток строки, если есть
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        return is;
    }
};


// ======================= КЛАСС GROUP =========================

class Group {
    Student* students;
    int count;
    int number;

public:
    Group() : students(nullptr), count(0), number(0) {
        cout << "[Group] Конструктор без параметров\n";
    }

    Group(int num, int n) : students(nullptr), count(0), number(num) {
        cout << "[Group] Конструктор с параметрами\n";
        if (n < 0) n = 0;
        count = n;
        if (count > 0) {
            students = new Student[count];
            for (int i = 0; i < count; i++) {
                cout << "=== Ввод студента " << i + 1 << " ===\n";
                cin >> students[i];
            }
        }
        else {
            students = nullptr;
        }
    }

    Group(const Group& g) : students(nullptr), count(0), number(g.number) {
        cout << "[Group] Конструктор копирования\n";
        count = g.count;
        if (count > 0) {
            students = new Student[count];
            for (int i = 0; i < count; i++) students[i] = g.students[i];
        }
        else {
            students = nullptr;
        }
    }

    ~Group() {
        cout << "[Group] Деструктор вызван для группы №" << number << "\n";
        delete[] students;
    }

    int getNumber() const { return number; }
    int getCount() const { return count; }

    Student& getStudent(int i) { return students[i]; }

    void print() const {
        cout << "\nГруппа №" << number << " (" << count << " студентов):\n";
        for (int i = 0; i < count; i++)
            cout << i + 1 << ") " << students[i] << "\n";
    }

    // ---------- Редактирование группы ----------
    void editGroup() {
        cout << "Редактирование группы №" << number << "\n";
        cout << "Введите новый номер группы: ";
        cin >> number;

        cout << "Изменить количество студентов? (1 = да, 0 = нет): ";
        int f;
        cin >> f;
        if (f == 1) {
            int newCount;
            cout << "Введите новое количество: ";
            cin >> newCount;
            if (newCount < 0) newCount = 0;

            // выделяем новый массив
            Student* temp = nullptr;
            if (newCount > 0) temp = new Student[newCount];

            // копируем существующие записи (сколько есть)
            int m = (newCount < count) ? newCount : count;
            for (int i = 0; i < m; i++) {
                temp[i] = students[i]; // использует operator=
            }

            // освобождаем старую память и обновляем поля
            delete[] students;
            students = temp;
            count = newCount;

            // после ввода чисел возможен мусор в потоке — уберём
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // ---------- Удаление студента по имени ----------
    void removeStudentByName(const char* nameToRemove) {
        if (count == 0 || students == nullptr) {
            cout << "В группе нет студентов.\n";
            return;
        }
        int idx = -1;
        for (int i = 0; i < count; i++) {
            const char* sname = students[i].getName();
            if (sname && strcmp(sname, nameToRemove) == 0) {
                idx = i;
                break;
            }
        }

        if (idx == -1) {
            cout << "Студент не найден.\n";
            return;
        }

        if (count == 1) {
            delete[] students;
            students = nullptr;
            count = 0;
            cout << "Студент удалён. Группа теперь пуста.\n";
            return;
        }

        Student* tmp = new Student[count - 1];
        for (int i = 0, j = 0; i < count; i++) {
            if (i == idx) continue;
            tmp[j++] = students[i];
        }

        delete[] students;
        students = tmp;
        count--;

        cout << "Студент удалён.\n";
    }
};


// ================= ФУНКЦИЯ: перестановка слов ==================

void swapTwoWords(const char* inFile, const char* outFile) {
    ifstream fin(inFile);
    if (!fin) throw runtime_error("Ошибка открытия входного файла");

    ofstream fout(outFile);
    if (!fout) throw runtime_error("Ошибка открытия выходного файла");

    char w1[100], w2[100];

    while (true) {
        if (!(fin >> w1)) break;
        if (!(fin >> w2)) {
            fout << w1;
            break;
        }
        fout << w2 << " " << w1 << " ";
    }

    cout << "Готово.\n";
}


// ================= РЕДАКТИРОВАНИЕ СТУДЕНТА ==================

void editStudent(Student& s) {
    cout << "Редактирование студента: " << s.getName() << "\n";

    cout << "1 — изменить имя\n"
        << "2 — изменить оценки\n"
        << "0 — выход\n";

    int ch;
    cin >> ch;

    if (ch == 1) {
        char newName[255];
        cout << "Введите новое имя: ";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.getline(newName, 255);
        s.setName(newName);
    }
    else if (ch == 2) {
        int cnt;
        cout << "Введите новое количество оценок: ";
        cin >> cnt;
        if (cnt < 0) cnt = 0;
        int* a = nullptr;
        if (cnt > 0) a = new int[cnt];

        cout << "Введите оценки: ";
        for (int i = 0; i < cnt; i++) cin >> a[i];

        s.setScores(a, cnt);
        delete[] a;
        // очистим остаток строки
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}


// ============================ МЕНЮ ===============================

void menu() {
    Group** groups = nullptr;
    int groupCount = 0;

    while (true) {
        cout << "\n===== МЕНЮ =====\n"
            << "1. Добавить группу\n"
            << "2. Удалить группу по номеру\n"
            << "3. Показать все группы\n"
            << "4. Показать студентов со ср. баллом > 4\n"
            << "5. Обработать файл (перестановка слов)\n"
            << "6. Редактировать группу\n"
            << "7. Редактировать студента\n"
            << "8. Удалить студента по имени\n"
            << "0. Выход\n";

        int choice;
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {

            // ---------------- ДОБАВИТЬ ГРУППУ -----------------
        case 1: {
            int gnum, cnt;
            cout << "Введите номер группы: ";
            cin >> gnum;
            cout << "Введите количество студентов: ";
            cin >> cnt;
            if (cnt < 0) cnt = 0;

            Group** tmp = new Group * [groupCount + 1];
            for (int i = 0; i < groupCount; i++) tmp[i] = groups[i];
            tmp[groupCount] = new Group(gnum, cnt);

            delete[] groups;
            groups = tmp;
            groupCount++;

            // очистим остаток
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }

              // ---------------- УДАЛИТЬ ГРУППУ ПО НОМЕРУ -----------------
        case 2: {
            cout << "Введите номер группы: ";
            int num;
            cin >> num;
            int idx = -1;
            for (int i = 0; i < groupCount; i++)
                if (groups[i]->getNumber() == num) { idx = i; break; }

            if (idx == -1) {
                cout << "Группа не найдена.\n";
                break;
            }

            delete groups[idx];

            Group** tmp = nullptr;
            if (groupCount - 1 > 0) {
                tmp = new Group * [groupCount - 1];
                for (int i = 0, j = 0; i < groupCount; i++) {
                    if (i == idx) continue;
                    tmp[j++] = groups[i];
                }
            }

            delete[] groups;
            groups = tmp;
            groupCount--;

            cout << "Группа удалена.\n";
            // очистим остаток
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }

              // ---------------- ПОКАЗАТЬ ГРУППЫ -----------------
        case 3:
            if (groupCount == 0) cout << "Нет групп.\n";
            for (int i = 0; i < groupCount; i++)
                groups[i]->print();
            break;

            // ---------------- ВЫВОД СРЕДНИЙ > 4 -----------------
        case 4:
            for (int i = 0; i < groupCount; i++) {
                for (int j = 0; j < groups[i]->getCount(); j++) {
                    if (groups[i]->getStudent(j).avg() > 4.0)
                        cout << "[Группа " << groups[i]->getNumber() << "] "
                        << groups[i]->getStudent(j) << "\n";
                }
            }
            break;

            // ---------------- ОБРАБОТКА ФАЙЛА -----------------
        case 5: {
            char inF[100], outF[100];
            cout << "Введите входной файл: ";
            cin >> inF;
            cout << "Введите выходной файл: ";
            cin >> outF;

            try {
                swapTwoWords(inF, outF);
            }
            catch (exception& e) {
                cout << e.what() << endl;
            }
            // очистим остаток
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }

              // ---------------- РЕДАКТИРОВАТЬ ГРУППУ -----------------
        case 6: {
            cout << "Введите номер группы: ";
            int num;
            cin >> num;

            int idx = -1;
            for (int i = 0; i < groupCount; i++)
                if (groups[i]->getNumber() == num) { idx = i; break; }

            if (idx == -1) { cout << "Не найдено\n"; break; }

            groups[idx]->editGroup();

            break;
        }

              // ---------------- РЕДАКТИРОВАТЬ СТУДЕНТА -----------------
        case 7: {
            int num;
            cout << "Введите номер группы: ";
            cin >> num;

            int idx = -1;
            for (int i = 0; i < groupCount; i++)
                if (groups[i]->getNumber() == num) { idx = i; break; }

            if (idx == -1) { cout << "Группа не найдена\n"; break; }

            groups[idx]->print();

            cout << "Введите номер студента: ";
            int s;
            cin >> s;

            if (s < 1 || s > groups[idx]->getCount()) {
                cout << "Ошибка\n"; break;
            }

            editStudent(groups[idx]->getStudent(s - 1));

            break;
        }

              // ---------------- УДАЛЕНИЕ СТУДЕНТА ПО ИМЕНИ -----------------
        case 8: {
            int num;
            char name[255];

            cout << "Введите номер группы: ";
            cin >> num;

            int idx = -1;
            for (int i = 0; i < groupCount; i++)
                if (groups[i]->getNumber() == num) { idx = i; break; }

            if (idx == -1) { cout << "Группа не найдена\n"; break; }

            cout << "Введите ФИО студента: ";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.getline(name, 255);

            groups[idx]->removeStudentByName(name);

            break;
        }

        default:
            cout << "Неверный ввод\n";
        }
    }
    for (int i = 0; i < groupCount; i++) delete groups[i];
    delete[] groups;
}


// ============================ MAIN ===============================

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    menu();
    return 0;
}















/*#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <stdexcept>
#include <windows.h>
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

    ~Student() {
        cout << "[Student] Деструктор вызван\n";
        delete[] name;
        delete[] scores;
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

public:
    Group() : students(nullptr), count(0), number(0) {
        cout << "[Group] Конструктор без параметров\n";
    }

    Group(int num, int n) : number(num), count(n) {
        cout << "[Group] Конструктор с параметрами\n";

        students = new Student[count];
        for (int i = 0; i < count; i++) {
            cout << "=== Ввод студента " << i + 1 << " ===\n";
            cin >> students[i];
        }
    }

    Group(const Group& g) {
        cout << "[Group] Конструктор копирования\n";
        number = g.number;
        count = g.count;

        students = new Student[count];
        for (int i = 0; i < count; i++) students[i] = g.students[i];
    }

    ~Group() {
        cout << "[Group] Деструктор вызван\n";
        delete[] students;
    }

    int getNumber() const { return number; }
    int getCount() const { return count; }
    Student& getStudent(int i) { return students[i]; }

    void print() const {
        cout << "Группа №" << number << " (" << count << " студентов):\n";
        for (int i = 0; i < count; i++) cout << i + 1 << ") " << students[i] << "\n";
    }

    void reorderStudents() {
        // сортировка не требуется по условию, сортируем группы, не студентов
    }
};

// ------------------ ПРОГРАММНАЯ ЧАСТЬ ----------------------
void swapTwoWords(const char* inFile, const char* outFile) {
    ifstream fin(inFile);
    if (!fin) throw runtime_error("Ошибка открытия входного файла");

    ofstream fout(outFile);
    if (!fout) throw runtime_error("Ошибка открытия выходного файла");

    char w1[100], w2[100];
    bool ok = true;

    while (true) {
        if (!(fin >> w1)) break;
        if (!(fin >> w2)) {
            fout << w1;
            break;
        }
        fout << w2 << " " << w1 << " ";
    }

    cout << "Файл обработан успешно\n";
}

void menu() {
    Group** groups = nullptr;
    int groupCount = 0;

    while (true) {
        cout << "\n===== МЕНЮ =====\n"
            << "1. Добавить группу\n"
            << "2. Удалить группу\n"
            << "3. Показать все группы\n"
            << "4. Показать студентов со ср.баллом > 4.0\n"
            << "5. Обработать файл (поменять местами слова)\n"
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
            cout << "Введите число студентов: ";
            cin >> cnt;

            Group** tmp = new Group * [groupCount + 1];
            for (int i = 0; i < groupCount; i++) tmp[i] = groups[i];
            tmp[groupCount] = new Group(gnum, cnt);

            delete[] groups;
            groups = tmp;
            groupCount++;

            cout << "Группа добавлена\n";
            break;
        }

        case 2: {
            cout << "Введите индекс группы (1.." << groupCount << "): ";
            int idx; cin >> idx;
            if (idx < 1 || idx > groupCount) {
                cout << "Ошибка индекса\n"; break;
            }

            delete groups[idx - 1];

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

        default:
            cout << "Неверный ввод\n";
        }
    }

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
} */