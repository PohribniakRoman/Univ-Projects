#include <iostream>
#include "attendees/AttendeeManager.h"
#include "attendees/AttendeeManager.cpp"
#include "event/EventManager.h"
#include "event/EventManager.cpp"
#include "FileWatcher.h"

using namespace std;

void invokeUpdate(string path){
    string fileName = "CommandBus.txt";
    if(includes(path.begin(), path.end(),fileName.begin(),fileName.end())){
        AttendeeManager newManager;
        EventManager newEventManager(&newManager);
        ifstream readFile(fileName);
        string commandLine;
        while(getline(readFile,commandLine,'/')){
            string currentLine;
            getline(readFile,currentLine);
            if(commandLine == "ADD_ATTENDEE"){
                newManager.loadAttendeeFromText(currentLine);
            }
            if(commandLine == "ADD_EVENT"){
                newEventManager.loadEventFromText(currentLine,&newManager);
            }
            if(commandLine == "REMOVE_ATTENDEE") {
                newManager.deleteAttendee(currentLine);

            }
            if(commandLine == "REMOVE_EVENT") {
                newEventManager.deleteEvent(currentLine);
            }
        }
        readFile.close();
        cout<<newEventManager.getEventById("5")->eventAttendees.size();
        cout<<newManager.getAttendeeById("2")->name;
        cout<<newEventManager.getEventById("5")->eventAttendees[2]->name;

    };
};

int main(){
    invokeUpdate("CommandBus.txt");
    FileWatcher fw("./", chrono::milliseconds(1000));
    fw.start([] (string path_to_watch, FileStatus status) -> void {
         if(!filesystem::is_regular_file(filesystem::path(path_to_watch)) && status != FileStatus::erased) {
             return;
         }
         if(status == FileStatus::modified){
             invokeUpdate(path_to_watch);
        }
    });
 return 0;
};
