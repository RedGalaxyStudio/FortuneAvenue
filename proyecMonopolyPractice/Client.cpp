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
    static bool enetInitialized = false;
    if (!enetInitialized) {
        if (enet_initialize() != 0) {
            std::cerr << "Error initializing ENet!" << std::endl;
            return false;
        }
        enetInitialized = true;
    }

    // Solo crear cliente si no existe
    if (!client) {
        client = enet_host_create(nullptr, 1, 2, 0, 0);
        if (!client) {
            std::cerr << "Error creating ENet client!" << std::endl;
            return false;
        }
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
          //      std::cout << "Disconnected from server!" << std::endl;
                running = false;
                break;
            default:
                break;
            }
        }
    }
}

bool Client::connectToServer(const std::string& address, uint16_t port) {
    // Si ya está conectado, desconectarse primero
    if (isConnected) {
     //   std::cerr << "Already connected, disconnecting first..." << std::endl;
        disconnect(); // Llamamos a disconnect para desconectar primero
    }

    ENetAddress enetAddress;
    enet_address_set_host(&enetAddress, address.c_str());
    enetAddress.port = port;

    // Conectar al servidor
    peer = enet_host_connect(client, &enetAddress, 2, 0);
    if (!peer) {
       // std::cerr << "No available peers for initiating an ENet connection!" << std::endl;
        return false;
    }

    ENetEvent event;
    const int maxRetries = 10;
    const int retryDelay = 10;
    int totalTimeWaited = 0;

    // Intentar conectar
    for (int i = 0; i < maxRetries; ++i) {
        if (enet_host_service(client, &event, retryDelay) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
         //   std::cout << "Connected to server!" << std::endl;
            isConnected = true;
            clientThread = std::thread(&Client::run, this);  // Iniciar el hilo
            return true;
        }
        totalTimeWaited += retryDelay;
        if (totalTimeWaited >= 100) break;
    }

   // std::cerr << "Failed to connect to server within 0.1 seconds." << std::endl;
    enet_peer_reset(peer);  // Limpiar la conexión si falla
    return false;
}

void Client::disconnect() {
    if (!isConnected) return;  // Si no está conectado, no hace nada

    // Desconectar y liberar recursos
    if (peer) {
        enet_peer_disconnect(peer, 0);
        peer = nullptr;
    }

    running = false;  // Detener el hilo de ejecución
    if (clientThread.joinable()) {
        clientThread.join();  // Esperar a que termine el hilo
    }

    // Destruir el cliente y liberar recursos
    if (client) {
        enet_host_destroy(client);
        client = nullptr;
    }

    isConnected = false;  // Actualizar estado de la conexión
    std::cout << "Disconnected from server!" << std::endl;
}



std::string Client::createRoom(const std::string& username, const std::string& filename) {
    if (!peer) {
        std::cerr << "Client is not connected to a server!" << std::endl;
        return "No";
    }
    std::cout << "112";

    std::string roomCode = generateRoomCode();
    std::cout << "Room created with code: " << roomCode << std::endl;
    playerIndex = 0;

    // Crear el mensaje que incluye roomCode y username
    std::string prefix = "CREATE_ROOM:" + roomCode + ":" + username + ":";
    std::vector<char> packetData(prefix.begin(), prefix.end());

    // Crear el paquete ENet
    ENetPacket* packet = enet_packet_create(packetData.data(), packetData.size(), ENET_PACKET_FLAG_RELIABLE);
    if (enet_peer_send(peer, 0, packet) < 0) {
        std::cerr << "Failed to send the packet!" << std::endl;
        enet_packet_destroy(packet);
    }

    enet_host_flush(client);
    std::cout << "144";
    return roomCode;
}


bool Client::joinRoom(const std::string& roomCode, const std::string& username, const std::string& filename) {
    if (!peer) {
        std::cerr << "Client is not connected to a server!" << std::endl;
        return false;
    }

    std::cout << "12";

    // Crear el mensaje que incluye roomCode y username
    std::string prefix = "JOIN_ROOM:" + roomCode + ":" + username + ":";
    std::vector<char> packetData(prefix.begin(), prefix.end());

    // Crear el paquete ENet
    ENetPacket* packet = enet_packet_create(packetData.data(), packetData.size(), ENET_PACKET_FLAG_RELIABLE);
    if (enet_peer_send(peer, 0, packet) < 0) {
        std::cerr << "Failed to send the packet!" << std::endl;
        enet_packet_destroy(packet);
        return false;
    }

    enet_host_flush(client);
    return true;
}



bool Client::sendImage(const std::string& filename) {
    if (!peer) {
        std::cerr << "Client is not connected to a server!" << std::endl;
        return false;
    }

    // Cargar la imagen desde el archivo
    sf::Image image;
    if (!image.loadFromFile(filename)) {
        std::cerr << "Failed to load image: " << filename << std::endl;
        return false;
    }

    // Convertir la imagen a un arreglo de bytes
    std::vector<char> imageData(image.getSize().x * image.getSize().y * 4);  // Asumimos 4 bytes por píxel (RGBA)
    const sf::Uint8* pixels = image.getPixelsPtr();

    // Copiar los datos de los píxeles al vector de bytes
    std::copy(pixels, pixels + image.getSize().x * image.getSize().y * 4, imageData.begin());

    // Crear un paquete ENet para enviar la imagen
    std::string message = "SEND_IMAGE:";
    message += std::string(imageData.begin(), imageData.end());  // Agregar los datos de la imagen después del encabezado

    ENetPacket* packet = enet_packet_create(message.c_str(), message.size(), ENET_PACKET_FLAG_RELIABLE);

    // Enviar el paquete al servidor
    if (enet_peer_send(peer, 0, packet) < 0) {
        std::cerr << "Failed to send image." << std::endl;
        enet_packet_destroy(packet);
        return false;
    }

    // Liberar el paquete después de enviarlo
    enet_packet_destroy(packet);

    std::cout << "Image sent!" << std::endl;
    return true;
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
    std::cout << "\nSELECTING_PIECE:" << playerInfos[0].indexPiece;
    ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
    enet_host_flush(client);
}


void Client::ReadyPlayer() {
    if (!peer) {
        std::cerr << "Client is not connected to a server!" << std::endl;
    }

    std::string message = "PLAYER_READY";
    ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
    enet_host_flush(client);

}






// Manejar mensajes recibidos del servidor
void Client::handleServerMessage(const std::string& message) {

    std::cout << "\n mensage:" << message;

    if (message.rfind("YOUR_TURN", 0) == 0) {
        std::cout << "It's your turn!" << std::endl;
        // Aquí el jugador puede decidir llamar a `rollDice`
    }
    else if(message.rfind("ROLL_RESULT:", 0) == 0) {
        std::cout << "\nEjecución de ROLL_RESULT";

        // Extrae `currentPlayerIndex` y `dado` del mensaje.
        size_t playerIndexPos = message.find(":PLAYER_INDEX:") + std::string(":PLAYER_INDEX:").length();
        size_t dicePos = message.find(":DICE:", playerIndexPos);

        if (playerIndexPos != std::string::npos && dicePos != std::string::npos) {
            int currentPlayerIndex = std::stoi(message.substr(playerIndexPos, dicePos - playerIndexPos));
            int diceRoll = std::stoi(message.substr(dicePos + std::string(":DICE:").length()));

            lastRollResult = diceRoll;

            {
                std::lock_guard<std::mutex> lock(mtx);
                espera = true; // Cambia espera a true
            }

            cv.notify_one(); // Notifica a cualquier hilo en espera

            std::cout << "\nResultado en clase cliente:" << lastRollResult;
            std::cout << "\nDice roll result: " << diceRoll << " para jugador con índice: " << currentPlayerIndex << std::endl;
        }
        else {
            std::cerr << "Formato del mensaje ROLL_RESULT incorrecto" << std::endl;
        }
    }

    else if (message == "NOT_YOUR_TURN") {

        std::cout << "Wait for your turn!" << std::endl;

    }
    else if (message.rfind("PLAYER_INDEX:", 0) == 0) {
        std::cout << "\nEJEcuto playerindex1";
            // Extraer el índice del jugador
            std::string indexStr = message.substr(std::string("PLAYER_INDEX:").length());
            playerIndex = std::stoi(indexStr);


            // Aquí puedes realizar la lógica que necesites con el índice del jugador
            std::cout << "Tu índice de jugador es: " << playerIndex << std::endl;
            std::cout << "\nEJEcuto playerindex2";
    }else
        
        
        
        
        
    if (message.rfind("NEW_PLAYER:", 0) == 0) {
        std::cout << "\nNEW_PLAYER";
        // Eliminar el prefijo "NEW_PLAYER:"
        if (message.length() < 11) { // 11 es la longitud de "NEW_PLAYER:"
            std::cout << "\nEJEcuto toy mal";
            return;
        }
        std::cout << "\nEJEcuto existen1";
        std::string data = message.substr(11); // Obtener los datos sin el prefijo

        // Dividir la cadena de datos en partes usando ":" como delimitador
        std::istringstream iss(data);
        std::string username, indexStr, moneyStr, isSelectingStr, isInGameStr;

        if (std::getline(iss, username, ':') &&
            std::getline(iss, indexStr, ':') &&
            std::getline(iss, moneyStr, ':') &&
            std::getline(iss, isSelectingStr, ':') &&
            std::getline(iss, isInGameStr, ':')) { 
            //&&std::getline(iss, imageStr)
            // Todos los valores se han leído correctamente
        }
        else {
            std::cout << "\nEJEcuto toy remal";
            return;
        }

        int index;
        int money;
        bool isSelecting;
        bool isInGame;

        std::cout << "indexStr: '" << indexStr << "', moneyStr: '" << moneyStr << "'\n";

        // Convertir el índice y el dinero a sus tipos apropiados
        try {
            index = std::stoi(indexStr);
            money = std::stoi(moneyStr);
            isSelecting = (isSelectingStr == "true");
            isInGame = (isInGameStr == "true");
        }
        catch (const std::invalid_argument& e) {
            // Manejar el error (el valor no es un número)
            std::cout << "\nEJEcuto no sirvo";
            return;
        }
        catch (const std::out_of_range& e) {
            // Manejar el error (el número está fuera del rango)
            std::cout << "\nEJEcuto no 98989";
            return;
        }
        std::cout << "\nEJEcuto existen3";



        if (playerIndex != 0) {

            index = (index - playerIndex + 4) % 4;

        }


        // Asegurarse de que el índice esté dentro de los límites
        if (index >= 0 && index < playerInfos.size()) {
            std::cout << "\nEJEcuto existen6";
            // Actualizar la información del jugador en la posición correspondiente
            playerInfos[index].username = username;
            playerInfos[index].money = money;
            playerInfos[index].isSelectingPiece = isSelecting;
            playerInfos[index].isInGame = isInGame;

            // Procesar la imagen
            //std::vector<char> image(imageStr.begin(), imageStr.end());
            //playerInfos[index].image = image;

            // Cargar la textura del avatar
          //  playersGame[index].textureAvatarPLayer.loadFromMemory(image.data(), image.size());
            playersGame[index].NamePlayer.setString(playerInfos[index].username);

            // Imprimir la información del jugador
            std::cout << "Player " << index << ": " << username
                << " | Money: " << money
                << " | Is Selecting: " << (isSelecting ? "Yes" : "No")
                << " | Is In Game: " << (isInGame ? "Yes" : "No")
                << std::endl;

            std::cout << "\nEJEcuto existen4";
        }else{
            std::cerr << "Error: Index out of bounds for player information." << std::endl;
        }


        std::cout << "\nEJEcuto existen2";
    }


    else if (message.rfind("EXISTING_PLAYER:", 0) == 0) {
        // Eliminar el prefijo "EXISTING_PLAYER:"
        std::cout << "\nEXISTING_PLAYER";

        if (message.length() < 16) {
            std::cout << "\nEJEcuto toy mal";
            return;
        }
        std::cout << "\nEJEcuto existen1";
        std::string data = message.substr(16);

        // Dividir la cadena de datos en partes usando ":" como delimitador
        std::istringstream iss(data);
        std::string username, indexStr, moneyStr, isSelectingStr, isInGameStr;

        if (std::getline(iss, username, ':')&&
            std::getline(iss, indexStr, ':')&&
            std::getline(iss, moneyStr, ':')&&
            std::getline(iss, isSelectingStr, ':')&&
            std::getline(iss, isInGameStr, ':')){ //&&
         //   std::getline(iss, imageStr)
         
            // Todos los valores se han leído correctamente
        }
        else {
            std::cout << "\nEJEcuto toy remal";
            
        }

        int index;
        int money;
        bool isSelecting;
        bool isInGame;

        std::cout << "indexStr: '" << indexStr << "', moneyStr: '" << moneyStr << "'\n";

        // Convertir el índice y el dinero a sus tipos apropiados
        try {
             index = std::stoi(indexStr);
             money = std::stoi(moneyStr);
             isSelecting = (isSelectingStr == "true");
             isInGame = (isInGameStr == "true");
            
        }
        catch (const std::invalid_argument& e) {
            // Manejar el error (el valor no es un número)
            std::cout << "\nEJEcuto no sirvo";
            return;
        }
        catch (const std::out_of_range& e) {
            // Manejar el error (el número está fuera del rango)
            std::cout << "\nEJEcuto no 98989";
            return;
        }
        std::cout << "\nEJEcuto existen3";



        if (playerIndex != 0) {

            index = (index - playerIndex + 4) % 4;

        }


        //std::vector<char> image(imageStr.begin(), imageStr.end());


        // Asegurarse de que el índice esté dentro de los límites
        if (index >= 0 && index < playerInfos.size()) {
            std::cout << "\nEJEcuto existen6";
            // Actualizar la información del jugador en la posición correspondiente
            playerInfos[index].username = username;
            playerInfos[index].money = money;
            playerInfos[index].isSelectingPiece = isSelecting;
            playerInfos[index].isInGame = isInGame;
            
           /*
            std::vector<char>& imageData = playerInfos[index].image;

            playersGame[index].textureAvatarPLayer.loadFromMemory(imageData.data(), imageData.size());*/
            playersGame[index].NamePlayer.setString(playerInfos[index].username);
            

            // Imprimir la información del jugador
            std::cout << "Player " << index << ": " << username
                << " | Money: " << money
                << " | Is Selecting: " << (isSelecting ? "Yes" : "No")
                << " | Is In Game: " << (isInGame ? "Yes" : "No")
                << std::endl;

            std::cout << "\nEJEcuto existen4";
        }
        else {
            std::cerr << "Error: Index out of bounds for player information." << std::endl;
        }

        std::cout << "\nEJEcuto existen2";
    }
    else if (message.rfind("PLAYER_COUNT:", 0) == 0) {
        // Extraer la cantidad de jugadores de la mensaje
        std::string playerCountStr = message.substr(13); // "PLAYER_COUNT:".length() == 13
        int playerCount = std::stoi(playerCountStr);
        NumPlayers = playerCount;

    } else if (message.rfind("SEND_IMAGE:", 0) == 0) {
        // Recuperar el índice del jugador
        int IIndex = 0;
        size_t pos = 11;  // Después del encabezado "SEND_IMAGE:"

        try {
            IIndex = std::stoi(message.substr(pos, message.find(":", pos) - pos));
        }
        catch (const std::exception& e) {
            std::cerr << "Error parsing player index: " << e.what() << std::endl;
            return;
        }

        IIndex = (IIndex - playerIndex + 4) % 4;

        // Extraer los datos de la imagen
        size_t imageStartPos = message.find(":", pos) + 1;  // Después del índice
        std::vector<char> imageData(message.begin() + imageStartPos, message.end());
        // Cargar la textura desde los datos de la imagen
        if (playersGame[IIndex].textureAvatarPLayer.loadFromMemory(imageData.data(), imageData.size())) {
            std::cout << "Texture loaded successfully for player " << IIndex << std::endl;
        }
        else {
            std::cerr << "Failed to load texture for player " << IIndex << std::endl;
        }
        // Aquí puedes manejar la imagen recibida
        std::cout << "Received image from player " << IIndex << std::endl;
        std::string filename = "received_player_" + std::to_string(IIndex) + "_image.png";

    }

    else
        
    if (message.rfind("PLAYER_CHANGED_PIECE:", 0) == 0) {
        std::cout << "\nEJEcuto index1";
        std::cout << "\nMensaje recibido: " << message;
        std::string indexStr;
        std::string pieceIndexStr;
        try {
            // Encontrar las posiciones de los delimitadores ":" en el mensaje
            size_t firstColon = message.find(":", 20);   // Buscar el primer ":" después del prefijo
            size_t secondColon = message.find(":", firstColon + 1); // Buscar el segundo ":" después del primero

            if (firstColon == std::string::npos || secondColon == std::string::npos) {
                std::cerr << "Error: Formato de mensaje inesperado. Faltan delimitadores." << std::endl;
                return;
            }

            // Extraer las subcadenas correspondientes al índice del jugador y al índice de la pieza
             indexStr = message.substr(firstColon + 1, secondColon - firstColon - 1);
            pieceIndexStr = message.substr(secondColon + 1);

            // Mostrar los valores extraídos para depuración
            std::cout << "\nindexStr: '" << indexStr << "', pieceIndexStr: '" << pieceIndexStr << "'";

            // Convertir los valores a enteros
            int Index = std::stoi(indexStr);
            int indexselectinpiece = std::stoi(pieceIndexStr);

            // Ajustar el índice del jugador
            Index = (Index - playerIndex + 4) % 4;
            CplayerIndex = Index;

            // Actualizar la información en el cliente
            std::cout << "Player " << playerIndex << " seleccionó la pieza con índice " << indexselectinpiece << std::endl;
            playerInfos[Index].indexPiece = indexselectinpiece;
            std::cout << "\nEJEcuto index 2";
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "\nError: Argumento no válido al intentar convertir a entero. indexStr: '" << indexStr << "', pieceIndexStr: '" << pieceIndexStr << "'" << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "\nError: Número fuera de rango al intentar convertir a entero. indexStr: '" << indexStr << "', pieceIndexStr: '" << pieceIndexStr << "'" << std::endl;
        }
    }
    else if (message.rfind("PLAYER_READY:", 0) == 0) {
            // Extraer el `indexPlayer` del mensaje
            int indexPlayer = std::stoi(message.substr(13)); // "PLAYER_READY:" tiene 13 caracteres
            indexPlayer = (indexPlayer - playerIndex + 4) % 4;
            playerInfos[indexPlayer].isSelectingPiece = true;

            // Ahora puedes usar `indexPlayer` para actualizar el estado del jugador en el cliente
            std::cout << "Jugador " << indexPlayer << " está listo." << std::endl;

            // Realiza cualquier acción adicional para indicar que este jugador está listo,
            // como actualizar el estado en la interfaz de usuario.
           
    }
    else{
        std::cerr << "Unknown message received from server: " << message << std::endl;
    }
}
