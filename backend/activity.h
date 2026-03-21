#pragma once

#include <string>

class Activity
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
