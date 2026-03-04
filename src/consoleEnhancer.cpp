module;

#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <ctime>
#include <limits>
#include <iomanip>
#include <cstdlib>

export module consoleEnhancer;

HANDLE hConsole;

export const int C_ERROR = 12;
export const int C_SUCCESS = 10;
export const int C_WARNING = 14;
export const int C_INFO = 11;
export const int C_NORMAL = 7;
export const int C_TEXT = 15; //bright white

export void initConsole()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	//UTF-8 for more characters
	SetConsoleOutputCP(CP_UTF8);
	
	//To enable virtual terminal processing for better rendering
	DWORD mode;
	GetConsoleMode(hConsole, &mode);
	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hConsole, mode);
}

export void setColour(int colour)
{
	//initialize
	if (!hConsole)
		initConsole();
	SetConsoleTextAttribute(hConsole, colour);
}

export void resetColour()
{
	setColour(C_TEXT);
}

export void setBoarder()
{
	setColour(9); //bright blue
}

export void textInBoarder(std::string text)
{
	setColour(9);
	std::cout << "║";
	setColour(15);
	std::cout << " " << std::left << std::setw(53) << text << " "; //auto pad to 53 chars
	setColour(9);
	std::cout << "║" << std::endl;
}

export void dataInBoarder(std::string text)
{
	setColour(9);
	std::cout << "║";
	setColour(10);
	std::cout << " " << std::left << std::setw(53) << text << " "; //auto pad to 53 chars
	setColour(9);
	std::cout << "║" << std::endl;
}

export void printError(std::string message)
{
	setColour(C_ERROR);
	std::cout << "✗ ERROR: " << message << std::endl;
	setColour(C_NORMAL);
}

export void printSuccess(std::string message)
{
	setColour(C_SUCCESS);
std::cout << "✓ " << message << std::endl;
	setColour(C_NORMAL);
}

export void printWarning(std::string message)
{
	setColour(C_WARNING);
	std::cout << "⚠  " << message << std::endl;
	setColour(C_NORMAL);
}

export void printInfo(std::string message)
{
	setColour(C_INFO);
	std::cout << "ℹ  " << message << std::endl;
	setColour(C_NORMAL);
}

export void clearInputBuffer()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

export void clearConsole()
{
	#ifdef _WIN32
		system("cls");
	#else
		system("clear"); 
	#endif	
}