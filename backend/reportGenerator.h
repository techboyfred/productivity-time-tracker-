#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <string>
#include <iomanip>

#include "timeSession.h"

class ReportGenerator
{
	public:
		ReportGenerator(std::string fileName);
		
		static std::string generateDailyReport(const std::vector<TimeSession*>& sessions);
		static std::string generateWeeklyReport(const std::vector<TimeSession*>& sessions);
		static std::string generateMonthlyReport(const std::vector<TimeSession*>& sessions);
		
		static std::string formatDuration(int seconds);
		
	private:
		//date helper functions
		static time_t getStartOfDay(time_t timestamp);
		static time_t getStartOfWeek(time_t timestamp);
		static time_t getStartOfMonth(time_t timestamp);
		
		static std::vector<TimeSession*> filterSessionsByDate(const std::vector<TimeSession*>& sessions, time_t startDate, time_t endDate);
		static std::map<std::string, int> groupByActivity(const std::vector<TimeSession*>& sessions);
		static std::string formatReport(const std::map<std::string, int>& activityTotals, const std::string& title);
};
