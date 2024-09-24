#ifndef WEBVIEWMANAGER_HPP
#define WEBVIEWMANAGER_HPP

#include "menuP.hpp"
#include <windows.h>
#include <WebView2.h>
#include <wrl.h>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include "ObjetosGlobal.hpp"
using namespace Microsoft::WRL;

class WebViewManager {
public:
    WebViewManager(HWND parentHwnd);
    void CreateWebView();
    void OnAuthenticationComplete(const std::wstring& token);
    std::wstring ExtractTokenFromUrl(const std::wstring& url);
    void ClearCookiesUsingJavaScript(ICoreWebView2* webview);
private:
    HWND hwnd;
    ComPtr<ICoreWebView2Controller> webviewController;
   
};

#endif // WEBVIEWMANAGER_HPP

