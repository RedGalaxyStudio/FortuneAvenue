#ifndef CLIENT_HPP
#define CLIENT_HPP
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#include <enet/enet.h>
#include <fstream>
#include <iostream>
#include <vector>

class Client {
public:
    Client();
    ~Client();

    bool initialize();
    bool connectToServer(const std::string& address, uint16_t port);
    bool sendImage(const std::string& filename);
    void disconnect();

private:
    ENetHost* client;
    ENetPeer* peer;

    std::vector<char> loadImage(const std::string& filename);
};

#endif // CLIENT_HPP
