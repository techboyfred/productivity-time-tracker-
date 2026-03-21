#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

#include "utility.h"
#include "timeSession.h"

TimeSession::TimeSession(std::string name)
{
	_activityName = name;
	_active = false;
	_startTime = 0;
	_endTime = 0;
	_pauseTime = 0;
	_resumeTime = 0;
	_totalActiveDuration = 0;
	_totalPausedDuration = 0;
}

TimeSession::TimeSession(std::string name, time_t start, time_t end)
{
	_activityName = name;
	_active = false;
	_startTime = start;
	_endTime = end;
}

TimeSession::TimeSession(std::string name, std::string date, std::string start, std::string end)
{
	_activityName = name;
	_startTime = convertToTimeT(date, start);
	_endTime = convertToTimeT(date, end);
	_active = false;
}
		
int TimeSession::getDuration() const
{
	return (_totalActiveDuration - _totalPausedDuration);
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
		
std::string TimeSession::outputData()
{
	std::stringstream ss;
	ss << _activityName << ", "
	   << _startTime << ", "
	   << _endTime << ", "
	   << getDuration();
	   
	return ss.str();
}

void TimeSession::start()
{
	_startTime = time(nullptr);
	_active = true;
	_paused = false;
	_totalActiveDuration = 0;
	_totalPausedDuration = 0;
}

void TimeSession::end()
{
	if (_active)
	{
		_endTime = time(nullptr);
		_active = false;
		_totalActiveDuration = _endTime - _startTime;
	}
}

void TimeSession::pause()
{
	_pauseTime = time(nullptr);
	_paused = true;
	_totalActiveDuration = time(nullptr) - _startTime;
}

void TimeSession::resume()
{
	_resumeTime = time(nullptr);
	_paused = false;
	_totalActiveDuration = time(nullptr) - _startTime;
	int pausedDuration =  _resumeTime - _pauseTime;
	_totalPausedDuration = _totalPausedDuration + pausedDuration;
}		
