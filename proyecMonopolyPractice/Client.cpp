#include "Client.hpp"

Client::Client() : client(nullptr), peer(nullptr), running(false) ,lastRollResult(0){}

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
            case ENET_EVENT_TYPE_RECEIVE: {
                std::string message(reinterpret_cast<char*>(event.packet->data), event.packet->dataLength);
                handleServerMessage(message);  // Manejar el mensaje recibido
                enet_packet_destroy(event.packet);
                break;
            }
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

std::string Client::createRoom() {
    if (!peer) {
        std::cerr << "Client is not connected to a server!" << std::endl;
        return "No";
    }

    std::string roomCode = generateRoomCode();
    std::cout << "Room created with code: " << roomCode << std::endl;
    playerIndex = 0;
    std::string message = "CREATE_ROOM:" + roomCode;
    ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
    enet_host_flush(client);

    return roomCode;
}

bool Client::joinRoom(const std::string& roomCode) {
    if (!peer) {
        std::cerr << "Client is not connected to a server!" << std::endl;
        return false;
    }

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

    std::string prefix = "SEND_IMAGE:";
    std::vector<char> packetData(prefix.begin(), prefix.end());
    packetData.insert(packetData.end(), imageData.begin(), imageData.end());

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

// Nueva función para solicitar tirada de dados
void Client::rollDice() {
    if (!peer) {
        std::cerr << "Client is not connected to a server!" << std::endl;
    }

    std::string message = "ROLL_DICE";
    ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
    enet_host_flush(client);
}


void Client::playerChangedPiece() {
    std::string message = "SELECTING_PIECE:"+ std::to_string(playerInfos[0].indexPiece);
    ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
    enet_host_flush(client);
}

// Manejar mensajes recibidos del servidor
void Client::handleServerMessage(const std::string& message) {
    if (message.rfind("YOUR_TURN", 0) == 0) {
        std::cout << "It's your turn!" << std::endl;
        // Aquí el jugador puede decidir llamar a `rollDice`
    }
    else if (message.rfind("TURN_RESULT:", 0) == 0) {
        int diceRoll = std::stoi(message.substr(12)); // Lee el resultado después de "TURN_RESULT:"
        lastRollResult = diceRoll;
        espera = true;
        std::cout << "Dice roll result: " << diceRoll << std::endl;
    }
    else if (message == "NOT_YOUR_TURN") {

        std::cout << "Wait for your turn!" << std::endl;

    }
    else if (message.rfind("PLAYER_INDEX:", 0) == 0) {

            // Extraer el índice del jugador
            std::string indexStr = message.substr(std::string("PLAYER_INDEX:").length());
            playerIndex = std::stoi(indexStr);


            // Aquí puedes realizar la lógica que necesites con el índice del jugador
            std::cout << "Tu índice de jugador es: " << playerIndex << std::endl;

    }
    else if (message.rfind("EXISTING_PLAYER:", 0) == 0) {
        // Eliminar el prefijo "EXISTING_PLAYER:"
        std::string data = message.substr(16);

        // Dividir la cadena de datos en partes usando ":" como delimitador
        std::istringstream iss(data);
        std::string username, indexStr, moneyStr, isSelectingStr, isInGameStr;

        std::getline(iss, username, ':');
        std::getline(iss, indexStr, ':');
        std::getline(iss, moneyStr, ':');
        std::getline(iss, isSelectingStr, ':');
        std::getline(iss, isInGameStr, ':');

        // Convertir el índice y el dinero a sus tipos apropiados
        int index = std::stoi(indexStr);
        int money = std::stoi(moneyStr);
        bool isSelecting = (isSelectingStr == "true");
        bool isInGame = (isInGameStr == "true");

        if (playerIndex != 0) {

            index = (index - playerIndex + 4) % 4;

        }


        // Asegurarse de que el índice esté dentro de los límites
        if (index >= 0 && index < playerInfos.size()) {
            // Actualizar la información del jugador en la posición correspondiente
            playerInfos[index].username = username;
            playerInfos[index].money = money;
            playerInfos[index].isSelectingPiece = isSelecting;
            playerInfos[index].isInGame = isInGame;

            // Imprimir la información del jugador
            std::cout << "Player " << index << ": " << username
                << " | Money: " << money
                << " | Is Selecting: " << (isSelecting ? "Yes" : "No")
                << " | Is In Game: " << (isInGame ? "Yes" : "No")
                << std::endl;
        }
        else {
            std::cerr << "Error: Index out of bounds for player information." << std::endl;
        }
    }
    else  if (message.rfind("PLAYER_CHANGED_PIECE:", 0) == 0) {
        // Extraer la información del mensaje
        size_t firstColon = message.find(":", 20); // La primera posición después de "PLAYER_CHANGED_PIECE:"
        int Index = std::stoi(message.substr(20, firstColon - 20));
        int indexselectinpiece = std::stoi(message.substr(firstColon + 1));
        std::cout << "\n\n" << Index;
        Index = (Index - playerIndex + 4) % 4;
        CplayerIndex = Index;
        
        // Actualizar la información en el cliente (puedes adaptar esto según tu interfaz)
        std::cout << "Player " << playerIndex << " selected piece index " << indexselectinpiece << std::endl;

        playerInfos[Index].indexPiece = indexselectinpiece;
    }
    else{
        std::cerr << "Unknown message received from server: " << message << std::endl;
    }
}
