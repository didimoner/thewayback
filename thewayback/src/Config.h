#pragma once

#include "vendor/INIReader.h"

class Log;

class Config {

private:
    Config() = default;

    std::unordered_map<std::string, std::unique_ptr<INIReader>> m_readers;
    static std::unique_ptr<Config> s_pInstance;
    static Log Logger;

public:
    Config(const Config&) = delete;
    Config& operator=(Config&) = delete;

    static Config& instance() {
        if (!s_pInstance) {
            s_pInstance.reset(new Config());
        }

        return *s_pInstance;
    }

    // ------------------------------------

    bool load(const std::string& filename, const std::string& id);
    const INIReader& get(const std::string& key);

};
