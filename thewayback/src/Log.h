#pragma once
#include "vendor/INIReader.h"

class Log {

private:
    enum class ELevel {
        ERROR = 0,
        WARNING,
        INFO,
        DEBUG,
        TRACE
    };

private:
    std::string m_name;
    ELevel m_logLevel;

    static Log Logger;
    static std::unique_ptr<INIReader> s_pConfigReader;

public:
    Log() : Log("root") {
    }

    explicit Log(std::string loggerName);

    static const Log& getLogger();

    void trace(const std::string& msg) const;
    void debug(const std::string& msg) const;
    void info(const std::string& msg) const;
    void warn(const std::string& msg) const;
    void error(const std::string& msg) const;

private:
    void print(const std::string& level, const std::string& msg) const;
    static std::string getNow();

};
