#pragma once
#include "pch.h"

class Dialog {

public:
    struct Phrase {
        std::wstring text;
        std::string character;
    };

    friend class DialogParser;

private:
    std::vector<Phrase> m_phrases;

public:
    std::vector<Phrase>& getPhrases() {
        return m_phrases;
    }

};