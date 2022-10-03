#include "log.h"
#include "enums.h"
#include <iostream>

namespace FW {
	log& Log() {
		static log s;
		return s;
	}

#if defined _DEBUG
	log::log() : handler(nullptr), level(EL_DEBUG), toConsole(true), fileName("../FWLog.txt") {
#else
	log::log() : handler(nullptr), level(EL_ERROR), toConsole(false) {
#endif
		logFile.open(fileName, std::ios::out | std::ios::trunc);
		logFile << "=== start of FW log ===" << std::endl;
	}

	log::~log() {
		logFile << "=== end of FW log ===" << std::endl;
		logFile.close();
	}

	ERROR_LEVEL log::getLevel() {
		return level;
	}

	log& log::setLevel(ERROR_LEVEL level) {
		this->level = level;
		return *this;
	}

	log& log::setHandler(logHandler* handler) {
		this->handler = handler;
		return *this;
	}

	log& log::setLogfile(std::string path) {
		logFile.close();
		fileName = path;
		logFile.open(fileName, std::ios::out | std::ios::app);
		logFile << "=== start of FW log ===" << std::endl;
		return *this;
	}

	std::string log::getLogfile() {
		return fileName;
	}

	void log::logMessage(std::string message) {
		if (handler != nullptr) {
			handler->AddMessage(message);
		}
		else {
			logFile << message << std::endl;
		}
		if (toConsole) {
			std::cout << message << std::endl;
		}
	}

	log& log::sendError(std::string message) {
		if (level == EL_NONE) return *this;

		std::string line = "(FW Error) " + message;
		logMessage(line);
		return *this;
	}

	log& log::sendWarning(std::string message) {
		if (level == EL_NONE || level == EL_ERROR) return *this;

		std::string line = "(FW Warning) " + message;
		logMessage(line);
		return *this;
	}

	log& log::sendInfo(std::string message) {
		if (level != EL_DEBUG) return *this;

		std::string line = "(FW Info) " + message;
		logMessage(line);
		return *this;
	}



}