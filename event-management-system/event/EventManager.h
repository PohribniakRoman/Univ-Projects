#include <string>
#include <vector>

using namespace std;

struct EventInterface{
    string title,description,id;
    AttendeeInterface * author;
    vector<AttendeeInterface*> eventAttendees;
    double dateOfBirth,dateOfStart;
};

class EventManager{
private:
    vector<EventInterface> EventStore;
    void loadData(AttendeeManager * manager);
    void saveData();
    bool isAttendeeAlreadyIn(string attendeeID,string eventID);
    bool isEventExist(string eventID);
public:
    EventManager(AttendeeManager * manager);
    void addNewEvent(string title,string description,string id,string authorID,double birth,double start,AttendeeManager * Manager);
    void deleteEvent(string id);
    void addAttendeeToEvent(string attendeeID,string eventID,AttendeeManager * Manager);
    void removeAttendeeFromEvent(string attendeeID,string eventID,AttendeeManager * Manager);
    void loadEventFromText(string str,AttendeeManager * manager);
    void deleteAttendee(string id,AttendeeManager * manager);
    void joinEvent(string rawData,AttendeeManager * manager);
    void leaveEvent(string rawData,AttendeeManager * manager);
    EventInterface * getEventById(string id);
};
