#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <limits>
#include <iomanip>
#include <cstdlib>

#include "utility.h"

std::string fileName = "../data/sessions.txt";

//function converts human friendly time format into computer language time format
//Date: YEAR-MON-DAY..... Time: HR:MIN
time_t convertToTimeT(const std::string&date, const std::string& time)
{
	struct tm tm = {}; //place holder
	
	std::stringstream ss(date + " " + time);
	ss >> std::get_time(&tm, "%Y-%m-%d %H:%M"); //place date & time in special format into tm
	
	return mktime(&tm); //coversion to time_t
}
