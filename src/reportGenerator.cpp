module;

#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <string>
#include <iomanip>

import Utility;
import consoleEnhancer;
import TimeSession;
import FileManager;

export module ReportGenerator;

namespace ReportColors {
    const std::string BORDER = "\033[94m";    // Bright Blue
    const std::string TITLE = "\033[93m";    // Bright Yellow
    const std::string TEXT = "\033[97m";           // Bright White
    const std::string ACCENT = "\033[92m";    // Bright Green
    const std::string RESET = "\033[0m";
}

export class ReportGenerator
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
	
	//title padding
	const int width = 55;
	int paddingLeft = (width - title.length()) / 2;
	int paddingRight = width -title.length() - paddingLeft;
	
	//header
    report << "\n" << ReportColors::BORDER;
	report << "╔═══════════════════════════════════════════════════════╗" << std::endl;
    report << "║" << ReportColors::TITLE;
	report << std::string(paddingLeft, ' ') << title << std::string(paddingRight, ' ')
	       << ReportColors::BORDER << "║\n";
    report << "╠═══════════════════════════════════════════════════════╣" << std::endl;
	
	//check if there's any data
	if (activityTotals.empty())
	{
		report << "║" << ReportColors::TEXT;
		report << "No activity recorded for this period." << ReportColors::BORDER;
		report << std::setw(18) << " " << "║\n";
		report << "╚═══════════════════════════════════════════════════════╝";
		report << ReportColors::RESET << "\n";
		return report.str();
	}
	
	//get total time
	int totalSeconds = 0;
	for (const auto& pair: activityTotals)
	{
		totalSeconds += pair.second;
	}
	
	std::string totalLabel = " Total                ";
	std::string data = formatDuration(totalSeconds);
	
	int visibleCharLength = totalLabel.length() + data.length();
	int totalPadding = width - visibleCharLength;
	
	report << "║" << ReportColors::TEXT << totalLabel
	       << ReportColors::ACCENT << data
		   << std::string(totalPadding , ' ');
	report << ReportColors::BORDER << "║\n";
	report << "║" << std::string(width, ' ') << "║\n";
	
	//activity breakdown
	std::string breakdownHeader = " Activity breakdown";
	int headerPadding = width - breakdownHeader.length();
	
	report << "║" << ReportColors::TITLE << breakdownHeader
		   << std::string(headerPadding, ' ')
		   << ReportColors::BORDER<< "║\n";
	report << "╠═══════════════════════════════════════════════════════╣\n";
		   
	for (const auto& pair: activityTotals)
	{
		std::string activity = pair.first;
		int seconds = pair.second;
		double percentage = (static_cast<double>(seconds) / totalSeconds) * 100.0;
		
		// format time and percentage strings without colouring
		std::string strTime = formatDuration(seconds);
		
		std::stringstream percentageStream;
		percentageStream << "(" << std::setw(5) << std::right << std::fixed
		                 << std::setprecision(1) << percentage << "%)";
		std::string strPercent = percentageStream.str();
		
		/*Build activityLine
		std::stringstream activityLine;
	    activityLine << " " << std::left << std::setw(20) << activity << " " //left and setw for alignment
			   << ReportColors::ACCENT << formatDuration(seconds)
			   << " (" << std::fixed << std::setprecision(2) << percentage << "%)" << ReportColors::TEXT; //precision for decimal
		std::string actLine = activityLine.str();*/
		
		// calculate visible char length
		int activityFieldWidth = 20; //hardcoded: name of activity should not be more than 20 char long
		std::string paddedActivity = activity;
		if (activity.length() <= activityFieldWidth)
		{
            paddedActivity += std::string(activityFieldWidth - activity.length(), ' ');
		}
        else
		{
            paddedActivity = activity.substr(0, activityFieldWidth);  // Truncate if too long
		}
		
		int visibleContentLength = 1 + activityFieldWidth + 1 + strTime.length() + 1 + strPercent.length();
		int activityPadding = width - visibleContentLength;
		
		//update repor string with colours
		report << "║" << ReportColors::TEXT << " " << paddedActivity << " "
		       << ReportColors::ACCENT << strTime << " " << strPercent
		       << std::string(activityPadding, ' ') << ReportColors::BORDER << "║\n"; 
	}
	report << "╚═══════════════════════════════════════════════════════╝"
		   << ReportColors::RESET << "\n";
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
