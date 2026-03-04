module;

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

import Utility;

export module Activity;

export class Activity
{
	public:
		Activity(std::string name);
		
		std::string getName() const;
		int getTotalTime() const;
		std::string getFormattedTime();
		
		void addTime(int time);
		
	private:
		std::string _name;
		int _totalSeconds;
};

//Implementations
Activity::Activity(std::string name)
{
	_name = name;
	_totalSeconds = 0;
}
		
std::string Activity::getName() const
{
	return _name;
}

int Activity::getTotalTime() const
{
	return _totalSeconds;
}

std::string Activity::getFormattedTime()
{
	int hours, min, secs;
	hours = static_cast<int>(_totalSeconds / 3600);
	min = static_cast<int>(_totalSeconds % 3600) / 60;
	secs = _totalSeconds % 60;
	
	std::stringstream output;
	output << std::setfill('0') << std::setw(2)<< hours << " : " 
	       << std::setfill('0') << std::setw(2) <<  min << " : "
		   << std::setfill('0') << std::setw(2) <<  secs;
		   
	return output.str();
}		

void Activity::addTime(int time)
{
	_totalSeconds = _totalSeconds + time;
}