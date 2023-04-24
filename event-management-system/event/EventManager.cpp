using namespace std;

EventManager::EventManager(AttendeeManager * manager) {
    this->loadData(manager);
}

void EventManager::saveData(){
    ofstream outPutFile("C:\\Users\\Roman\\Desktop\\c\\Univ\\event-management-system\\client-side\\Event.txt");
    outPutFile<<"!WITH_LOAD!\n";
    for (auto &i:this->EventStore) {
            string eventData = i.title+"|"+i.description+"|"+i.author->id+"|"+to_string(i.dateOfBirth)+"|"+to_string(i.dateOfStart)+"|"+i.id+"|";
            for (auto &j:i.eventAttendees) {
                if(j->id.length() >= 1){
                    eventData+=j->id+":";
                }
            }
            outPutFile<<eventData<<"\n";
    }
    outPutFile.close();
}

void EventManager::deleteEvent(string id) {
    auto localCopy = this->EventStore;
    this->EventStore = {};
    for (auto &i : localCopy) {
        if(i.id !=  id){
            this->EventStore.push_back(i);
        }
    }
    this->saveData();
}

void EventManager::addNewEvent(string title, string description, string id, string authorID, double birth,double start,AttendeeManager* Manager) {
    if(this->isEventExist(id))return;
    AttendeeInterface * author =  Manager->getAttendeeById(authorID);
    EventInterface newEvent {title,description,id,author,{},birth,start};
    this->EventStore.push_back(newEvent);
    this->saveData();
};

void EventManager::joinEvent(string rawData, AttendeeManager *manager) {
    stringstream ss(rawData);
    string id;
    getline(ss,id,'|');
    string eventId;
    getline(ss,eventId,'|');
    this->addAttendeeToEvent(id,eventId,manager);
}

void EventManager::leaveEvent(string rawData, AttendeeManager *manager) {
    stringstream ss(rawData);
    string id;
    getline(ss,id,'|');
    string eventId;
    getline(ss,eventId,'|');
    this->removeAttendeeFromEvent(id,eventId,manager);
}


void EventManager::deleteAttendee(string id,AttendeeManager * manager) {
    for (auto &i : this->EventStore) {
        if(i.author->id == id){
            this->deleteEvent(i.id);
        }else{
        for (auto &j:i.eventAttendees) {
            if(j->id == id){
                this->removeAttendeeFromEvent(i.id,j->id,manager);
            }
           }
        }
    }
    manager->deleteAttendee(id);
}

void EventManager::loadEventFromText(string str, AttendeeManager *manager) {
    stringstream ss(str);
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
                    newEvent.eventAttendees.push_back(manager->getAttendeeById(attendee));
                }
        }
    }
    this->EventStore.push_back(newEvent);
    this->saveData();
}

void EventManager::loadData(AttendeeManager * manager) {
    ifstream readFile("C:\\Users\\Roman\\Desktop\\c\\Univ\\event-management-system\\client-side\\Event.txt");
    string marker;
    getline(readFile,marker);
    if(marker == "!WITH_LOAD!") {
        this->EventStore = {};
        string currentEvent;
        while(getline(readFile,currentEvent)){
            this->loadEventFromText(currentEvent,manager);
        }
    }
}


EventInterface * EventManager::getEventById(string id) {
    for (auto & i : this->EventStore) {
            if(i.id == id){
                return &i;
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
        if(j->id == attendeeID){
            res = true;
        }
    }
    return res;
}

void EventManager::addAttendeeToEvent(string attendeeID, string eventID,AttendeeManager * Manager) {
    if(!this->isEventExist(eventID))return;
    if(this->isAttendeeAlreadyIn(attendeeID,eventID))return;
    AttendeeInterface * attendee = Manager->getAttendeeById(attendeeID);
    this->getEventById(eventID)->eventAttendees.push_back(attendee);
    this->saveData();
}

void EventManager::removeAttendeeFromEvent(string attendeeID, string eventID,AttendeeManager * Manager){
    if(!this->isEventExist(eventID))return;
    if(!this->isAttendeeAlreadyIn(attendeeID,eventID))return;
    AttendeeInterface * attendee = Manager->getAttendeeById(attendeeID);
    auto * currentEvent = this->getEventById(eventID);
    auto currentClientList = currentEvent->eventAttendees;
    vector<AttendeeInterface*> newClients = {};
    for (auto &i  :  currentClientList) {
        if(i->id != attendeeID){
            newClients.push_back(i);
        }
    }
    currentEvent->eventAttendees = newClients;
    this->saveData();
}