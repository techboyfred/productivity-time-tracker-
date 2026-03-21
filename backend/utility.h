#pragma once

#include <string>
#include <ctime>

extern std::string fileName;

time_t convertToTimeT(const std::string& date, const std::string& time);