#include <iostream>
#include "attendees/AttendeeManager.h"
#include "attendees/AttendeeManager.cpp"
#include "event/EventManager.h"
#include "event/EventManager.cpp"
#include "event/Workshop.h"
#include "FileWatcher.h"

using namespace std;

void invokeUpdate(){
        string fileName = "C:\\Users\\Roman\\Desktop\\c\\Univ\\event-management-system\\client-side\\CommandBus.txt";
        AttendeeManager newManager;
        EventManager newEventManager(&newManager);
        Workshop newWorkshopManager(&newManager);
        newEventManager();
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
                newEventManager.saveData();
            }
            if(commandLine == "ADD_WORKSHOP"){
                newWorkshopManager.loadLineWorkshop(currentLine,&newManager);
            }
            if(commandLine == "JOIN_WORKSHOP"){
                newWorkshopManager.joinWorkshop(currentLine,&newManager);
            }
            if(commandLine == "LEAVE_WORKSHOP"){
                newWorkshopManager.leaveWorkshop(currentLine,&newManager);
            }
            if(commandLine == "DELETE_WORKSHOP"){
                newWorkshopManager.deleteWorkshop(currentLine);
            }
            if(commandLine == "JOIN_EVENT"){
                newEventManager.joinEvent(currentLine,&newManager);
            }
            if(commandLine == "LEAVE_EVENT"){
                newEventManager.leaveEvent(currentLine,&newManager);
            }
            if(commandLine == "REMOVE_ATTENDEE") {
                newEventManager.deleteAttendee(currentLine,&newManager);
            }
            if(commandLine == "REMOVE_EVENT") {
                newEventManager.deleteEvent(currentLine);
            }
        }
        if(commandLine.size()>1){
        readFile.close();
        ofstream clearFile(fileName);
        clearFile<<"";
        clearFile.close();
        }
};

int main(){
    invokeUpdate();
    FileWatcher fw("./", chrono::milliseconds(1000));
    fw.start([] (string path_to_watch, FileStatus status) -> void {
         if(!filesystem::is_regular_file(filesystem::path(path_to_watch)) && status != FileStatus::erased) {
             return;
         }
         if(status == FileStatus::modified){
             if(path_to_watch == "./client-side\\CommandBus.txt"){
             invokeUpdate();
             }
        }
    });
 return 0;
};
