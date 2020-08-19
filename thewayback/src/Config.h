#pragma once

#include "INIReader.h"
#include "Log.h"

class Config {

private:
    Config() {}
    ~Config();

    std::map<std::string, INIReader*> m_readers;

    static Config* s_pInstance;
    static Log* Logger;

public:
    Config(const Config&) = delete;
    Config& operator=(Config&) = delete;

    static Config* instance() {
        if (s_pInstance == nullptr) {
            s_pInstance = new Config();
        }

        return s_pInstance;
    }

    // ------------------------------------

    bool load(std::string filename, std::string id);
    INIReader* get(std::string key);

};