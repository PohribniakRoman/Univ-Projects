void AttendeeManager::addNewAttendee (string name, string surname,double date,double age,string email,string phoneNumber,string id) {
    AttendeeInterface newAttendee{name,email,phoneNumber,surname,id,age,date};
    this->AttendeesStore.push_back(newAttendee);
}

AttendeeInterface * AttendeeManager::getAttendeeById(string id){
    for (auto & i : this->AttendeesStore) {
        if(i.id == id){
            return &i;
        }
    }
}

