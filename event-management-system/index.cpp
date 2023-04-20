#include <iostream>
#include "attendees/AttendeeManager.h"
#include "attendees/AttendeeManager.cpp"
#include "event/EventManager.h"
#include "event/EventManager.cpp"
#include "FileWatcher.h"

using namespace std;

void invokeUpdate(string path){
    string fileName = "Attendee.txt";
    if(includes(path.begin(), path.end(),fileName.begin(),fileName.end())){
        AttendeeManager newManager;
        EventManager newEventManager(&newManager);
//        if(newManager.getAttendeeById("27")->id == "failed"){
//            cout<<"Failed to find\n";
//        }else{
//            cout<<newManager.getAttendeeById("27")->name<<"\n";
//        }
        cout<<newEventManager.getEventById("1")->eventAttendees.size();
    };

    //    newManager.getAttendeeById("1")->age = 10;
//    newEventManager.addNewEvent("newEvent","eventDescription","1","1",12,5,&newManager);
//    newEventManager.getEventById("1")->author->name = "Lukovskii54";
//    newEventManager.addAttendeeToEvent("1","1",&newManager);
//    cout<<newEventManager.getEventById("1")->eventAttendees.size();
//    newEventManager.removeAttendeeFromEvent("1","1",&newManager);
//    cout<<newEventManager.getEventById("1")->eventAttendees.size();
};

int main(){
    FileWatcher fw{"./", std::chrono::milliseconds(1000)};
    fw.start([] (string path_to_watch, FileStatus status) -> void {
         if(!filesystem::is_regular_file(filesystem::path(path_to_watch)) && status != FileStatus::erased) {
             return;
         }
         if(status == FileStatus::modified){
             cout<<path_to_watch<<"\n";
             invokeUpdate(path_to_watch);
        }
    });
 return 0;
};
