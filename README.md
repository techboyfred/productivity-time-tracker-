# productivity-time-tracker-
C++ console application for tracking study/work time with daily, weekly, and monthly reports

## Features
- **Activity Tracking**: Track time spent on multiple subjects/activities
- **Automatic Timing**: Start/stop sessions with precise timestamps
- **Comprehensive Reports**: Daily, weekly, and monthly summaries
- **Data Persistence**: All sessions saved automatically
- **Activity Statistics**: View total time spent on each activity

## Technologies used
- **Language**: C++ (C++20 modules)
- **Data Storage**: File-based persistence
- **Architecture**: Object-oriented design

## Project Structure
```
TimeTracker/
├── docs/
│   ├── build.bat
│   ├── design.pdf
│   └── changeLog.md
├── src/
│   ├── consoleEnhancer.cpp
│   ├── utility.cpp
│   ├── activity.cpp
│   ├── timeSession.cpp
│   ├── fileManager.cpp
│   ├── reportGenerator.cpp
│   ├── timeTracker.cpp
│   └── main.cpp
├── data/               # Data storage
│   └── sessions.txt
└── bin/
    └── main.exe
```

## Getting Started
### Prerequisites
- C++ compiler with C++20 support (GCC 11+)
- Windows

### Installation

## Main Functionality
1. Start Tracking: Select an activity and start the timer
2. Stop Tracking: Stop the current session (automatically saved)
3. Show current session: Show name of activity currently in session, along with the elapsed time
4. Pause/Resume Session: A single button to either pause or resume the session
5. Add Past Session: Add session to data file by providing the date, start time and end time
6. View Reports: Generate daily, weekly, and monthly reports
7. View All Activities: See cumulative time for all tracked activities

## Future Enhancements
- [ ] GUI implementation with Qt
- [ ] Custom activity creation
- [ ] Daily goals and progress tracking
- [ ] Export to CSV/Excel
- [ ] Exception handling class

## Author
- **Freddy Senamela**
- University of Johannesburg
- Second Year
- freddymailula@gmail.com
- www.linkedin.com/in/freddy-senamela-0b0417190

##  License
This project is open source and available under the MIT License.

## Acknowledgments
- [University of Johannesburg] Academy of Computer Science and Software Engineering
- Module: Introduction to Data Structures (Computer Science 1B)
- Special thanks to Dr Sithungu who lectured me in Computer Science 1

## Screenshots
<img width="767" height="1082" alt="1" src="https://github.com/user-attachments/assets/b0c3f668-28b9-468a-9d98-3407267664c0" />
<img width="795" height="751" alt="2" src="https://github.com/user-attachments/assets/0007f693-fc68-41fe-991a-2c312b8f8b1e" />
<img width="740" height="726" alt="3" src="https://github.com/user-attachments/assets/339b88ba-fc91-4fc2-8eaf-ada7fafa3c05" />



