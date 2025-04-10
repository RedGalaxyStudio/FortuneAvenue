#include <SFML/Graphics.hpp>
#include <ultralight/Ultralight.h>
#include <ultralight/platform/Platform.h>
#include <curl/curl.h>
#include <iostream>
#include <string>

class MyLogger : public ultralight::Logger {
public:
    void LogMessage(ultralight::LogLevel level, const ultralight::String& message) override {
        switch (level) {
        case ultralight::LogLevel::Info: // Cambiado de Log a Info
            std::cout << "Info: " << message.utf8().data() << std::endl;
            break;
        case ultralight::LogLevel::Warning:
            std::cerr << "Warning: " << message.utf8().data() << std::endl;
            break;
        case ultralight::LogLevel::Error:
            std::cerr << "Error: " << message.utf8().data() << std::endl;
            break;
        default:
            break;
        }
    }
};

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

std::string getAuthorizationURL() {
    const std::string clientId = "YOUR_CLIENT_ID";
    const std::string redirectUri = "http://localhost:8080/callback"; // Cambia esto a tu URI real
    const std::string scope = "https://www.googleapis.com/auth/userinfo.email https://www.googleapis.com/auth/userinfo.profile";
    const std::string authUrl = "https://accounts.google.com/o/oauth2/auth?response_type=code&client_id=" + clientId +
        "&redirect_uri=" + redirectUri +
        "&scope=" + scope +
        "&access_type=offline";
    return authUrl;
}

void getAccessToken(const std::string& code) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://oauth2.googleapis.com/token");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS,
            ("grant_type=authorization_code&code=" + code +
                "&redirect_uri=http://localhost:8080/callback&client_id=YOUR_CLIENT_ID&client_secret=YOUR_CLIENT_SECRET").c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            std::cout << "Response: " << readBuffer << std::endl;
            // Aquí puedes parsear el JSON para extraer el token si es necesario.
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mi Juego con Gmail");

    auto& platform = ultralight::Platform::instance();
    ultralight::View* view = platform.instance(800, 600, true, false);
    MyLogger logger;
    ultralight::Logger::set(&logger);

    // Cargar la URL de autorización
    std::string authUrl = getAuthorizationURL();
    view->LoadURL(authUrl.c_str());

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        platform->Update();
        platform->Render();

        window.clear();
        window.display();
    }

    platform->Shutdown();
    return 0;
}
