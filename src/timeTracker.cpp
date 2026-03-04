module;

#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <string>


import Utility;
import Activity;
import TimeSession;
import FileManager;
import ReportGenerator;
import consoleEnhancer;

export module TimeTracker;

export class TimeTracker
{
	public:
		TimeTracker();
		TimeTracker(const TimeTracker& objOG);
		~TimeTracker();
		
		//core functionality
		void startSession(std::string name);
		void stopSession();
		void showAllActivities();
		void showCurrentSession();
		void addPastSession(std::string name, std::string date, std::string startTime, std::string endTime);
		void pauseOrResume();
		
		//reports
		std::string getDailyReport();
		std::string getWeeklyReport();
		std::string getMonthlyReport();
	
	private:
		std::vector<Activity*> _activities;
		TimeSession* _currentSession;
		FileManager* _fileManager;
		
		//helper functions
		std::vector<TimeSession*> loadPreviousSessions();
		Activity* findOrCreateActivity(std::string name);
		
		std::vector<Activity*> getAllActivities();
		Activity* getActivity(std::string name);
		std::string getCurrentAcivity();
};
TimeTracker::TimeTracker()
{
	_currentSession = nullptr;
	_fileManager = new FileManager(fileName);
	
	//load previous sessions and rebuild activity totals
	loadPreviousSessions();	
}	

TimeTracker::~TimeTracker()
{
	//clean up all activity objects
	for (Activity* activity: _activities)
		delete activity;
	
	//clean up current session
	if (_currentSession != nullptr)
	{
		delete _currentSession;
		_currentSession = nullptr;
	}
	
	delete _fileManager; //clean up file manager
}
		
//helper functions
std::vector<TimeSession*> TimeTracker::loadPreviousSessions()
{
	printInfo("loading previous sessions");
	
	std::vector<TimeSession*> prevSessions = _fileManager->loadAllSessions();
	
	//get activity totals from previous sessions
	for (TimeSession* session: prevSessions)
	{
		Activity* activity = findOrCreateActivity(session->getActivityName());
		
		// Calculate duration from timestamps, not from saved value!
        int duration = session->getDuration();
        activity->addTime(duration);
		
	}
	return prevSessions;
}

Activity* TimeTracker::findOrCreateActivity(std::string name)
{
	//search for existing activity
	for (Activity* activity: _activities)
	{
		if (activity->getName() == name)
			return activity; // found it
	}
	
	//Not found! create new activity
	Activity* newActivity = new Activity(name);
	_activities.push_back(newActivity);
	
	//std::cout << "created new activity" << name << std::endl;
	printSuccess("created new activity " + name);
	return newActivity;
}

//core functionality
void TimeTracker::startSession(std::string name)
{
	if (_currentSession != nullptr)
	{
		setColour(C_ERROR);
		std::cout << "✗ ERROR : Already tracking " << _currentSession->getActivityName() << std::endl;	
		resetColour();
	}
	else
	{
		_currentSession = new TimeSession(name);
		_currentSession->start();
		
		setColour(C_SUCCESS);
		std::cout << "✓ Now tracking " << _currentSession->getActivityName() << "\n" << std::endl;
		resetColour();
	}
}

void TimeTracker::stopSession()
{
	if (_currentSession != nullptr)
	{
		_currentSession->end();
		_fileManager->saveSession(_currentSession);
		
		setColour(C_SUCCESS);
		std::cout << "✓ Stopped tracking " << _currentSession->getActivityName() << "\n" << std::endl;
		resetColour();
	}
	else
		printError("No current session- cannot stop tracking");
	
	
}

void TimeTracker::pauseOrResume()
{
	if (_currentSession != nullptr)
	{
		if (_currentSession->isSessionPaused())
		{
			_currentSession->resume();
			printSuccess("Session succesfully resumed");
		}
		else
		{
			_currentSession->pause();
			printSuccess("Session succesfully paused");
		}
		
	}
	else
	{
		printError("cannot pause or resume an inactive session");
	}
}

void TimeTracker::showCurrentSession()
{
	if (_currentSession != nullptr)
	{
		setColour(C_INFO);
		std::cout << "ℹ  You are currently tracking " << _currentSession->getActivityName() << std::endl;
		
		int duration = _currentSession->getDuration();
		std::cout << "Elapsed time: (" << ReportGenerator::formatDuration(duration) << ")" << std::endl;
		resetColour();
	}
	else
	{	
		printError("No active session");
	}
	
}

//reports
std::string TimeTracker::getDailyReport()
{
	std::vector<TimeSession*> sessions = loadPreviousSessions();
	std::string dailyReport = ReportGenerator::generateDailyReport(sessions);
	
	// Clean up the loaded sessions
    for (TimeSession* session : sessions)
    {
        delete session;
    }
	
	return dailyReport;
}

std::string TimeTracker::getWeeklyReport()
{
	std::vector<TimeSession*> sessions = loadPreviousSessions();
	std::string WeeklyReport = ReportGenerator::generateWeeklyReport(sessions);
	
	// Clean up the loaded sessions
    for (TimeSession* session : sessions)
    {
        delete session;
    }
	
	return WeeklyReport;
}

std::string TimeTracker::getMonthlyReport()
{
	std::vector<TimeSession*> sessions = loadPreviousSessions();
	std::string monthlyReport = ReportGenerator::generateMonthlyReport(sessions);
	
	// Clean up the loaded sessions
    for (TimeSession* session : sessions)
    {
        delete session;
    }
	
	return monthlyReport;
}
		
std::vector<Activity*> TimeTracker::getAllActivities()
{
	return _activities;
}

Activity* TimeTracker::getActivity(std::string name)
{
	return findOrCreateActivity(name);
}

void TimeTracker::showAllActivities()
{
	std::vector<Activity*> activities = getAllActivities();
    
    setColour(9);
	std::cout << "\n╔═══════════════════════════════════════════════════════╗" << std::endl;
	std::cout << std::left << "║";
	setColour(14);
    std::cout << "                  ALL TIME ACTIVITIES                  ";
	setColour(9);
	std::cout << "║" << std::endl;
    std::cout << "╠═══════════════════════════════════════════════════════╣" << std::endl;
	resetColour();
    
    if (activities.empty())
    {
        setColour(9);
		std::cout << std::left << "║";
		setColour(C_INFO);
		std::cout << " [i] No activities recorded yet.";
		setColour(9);
		std::cout << "                       ║\n";
		std::cout << std::left << "║";
		resetColour();
        std::cout << " Start tracking to see your stats!";
		setColour(9);
		std::cout << "                     ║\n";
		resetColour();
    }
    else
    {
        // Calculate total time across all activities
        int totalSeconds = 0;
        for (Activity* activity : activities)
        {
            totalSeconds += activity->getTotalTime();
        }
		
		setColour(15);
        textInBoarder("Total Time Tracked: ");
        
        // Format total time
        int hours = totalSeconds / 3600;
        int minutes = (totalSeconds % 3600) / 60;
		std::string strHours = std::to_string(hours);
		std::string strMins = std::to_string(minutes);
		std::string output = strHours + "h " + strMins + "m";
		dataInBoarder(output);
        
		setColour(9);
		std::cout << "║                                                       ║" << std::endl;
		std::cout << std::left << "║";
		setColour(14);
        std::cout << " Activity Breakdown";
		setColour(9);
		std::cout << "                                    ║\n";

        std::cout << "╠═══════════════════════════════════════════════════════╣\n";
		resetColour();
        
        // Display each activity
        for (Activity* activity : activities)
        {
            int activityTime = activity->getTotalTime();
            double percentage = (activityTime * 100.0) / totalSeconds;
			
			setColour(9);
            std::cout << std::left << "║";
			resetColour();
			std::cout << " " << std::setw(25) << activity->getName() << " ";
			setColour(10);
            std::cout << std::setw(12) << activity->getFormattedTime()
                      << " (" << std::setw(5) << std::fixed << std::setprecision(1) << std::right
                      << percentage << "%)" << std::setw(7) << " ";
			setColour(9);
			std::cout << "║" << std::endl;
        }
        
		
    }
    setColour(9);
    std::cout << "╚═══════════════════════════════════════════════════════╝" << std::endl;
	resetColour();
}

void TimeTracker::addPastSession(std::string name, std::string date, std::string startTime, std::string endTime)
{
	_currentSession = new TimeSession(name, date, startTime, endTime);
	_fileManager->saveSession(_currentSession);
	
	setColour(C_SUCCESS);
	std::cout << "✓ Added session " << _currentSession->getActivityName() << "\n" << std::endl;
	resetColour();
}