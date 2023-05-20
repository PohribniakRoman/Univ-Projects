// #1 Конструктор копії, якщо необхідно створити копію об’єкта (стандартний конструктор копії
// скопіює поля-вказівники, які будуть прив’язані до тієї ж ділянки пам’яті, а тому одна ділянка буде належати одразу обом об’єктам).
// Конструктор переміщення, якщо потрібно передати ті ж ділянки від одного об’єкта до іншого
// (старий об’єкт втрачає доступ до цих динамічних даних, а новий стає їх власником)
// Деструктор потрібен для того, щоб вивільнити зайняті динамічні дані.
// 
// #2 Це двостороння черга – послідовність, у яку можна додавати елементи з обох боків: додати в початок,
// додати в кінець. Отримувати і видаляти елементи так само можна з обох боків: отримати з початку, отримати з кінця,
// видалити з початку, видалити з кінця. Часто отримати і видалити - одне і те саме, але бувають випадки, коли ні.
// Це вже залежить від конкретної реалізації, головна ідея - обробка послідовності з двох боків.
// 
// #3
// // insert
// vector<int> vect = {};
// vect.insert(vect.end(), 100, 100);
// vect.insert(vect.end(), 200, 200);
// // push_back
// vector<int> vect = {};
// for (int i = 0; i < 100; i++) {
// vect.push_back(100);
// }
// for (int i = 0; i < 200; i++) {
// vect.push_back(200);
// }
// 
// #4 Використання суто віртуальних методів дозволяє досягти поліморфізму.
// Ці методи дозволяють викликати методи на об'єктах підкласів за допомогою вказівника або посилання на базовий клас незалежно від конкретної реалізації підкласу.
// Це дозволяє замінювати об'єкти підкласів у коді спрощуючи розширення та підтримку програми.
// 
// #5
// 1)T = int, U = int:
// template <>
// bool tf<int, int>(int a, int b, int c);
// 2)T = int, U = double:
// template <>
// bool tf<int, double>(int a, int b, double c);
// 3) T = double, U = double:
// template <>
// bool tf<double, double>(double a, double b, double c);

// #6 O(n! * n)
// n! - К-сть перестановок
// O(n) - Складнітсь виведення одного варіанту

#include "iostream"
#include "vector"

using namespace std;

// 1 Завдання

struct Dis
{
    string label;
    unsigned short termIndex, grade;
};

class Stud
{
private:
    string surname;
    unsigned short id;
    vector<Dis> disList;
    // Додаткові методи для задачі 3
public:
    string getSurname() { return this->surname; };
    unsigned short getId() { return this->id; };
    vector<Dis> getDisList() { return this->disList; };
};

// 2 Завдання

class Group
{
private:
    string title;
    struct Node
    {
        Stud student;
        Node *next;
    };
    Node *head;
    Node *tail;
    unsigned short numberOfStudents;

public:
    Group();
    Group(Group &&relocateGroup);
    ~Group();
    bool operator=(Group &&assignedGroup) noexcept;
    vector<pair<string, unsigned short>> getAverageMaxGrade();
    int getAverage(pair<string, unsigned short> studentData);
    bool updateStudent(const pair<string, unsigned short> &studentData, const Dis &newDis);
    bool operator+(pair<string, unsigned short> studentData);
    bool operator-(pair<string, unsigned short> studentData);
    bool operator>>(ofstream stream);
};

// 3 Завдання

bool Group::updateStudent(const pair<string, unsigned short> &studentData, const Dis &newDis)
{
    if (newDis.grade > 100 || newDis.grade < 0)
        return false;
    Node *current = this->head;
    while (studentData.second != current->student.getId() || studentData.first != current->student.getSurname())
    {
        if (current->next == nullptr)
            return false;
        current = current->next;
    }
    for (auto &i : current->student.getDisList())
    {
        if (i.label == newDis.label && i.termIndex == newDis.termIndex)
        {
            i.grade = newDis.grade;
            return true;
        }
    }
    return false;
}

bool Group::operator=(Group &&assignedGroup) noexcept
{
    this->head = assignedGroup.head;
    this->tail = assignedGroup.tail;
    this->numberOfStudents = assignedGroup.numberOfStudents;
}

Group::~Group()
{
    Node *current = this->head;
    while (current)
    {
        Node *nextStudent = current->next;
        delete current;
        current = nextStudent;
    }
    this->head = nullptr;
    this->tail = nullptr;
}