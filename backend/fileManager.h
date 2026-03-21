#pragma once

#include <string>
#include <vector>

#include "timeSession.h"

class FileManager
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
