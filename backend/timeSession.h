#pragma once

#include <string>
#include <ctime>

class TimeSession
{
	public:
		TimeSession(std::string name);
		TimeSession(std::string name, time_t start, time_t end); //for reading from file
		TimeSession(std::string name, std::string date, std::string start, std::string end); // for adding a past session
		
		//getters
		int getDuration() const;
		std::string getActivityName() const;
		bool isSessionActive() const;
		bool isSessionPaused() const;
		time_t getStartTime() const;
		time_t getEndTime() const;
		int getTotalActiveDuration();
		int getTotalPausedDuration();
		
		
		std::string outputData();
		void start();
		void end();
		void pause();
		void resume();
		
	private:
		std::string _activityName;
		bool _active;
		bool _paused;
		time_t _startTime;
		time_t _endTime;
		time_t _pauseTime;
		time_t _resumeTime;
		int _totalActiveDuration;
		int _totalPausedDuration;
};
