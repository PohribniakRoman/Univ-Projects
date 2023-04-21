#include <sstream>

void AttendeeManager::addNewAttendee (string name, string surname, double date, double age, string email, string phoneNumber, string id) {
    AttendeeInterface newAttendee{name,surname,email,phoneNumber,id,age,date};
    this->AttendeesStore.push_back(newAttendee);
    this->saveData();
    this->loadData();
}

void AttendeeManager::loadNewAttendee(AttendeeInterface attendee){
    this->AttendeesStore.push_back(attendee);
}


void AttendeeManager::saveData(){
    ofstream newStream("Attendee.txt");
    newStream<<"!WITH_LOAD!\n";
    for (auto &i: this->AttendeesStore) {
        string attendeeData =i.name+"|"+i.surname+"|"+i.email+"|"+i.phoneNumber+"|"+ to_string(i.age)+"|"+to_string(i.date)+"|"+i.id;
        newStream<< attendeeData<<"\n";
    }
    newStream.close();
}

void AttendeeManager::loadAttendeeFromText(string str){
    stringstream ss(str);
    string currentData;
    AttendeeInterface loadAttendee;
    loadAttendee.id = "";
    for(int i = 0;getline(ss,currentData,'|');i++){
        switch (i) {
            case 0:loadAttendee.name = currentData;break;
            case 1:loadAttendee.surname = currentData;break;
            case 2:loadAttendee.email = currentData;break;
            case 3:loadAttendee.phoneNumber = currentData;break;
            case 4:loadAttendee.age = stod(currentData);break;
            case 5:loadAttendee.date = stod(currentData);break;
            case 6:loadAttendee.id = currentData;break;
        }
    }
    if(loadAttendee.id != ""){
        this->loadNewAttendee(loadAttendee);
    }
}

void AttendeeManager::loadData() {
    ifstream readFile("Attendee.txt");
    string marker;
    getline(readFile,marker);
    if(marker == "!WITH_LOAD!"){
        this->AttendeesStore = {};
        string currentAttendee;
        while(getline(readFile,currentAttendee)){
           this->loadAttendeeFromText(currentAttendee);
        }
    }
    readFile.close();
}

AttendeeInterface * AttendeeManager::getAttendeeById(string id){
    for (auto & i : this->AttendeesStore) {
        if(i.id == id){
            return &i;
        }
    }

    AttendeeInterface staticAT;
    auto & i = staticAT;
    string failed = "failed";
    i.id = failed;
    return &i;
}
AttendeeManager::AttendeeManager() {
    this->loadData();
}
void AttendeeManager::deleteAttendee(string id){
    auto localCopy = this->AttendeesStore;
    this->AttendeesStore = {};
    for (auto &i : localCopy) {
        if(i.id != id){
            AttendeesStore.push_back(i);
        }
    }
    this->saveData();
}
