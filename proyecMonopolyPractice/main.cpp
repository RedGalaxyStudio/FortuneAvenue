#include <SFML/Graphics.hpp>
#include "Cinematic.hpp"
#include "ObjetosGlobal.hpp"
#include "ResourceGlobal.hpp"
#include "Game.hpp"

int main() {
    // Crear la ventana en pantalla completa
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Juego en Pantalla Completa", sf::Style::Fullscreen);

    // Configuraci n del frame rate (opcional)
    window.setFramerateLimit(60);

    sf::Image icono;
    if (!icono.loadFromFile("resource/texture/Icon/FortuneAvenue.png")) return EXIT_FAILURE;

    window.setMouseCursorVisible(false);
    // Establecer el  cono de la ventana
    window.setIcon(icono.getSize().x, icono.getSize().y, icono.getPixelsPtr());

    // Inicializar COM
    HRESULT hr = CoInitialize(nullptr);
    if (FAILED(hr)) {
        std::cerr << "Error al inicializar COM." << std::endl;
        return -1;
    }

    /*
    // Crear una instancia de la clase Cinematic y pasarle la ventana por referencia
    Cinematic cinematic(window);

    // Cargar los recursos necesarios para la cinem tica
    cinematic.Resource();

    //Iniciar la animaci n
    cinematic.Update();*/
    loadTextures();
    Menup.setWindow(window);
    // Cargar los recursos necesarios para la cinem tica
    Menup.Resource();

    // Iniciar la animaci n
    Menup.MenuPrincipal();

    CoUninitialize();

    return EXIT_SUCCESS;
}


/*#include <SFML/Graphics.hpp>
#include <Ultralight/Ultralight.h>
#include <Ultralight/platform/FileSystem.h>
#include <Ultralight/platform/FontLoader.h>
#include <Ultralight/platform/Logger.h>
#include <Ultralight/View.h>
#include <Ultralight/Renderer.h>
#include <Ultralight/platform/Platform.h>
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class MyFileSystem : public ultralight::FileSystem {
public:
    virtual bool FileExists(const ultralight::String& path) override {
        std::ifstream file(path.utf8().data());
        return file.good(); // Comprueba si el archivo se puede abrir
    }

    virtual ultralight::String GetFileMimeType(const ultralight::String& path) override {
        // Convertir el string UTF-8 a std::string para hacer comparaciones
        std::string file_path = path.utf8().data();

        if (file_path.size() >= 5 && file_path.compare(file_path.size() - 5, 5, ".html") == 0) {
            return ultralight::String("text/html");
        }
        else if (file_path.size() >= 4 && file_path.compare(file_path.size() - 4, 4, ".css") == 0) {
            return ultralight::String("text/css");
        }
        else if (file_path.size() >= 3 && file_path.compare(file_path.size() - 3, 3, ".js") == 0) {
            return ultralight::String("application/javascript");
        }
        return ultralight::String("application/unknown"); // Si no se reconoce la extensión
    }

    virtual ultralight::String GetFileCharset(const ultralight::String& path) override {
        // Asumimos que todos los archivos son UTF-8
        return ultralight::String("utf-8");
    }

    virtual ultralight::RefPtr<ultralight::Buffer> OpenFile(const ultralight::String& path) override {
        std::ifstream file(path.utf8().data(), std::ios::binary);
        if (!file) return nullptr;

        std::ostringstream oss;
        oss << file.rdbuf(); // Leer el archivo en un string
        std::string content = oss.str();
        // Usamos CreateFromCopy para crear el Buffer, haciendo una copia de los datos
        return ultralight::Buffer::CreateFromCopy((const void*)content.data(), content.size());
    }
};

class MyFontLoader : public ultralight::FontLoader {
public:
    // Proporciona un nombre de familia de fuentes de respaldo
    virtual ultralight::String fallback_font() const override {
        return "Arial"; // Cambia esto al nombre de la fuente de respaldo que prefieras
    }

    // Proporciona una fuente de respaldo para caracteres específicos
    virtual ultralight::String fallback_font_for_characters(const ultralight::String& characters, int weight, bool italic) const override {
        // Aquí podrías devolver una fuente específica basada en los caracteres
        return fallback_font();
    }

    // Carga los datos de una fuente a partir de su familia
    virtual ultralight::RefPtr<ultralight::FontFile> Load(const ultralight::String& family, int weight, bool italic) override {
        // Implementar lógica para cargar fuentes, por ahora solo devuelvo nullptr
        return nullptr; // Esto indica que no se pudo cargar la fuente
    }
};


class MyLogger : public ultralight::Logger {
public:
    virtual void LogMessage(ultralight::LogLevel level, const ultralight::String& message) override {
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
    const std::string redirectUri = "http://localhost:8080/callback";
    const std::string scope = "https://www.googleapis.com/auth/userinfo.email https://www.googleapis.com/auth/userinfo.profile";
    const std::string authUrl = "https://accounts.google.com/o/oauth2/auth?response_type=code&client_id=" + clientId +
        "&redirect_uri=" + redirectUri +
        "&scope=" + scope +
        "&access_type=offline";
    return authUrl;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Mi Juego con Gmail");
    MyFileSystem fileSystem;
    MyFontLoader fontLoader;
    MyLogger logger;

    ultralight::Config config2;
    config2.num_renderer_threads = 1;  // Usa un solo hilo para simplificar el depurado

    // Configura Ultralight
    auto& platform = ultralight::Platform::instance();
    platform.set_file_system(&fileSystem);
    platform.set_font_loader(&fontLoader);
    platform.set_logger(&logger);   // Implementa según sea necesario

    if (!fileSystem.FileExists("C:/Users/Daniel/Desktop/proyecMonopolyPractice/ultralight-sdk-1.3.0-win-x64/resources/icudt67l.dat")) {
        std::cerr << "Error: el archivo icudt67l.dat no se encuentra en la ruta especificada." << std::endl;
        return -1;
    }


    ultralight::Config config;
    config.resource_path_prefix = "C:/Users/Daniel/Desktop/proyecMonopolyPractice/ultralight-sdk-1.3.0-win-x64/resources/";

    platform.set_config(config);
    if (!fileSystem.FileExists("C:/Users/Daniel/Desktop/proyecMonopolyPractice/ultralight-sdk-1.3.0-win-x64/resources/icudt67l.dat")) {
        std::cerr << "Error: el archivo icudt67l.dat no se encuentra en la ruta especificada." << std::endl;
        return -1;
    }

    
    // Crea el Renderer
    auto renderer = ultralight::Renderer::Create();
    if (!renderer) {
        std::cerr << "Error: no se pudo crear el Renderer de Ultralight." << std::endl;
        return -1;
    }
    else {
        std::cout << "Renderer creado correctamente." << std::endl;
    }

 // Crear una sesión
    auto session = renderer->CreateSession(true, "my_session_name");
    if (!session) {
        std::cerr << "Error: no se pudo crear la sesión." << std::endl;
        return -1;
    }
    else {
        std::cout << "Sesión creada correctamente, ID: " << session->id() << std::endl;
    }

    ultralight::ViewConfig viewConfig;
    viewConfig.is_accelerated = false;  // Desactiva la aceleración para evitar posibles conflictos con GPU

    std::cout << "Antes de CreateView" << std::endl;
    auto view = renderer->CreateView(1280, 720, viewConfig, session);
    std::cout << "Después de CreateView" << std::endl;

    if (!view) {
        std::cerr << "Error: no se pudo crear el View de Ultralight." << std::endl;
        return -1; // Abortar si la vista no se creó correctamente
    } else {
        std::cerr << "se pudo crear el View de Ultralight." << std::endl;
        // Abortar si la vista no se creó correctamente
    }
    if (!session) {
        std::cerr << "Error: no se pudo crear la sesión." << std::endl;
        return -1;
    }
    else {
        std::cout << "Sesión creada correctamente, ID: " << session->id() << std::endl;
    }

    if (!renderer) {
        std::cerr << "Error: no se pudo crear el Renderer de Ultralight." << std::endl;
        return -1;
    }
    else {
        std::cout << "Renderer creado correctamente." << std::endl;
    }



    // Cargar la URL de autorización
    std::string authUrl = getAuthorizationURL();

    std::cout << "Cargando URL de autorización: " << authUrl << std::endl;
    view->LoadURL(authUrl.c_str());
    std::cout << "URL cargada correctamente." << std::endl;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Manejar eventos de teclado y ratón
            // Ejemplo para ratón:
            if (event.type == sf::Event::MouseButtonPressed) {
                ultralight::MouseEvent mouse_event;
                mouse_event.button = (event.mouseButton.button == sf::Mouse::Left) ?
                    ultralight::MouseEvent::Button::kButton_Left :
                    ultralight::MouseEvent::Button::kButton_None;
                mouse_event.x = event.mouseButton.x;
                mouse_event.y = event.mouseButton.y;
                view->FireMouseEvent(mouse_event);
            }

        }

        // Actualiza el Renderer
        renderer->Update();

        // Renderiza la vista de Ultralight
        renderer->Render();

        window.clear();
        // Aquí puedes dibujar otros elementos de SFML si lo deseas
        window.display();
    }

   // platform.Shutdown();
    return 0;
}







class MyFileSystem : public ultralight::FileSystem {
public:
    virtual bool FileExists(const ultralight::String& path) override {
        std::ifstream file(path.utf8().data());
        return file.good(); // Comprueba si el archivo se puede abrir
    }

    virtual ultralight::String GetFileMimeType(const ultralight::String& path) override {
        // Convertir el string UTF-8 a std::string para hacer comparaciones
        std::string file_path = path.utf8().data();

        if (file_path.size() >= 5 && file_path.compare(file_path.size() - 5, 5, ".html") == 0) {
            return ultralight::String("text/html");
        }
        else if (file_path.size() >= 4 && file_path.compare(file_path.size() - 4, 4, ".css") == 0) {
            return ultralight::String("text/css");
        }
        else if (file_path.size() >= 3 && file_path.compare(file_path.size() - 3, 3, ".js") == 0) {
            return ultralight::String("application/javascript");
        }
        return ultralight::String("application/unknown"); // Si no se reconoce la extensión
    }

    virtual ultralight::String GetFileCharset(const ultralight::String& path) override {
        // Asumimos que todos los archivos son UTF-8
        return ultralight::String("utf-8");
    }

    virtual ultralight::RefPtr<ultralight::Buffer> OpenFile(const ultralight::String& path) override {
        std::ifstream file(path.utf8().data(), std::ios::binary);
        if (!file) return nullptr;

        std::ostringstream oss;
        oss << file.rdbuf(); // Leer el archivo en un string
        std::string content = oss.str();
        // Usamos CreateFromCopy para crear el Buffer, haciendo una copia de los datos
        return ultralight::Buffer::CreateFromCopy((const void*)content.data(), content.size());
    }
};




class MyFontLoader : public ultralight::FontLoader {
public:
    // Proporciona un nombre de familia de fuentes de respaldo
    virtual ultralight::String fallback_font() const override {
        return "Arial"; // Cambia esto al nombre de la fuente de respaldo que prefieras
    }

    // Proporciona una fuente de respaldo para caracteres específicos
    virtual ultralight::String fallback_font_for_characters(const ultralight::String& characters, int weight, bool italic) const override {
        // Aquí podrías devolver una fuente específica basada en los caracteres
        return fallback_font();
    }

    // Carga los datos de una fuente a partir de su familia
    virtual ultralight::RefPtr<ultralight::FontFile> Load(const ultralight::String& family, int weight, bool italic) override {
        // Implementar lógica para cargar fuentes, por ahora solo devuelvo nullptr
        return nullptr; // Esto indica que no se pudo cargar la fuente
    }
};


class MyLogger : public ultralight::Logger {
public:
    virtual void LogMessage(ultralight::LogLevel level, const ultralight::String& message) override {
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


class SimpleHandler : public ultralight::LoadListener {
public:
    virtual void OnBeginLoading(ultralight::View* caller, uint64_t frame_id, bool is_main_frame, const ultralight::String& url) override {
        std::cout << "Comenzando carga: " << url.utf8().data() << std::endl;
    }

    virtual void OnFinishLoading(ultralight::View* caller, uint64_t frame_id, bool is_main_frame, const ultralight::String& url) override {
        std::cout << "Carga completada: " << url.utf8().data() << std::endl;
    }

    virtual void OnFailLoading(ultralight::View* caller, uint64_t frame_id, bool is_main_frame, const ultralight::String& url, const ultralight::String& description, const ultralight::String& error_domain, int error_code) override {
        std::cerr << "Error al cargar: " << url.utf8().data() << " - " << description.utf8().data() << std::endl;
    }

    virtual void OnWindowObjectReady(ultralight::View* caller, uint64_t frame_id, bool is_main_frame, const ultralight::String& url) override {
        std::cout << "Objeto de ventana listo para: " << url.utf8().data() << std::endl;
    }

    virtual void OnDOMReady(ultralight::View* caller, uint64_t frame_id, bool is_main_frame, const ultralight::String& url) override {
        std::cout << "DOM listo para: " << url.utf8().data() << std::endl;
    }

    virtual void OnUpdateHistory(ultralight::View* caller) override {
        std::cout << "Historia actualizada." << std::endl;
    }
};

int main() {
    // Crea instancias de los controladores
    MyFileSystem fileSystem;
    MyFontLoader fontLoader;
    MyLogger logger;
     
   

    // Configura Ultralight
    auto& platform = ultralight::Platform::instance();
    platform.set_file_system(&fileSystem);
    platform.set_font_loader(&fontLoader);
    platform.set_logger(&logger);

    // Crea el Renderer
    auto renderer = ultralight::Renderer::Create();

    // Inicializa la ventana de SFML
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Mi Juego");

    // Crea un View de Ultralight
    auto session = renderer->default_session();
    auto view = renderer->CreateView(1280, 720, ultralight::ViewConfig(), session);
    view->LoadURL("https://accounts.google.com/o/oauth2/v2/auth?client_id=YOUR_CLIENT_ID&redirect_uri=YOUR_REDIRECT_URI&response_type=code&scope=email");

    SimpleHandler handler;
    view->set_load_listener(&handler);

    // Bucle principal
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Actualiza el Renderer
        renderer->Update();

        // Renderiza la vista de Ultralight
        renderer->Render();

        window.clear();
        // Aquí puedes dibujar otros elementos de SFML si lo deseas
        window.display();
    }

    return 0;
}
*/