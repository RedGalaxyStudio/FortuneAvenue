#ifndef CLIENT_HPP
#define CLIENT_HPP
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#include <enet/enet.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <string>

class Client {
public:
    Client();
    ~Client();
    void run();
    bool initialize();
    bool createRoom();
    bool joinRoom(const std::string& roomCode);
    bool connectToServer(const std::string& address, uint16_t port);
    bool sendImage(const std::string& filename);
    void disconnect();

private:
    ENetHost* client;
    ENetPeer* peer;

    std::vector<char> loadImage(const std::string& filename);

    std::thread clientThread; 
    std::atomic<bool> running; 
};

#endif
