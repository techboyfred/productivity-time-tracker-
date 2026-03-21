#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>

#include "utility.h"
#include "activity.h"
#include "timeSession.h"
#include "fileManager.h"
#include "reportGenerator.h"

class TimeTracker
{
	public:
		TimeTracker();
		TimeTracker(const TimeTracker& objOG);
		~TimeTracker();
		
		//core functionality
		void startSession(std::string name);
		void stopSession();
		void showAllActivities();
		void addPastSession(std::string name, std::string date, std::string startTime, std::string endTime);
		void pauseOrResume();

        //Getters for gui
        bool hasActiveSession() const;
        bool isSessionPaused() const;
        std::string getCurrentSessionName() const;
        int getCurrentSessionElapsed() const;
        std::vector<Activity*> getAllActivities();
		
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
		
		Activity* getActivity(std::string name);
		std::string getCurrentAcivity();
};
