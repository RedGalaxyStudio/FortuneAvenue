#include "Client.hpp"
#include <random>
#include <iostream>
#include <thread>

Client::Client() : client(nullptr), peer(nullptr), running(false) {}

std::string generateRoomCode() {
    std::string code;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 9);

    for (int i = 0; i < 5; ++i) {
        code += std::to_string(dist(mt));
    }

    return code;
}

Client::~Client() {
    disconnect(); 
    if (client) {
        enet_host_destroy(client);
    }
    enet_deinitialize();
}

bool Client::initialize() {
    if (enet_initialize() != 0) {
        std::cerr << "Error initializing ENet!" << std::endl;
        return false;
    }

    client = enet_host_create(nullptr, 1, 2, 0, 0);
    if (!client) {
        std::cerr << "Error creating ENet client!" << std::endl;
        return false;
    }
    return true;
}

void Client::run() {
    running = true;
    while (running) {
        ENetEvent event;
        while (enet_host_service(client, &event, 100) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                
                enet_packet_destroy(event.packet); 
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "Disconnected from server!" << std::endl;
                running = false; 
                break;
            default:
                break;
            }
        }
    }
}

bool Client::connectToServer(const std::string& address, uint16_t port) {
    ENetAddress enetAddress;
    enet_address_set_host(&enetAddress, address.c_str());
    enetAddress.port = port;

    peer = enet_host_connect(client, &enetAddress, 2, 0);
    if (!peer) {
        std::cerr << "No available peers for initiating an ENet connection!" << std::endl;
        return false;
    }

    ENetEvent event;
    if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
        std::cout << "Connected to server!" << std::endl;
        clientThread = std::thread(&Client::run, this); 
        return true;
    }
    else {
        std::cerr << "Failed to connect to server." << std::endl;
        return false;
    }
}

bool Client::createRoom() {
    if (!peer) {
        std::cerr << "Client is not connected to a server!" << std::endl;
        return false;
    }

    
    std::string roomCode = generateRoomCode();
    std::cout << "Room created with code: " << roomCode << std::endl;

    
    std::string message = "CREATE_ROOM:" + roomCode;
    ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
    enet_host_flush(client);

    return true;
}

bool Client::joinRoom(const std::string& roomCode) {
    if (!peer) {
        std::cerr << "Client is not connected to a server!" << std::endl;
        return false;
    }

    // Enviar el código de la sala al servidor
    std::string message = "JOIN_ROOM:" + roomCode;
    ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
    enet_host_flush(client);

    return true;
}

bool Client::sendImage(const std::string& filename) {
    if (!peer) {
        std::cerr << "Client is not connected to a server!" << std::endl;
        return false;
    }

    std::vector<char> imageData = loadImage(filename);
    if (imageData.empty()) {
        std::cerr << "Failed to load image!" << std::endl;
        return false;
    }

    // Añadir prefijo "SEND_IMAGE:" a los datos
    std::string prefix = "SEND_IMAGE:";
    std::vector<char> packetData(prefix.begin(), prefix.end());
    packetData.insert(packetData.end(), imageData.begin(), imageData.end());

    // Crear el paquete con los datos binarios
    ENetPacket* packet = enet_packet_create(packetData.data(), packetData.size(), ENET_PACKET_FLAG_RELIABLE);
    if (enet_peer_send(peer, 0, packet) < 0) {
        std::cerr << "Failed to send the packet!" << std::endl;
        enet_packet_destroy(packet);
        return false;
    }
    enet_host_flush(client);

    std::cout << "Image sent!" << std::endl;
    return true;
}


void Client::disconnect() {
    if (peer) {
        enet_peer_disconnect(peer, 0);
        peer = nullptr;  
    }
    running = false;
    if (clientThread.joinable()) {
        clientThread.join(); 
    }
}

std::vector<char> Client::loadImage(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open the image file!" << std::endl;
        return {};
    }

    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return buffer;
}
