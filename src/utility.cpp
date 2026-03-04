module;

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <limits>
#include <iomanip>
#include <cstdlib>

import consoleEnhancer;

export module Utility;

export enum Errors
{
	SUCCESS,
	ERR_FILE,
	ERR_ARG
};

export std::string fileName = "../data/sessions.txt";

export void pressEnterToContinue()
{
	std::cout << "Press Enter to continue..." << std::endl;
	std::cin.get();
}

export void displayHeading()
{
	setBoarder();
	std::cout << "╔═══════════════════════════════════════════════════════╗" << std::endl;
	textInBoarder("Productivity Time Tracker v1.3.1 ");
    std::cout << "╚═══════════════════════════════════════════════════════╝" << "\n" << std::endl;
	resetColour();
}

export void displayMenu() {
    setBoarder();
	std::cout << "\n╔═══════════════════════════════════════════════════════╗" << std::endl;
    std::cout<< "║"; 
	resetColour();
	std::cout << "                      MAIN MENU                        ";
	setBoarder();
	std::cout << "║" << std::endl;
    std::cout << "╠═══════════════════════════════════════════════════════╣" << std::endl;
	
    textInBoarder("1. Start tracking activity");
    textInBoarder("2. Stop current session");
	textInBoarder("3. Show current session");
	textInBoarder("4. Pause/Resume current session");
	textInBoarder("5. Add past session");
    textInBoarder("6. View daily report");
    textInBoarder("7. View weekly report");
    textInBoarder("8. View monthly report");
	textInBoarder("9. View all time activities report");
    textInBoarder("10. Exit");
	
    std::cout << "╚═══════════════════════════════════════════════════════╝" << std::endl;
	resetColour();
}

export void activityChoices()
{
	setBoarder();
	std::cout << "\n╔═══════════════════════════════════════════════════════╗" << std::endl;
	std::cout<< "║"; 
	resetColour();
	std::cout << "Pick activity                                          ";
	setBoarder();
	std::cout << "║" << std::endl;
    std::cout << "╠═══════════════════════════════════════════════════════╣" << std::endl;
	textInBoarder("A: Computer science");
	textInBoarder("B: Informatics");
	textInBoarder("C: MAT01");
	textInBoarder("D: MAT02");
	textInBoarder("E: Extra-curricular work");
	textInBoarder("F: New/custom activity");
			  
	std::cout << "╚═══════════════════════════════════════════════════════╝" << std::endl;
	resetColour();
}

//function converts human friendly time format into computer language time format
//Date: YEAR-MON-DAY..... Time: HR:MIN
export time_t convertToTimeT(const std::string&date, const std::string& time)
{
	struct tm tm = {}; //place holder
	
	std::stringstream ss(date + " " + time);
	ss >> std::get_time(&tm, "%Y-%m-%d %H:%M"); //place date & time in special format into tm
	
	return mktime(&tm); //coversion to time_t
}
