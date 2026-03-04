module;

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

import Utility;
import consoleEnhancer;

export module TimeSession;

export class TimeSession
{
	public:
		TimeSession(std::string name);
		TimeSession(std::string name, time_t start, time_t end, int pausedSeconds); //for reading from file
		TimeSession(std::string name, std::string date, std::string start, std::string end); // for adding a past session
		
		//getters
		int getDuration() const;
		std::string getActivityName() const;
		bool isSessionActive() const;
		bool isSessionPaused() const;
		time_t getStartTime() const;
		time_t getEndTime() const;
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
		time_t _pauseStartTime;
		int _totalPausedSeconds;
};
//Constructors
TimeSession::TimeSession(std::string name)
{
	_activityName = name;
	_active = false;
	_paused = false;
	_startTime = 0;
	_endTime = 0;
	_pauseStartTime = 0;
	_totalPausedSeconds = 0;
}

TimeSession::TimeSession(std::string name, time_t start, time_t end, int pausedSeconds)
{
	_activityName = name;
	_active = false;
	_paused = false;
	_startTime = start;
	_endTime = end;
	_pauseStartTime = 0;
	_totalPausedSeconds = pausedSeconds;
}

TimeSession::TimeSession(std::string name, std::string date, std::string start, std::string end)
{
	_activityName = name;
	_startTime = convertToTimeT(date, start);
	_endTime = convertToTimeT(date, end);
	_pauseStartTime = 0;
	_active = false;
	_paused = false;
	_totalPausedSeconds = 0;
}

//getters		
int TimeSession::getDuration() const
{
	if (_active)
    {
        int elapsed = time(nullptr) - _startTime; //total elapsed
		if (!_paused)
		{
			// Session is actively running
			return elapsed - _totalPausedSeconds;
		}
		else
		{
			// Session is paused
			return elapsed - _totalPausedSeconds;
		}
    }
    else
    {
        // Session has ended
		int elapsed = _endTime - _startTime;
        return elapsed - _totalPausedSeconds;
    }
}

std::string TimeSession::getActivityName() const
{
	return _activityName;
}

bool TimeSession::isSessionActive() const
{
	return _active;
}

bool TimeSession::isSessionPaused() const
{
	return _paused;
}

time_t TimeSession::getStartTime() const
{
	return _startTime;
}

time_t TimeSession::getEndTime() const
{
	return _endTime;
}

//Methods		
std::string TimeSession::outputData()
{
	std::stringstream ss;
	ss << _activityName << ", "
	   << _startTime << ", "
	   << _endTime << ", "
	   << _totalPausedSeconds << ", "
	   << getDuration();
	   
	   
	return ss.str();
}

void TimeSession::start()
{
	_startTime = time(nullptr);
	_active = true;
	_paused = false;
	_totalPausedSeconds = 0;
}

void TimeSession::end()
{
	if (_active)
	{
		if (_paused) //unpause first
		{
			int pauseDuration = time(nullptr) - _pauseStartTime;
			_totalPausedSeconds += pauseDuration;
			_paused = false;
		}
		_endTime = time(nullptr);
		_active = false;
	}
}

void TimeSession::pause()
{
	if (_active)
	{
		if (_paused)
			return; //already paused
		
		_pauseStartTime = time(nullptr);
		_paused = true;
	}
}

void TimeSession::resume()
{
	if (_active)
	{
		if (!_paused)
			return; //session not paused
		
		//calculate pause time and add to total
		int pauseDuration = time(nullptr) - _pauseStartTime;
		_totalPausedSeconds += pauseDuration;
		
		_paused = false;
		_pauseStartTime = 0;
	}
}		