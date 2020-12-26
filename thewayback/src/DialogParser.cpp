#include "pch.h"
#include "DialogParser.h"
#include "Log.h"
#include "SystemUtils.h"


using namespace tinyxml2;

Log DialogParser::Logger(typeid(DialogParser).name());

std::vector<std::shared_ptr<Dialog>> DialogParser::parse(const std::string& filename) {
    Logger.debug("Loading dialog from " + filename);

    const std::string resourcesPath = getResourcePath("dialogs");
    const std::string filepath = resourcesPath + filename;

    XMLDocument xmlDoc(true, COLLAPSE_WHITESPACE);
    std::vector<std::shared_ptr<Dialog>> result;

    XMLError loadResult = xmlDoc.LoadFile(filepath.c_str());
    if (loadResult != XML_SUCCESS) {
        Logger.error("Cannot load " + filename);
        return result;
    }

    XMLElement* pRoot = xmlDoc.FirstChildElement();
    if (pRoot == nullptr) {
        Logger.warn("No root element found in " + filename);
        return result;
    }

    const std::string npcId = pRoot->Attribute("npcId");

    for (XMLElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() != std::string("dialog")) {
            continue;
        }
        auto pDialog = std::make_shared<Dialog>();
        parseDialog(e, *pDialog);
        result.push_back(pDialog);
    }


    return result;
}

void DialogParser::parseDialog(tinyxml2::XMLElement* pDialogRoot, Dialog& dialog) {
    for (XMLElement* e = pDialogRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() != std::string("phrase")) {
            continue;
        }

        Dialog::Phrase phrase;
        phrase.character = e->Attribute("character");
        phrase.text = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(e->GetText());
        dialog.m_phrases.push_back(phrase);
    }
}
