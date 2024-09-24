#include "WebViewManager.hpp"
#include <fstream> // Para manejar archivos


WebViewManager::WebViewManager(HWND parentHwnd) : hwnd(parentHwnd){}

void WebViewManager::CreateWebView() {
    ComPtr<ICoreWebView2Environment> env;
    WCHAR tempPath[MAX_PATH];
    GetTempPath(MAX_PATH, tempPath); // Obtiene la carpeta temporal
    WCHAR tempUserDataFolder[MAX_PATH];
    GetTempFileName(tempPath, L"wv2", 0, tempUserDataFolder); // Crea un nombre de carpeta temporal

    // Elimina el archivo temporal (GetTempFileName crea un archivo, lo eliminamos)
    DeleteFile(tempUserDataFolder);
    CreateDirectory(tempUserDataFolder, NULL); // Creas la carpeta temporal

    HRESULT hr = CreateCoreWebView2EnvironmentWithOptions(nullptr, tempUserDataFolder, nullptr,
        Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
            [this, &env](HRESULT result, ICoreWebView2Environment* environment) -> HRESULT {
                if (SUCCEEDED(result)) {
                    env = environment;
                    env->CreateCoreWebView2Controller(hwnd, Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                        [this, &env](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
                            if (SUCCEEDED(result)) {
                                webviewController = controller;
                                ComPtr<ICoreWebView2> webview;

                                HRESULT hrWebview = webviewController->get_CoreWebView2(&webview);
                                if (SUCCEEDED(hrWebview)) {
                                    RECT bounds;
                                    GetClientRect(hwnd, &bounds);
                                    webviewController->put_Bounds(bounds);
                                    webviewController->put_IsVisible(TRUE);

                                    // Limpiar cookies antes de navegar a la URL
                                     // Limpiar cookies usando JavaScript antes de navegar a la URL
                                   // ClearCookiesUsingJavaScript(webview.Get());

                                    // Definir clientId, redirectUri y scope
                                    const wchar_t* clientId = L"978916635169-4a7ti1bdu3e07d3a14o1s5or4n8s4msg.apps.googleusercontent.com";
                                    const wchar_t* redirectUri = L"https://8e07-190-97-251-12.ngrok-free.app";
                                    const wchar_t* scope = L"https://www.googleapis.com/auth/userinfo.email";

                                    // Construir la URL de navegación
                                    std::wstring url = L"https://accounts.google.com/o/oauth2/auth?client_id=" + std::wstring(clientId) +
                                        L"&redirect_uri=" + std::wstring(redirectUri) +
                                        L"&response_type=token" +
                                        L"&scope=" + std::wstring(scope);

                                    // Navegar a la URL
                                    HRESULT hrNavigate = webview->Navigate(url.c_str());
                                    if (FAILED(hrNavigate)) {
                                        std::cerr << "Error al navegar a la URL. HRESULT: " << hrNavigate << std::endl;
                                    }
                                    
                                    // Manejar el evento de navegación cuando la navegación se completa
                                    EventRegistrationToken navigationCompletedToken;
                                    webview->add_NavigationCompleted(Callback<ICoreWebView2NavigationCompletedEventHandler>(
                                        [this](ICoreWebView2* sender, ICoreWebView2NavigationCompletedEventArgs* args) -> HRESULT {
                                            LPWSTR uri = nullptr;
                                            sender->get_Source(&uri); // Obtener la URL actual después de que la navegación se complete
                                            std::wstring url(uri);

                                            // Verificar si la URL es la que queremos detectar (después de la redirección de autenticación)
                                            if (url.find(L"https://8e07-190-97-251-12.ngrok-free.app") != std::wstring::npos) {
                                                std::wcout << L"Navegación completada. URL detectada: " << url << std::endl;

                                                // Extraer el token de la URL
                                                std::wstring token = ExtractTokenFromUrl(url);

                                                // Llama al evento de autenticación
                                                OnAuthenticationComplete(token); // Llama al evento cuando se detecta la redirección correcta
                                            }

                                            CoTaskMemFree(uri); // Liberar memoria asignada
                                            return S_OK;
                                        }).Get(), &navigationCompletedToken);

                                }
                                else {
                                    std::cerr << "Error al obtener el WebView2. HRESULT: " << hrWebview << std::endl;
                                }
                            }
                            else {
                                std::cerr << "Error al crear el controlador WebView2. HRESULT: " << result << std::endl;
                            }
                            return S_OK;
                        }).Get());
                }
                else {
                    std::cerr << "Error al crear el entorno WebView2. HRESULT: " << result << std::endl;
                }
                return S_OK;
            }).Get());

    if (FAILED(hr)) {
        std::cerr << "Error en CreateCoreWebView2EnvironmentWithOptions. HRESULT: " << hr << std::endl;
    }
}

// Asumiendo que tienes tu controlador y WebView inicializado
void WebViewManager::ClearCookiesUsingJavaScript(ICoreWebView2* webview)
{
    if (!webview) {
        std::cerr << "WebView no está inicializado." << std::endl;
        return;
    }

    // JavaScript para eliminar todas las cookies
    std::wstring script = LR"(
        (function() {
            var cookies = document.cookie.split("; ");
            for (var i = 0; i < cookies.length; i++) {
                var cookie = cookies[i];
                var eqPos = cookie.indexOf("=");
                var name = eqPos > -1 ? cookie.substr(0, eqPos) : cookie;
                document.cookie = name + '=;expires=Thu, 01 Jan 1970 00:00:00 GMT;path=/';
            }
            return 'Cookies eliminadas';
        })();
    )";

    // Ejecutar el script en el WebView
    webview->ExecuteScript(script.c_str(), Callback<ICoreWebView2ExecuteScriptCompletedHandler>(
        [](HRESULT errorCode, LPCWSTR resultObjectAsJson) -> HRESULT {
            if (SUCCEEDED(errorCode)) {
                std::wcout << L"Resultado del script: " << resultObjectAsJson << std::endl;
            }
            else {
                std::cerr << "Error al ejecutar el script para eliminar cookies." << std::endl;
            }
            return S_OK;
        }).Get());
}

void WebViewManager::OnAuthenticationComplete(const std::wstring& token) {
    std::wcout << L"Token de acceso obtenido: " << token << std::endl;
    std::wofstream tokenFile("token.txt");
    if (tokenFile.is_open()) {
        tokenFile << token;
        tokenFile.close();
        std::wcout << L"Token guardado en el archivo 'token.txt'." << std::endl;
    }
    else {
        std::cerr << "Error al abrir el archivo para guardar el token." << std::endl;
    }
    
    //CloseWebView();

}




std::wstring WebViewManager::ExtractTokenFromUrl(const std::wstring& url) {
    // Lógica para extraer el token de la URL
    size_t tokenPos = url.find(L"access_token=");
    if (tokenPos != std::wstring::npos) {
        tokenPos += wcslen(L"access_token=");
        size_t endPos = url.find(L"&", tokenPos);
        return url.substr(tokenPos, endPos - tokenPos);
    }
    return L""; // Retornar una cadena vacía si no se encuentra
}

