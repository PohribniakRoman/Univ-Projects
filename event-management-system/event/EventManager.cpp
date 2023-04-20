using namespace std;

EventManager::EventManager(AttendeeManager * manager) {
    this->loadData(manager);
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

void EventManager::loadData(AttendeeManager * manager) {
    ifstream readFile("Event.txt");
    string marker;
    getline(readFile,marker);
    if(marker == "!WITH_LOAD!") {
        this->EventStore = {};
        string currentEvent;
        while(getline(readFile,currentEvent)){
            stringstream ss(currentEvent);
            string currentData;
            EventInterface newEvent;
            for(int i = 0;getline(ss,currentData,'|');i++){
                switch (i) {
                    case 0:newEvent.title = currentData;break;
                    case 1:newEvent.description = currentData;break;
                    case 2:newEvent.author = manager->getAttendeeById(currentData);break;
                    case 3:newEvent.dateOfBirth = stod(currentData);break;
                    case 4:newEvent.dateOfStart = stod(currentData);break;
                    case 5:newEvent.id = currentData;break;
                    case 6:
                        stringstream ssc(currentData);
                        string attendee;
                        while (getline(ssc,attendee,':')){
                            newEvent.eventAttendees.push_back(*manager->getAttendeeById(attendee));
                        }
                }
            }
            this->EventStore.push_back(newEvent);
        }
    }
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
    if(!this->isEventExist(eventID))return false;
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

void EventManager::removeAttendeeFromEvent(string attendeeID, string eventID,AttendeeManager * Manager){
    if(!this->isEventExist(eventID))return;
    if(!this->isAttendeeAlreadyIn(attendeeID,eventID))return;
    AttendeeInterface * attendee = Manager->getAttendeeById(attendeeID);
    auto * currentEvent = this->getEventById(eventID);
    auto currentClientList = currentEvent->eventAttendees;
    vector<AttendeeInterface> newClients = {};
    for (auto &i  :  currentClientList) {
        if(i.id != attendeeID){
            newClients.push_back(i);
        }
    }
    currentEvent->eventAttendees = newClients;
}