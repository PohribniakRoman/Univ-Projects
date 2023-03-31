#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Dis{
    string name;
    int id;
};
class Student{
private:
    string name;
    string surname;
    const int SUBJECT_SIZE = 55;
    int discipline_count = 0;
public:
    struct Subject {
        Dis discipline;
        int grade;
    };
    Subject * subjects = new Subject[SUBJECT_SIZE];
    Student();
    Student(string name, string surname);
    bool operator +(Subject subjectToAdd);
    bool operator < (Student &compareStudent){
        double thisAverage = 0;
        double compareAverage = 0;
        for (int i = 0; i < this->discipline_count; i++) {
            thisAverage += this->subjects[i].grade;
        }
        thisAverage /= this->discipline_count;
        for (int x = 0; x < compareStudent.discipline_count; x++) {
            compareAverage += compareStudent.subjects[x].grade;
        }
        compareAverage /= compareStudent.discipline_count;
        if (thisAverage < compareAverage) {
            return true;
        }
        return false;
    };
    void operator >>(ostream &output){
        output<< this->name <<" "<< this->surname <<"\n";
        for (int i = 0; i < this->discipline_count; ++i) {
            output<<"Discipline: "
                << this->subjects[i].discipline.name
                << " | id - " <<  this->subjects[i].discipline.id
                <<";\n" <<"Grade: " << this->subjects[i].grade << "\n";
        }
    };
    void setName(string name);
    void setSurname(string name);
    ~Student();
};

Student::Student(){}
Student::Student(string name, string surname) {
    this->name = name;
    this->surname = surname;
}

bool Student::operator +(Subject subjectToAdd) {
    if (subjectToAdd.grade >= 0 && subjectToAdd.grade <= 100){
        this->subjects[discipline_count] = subjectToAdd;
        this->discipline_count++;
        return true;
    }
    cout<<"Failed to add\n";
    return false;
}

void Student::setName(string name){
    this->name = name;
}

void Student::setSurname(string surname){
    this->surname = surname;
}

Student::~Student(){
    delete [] this->subjects;
    subjects = nullptr;
}

void fillStudent(Student &student, ifstream &dataStream){
    string currentString;
    int index = 0;
    while (getline(dataStream,currentString)){
        string data;
        if(index==0){
            for(int i = 0;i < currentString.size();i++){
                if(currentString[i] == ' '){
                    student.setName(data);
                    data = "";
                }else data.push_back(currentString[i]);
            }
            student.setSurname(data);
        }else {
            string *arrString = new string[3];
            int ind = 0;
            for (int i = 0; i <= currentString.size(); i++) {
                if (currentString[i] == ' ') {
                    arrString[ind++] = data;
                    data = "";
                } else data.push_back(currentString[i]);
            };
            arrString[2] = data;
            Dis discipline;
            Student::Subject newSubject;
            discipline.name = arrString[0];
            discipline.id = stoi(arrString[1]);
            newSubject.discipline = discipline;
            newSubject.grade = stoi(arrString[2]);
            student + newSubject;
            delete[] arrString;
            arrString = nullptr;
        }
        index++;
    }
}

int main() {
    Student Max;
    ifstream dataStream("index.txt");
    fillStudent(Max,dataStream);
    ofstream outPutFile;
    Max>>cout;
    dataStream.close();
    ifstream data2Stream("roman.txt");
    Student Roman;
    fillStudent(Roman,data2Stream);
    data2Stream.close();
}