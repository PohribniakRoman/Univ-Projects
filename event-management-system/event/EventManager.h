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
public:
    vector<EventInterface> EventStore;
    bool isEventExist(string eventID);
    bool isAttendeeAlreadyIn(string attendeeID,string eventID);
    void saveData();
    void loadData(AttendeeManager * manager);
    EventManager(AttendeeManager * manager);
    EventManager();
    void addNewEvent(string title,string description,string id,string authorID,double birth,double start,AttendeeManager * Manager);
    void deleteEvent(string id);
    void addAttendeeToEvent(string attendeeID,string eventID,AttendeeManager * Manager);
    void removeAttendeeFromEvent(string attendeeID,string eventID,AttendeeManager * Manager);
    void loadEventFromText(string str,AttendeeManager * manager);
    void deleteAttendee(string id,AttendeeManager * manager);
    void joinEvent(string rawData,AttendeeManager * manager);
    void leaveEvent(string rawData,AttendeeManager * manager);
    EventInterface * getEventById(string id);
    void operator()();
};


class EventSorter : EventManager{
private:

public:
};