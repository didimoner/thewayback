#pragma once

class Properties {

private:
    std::unordered_map<std::string, std::string> m_data;

public:
    void addProperty(const std::string& key, const std::string& value);

    int32_t intVal(const std::string& key) const;
    float_t floatVal(const std::string& key) const;
    bool boolVal(const std::string& key) const;
    std::string stringVal(const std::string& key) const;

};