#include "pch.h"
#include "Properties.h"

void Properties::addProperty(const std::string& key, const std::string& value) {
    m_data.emplace(key, value);
}

int32_t Properties::intVal(const std::string& key) const {
    if (m_data.find(key) == m_data.end()) {
        throw std::invalid_argument("No int32_t property for key " + key);
    }

    return std::stoi(m_data.at(key));
}

float_t Properties::floatVal(const std::string& key) const {
    if (m_data.find(key) == m_data.end()) {
        throw std::invalid_argument("No float_t property for key " + key);
    }

    return std::stof(m_data.at(key));
}

bool Properties::boolVal(const std::string& key) const {
    if (m_data.find(key) == m_data.end()) {
        throw std::invalid_argument("No bool property for key " + key);
    }

    const auto value = m_data.at(key);
    return value == "true" || value == "TRUE" || value == "1";
}

std::string Properties::stringVal(const std::string& key) const {
    if (m_data.find(key) == m_data.end()) {
        throw std::invalid_argument("No string property for key " + key);
    }

    return m_data.at(key);
}
