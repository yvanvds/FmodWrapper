#pragma once

#include <string>
#include <fstream>
#include "defines.h"
#include "enums.h"

namespace FW {
    // a base class with a virtual method which can be passed to the log
    // class for custom output
    class API  logHandler {
    public:
        virtual void AddMessage(const std::string& message) {}
        virtual ~logHandler() {}
    };

    /**
        A singleton class for logging. Normally this will write messages to a file when asked for. The behaviour can be
          overwritten though. Keep in mind that the logging system is
          only available between System().Init() and System().close().
    */
    class log {
    public:
        ~log();

        /** You can send your own log messages to the YSE log
            system. They will be printed with the keyword 'app message'.
            They will appear at Error loglevel.
        */
        API log& sendError(std::string message);
        API log& sendWarning(std::string message);
        API log& sendInfo(std::string message);

        /** set the current loglevel.
            By default this is set to EL_DEBUG in debug mode
            and EL_ERRORS in release mode. Other modes are
            EL_WARNINGS and EL_NONE.
        */
        API log& setLevel(ERROR_LEVEL level);

        /** Get the current loglevel.
        */
        API ERROR_LEVEL getLevel();

        /** You can set a custom log handler here.
            This overwrites the normal logfile output
        */
        API log& setHandler(logHandler* handler);

        /** set the current output file. By default
            this file is called 'YSElog.txt' and will be
            placed in the work directory. (Dependant on OS)
        */
        API log& setLogfile(std::string path);

        /** Get the current output file.
        */
        API std::string getLogfile();

    private:
        friend API log& Log();
        log();
        void logMessage(std::string message);

        ERROR_LEVEL level = EL_ERROR;
        std::string fileName = "FWLog.txt";
        logHandler* handler = nullptr;
        std::ofstream logFile;
        bool toConsole;
    };

    /**
        A functor to retrieve the Logging object.
    */
    API log& Log();
}