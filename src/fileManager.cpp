module;

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>


import Utility;
import TimeSession;
import consoleEnhancer;

export module FileManager;

//using namespace std;
export class FileManager
{
	public:
		FileManager(std::string fileName);
		
		void saveSession(TimeSession* session);
		std::vector<TimeSession*> loadAllSessions(); //load all sessions in file to vector list of sessions
		bool createBackup();
		
	private:
		std::string _fileName;
		
		//helper functions
		bool validateLine(const std::string& line); //returns true if line has 3 commas
		TimeSession* parseLine(const std::string& line); //parse data from each line into TimeSession objects
		bool fileExists() const;
};

FileManager::FileManager(std::string fileName)
{
	_fileName = fileName;
}
		
void FileManager::saveSession(TimeSession* session)
{
	std::ofstream out(_fileName, std::ios::app);
	//out.open(_fileName, std::ios::app);
	if(!out.is_open())
	{
		printError("Failed to open output file");
	
	}
	out << session->outputData() << "\n"; //output specified session data
	
	out.close();
}

std::vector<TimeSession*> FileManager::loadAllSessions()
{
	std::vector<TimeSession*> sessions;
	std::ifstream inFile(_fileName);
	if (!inFile.is_open())
	{
		printInfo("No previous data found. Starting afresh!");
		return sessions;
	}
	
	std::string line;
	int lineNumber = 0;
	
	while (getline(inFile, line))
	{
		lineNumber++;
		
		//skip empty lines
		if (line.empty() || line.find_first_not_of(" \t\r\n"))
			continue;
		
		if (validateLine(line))
		{
			TimeSession* session = parseLine(line);
			if (session != nullptr)
				sessions.push_back(session); //save new session to back
			else
				std::cerr << "⚠ Warning: Invalid data on line " << lineNumber << " - skipping" << std::endl;
		}
	}
	inFile.close();
	
	setColour(11);
	std::cout << "ℹ " << "Loaded " << sessions.size() << " previous sessions." << "\n" << std::endl;
	resetColour();
	return sessions;
}

bool FileManager::createBackup()
{
	if (!fileExists()) {
        return true;  // No file to backup
    }
	
	std::string backupFileName = fileName + "_backup";
	
	std::ifstream og(fileName, std::ios::binary);
	std::ofstream backup(backupFileName, std::ios::binary);
	
	if (og.fail() || backup.fail())
	{
		std::cerr << "Error backing up: one or both files cannot be opened" << std::endl;
		return false;
	}
	
	backup << og.rdbuf(); //method for copying file contents
	
	og.close();
	backup.close();
	
	std::cout << "Backup successfully created: " << backupFileName << std::endl;
	return true;
}

bool FileManager::validateLine(const std::string& line)
{
	int numCommas = 0;
	for (char c: line)
	{
		if (c == ',') 
			numCommas++;
	}
	return numCommas == 4;
}

TimeSession* FileManager::parseLine(const std::string& line)
{
	std::stringstream ss(line); 
	std::string activityName, strStart, strEnd, strPausedSeconds, strDuration;
	
	try
	{
		//Parse format: activityName, startTime, endTime, pausedSeconds, duration
		getline(ss, activityName, ',');
		getline(ss, strStart, ',');
		getline(ss, strEnd, ',');
		getline(ss, strPausedSeconds, ',');
		getline(ss, strDuration, ',');
		
		//convert strings to numbers
		time_t startTime = stoll(strStart);
		time_t endTime = stoll(strEnd);
		int pausedSeconds = std::stoi(strPausedSeconds);
		
		//create TimeSession with loaded data
		TimeSession* session = new TimeSession(activityName, startTime, endTime, pausedSeconds);
		return session;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error parsing Line:" << line << std::endl;
		std::cerr << "Exception: " << e.what() << std::endl;
		return nullptr;
	}
}

bool FileManager::fileExists() const
{
	std::ifstream file(_fileName);
	return file.good();
}