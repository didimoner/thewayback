#pragma once
#include "INIReader.h"

class Log {

public:
    enum class Level {
        ERROR = 0, WARNING, INFO, DEBUG, TRACE
    };

private:
    std::string m_name;
    Level m_logLevel;

    static INIReader* s_pConfigReader;
    static std::string getNow();

public:
    Log() : Log("root") {};
    Log(std::string loggerName);

    void trace(const std::string& msg) const;
    void debug(const std::string& msg) const;
    void info(const std::string& msg) const;
    void warn(const std::string& msg) const;
    void error(const std::string& msg) const;

private:
    void print(std::string level, std::string msg) const;

};