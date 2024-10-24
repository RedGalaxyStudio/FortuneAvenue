#include "Client.hpp"

Client::Client() : client(nullptr), peer(nullptr) {}

Client::~Client() {
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
        return true;
    }
    else {
        std::cerr << "Failed to connect to server." << std::endl;
        return false;
    }
}

bool Client::sendImage(const std::string& filename) {
    // Load the image data
    std::vector<char> imageData = loadImage(filename);
    if (imageData.empty()) {
        std::cerr << "Failed to load image!" << std::endl;
        return false;
    }

    // Send the image as a packet
    ENetPacket* packet = enet_packet_create(imageData.data(), imageData.size(), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
    enet_host_flush(client);

    std::cout << "Image sent!" << std::endl;
    return true;
}

void Client::disconnect() {
    if (peer) {
        enet_peer_disconnect(peer, 0);
    }
    std::cout << "Disconnected from server!" << std::endl;
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
