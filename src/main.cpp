#include <iostream>
#include <string>
#include <limits>
#include <ctime>

import consoleEnhancer;
import Utility;
import Activity;
import TimeSession;
import FileManager;
import ReportGenerator;
import TimeTracker;

int main()
{
	initConsole();
	
	displayHeading();
	TimeTracker tracker;
	int choice;
	bool running = true;
	
	while (running)
	{
		displayMenu();
		std::cout << "Enter your choice" << "\n";
		std::cin >> choice;
		
		//clear input buffer
		clearInputBuffer();
		switch (choice)
		{
			case 1:
			{
				activityChoices();
				char activity;
				std::cin >> activity;
				clearInputBuffer();
				
				switch (activity)
				{
					case 'A':
					case 'a':
						tracker.startSession("Computer Science");
						break;
						
					case 'B':
					case 'b':
						tracker.startSession("Informatics");
						break;
						
					case 'C':
					case 'c':
						tracker.startSession("MAT01");
						break;
						
					case 'D':
					case 'd':
						tracker.startSession("MAT02");
						break;
						
					case 'E':
					case 'e':
						tracker.startSession("Extra-curricular work");
						break;
						
					case 'F':
					case 'f':
					{
						std::string name;
						std::cout << "Enter the name of activity you wish to track" << std::endl;
						std::cin >> name;
						
						tracker.startSession(name);
					}
						break;
						
					default:
						printError("Invalid choice. Please try again.");
						pressEnterToContinue();
						break;
					
				}
				pressEnterToContinue();
				clearConsole();
			
				break;
			}
				
			case 2:
			{
				tracker.stopSession();
				pressEnterToContinue();
				clearConsole();
			}
				break;
				
			case 3:
				tracker.showCurrentSession();
				pressEnterToContinue();
				clearConsole();
			break;
			
			case 4:
			{
				tracker.pauseOrResume();
			}
			pressEnterToContinue();
			clearConsole();
			break;
			
			case 5:
			{
				activityChoices();
				std::string name;
				
				char activity;
				std::cin >> activity;
				clearInputBuffer();
				
				switch (activity)
				{
					case 'A':
					case 'a':
						name = "Computer science";
						break;
						
					case 'B':
					case 'b':
						name = "Informatics";
						break;
						
					case 'C':
					case 'c':
						name = "MAT01";
						break;
						
					case 'D':
					case 'd':
						name = "MAT02";
						break;
						
					case 'E':
					case 'e':
						name = "Extra-curricular";
						break;
						
					case 'F':
					case 'f':
					{
						std::cout << "Enter the name of activity you wish to track" << std::endl;
						std::cin >> name;
						
						tracker.startSession(name);
					}
						break;
						
					default:
						printError("Invalid choice. Please try again.");
						pressEnterToContinue();
						break;
					
				}
				
				std::string date;
				std::cout << "Enter the date (YEAR-MON-DAY)" << std::endl;
				std::cin >> date;
				
				std::string startTime;
				std::cout << "Enter the session start time (HOUR:MIN)" << std::endl;
				std::cin >> startTime;
				
				std::string endTime;
				std::cout << "Enter the session end time (HOUR:MIN)" << std::endl;
				std::cin >> endTime;
				
				clearInputBuffer();
				tracker.addPastSession(name, date, startTime, endTime);
				
				pressEnterToContinue();
				clearConsole();
			}
			break;
				
			case 6:
			{
				std::string report = tracker.getDailyReport();
				std::cout << report << "\n" << std::endl;
				pressEnterToContinue();
				clearConsole();
			}
				break;
				
			case 7:
			{
				std::string report = tracker.getWeeklyReport();
				std::cout << report << "\n" << std::endl;
				pressEnterToContinue();
				clearConsole();
			}
				break;
				
			case 8:
			{
				std::string report = tracker.getMonthlyReport();
				std::cout << report << "\n" << std::endl;
				pressEnterToContinue();
				clearConsole();
			}
				break;
				
				
			case 9:
				{
					tracker.showAllActivities();
				}
				pressEnterToContinue();
				clearConsole();
				break;
			
			case 10:
				running = false;
				break;
				
			default:
				printError("Invalid choice. Please try again.");
				pressEnterToContinue();
				break;
		
		}
		
	}
	return SUCCESS;
}