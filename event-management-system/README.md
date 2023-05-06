<h1 align="center">Event Managment System</h1>
<hr/>
<p align="center">This project was created by <a href="https://github.com/PohribniakRoman">Roman Pohribniak</a></p>
<h5>Stack of technologies used in project:</h5>
<ul>
    <li>C++</li>
    <li>Node.js/Express.js</li>
    <li>Vite</li>
    <li>React(TypeScript+SWC)</li>
    <li>Redux</li>
    <li>React-Router</li>
    <li>SCSS/SASS</li>
    <li>MUI</li>
</ul>
<h5>Project logic was realized in С++ here is description:</h5>
<ul>
    <li><a href="https://github.com/PohribniakRoman/Univ-Projects/tree/main/event-management-system/attendees">Operations with Attendees</a></li>
    <li><a href="https://github.com/PohribniakRoman/Univ-Projects/tree/main/event-management-system/event">Operations with Events</a>(Includes extended instance from event - workshop)</li>
    <li><a href="https://github.com/PohribniakRoman/Univ-Projects/blob/main/event-management-system/FileWatcher.h">File Watcher</a>(Makes script invoke update after changing files)</li>
    <li><a href="https://github.com/PohribniakRoman/Univ-Projects/blob/main/event-management-system/index.cpp">Main file</a>(Contains all commands & Run script)</li>
</ul>
<h5>The application inherits the RESTful API architecture. The C++ side of the application acts as a server and performs the following tasks:</h5>

1. Get a command; 
1. Extract data from the command body;
1. Processes the request; 
1. Creation/Editing of records in storage files; 
1. Deleting command when it is done; 

<h5>The client side of the application was written in React with several extensions(redux,mui,etc)</h5>
<p>This is not a SPA, so it contains more than one page, here is the list:</p>   

<h3 align="center">Registration Page</h3>
<p align="center">You can change your login/registration by clicking the text below the input button.</p>
<img src="https://github.com/PohribniakRoman/Univ-Projects/blob/main/event-management-system/client-side/documentation-img-lib/reg.png?raw=true">
<h3 align="center">Login Page</h3>
<img src="https://github.com/PohribniakRoman/Univ-Projects/blob/main/event-management-system/client-side/documentation-img-lib/login.png?raw=true">
<h3 align="center">Event Page(unauthorized)</h3>
<img src="https://github.com/PohribniakRoman/Univ-Projects/blob/main/event-management-system/client-side/documentation-img-lib/EventUNlogined.png?raw=true">
<h3 align="center">Event Page(authorized)</h3>
<p align="center">Here is presented the delete event button, because the client created the event, other clients don't have this button</p>
<img src="https://github.com/PohribniakRoman/Univ-Projects/blob/main/event-management-system/client-side/documentation-img-lib/EventAttendedLogined.png?raw=true">
<p align="center">The user unsubscribed from the event.</p>
<img src="https://github.com/PohribniakRoman/Univ-Projects/blob/main/event-management-system/client-side/documentation-img-lib/EvenUnAttendedtLogined.png?raw=true">
<h3 align="center">Events List Page</h3>
<img src="https://github.com/PohribniakRoman/Univ-Projects/blob/main/event-management-system/client-side/documentation-img-lib/EventLogined.png?raw=true">
<h3 align="center">Workshop List Page</h3>
<img src="https://github.com/PohribniakRoman/Univ-Projects/blob/main/event-management-system/client-side/documentation-img-lib/WorkshopsLogined.png?raw=true">
<h3 align="center">Workshop Page(authorized)</h3>
<p align="center">Here is presented the delete event button, because the client created the workshop, other clients don't have this button</p>
<img src="https://github.com/PohribniakRoman/Univ-Projects/blob/main/event-management-system/client-side/documentation-img-lib/WorkshopAttendedLogined.png?raw=true">
<h3 align="center">Workshop Page(unauthorized)</h3>
<img src="https://github.com/PohribniakRoman/Univ-Projects/blob/main/event-management-system/client-side/documentation-img-lib/WorkshopUNlogined.png?raw=true">
