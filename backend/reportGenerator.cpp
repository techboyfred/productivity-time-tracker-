#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <string>
#include <iomanip>

#include "timeSession.h"
#include "reportGenerator.h"

std::vector<TimeSession*> ReportGenerator::filterSessionsByDate(const std::vector<TimeSession*>& sessions, time_t startDate, time_t endDate)
{
	std::vector<TimeSession*> filtered;
	for (TimeSession* session: sessions)
	{
		time_t sessionStart = session->getStartTime();
		if (sessionStart >= startDate && sessionStart <= endDate)
			filtered.push_back(session);
	}
	return filtered;
}

std::map<std::string, int> ReportGenerator::groupByActivity(const std::vector<TimeSession*>& sessions)
{
	std::map<std::string, int> activityTotals; //stores int values, but mapped by a string
	for (TimeSession* session: sessions)
	{
		std::string activityName = session->getActivityName();
		int duration = session->getDuration();
		
		//add to existing or create neww entry
		activityTotals[activityName] += duration;
	}
	return activityTotals;
}

std::string ReportGenerator::formatReport(const std::map<std::string, int>& activityTotals, const std::string& title)
{
	std::stringstream report;
	
	//header
	report << "\n╔════════════════════════════════════╗\n"
		   << "       " << title << "\n"
		   << "╚════════════════════════════════════╝\n\n";
		   
	//check if there's any data
	if (activityTotals.empty())
	{
		report << "No activity recorded for this period. \n"
			   << "╚════════════════════════════════════╝\n";
		return report.str();
	}
	
	//get total time
	int totalSeconds = 0;
	for (const auto& pair: activityTotals)
	{
		totalSeconds += pair.second;
	}
	report << "Total time: " << formatDuration(totalSeconds) << "\n\n";
	
	//activity breakdown
	report << "Activity breakdown               \n"
		   << "╔════════════════════════════════════╗\n";
		   
	for (const auto& pair: activityTotals)
	{
		std::string activity = pair.first;
		int seconds = pair.second;
		double percentage = (seconds / totalSeconds) * 100.0;
		
		report << std::left << std::setw(20) << activity << ": " //left and setw for alignment
			   << std::setw(12) << formatDuration(seconds)
			   << " (" << std::fixed << std::setprecision(2) << percentage << "%)\n"; //precision for decimal
	}
	report << "\n╚════════════════════════════════════╝\n";
	return report.str();
}	

time_t ReportGenerator::getStartOfDay(time_t timestamp)
{
	struct tm* timeInfo = localtime(&timestamp);
	timeInfo->tm_hour = 0;
	timeInfo->tm_min = 0;
	timeInfo->tm_sec = 0;
	
	return mktime(timeInfo);
}

time_t ReportGenerator::getStartOfWeek(time_t timestamp)
{
	struct tm* timeInfo = localtime(&timestamp);
	
	//calculate days since Monday
	int daysSinceMonday = (timeInfo->tm_wday + 6) % 7;
	
	//subtract those days
	timeInfo->tm_mday -= daysSinceMonday;
	timeInfo->tm_hour = 0;
	timeInfo->tm_min = 0;
	timeInfo->tm_sec = 0;
	
	return mktime(timeInfo);
}

time_t ReportGenerator::getStartOfMonth(time_t timestamp)
{
	struct tm* timeInfo = localtime(&timestamp);
	timeInfo->tm_mday = 1;  // First day of month
	timeInfo->tm_hour = 0;
	timeInfo->tm_min = 0;
	timeInfo->tm_sec = 0;
	
	return mktime(timeInfo);
}

std::string ReportGenerator::generateDailyReport(const std::vector<TimeSession*>& sessions)
{
	time_t now = time(nullptr);
	time_t todayStart = getStartOfDay(now);
	time_t todayEnd = now;
	
	std::vector<TimeSession*> todaySessions = filterSessionsByDate(sessions, todayStart, todayEnd);
	std::map<std::string, int> activityTotals = groupByActivity(todaySessions);
	
	return formatReport(activityTotals, "Daily Report");
}

std::string ReportGenerator::generateWeeklyReport(const std::vector<TimeSession*>& sessions)
{
	time_t now = time(nullptr);
	time_t weekStart = getStartOfWeek(now);
	time_t weekEnd = now;
	
	std::vector<TimeSession*> weekSessions = filterSessionsByDate(sessions, weekStart, weekEnd);
	std::map<std::string, int> activityTotals = groupByActivity(weekSessions);
	
	return formatReport(activityTotals, "Weekly Report");
}

std::string ReportGenerator::generateMonthlyReport(const std::vector<TimeSession*>& sessions)
{
	time_t now = time(nullptr);
	time_t monthStart = getStartOfMonth(now);
	time_t monthEnd = now;
	
	std::vector<TimeSession*> monthSessions = filterSessionsByDate(sessions, monthStart, monthEnd);
	std::map<std::string, int> activityTotals = groupByActivity(monthSessions);
	
	return formatReport(activityTotals, "Monthly Report");
}
	
std::string ReportGenerator::formatDuration(int seconds)
{
	int hours = seconds / 3600;
	int mins = (seconds % 3600) / 60;
	int secs = seconds % 60;
	
	std::stringstream output;
	output << std::setfill('0') << std::setw(2)<< hours << " : " 
	       << std::setfill('0') << std::setw(2) <<  mins << " : "
		   << std::setfill('0') << std::setw(2) <<  secs;
		   
	return output.str();
}
