#pragma once

#include "INIReader.h"

class Log;

class Config {

private:
    Config() {}
    
    std::map<std::string, INIReader*> m_readers;

    static std::unique_ptr<Config> s_pInstance;
    static std::unique_ptr<Log> Logger;

public:
    ~Config();
    Config(const Config&) = delete;
    Config& operator=(Config&) = delete;

    static Config& instance() {
        if (!s_pInstance) {
            s_pInstance.reset(new Config());
        }

        return *s_pInstance;
    }

    // ------------------------------------

    bool load(std::string filename, std::string id);
    INIReader* get(std::string key);

};