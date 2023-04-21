#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct AttendeeInterface{
    string name,surname,email,phoneNumber,id;
    double age,date;
};

class AttendeeManager{
private:
    vector<AttendeeInterface> AttendeesStore;
    void saveData();
    void loadData();
    void loadNewAttendee(AttendeeInterface attendee);
public:
     AttendeeManager();
     void deleteAttendee(string id);
     void loadAttendeeFromText(string str);
     void addNewAttendee(string name,string surname,double date,double age,string email,string phoneNumber,string id);
     AttendeeInterface * getAttendeeById(string id);
};
