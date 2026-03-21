#include "fileManager.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "timeSession.h"

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
        //Fix needed
        std::cerr << "Failed to open output file" << std::endl;
	
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
        std::cerr << "No previous data found. Starting afresh!" << std::endl;
		return sessions;
	}
	
	std::string line;
	int lineNumber = 0;
	
	while (getline(inFile, line))
	{
		lineNumber++;
		
		//skip empty lines
		if (line.empty())
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
	
	std::cout << "ℹ " << "Loaded " << sessions.size() << " previous sessions." << "\n" << std::endl;
	return sessions;
}

bool FileManager::createBackup()
{
	if (!fileExists()) {
        return true;  // No file to backup
    }
	
    std::string backupFileName = _fileName + "_backup";
	
    std::ifstream og(_fileName, std::ios::binary);
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
	return numCommas == 3;
}

TimeSession* FileManager::parseLine(const std::string& line)
{
	std::stringstream ss(line); 
	std::string activityName, strStart, strEnd, strDuration;
	
	try
	{
		//Parse format: activityName, startTime, endTime, duration
		getline(ss, activityName, ',');
		getline(ss, strStart, ',');
		getline(ss, strEnd, ',');
		getline(ss, strDuration, ',');
		
		//convert strings to numbers
		time_t startTime = stoll(strStart);
		time_t endTime = stoll(strEnd);
		//int duration = static_cast<int>(strDuration);
		
		//create TimeSession with loaded data
		TimeSession* session = new TimeSession(activityName, startTime, endTime);
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
