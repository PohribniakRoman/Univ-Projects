#include <string>
#include <vector>

using namespace std;

struct EventInterface{
    string title,description,id;
    AttendeeInterface * author;
    vector<AttendeeInterface> eventAttendees;
    double dateOfBirth,dateOfStart;
};

class EventManager{
private:
    vector<EventInterface> EventStore;
public:
    EventManager();
    void addNewEvent(string title,string description,string id,string authorID,double birth,double start,AttendeeManager * Manager);
    void addAttendeeToEvent(string attendeeID,string eventID,AttendeeManager * Manager);
    bool isAttendeeAlreadyIn(string attendeeID,string eventID);
    bool isEventExist(string eventID);
    EventInterface * getEventById(string id);
    vector<EventInterface> getAllEvents();

};
