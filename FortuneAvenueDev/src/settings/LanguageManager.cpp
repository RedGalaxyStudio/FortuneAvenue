#include "LanguageManager.h"
#include <iostream>
#include <fstream>
#include "../../libs/nlohmann/json.hpp"
#include <shlobj.h>
using json = nlohmann::json;


LanguageManager::LanguageManager() {

    char appDataPath[MAX_PATH];
    if (SHGetFolderPathA(nullptr, CSIDL_APPDATA, nullptr, 0, appDataPath) != S_OK) {
        std::cerr << "No se pudo obtener la ruta de AppData." << std::endl;
        return;
    }

    std::string rutaFinalC = std::string(appDataPath) + "\\Fortune Avenue\\";
    std::string documente = rutaFinalC + "settings.json";

    if (std::filesystem::exists(documente)) {

        std::ifstream inFile(documente);
        if (inFile.is_open()) {
            json settingData;

            inFile >> settingData;
            inFile.close();

            languages = settingData.value("Language", "en");
            if (!verifyLanguage(languages)) {
                languages="en";

            }
            std::cout << "Languag"<<languages << std::endl;
        }
    }
}

std::vector<std::string> LanguageManager::getMenuLanguage() {

    return languageOptions[languages];
}

void LanguageManager::setLanguage(const std::string& lang) {

    std::string langg=conversionLanguage(lang);



    if (verifyLanguage(langg)){ languages = langg;}else {
        languages="en";
    }

    char appDataPath[MAX_PATH];
    if (SHGetFolderPathA(nullptr, CSIDL_APPDATA, nullptr, 0, appDataPath) != S_OK) {
        std::cerr << "No se pudo obtener la ruta de AppData." << std::endl;
        return;
    }

    std::string rutaFinalC = std::string(appDataPath) + "\\Fortune Avenue\\";

    if (!std::filesystem::exists(rutaFinalC)) {
        std::error_code ec;
        std::filesystem::create_directories(rutaFinalC, ec);
    }
    std::string documente = rutaFinalC + "settings.json";
    json settingData;

    std::ifstream inFile(documente);
    if (inFile.is_open()) {
        inFile >> settingData;  // Cargar el JSON existente
        inFile.close();
    }
    settingData["Language"] = languages;


    std::ofstream outFile(documente);

    if (outFile.is_open()) {
        outFile << settingData.dump(4);
        outFile.close();
    }
}
std::string LanguageManager::conversionLanguage(const std::string& translatedName) {
    static std::vector<std::string> codes = { "en", "es", "fr", "de", "pt", "it", "nl" };

    const auto& currentList = languageOptions[languages];

    for (size_t i = 0; i < currentList.size(); ++i) {
        if (currentList[i] == translatedName) {
            return codes[i];
        }
    }

    return "en"; // o "unknown", o lanza excepción si prefieres
}

bool LanguageManager::verifyLanguage(std::string lang) {
    for (auto a: Veriflang) {

        if (a==lang) return true;

    }

    return false;
}

sf::String LanguageManager::getmainMenuTranslations(const std::string& button) {
    std::string utf8 = mainMenuTranslations[button][languages];
    return sf::String::fromUtf8(utf8.begin(), utf8.end());
}

sf::String LanguageManager::getsettingsTranslations(const std::string& setting) {
    std::string utf8 = settingsTranslations[setting][languages];
    return sf::String::fromUtf8(utf8.begin(), utf8.end());
}

