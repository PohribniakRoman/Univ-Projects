#include<iostream>

using namespace std;
class Human{
private:
    int AGE;
    string NAME;
public:
    Human(int AGE, string NAME);
    void print(){
        cout<<"Person name "<<this->NAME<<endl;
        cout<<"Person age:"<<this->AGE<<endl;
    }
};

Human::Human(int _AGE, string _NAME): AGE(_AGE),NAME(_NAME)  {}

class Student: public Human{
private:
    int AVERAGE_MARK;
    int  GROUP;
public:
    Student(int AVERAGE_MARK, int  GROUP,int AGE, string NAME);
    void print();
};
void Student::print() {
    Human::print();
    cout<<"Person AVG mark: "<<this->AVERAGE_MARK<<endl;
    cout<<"Person group: "<<this->GROUP<<endl;
}

Student::Student(int _AVERAGE_MARK, int _GROUP, int _AGE, string _NAME) : Human(_AGE,  _NAME) {
    AVERAGE_MARK = _AVERAGE_MARK;
    GROUP =_GROUP;
}

class Bachelor: public Student{
private:
    string bach_diploma;
public:
    Bachelor(int AVERAGE_MARK, int GROUP,int AGE, string NAME, string bach_diploma):Student(AVERAGE_MARK, GROUP, AGE, NAME){
        this->bach_diploma = bach_diploma;
    };
    void print(){
        Student::print();
        cout<<"Bachelor diploma: "<<this->bach_diploma<<endl;
    }
};

class Master: public Bachelor{
private:
    string master_diploma;
public:
    Master(int AVERAGE_MARK, int GROUP,int AGE, string NAME, string bach_diploma, string master_diploma):Bachelor(AVERAGE_MARK, GROUP, AGE, NAME,bach_diploma){
        this->master_diploma = master_diploma;
    }
    void print(){
        Bachelor::print();
        cout<<"Master diploma: "<<this->master_diploma<<endl;
    }
};

int main(){
    Master(90,16,40,"Jon Doe","Bach-Diploma","Master-Diploma").print();
}