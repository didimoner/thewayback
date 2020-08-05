#include "pch.h"
#include "Log.h"
#include <ctime>
#include <sstream>
#include <iomanip>

Log::Log() {
    m_name = "root";
}

Log::Log(std::string loggerName) {
    m_name = loggerName;
}

void Log::trace(std::string msg) const {
    if (m_logLevel < Level::TRACE) {
        return;
    }

    this->print("TRACE", msg);
}

void Log::debug(std::string msg) const {
    if (m_logLevel < Level::DEBUG) {
        return;
    }

    this->print("DEBUG", msg);
}

void Log::info(std::string msg) const {
    if (m_logLevel < Level::INFO) {
        return;
    }

    this->print("INFO", msg);
}

void Log::warn(std::string msg) const {
    if (m_logLevel < Level::WARNING) {
        return;
    }

    this->print("WARNING", msg);
}

void Log::error(std::string msg) const {
    if (m_logLevel < Level::ERROR) {
        return;
    }
    
    this->print("ERROR", msg);
}

void Log::setLogLevel(Level level) {
    m_logLevel = level;
}

void Log::print(std::string levelStr, std::string msg) const {
    std::cout << Log::getNow() << " [" << levelStr << "] (" << m_name << ") - " << msg << std::endl;
}

std::string Log::getNow() {
    auto t = std::time(nullptr);
    struct tm tm;
    localtime_s(&tm, &t);

    std::stringstream buffer;
    buffer << std::put_time(&tm, "%T");

    return buffer.str();
}
