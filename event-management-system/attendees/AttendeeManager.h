#include <string>
#include <vector>

using namespace std;

struct AttendeeInterface{
    string name,surname,email,phoneNumber,id;
    double age,date;
};

class AttendeeManager{
private:
    vector<AttendeeInterface> AttendeesStore = {};
public:
     void addNewAttendee(string name,string surname,double date,double age,string email,string phoneNumber,string id);;
     AttendeeInterface * getAttendeeById(string id);
};
