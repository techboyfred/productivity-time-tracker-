# Productivity Time Tracker — GUI

A desktop productivity and time tracking application built with Qt6 and C++20.

## Features
- Track time spent on multiple subjects/activities
- Start, stop, pause and resume sessions
- Add past sessions manually
- Daily, weekly and monthly reports
- All-time activity breakdown
- Automatic data persistence

## Technologies
- **Language**: C++20
- **GUI Framework**: Qt6 Widgets
- **Build System**: CMake
- **Architecture**: Backend/Frontend separation

## Project Structure
```
ProductivityTracker/
├── CMakeLists.txt
├── README.md
├── docs/
│   ├── changeLog.md
│   └── design.pdf
├── backend/
│   ├── activity.h / activity.cpp
│   ├── timeSession.h / timeSession.cpp
│   ├── timeTracker.h / timeTracker.cpp
│   ├── reportGenerator.h / reportGenerator.cpp
│   ├── fileManager.h / fileManager.cpp
│   └── utility.h / utility.cpp
├── data/
│   └── sessions.txt
└── gui/
    ├── main.cpp
    ├── mainwindow.h
    ├── mainwindow.cpp
    └── mainwindow.ui
```

## Prerequisites
- Qt 6.x with MinGW
- CMake 3.16+
- C++20 compatible compiler

## Building
1. Open CMakeLists.txt in Qt Creator
2. Configure the project with Desktop Qt 6 MinGW kit
3. Build → Build All (Ctrl+B)
4. Run (Ctrl+R)

## Main Functionality
1. Start Tracking: Select an activity and start the timer
2. Stop Tracking: Stop the current session (automatically saved)
3. Show current session: Show name of activity currently in session, along with the elapsed time
4. Pause/Resume Session: A single button to either pause or resume the session
5. Add Past Session: Add session to data file by providing the date, start time and end time
6. View Reports: Generate daily, weekly, and monthly reports
7. View All Activities: See cumulative time for all tracked activities

## Future Enhancements
- [ ] Profile tab that will let user store their unique information
- [ ] Daily goals and progress tracking
- [ ] Export to CSV/Excel
- [ ] Exception handling class
- [ ] Montly report change in structure

## Author
- **Freddy Senamela**
- University of Johannesburg
- freddymailula@gmail.com
- www.linkedin.com/in/freddy-senamela-0b0417190

##  License
This project is open source and available under the MIT License.

## Acknowledgments

## Screenshots




