#include "iostream"
#include "vector"

using namespace std;

// 1 Завдання

struct Dis{
    string label;
    unsigned short termIndex,grade;
};

class Stud{
    private:
        string surname;
        unsigned short id;
        vector<Dis> disList;
// Додаткові методи для задачі 3
    public:
        string getSurname(){return this->surname;};
        unsigned short getId(){return this->id;};
        vector<Dis> getDisList(){return this->disList;};
};

// 2 Завдання

class Group{
    private:
        string title;
        struct Node{
            Stud student;
            Node *next;
        };
        Node *head;
        Node *tail;
        unsigned short numberOfStudents;
    public:
        Group();
        Group(Group&& relocateGroup);
        ~Group();
        bool operator = (Group&& assignedGroup) noexcept;
        vector<pair<string,unsigned short>> getAverageMaxGrade();
        int getAverage(pair<string,unsigned short> studentData);
        bool updateStudent(const pair<string,unsigned short>& studentData,const Dis& newDis);
        bool operator +(pair<string,unsigned short> studentData);
        bool operator -(pair<string,unsigned short> studentData);
        bool operator >>(ofstream stream);
};

// 3 Завдання

bool Group::updateStudent(const pair<string, unsigned short>& studentData, const Dis& newDis) {
    if(newDis.grade > 100 || newDis.grade < 0)return false;
    Node *current = this->head;
    while(studentData.second != current->student.getId() || studentData.first != current->student.getSurname()){
        if(current->next == nullptr)return false;
        current = current->next;
    }
    for(auto &i : current->student.getDisList()){
        if(i.label == newDis.label && i.termIndex == newDis.termIndex){
            i.grade = newDis.grade;
            return true;
        }
    }
    return false;
}

bool Group::operator=(Group &&assignedGroup) noexcept {
    this->head = assignedGroup.head;
    this->tail = assignedGroup.tail;
    this->numberOfStudents = assignedGroup.numberOfStudents;
}

Group::~Group() {
    this->head = nullptr;
    this->tail = nullptr;
}