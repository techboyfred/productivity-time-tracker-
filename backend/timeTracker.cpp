#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>

#include "timeTracker.h"

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

//getters
bool TimeTracker::hasActiveSession() const
{
    return _currentSession != nullptr && _currentSession->isSessionActive();
}

bool TimeTracker::isSessionPaused() const
{
    return _currentSession != nullptr && _currentSession->isSessionPaused();
}

int TimeTracker::getCurrentSessionElapsed() const
{
    if (_currentSession != nullptr)
        return _currentSession->getDuration();
    return 0;
}
		
//helper functions
std::vector<TimeSession*> TimeTracker::loadPreviousSessions()
{
	std::vector<TimeSession*> prevSessions = _fileManager->loadAllSessions();
	
	//get activity totals from previous sessions
	for (TimeSession* session: prevSessions)
	{
		Activity* activity = findOrCreateActivity(session->getActivityName());
		activity->addTime(session->getDuration());
		//we may need to add more details about the activity
		//like start and end time for the sessions
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

	return newActivity;
}

//core functionality
void TimeTracker::startSession(std::string name)
{
	if (_currentSession != nullptr)
        return; // will be handled

    _currentSession = new TimeSession(name);
    _currentSession->start();
}

void TimeTracker::stopSession()
{
	if (_currentSession != nullptr)
	{
		_currentSession->end();
		_fileManager->saveSession(_currentSession);
	}
}

void TimeTracker::pauseOrResume()
{
	if (_currentSession != nullptr)
	{
		if (_currentSession->isSessionPaused())
			_currentSession->resume();
		else
			_currentSession->pause();
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

void TimeTracker::addPastSession(std::string name, std::string date, std::string startTime, std::string endTime)
{
	_currentSession = new TimeSession(name, date, startTime, endTime);
	_fileManager->saveSession(_currentSession);
}
