#include "pch.h"
#include "Log.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include "SystemUtils.h"

std::unique_ptr<INIReader> Log::s_pConfigReader;
Log Log::Logger;

Log::Log(std::string loggerName) {
    m_name = loggerName;

    if (!s_pConfigReader) {
        std::string configsDirPath = getResourcePath("configs");
        s_pConfigReader = std::make_unique<INIReader>(configsDirPath + "log_config.ini");

        if (s_pConfigReader->ParseError() != 0) {
            std::cout << "Error while initialising Logger config." << std::endl;
        }
    }

    m_logLevel = static_cast<ELevel>(s_pConfigReader->GetInteger("Log", "level", 2));
}

const Log& Log::getLogger() {
    return Logger;
}

void Log::trace(const std::string& msg) const {
    if (m_logLevel < ELevel::TRACE) {
        return;
    }
    this->print("TRACE", msg);
}

void Log::debug(const std::string& msg) const {
    if (m_logLevel < ELevel::DEBUG) {
        return;
    }

    this->print("DEBUG", msg);
}

void Log::info(const std::string& msg) const {
    if (m_logLevel < ELevel::INFO) {
        return;
    }

    this->print("INFO", msg);
}

void Log::warn(const std::string& msg) const {
    if (m_logLevel < ELevel::WARNING) {
        return;
    }

    this->print("WARNING", msg);
}

void Log::error(const std::string& msg) const {
    if (m_logLevel < ELevel::ERROR) {
        return;
    }

    this->print("ERROR", msg);
}

void Log::print(std::string levelStr, std::string msg) const {
    std::cout << getNow() << " [" << levelStr << "] (" << m_name << ") - " << msg << std::endl;
}

std::string Log::getNow() {
    auto t = std::time(nullptr);
    struct tm tm;
    localtime_s(&tm, &t);

    std::stringstream buffer;
    buffer << std::put_time(&tm, "%T");

    return buffer.str();
}
