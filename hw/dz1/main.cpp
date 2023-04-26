#include <vector>
#include <string>

using namespace std;

struct day{
    vector<string> lessons;
};

class University_Course  {
    private:
        string courseName = "Course Name";
        string prerequisites = "some requires";
        string instructor = "Instructor Name";
        vector<day> schedule;
        vector<string> assignments;
};
//    bool operator < (Student OtherStudent){
//        return(this->getAverage()<OtherStudent.getAverage());
//    }
//    bool operator <=( Student OtherStudent){
//        return(this->getAverage()<=OtherStudent.getAverage());
//    }
//    bool operator > (Student OtherStudent){
//        return(this->getAverage()>OtherStudent.getAverage());
//    }
//    bool operator >= (Student other){
//        return(this->getAverage()>=OtherStudent.getAverage());
//    }
