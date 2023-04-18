using namespace std;

EventManager::EventManager() {
    this->EventStore = {};
}

void EventManager::addNewEvent(string title, string description, string id, string authorID, double birth,double start,AttendeeManager* Manager) {
    if(this->isEventExist(id))return;
    AttendeeInterface * author =  Manager->getAttendeeById(authorID);
    EventInterface newEvent {title,description,id,author,{},birth,start};
    this->EventStore.push_back(newEvent);
};

vector<EventInterface> EventManager::getAllEvents() {
    return this->EventStore;
}

EventInterface * EventManager::getEventById(string id) {
    if(this->isEventExist(id)){
    for (auto & i : this->EventStore) {
            if(i.id == id){
                return &i;
            }
        }
    }
}

bool EventManager::isEventExist(string eventID){
    bool res = false;
    for (auto &j : this->EventStore) {
        if(j.id == eventID){
            res = true;
        }
    }
    return res;
};

bool EventManager::isAttendeeAlreadyIn(string attendeeID, string eventID) {
    if(this->isEventExist(eventID))return false;
    bool res = false;
    for (auto &j : this->getEventById(eventID)->eventAttendees) {
        if(j.id == attendeeID){
            res = true;
        }
    }
    return res;
}

void EventManager::addAttendeeToEvent(string attendeeID, string eventID,AttendeeManager * Manager) {
    if(!this->isEventExist(eventID))return;
    if(this->isAttendeeAlreadyIn(attendeeID,eventID))return;
    AttendeeInterface * attendee = Manager->getAttendeeById(attendeeID);
    this->getEventById(eventID)->eventAttendees.push_back(*attendee);
}