#include "pch.h"
#include "Config.h"
#include "Log.h"
#include "SystemUtils.h"

std::unique_ptr<Config> Config::s_pInstance;
Log Config::Logger(typeid(Config).name());

bool Config::load(const std::string& filename, const std::string& id) {
    const std::string configsDirPath = getResourcePath("configs");
    const std::string filepath = configsDirPath + filename;

    auto pReader = std::make_unique<INIReader>(filepath);
    if (pReader->ParseError() != 0) {
        Logger.error("Cannot load config from a file " + filepath);
        return false;
    }

    m_readers.emplace(id, std::move(pReader));
    return true;
}

const INIReader& Config::get(const std::string& key) {
    if (m_readers.find(key) == m_readers.end()) {
        Logger.warn("Requested config not found: " + key);
    }

    return *m_readers[key];
}