#pragma once
#include "INIReader.h"

class Log {

public:
    enum class Level {
        ERROR = 0, WARNING, INFO, DEBUG, TRACE
    };

    Log() : Log("root") {};
    Log(std::string loggerName);

    void trace(std::string msg) const;
    void debug(std::string msg) const;
    void info(std::string msg) const;
    void warn(std::string msg) const;
    void error(std::string msg) const;

private:
    std::string m_name;
    Level m_logLevel;

    void print(std::string level, std::string msg) const;

    static INIReader* s_pConfigReader;

    static std::string getNow();

};