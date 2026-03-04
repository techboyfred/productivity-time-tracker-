# Time Tracker - Change Log

## [1.3.1] - 2026-02-02

### Fixed
- Fixed logical errors in TimeSession 
- Fixed more bugs in TimeSession, fileManager and TimeTracker


## Changed
- Changed the border colours and brightened the text to make it more readable by user
- Added colour for data in reports to distinguish between data(numbers) and text
- Completed changed the logic in "view all activities" functionality

## [1.3.0] - 2026-01-21

### Added
- consoleEnhancer file with UTF-8 characters
- Borders around the console application
- Colours coding errors, successes, warnings and infos
- Improved alignment 

### Changed
- Removed more redundant blocks of code in TimeSession, fileManager and TimeTracker classes

### Fixed
- A memory bug within the pause/resume function 
- An input buffer bug in the main program
- Another memory bug in the show current session function

## [1.2.0] - 2025-12-28

### Added
- Show current activity in main menu (displays "Currently tracking: Math")
- An option to track a non predefined activity
- An option to add past session
- Pause/resume session feature
- Functionality to clear the console (windows & Linux)
- An option to delete most recent session

### Changed
- Updated the menu layout
- Removed redundant functionality in TimeTracker and TimeSession classes

## [1.1.0] - 2025-12-26

### Changed
- Improved report formatting with better alignment
- Updated menu layout for clarity

### Fixed
- Memory leak when generating reports
- Crash when stopping non-existent session

## [1.0.0] - 2024-12-24

### Added
- Initial release
- Basic time tracking (start/stop)
- Daily/weekly/monthly reports
- All time activity reports 
- File persistence
- Five predefined activities