#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Dis{
    string name;
    int id;
};

struct Subject {
    Dis discipline;
    int grade;
};

class Student{
private:
    string name;
    string surname;
    int discipline_count = 0;
public:
    Student();
    Student(string name, string surname);
    Subject * subjects = new Subject[55];
    bool operator +(Subject subjectToAdd);
    bool operator < (Student compareStudent);
    void operator >>(ofstream &outStream);
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
        cout<<"Successfully added\n";
        return true;
    }
    cout<<"Failed to add\n";
    return false;
}

bool Student::operator < (Student compareStudent){
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
}

void Student::operator >>(ofstream &outStream){
    string fileName = this->name+this->surname+".txt";
    outStream.open(fileName);
    outStream<<"Name: "<< this->name << " " << this->surname<<";\n";
    for (int i = 0; i < this->discipline_count; ++i) {
        outStream<<"Discipline: "
                 << this->subjects[i].discipline.name
                 << " | id - " <<  this->subjects[i].discipline.id
                 <<";\n" <<"Grade: " << this->subjects[i].grade << "\n";
    }
};

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
            discipline.name = arrString[0];
            discipline.id = stoi(arrString[1]);
            Subject newSubject;
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
    Student Roman;
    ifstream dataStream("index.txt");
    fillStudent(Roman,dataStream);
    ofstream outPutFile;
    Roman>>outPutFile;

    dataStream.close();
}