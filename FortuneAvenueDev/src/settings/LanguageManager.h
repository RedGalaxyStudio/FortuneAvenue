#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include <map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
class LanguageManager {

public:

    static LanguageManager& getInstance() {
        static LanguageManager instance;
        return instance;
    };

    void setLanguage(const std::string& lang);
    sf::String getmainMenuTranslations(const std::string& button);
    sf::String getsettingsTranslations(const std::string& setting);
    std::vector<std::string> getMenuLanguage();




    private:
    LanguageManager(); //Constructor privado
    LanguageManager(const LanguageManager&) = delete;
    void operator=(const LanguageManager&) = delete;
    std::vector<std::string> Veriflang={"en","es","fr","de","pt","it","nl"};
    std::string languages;

    std::string conversionLanguage(const std::string& translatedName);
    bool verifyLanguage(std::string);

    std::map<std::string, std::map<std::string, std::string>> mainMenuTranslations = {
    { "play", {
        { "es", "JUGAR" },
        { "en", "PLAY" },
        { "fr", "JOUER" },
        { "de", "SPIELEN" },
        { "pt", "JOGAR" },
        { "it", "GIOCA" },
        { "nl", "SPELEN" }
    }},
    { "options", {
        { "es", "OPCIONES" },
        { "en", "OPTIONS" },
        { "fr", "OPTIONS" },
        { "de", "OPTIONEN" },
        { "pt", "OPÇÕES" },
        { "it", "OPZIONI" },
        { "nl", "OPTIES" }
    }},
    { "exit", {
        { "es", "SALIR" },
        { "en", "EXIT" },
        { "fr", "QUITTER" },
        { "de", "BEENDEN" },
        { "pt", "SAIR" },
        { "it", "ESCI" },
        { "nl", "AFSLUITEN" }
    }},
    { "about", {
        { "es", "ACERCA DE" },
        { "en", "ABOUT" },
        { "fr", "À PROPOS" },
        { "de", "ÜBER" },
        { "pt", "SOBRE" },
        { "it", "INFORMAZIONI" },
        { "nl", "OVER" }
    }}
};



    std::map<std::string, std::vector<std::string>> languageOptions = {
        { "es", { "Inglés", "Español",  "Francés","Alemán", "Portugués", "Italiano", "Neerlandés" } },
        { "en", { "English", "Spanish", "French", "German", "Portuguese", "Italian", "Dutch" } },
        { "fr", { "Anglais", "Espagnol",  "Français","Allemand", "Portugais", "Italien", "Néerlandais" } },
        { "de", { "Englisch", "Spanisch",  "Französisch","Deutsch", "Portugiesisch", "Italienisch", "Niederländisch" } },
        { "pt", { "Inglês", "Espanhol",  "Francês","Alemão", "Português", "Italiano", "Holandês" } },
        { "it", { "Inglese", "Spagnolo",  "Francese","Tedesco", "Portoghese", "Italiano", "Olandese" } },
        { "nl", { "Engels", "Spaans", "Frans", "Duits", "Portugees", "Italiaans", "Nederlands" } }
    };
    std::map<std::string, std::map<std::string, std::string>> settingsTranslations = {
        { "fullscreen", {
            { "es", "Pantalla Completa" },
            { "en", "Fullscreen" },
            { "fr", "Plein écran" },
            { "de", "Vollbildmodus" },
            { "pt", "Tela cheia" },
            { "it", "Schermo intero" },
            { "nl", "Volledig scherm" }
        }},
        { "music", {
            { "es", "Música" },
            { "en", "Music" },
            { "fr", "Musique" },
            { "de", "Musik" },
            { "pt", "Música" },
            { "it", "Musica" },
            { "nl", "Muziek" }
        }},
        { "sound_effects", {
            { "es", "Efectos" },
            { "en", "Effects" },
            { "fr", "Effets" },
            { "de", "Effekte" },
            { "pt", "Efeitos" },
            { "it", "Effetti" },
            { "nl", "Effecten" }
        }},
        { "instructions", {
            { "es", "Cómo jugar" },
            { "en", "How to play" },
            { "fr", "Comment jouer" },
            { "de", "Wie man spielt" },
            { "pt", "Como jogar" },
            { "it", "Come si gioca" },
            { "nl", "Hoe te spelen" }
        }}
    };


};



//LanguageManager languageManager();
#endif //LANGUAGEMANAGER_H
