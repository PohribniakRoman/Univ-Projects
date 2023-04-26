struct WorkshopInterface{
    EventInterface event;
    string orator,theme;
};

class Workshop :public EventManager{
private:
    vector<WorkshopInterface> WorkshopStore;
public:
    Workshop(AttendeeManager * manager) {
        WorkshopStore = {};
        this->loadWorkshops(manager);
    }
    void loadLineWorkshop(string rawData,AttendeeManager * manager){
        stringstream ss(rawData);
        string currentData;
        getline(ss,currentData,'#');
        this->loadEventFromText(currentData,manager);
        getline(ss,currentData,'*');
        WorkshopInterface newWorkshop;
        newWorkshop.event = this->EventStore[this->EventStore.size()-1];
        newWorkshop.orator = currentData;
        getline(ss,currentData);
        newWorkshop.theme = currentData;
        WorkshopStore.push_back(newWorkshop);
        this->saveWorkshop();
    }
    void saveWorkshop(){
        ofstream outPutFile("C:\\Users\\Roman\\Desktop\\c\\Univ\\event-management-system\\client-side\\Workshop.txt");
        outPutFile<<"!WITH_LOAD!\n";
        for (auto &i:this->WorkshopStore) {
            string eventData = i.event.title+"|"+i.event.description+"|"+i.event.author->id+"|"+to_string(i.event.dateOfBirth)+"|"+to_string(i.event.dateOfStart)+"|"+i.event.id+"|";
            for (auto &j:i.event.eventAttendees) {
                if(j->id.length() >= 1){
                    eventData+=j->id+":";
                }
            }
            eventData+="#"+i.orator+"*"+i.theme;
            outPutFile<<eventData<<"\n";
        }
        outPutFile.close();

    }
    void joinWorkshop(string rawData,AttendeeManager * manager){
        stringstream ss(rawData);
        string id;
        getline(ss,id,'|');
        string eventId;
        getline(ss,eventId,'|');
        auto attendee = manager->getAttendeeById(id);
        cout<<attendee->name;
        for (auto &i : this->WorkshopStore) {
            if(i.event.id == eventId){
                i.event.eventAttendees.push_back(attendee);
            }
        }
        this->saveWorkshop();

    }
    void leaveWorkshop(string rawData,AttendeeManager * manager){
        stringstream ss(rawData);
        string id;
        getline(ss,id,'|');
        string eventId;
        getline(ss,eventId,'|');
        auto attendee = manager->getAttendeeById(id);
        for (auto &i : this->WorkshopStore) {
            if (i.event.id == eventId) {
                auto currentClientList = i.event.eventAttendees;
                vector<AttendeeInterface*> newClients = {};
                for (auto &i  :  currentClientList) {
                    if(i->id != id){
                        newClients.push_back(i);
                    }
                }
                i.event.eventAttendees = newClients;
            }
        }
        this->saveWorkshop();

    }
    void deleteWorkshop(string id){
        auto localCopy = this->WorkshopStore;
        localCopy={};
        for (auto &i: this->WorkshopStore) {
            if(i.event.id != id){
                localCopy.push_back(i);
            }
        }
        this->WorkshopStore = localCopy;
        this->saveWorkshop();

    }
    void loadWorkshops(AttendeeManager * manager){
        ifstream readFile("C:\\Users\\Roman\\Desktop\\c\\Univ\\event-management-system\\client-side\\Workshop.txt");
        string marker;
        getline(readFile,marker);
        if(marker == "!WITH_LOAD!") {
            this->WorkshopStore = {};
            string currentEvent;
            while(getline(readFile,currentEvent)){
                this->loadLineWorkshop(currentEvent,manager);
            }
        }
    }
};