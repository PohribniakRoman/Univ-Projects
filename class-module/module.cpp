//1.struct Student{
//    std::string name;
//    int value;
//    double A[10];
//};
//Student * sArr = new(std::nothrow) Student[100];
//delete [] sArr;
//sArr = nullptr;
//
//2.Oператор >> для std::string пропускає такзвані "білі" символи(пробіл\табуляцію\символ), переписує в контейнер символи до натикання на такий "білий" символ,
//самостійно змінює розмір контейнера, у кінці рядка '\0' не дописується.
//Кількість символів, які можуть потрапити в рядок, обмежується тільки об'ємом доступної оперативної пам'яті на пристрої.
//
//3.Набір деяких даних, часто різних типів, організований у зручний спосіб, поділений на частини, які можна відрізнити за іменами.
//Сам набір позначає окремий тип даних.З точки зору математики, змінна-структура може розглядатися як вектор або матриця з декількома полями.
//
//4.Принцип інкапсуляції полягає в модифікаторах private/protected, гетерах/сетерах та інших функціях, які взаємодіють з приватними полями,
//        тим самим захищаючи їх від небажаних/не означених дій.
//
//5.class C {
//public:
//    C& operator >> (T a);
//    friend C& operator >> (C& c, T a);
//};
//
//6(f.fail() && !f.eof())
// (f.bad() &&  !(f.peek() == EOF))

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
    int discipline_count;
    const int SUBJECT_SIZE = 55;
public:
    struct Subject {
        Dis discipline;
        int grade;
    };
    Subject * subjects = new Subject[SUBJECT_SIZE];
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
                << "  |  Id: " <<  this->subjects[i].discipline.id
                <<";\n" <<"Grade: " << this->subjects[i].grade << "\n";
        }
    };
    ~Student();
};

Student::Student(string name, string surname) {
    this->name = name;
    this->surname = surname;
    this->discipline_count = 0;
}

bool Student::operator +(Subject subjectToAdd) {
    if (subjectToAdd.grade >= 0 && subjectToAdd.grade <= 100){
        this->subjects[this->discipline_count++] = subjectToAdd;
        return true;
    }
    cout<<"Failed to add\n";
    return false;
}

Student::~Student(){
    delete [] this->subjects;
    subjects = nullptr;
}

void fillStudent(Student &student, ifstream &dataStream){
    string currentString;
    int index = 0;
    int maxGradeIndex = -1;
    int grade = -1;
    while (getline(dataStream,currentString)){
        string data;
        if(index!= 0){
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
            if(stoi(arrString[2]) > grade){
                grade = stoi(arrString[2]);
                maxGradeIndex = index-1;
            };
            student + newSubject;
            delete[] arrString;
            arrString = nullptr;
        }
        index++;
    }
    cout <<"Discipline with max grade: "
         << student.subjects[maxGradeIndex].discipline.name
         << "  |  Id: " << student.subjects[maxGradeIndex].discipline.id
         <<";\n" <<"Grade: " << student.subjects[maxGradeIndex].grade << "\n";
}

int main() {
    Student Roman("Roman","Pohribniak");
    string path;
    cout<<"Enter correct filepath\n";
    cin>>path;
    ifstream dataStream(path);
    while(!dataStream.is_open()) { ;
        cout << "Path error!\n";
        cin >> path;
        dataStream.open(path);
    }
    fillStudent(Roman,dataStream);
//    Roman>>cout;
    dataStream.close();
}