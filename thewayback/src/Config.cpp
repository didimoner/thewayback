#include "pch.h"
#include "Config.h"
#include "SystemUtils.h"

Config* Config::s_pInstance = nullptr;
Log* Config::Logger = new Log(typeid(Config).name());

bool Config::load(std::string filename, std::string id) { 
    std::string configsDirPath = SystemUtils::getResourcePath("configs");
    std::string filepath = configsDirPath + filename;

    INIReader* pReader = new INIReader(filepath);
    if (pReader->ParseError() != 0) {
        Logger->error("Cannot load config from a file " + filepath);
        return false;
    }

    m_readers[id] = pReader;
    return true;
}

INIReader* Config::get(std::string key) {
    INIReader* pReader = m_readers[key];
    if (pReader == nullptr) {
        Logger->warn("Requested config not found: " + key);
    }

    return pReader;
}

Config::~Config() {
    for (std::pair<std::string, INIReader*> item : m_readers) {
        delete item.second;
    }

    m_readers.clear();
}