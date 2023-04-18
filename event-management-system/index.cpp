#include <iostream>
#include "attendees/AttendeeManager.h"
#include "attendees/AttendeeManager.cpp"
#include "event/EventManager.h"
#include "event/EventManager.cpp"


using namespace std;

int main(){
    AttendeeManager newManager;
    newManager.addNewAttendee("Roman","Lamer",12,12,"mail.ua","+380","1");
    newManager.getAttendeeById("1")->age = 10;
    EventManager newEventManager;
    newEventManager.addNewEvent("newEvent","eventDescription","1","1",12,5,&newManager);
    newEventManager.getEventById("1")->author->name = "Lukovskii54";
    cout<<newEventManager.getEventById("1")->author->name;
    cout<<newManager.getAttendeeById("1")->name;
    return 0;
};