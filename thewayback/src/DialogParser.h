#pragma once
#include "Dialog.h"
#include "vendor/tinyxml2.h"

class Log;

class DialogParser {

private:
    static Log Logger;

public:
    static std::vector<std::shared_ptr<Dialog>> parse(const std::string& filename);

private:
    static void parseDialog(tinyxml2::XMLElement* pDialogRoot, Dialog& dialog);

};