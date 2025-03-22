#include "ServerMessageHandler.hpp"
#include "iostream"
#include "../game/online/ResourceGame.hpp"
#include "../game/online/OnlineVars.hpp"
#include <fstream>

ServerMessageHandler::ServerMessageHandler(ClientData* cData) :clientData(cData), peer(nullptr) {}
void ServerMessageHandler::Enetpeer(ENetPeer* Peer) {
	this->peer = Peer;
}
int ServerMessageHandler::calcularNumeroDeLineas(const sf::Text& text) {

	sf::FloatRect bounds = text.getGlobalBounds();

	float alturaLinea = text.getCharacterSize();
	int numeroDeLineas = static_cast<int>(bounds.height / alturaLinea);

	return numeroDeLineas;
}
void ServerMessageHandler::moneyActu(int money) {
	std::string message = "MONEY_ACTU:" + std::to_string(money);

	//	ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	//	enet_peer_send(peer, 0, packet);
		//enet_host_flush();


}

void ServerMessageHandler::MONEYSALARIO(std::string message, int usuario) {
	size_t moneyPos = message.find(":MONEYSALARIO:");
	if (moneyPos != std::string::npos) {
		size_t moneyStart = moneyPos + 14;
		std::string moneyStr = message.substr(moneyStart);
		int playerMoney = std::stoi(moneyStr);
		playerInfos[usuario].money = playerMoney;
		playersGame[usuario].Money.setString(std::to_string(playerInfos[usuario].money));

	}
}

void ServerMessageHandler::handleServerMessage(const ENetPacket* preprocces) {
	//std::cout << "\nuuuuuuuuuuuuuuuuuu11111111111111111111111";


	if (preprocces == nullptr || preprocces->data == nullptr) {
		std::cerr << "Error: preprocces o preprocces->data es nulo." << std::endl;
		return;
	}

	// Verificar que la longitud de los datos sea válida
	if (preprocces->dataLength == 0) {
		std::cerr << "Error: los datos recibidos tienen longitud 0." << std::endl;
		return;
	}

	std::string message(reinterpret_cast<char*>(preprocces->data), preprocces->dataLength);
	//std::cout << "\nuuuuuuuuuuuuuuuuuu22222222222222222222222";
	std::cout << "\nMensaje recibido: " << message << std::endl;
	if (message.rfind("YOUR_TURN", 0) == 0) {

		MONEYSALARIO(message, playerIndex);

		if (playerInfos[UsuariosActivos[0]].final) {

			std::string message = "END_TURN";
			if (!peer) return;
			ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
			if (!packet) return;
			if (enet_peer_send(peer, 0, packet) < 0) return;
			enet_host_flush(peer->host);
			return;
		}

		if (turnopermitido != 0) {
			nular = false;
			return;
		}

		turn_dado = true;
		turn = true;
		eventoActivo = false;
		turn_ruleta = true;
		turn_casa = true;
		turn_impuesto = true;
		turn_Moviendo = true;
		IndexTurn = playerIndex;
		otherturn = false;
	}
	else if (message.rfind("TURN_START", 0) == 0) {

		otherturn = true;
		eventoActivo = false;
		turn_ruleta = true;
		turn_casa = true;
		turn_impuesto = true;
		turn_Moviendo = true;

		size_t indexPos = message.find("PLAYER_INDEX:");
		if (indexPos != std::string::npos) {

			std::string playerIndexStr = message.substr(indexPos + 13);
			int playerIndexTurn = std::stoi(playerIndexStr);
			IndexTurn = playerIndexTurn;

			MONEYSALARIO(message, playerIndexTurn);

		}

	}
	else if (message.rfind("ROLL_RESULT:", 0) == 0) {

		size_t playerIndexPos = message.find(":PLAYER_INDEX:") + std::string(":PLAYER_INDEX:").length();
		size_t dicePos = message.find(":DICE:", playerIndexPos);

		if (playerIndexPos != std::string::npos && dicePos != std::string::npos) {
			int currentPlayerIndex = std::stoi(message.substr(playerIndexPos, dicePos - playerIndexPos));
			int diceRoll = std::stoi(message.substr(dicePos + std::string(":DICE:").length()));

			//	currentPlayerIndex = (currentPlayerIndex - playerIndex + 4) % 4;
			clientData->lastRollResult = diceRoll;
			IndexTurn = currentPlayerIndex;
			if (turn) {

				{
					std::lock_guard<std::mutex> lock(clientData->mtx);
					espera = true;
				}

				clientData->cv.notify_one();
			}
			else {

				{
					std::lock_guard<std::mutex> lock(clientData->mtx);
					rolldiceJugador = true;
				}

				clientData->cv.notify_one();

			}

		}

	}
	else if (message.rfind("OPCION_CAMINO:", 0) == 0) {

		size_t pos = message.find(":");
		if (pos != std::string::npos && pos + 1 < message.size()) {
			int opcion = std::stoi(message.substr(pos + 1));
			Opcioncami = opcion;
		}

	}
	else if (message.find("COMPRADA:") == 0) {
		std::string data = message.substr(9);
		size_t delimiterPos = data.find(':');
		if (delimiterPos != std::string::npos) {
			int indexPlayerr = std::stoi(data.substr(0, delimiterPos));
			//	indexPlayerr = (indexPlayerr - playerIndex + 4) % 4;
			int moneyy = std::stoi(data.substr(delimiterPos + 1));
			playerInfos[indexPlayerr].money = moneyy;
			playersGame[indexPlayerr].Money.setString(std::to_string(playerInfos[indexPlayerr].money));
			accionCompra = true;
		}
	}
	else if (message.rfind("RULETE_GAME:", 0) == 0) {
		float angulo = std::stof(message.substr(12));

		{
			std::lock_guard<std::mutex> lock(clientData->ruletaMutex);
			clientData->anguloActualrule = angulo;
			clientData->ruletaMessageReceived = true;
		}

		clientData->ruletaCondVar.notify_one();

	}
	else if (message.rfind("START_SPIN", 0) == 0) {
		std::istringstream stream(message);
		std::string segment;
		std::vector<std::string> parts;

		while (std::getline(stream, segment, ':')) {
			parts.push_back(segment);
		}

		if (parts.size() == 5 && parts[0] == "START_SPIN") {

			initialSpeedActi = std::stof(parts[2]);
			decelerationRateActi = std::stof(parts[4]);
			giroActivo = true;

		}

	}
	else if (message.rfind("GANAR150:", 0) == 0) {
		size_t firstColon = message.find(':');
		size_t secondColon = message.find(':', firstColon + 1);

		if (firstColon != std::string::npos && secondColon != std::string::npos) {

			int indexjugador = std::stoi(message.substr(firstColon + 1, secondColon - firstColon - 1));
			playerInfos[indexjugador].money = std::stoi(message.substr(secondColon + 1));
			playersGame[indexjugador].Money.setString(std::to_string(playerInfos[indexjugador].money));

		}

	}
	else if (message.rfind("INVERCIONSEGURA", 0) == 0) {

		std::string data = message.substr(15 + 1);

		std::istringstream iss(data);
		std::string  indexStr, moneyStr;

		if (!(std::getline(iss, indexStr, ':') &&
			std::getline(iss, moneyStr, ':'))
			) {
			return;
		}
		int indext = std::stoi(indexStr);
		playerInfos[indext].money = std::stoi(moneyStr);

		playersGame[indext].Money.setString(std::to_string(playerInfos[indext].money));

	}
	else if (message.rfind("TODOSPIERDEN:", 0) == 0) {
		std::string data = message.substr(13);

		std::vector<std::string> tokens;
		size_t start = 0;
		size_t end = data.find(':');
		while (end != std::string::npos) {
			tokens.push_back(data.substr(start, end - start));
			start = end + 1;
			end = data.find(':', start);
		}

		for (size_t i = 0; i < tokens.size(); i += 2) {
			if (i + 1 < tokens.size()) { // Asegurarse de que hay un par índice/dinero
				int indexjugador = std::stoi(tokens[i]);
				int moneyAmount = std::stoi(tokens[i + 1]);


				playerInfos[indexjugador].money = moneyAmount;
				playersGame[indexjugador].Money.setString(std::to_string(playerInfos[indexjugador].money));

			}
		}
	}
	else if (message.rfind("PLAYER_INDEX:", 0) == 0) {

		playerIndex = std::stoi(message.substr(std::string("PLAYER_INDEX:").length()));
		clientData->agregardor = true;

		PlayerInfo playerInfoNew;
		PlayerGame playerGameNew;
		playerInfoNew.username = nameUser;
		playerInfoNew.PiecUserme = true;
		playerGameNew.NamePlayer.setCharacterSize(17);
		playerGameNew.NamePlayer.setFont(fontUserPerfil);
		playerGameNew.NamePlayer.setFillColor(sf::Color::White);
		playerGameNew.NamePlayer.setOutlineThickness(2);
		playerGameNew.NamePlayer.setOutlineColor(sf::Color(135, 135, 135));
		playerGameNew.NamePlayer.setString(playerInfoNew.username);
		playerGameNew.CashSprite.setTexture(TextureCash);
		playerGameNew.Home.setTexture(TextureHome);
		globalBounds = playerGameNew.NamePlayer.getGlobalBounds();
		playerGameNew.NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
		playerGameNew.Check.setTexture(CheckTexturesOff);
		playerGameNew.Check.setOrigin(50.0f, 46.5f);
		playerGameNew.boxPlayer.setTexture(textureBoxPerfil);
		playerGameNew.boxPlayer.setOrigin(125, 40);
		playerGameNew.boxPlayer.setScale(0.9f, 0.9f);
		playersGame.push_back(playerGameNew);
		playerInfos.push_back(playerInfoNew);
		UsuariosActivos.insert(UsuariosActivos.begin(), playerIndex);


	}
	else if (message.rfind("NEW_PLAYER:", 0) == 0) {

		std::istringstream iss(message.substr(11));
		std::string username, indexStr, moneyStr, isSelectingStr, isInGameStr;// , isimageStr;

		if (!(std::getline(iss, username, ':') &&
			std::getline(iss, indexStr, ':') &&
			std::getline(iss, moneyStr, ':') &&
			std::getline(iss, isSelectingStr, ':') &&
			std::getline(iss, isInGameStr, ':') //&&
			//std::getline(iss, isimageStr, ':')
			)
			) {

			return;

		}

		int index = std::stoi(indexStr);
		PlayerInfo playerInfoNew;
		PlayerGame playerGameNew;


		//playerInfoNew.image = isimageStr;
		playerGameNew.NamePlayer.setCharacterSize(17);
		playerGameNew.NamePlayer.setFont(fontUserPerfil);
		playerGameNew.NamePlayer.setFillColor(sf::Color::White);
		playerGameNew.NamePlayer.setOutlineThickness(2);
		playerGameNew.NamePlayer.setOutlineColor(sf::Color(135, 135, 135));
		playerInfoNew.username = username;
		playerGameNew.CashSprite.setTexture(TextureCash);
		playerGameNew.Home.setTexture(TextureHome);
		playerInfoNew.money = std::stoi(moneyStr);
		playerInfoNew.isSelectingPiece = (isSelectingStr == "true");
		playerInfoNew.isInGame = (isInGameStr == "true");
		//playerGameNew.textureAvatarPLayer.loadFromFile(playerInfoNew.image);
		playerGameNew.NamePlayer.setString(playerInfoNew.username);
		globalBounds = playerGameNew.NamePlayer.getGlobalBounds();
		playerGameNew.NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
		playerGameNew.Check.setTexture(CheckTexturesOff);
		playerGameNew.Check.setOrigin(50.0f, 46.5f);
		playerGameNew.boxPlayer.setTexture(textureBoxPerfil);
		playerGameNew.boxPlayer.setOrigin(125, 40);
		playerGameNew.boxPlayer.setScale(0.9f, 0.9f);
		playersGame.push_back(playerGameNew);
		playerInfos.push_back(playerInfoNew);
		UsuariosActivos.push_back(index);
	}
	else if (message.rfind("EXISTING_PLAYER:", 0) == 0) {

		std::string data = message.substr(16);
		std::istringstream iss(data);
		std::string username, indexStr, moneyStr, isSelectingStr, isInGameStr, indexPieceStr;// imagePath,;

		if (!(std::getline(iss, username, ':') &&
			std::getline(iss, indexStr, ':') &&
			std::getline(iss, moneyStr, ':') &&
			std::getline(iss, isSelectingStr, ':') &&
			std::getline(iss, isInGameStr, ':') &&
			//std::getline(iss, imagePath, ':') &&
			std::getline(iss, indexPieceStr))
			) {
			return;
		}

		int index = std::stoi(indexStr);

		std::unique_lock<std::mutex> lock(clientData->mtxExisting);
		PlayerInfo playerInfoNew;
		PlayerGame playerGameNew;
		playerGameNew.NamePlayer.setCharacterSize(17);
		playerGameNew.NamePlayer.setFont(fontUserPerfil);
		playerGameNew.NamePlayer.setFillColor(sf::Color::White);
		playerGameNew.NamePlayer.setOutlineThickness(2);
		playerGameNew.NamePlayer.setOutlineColor(sf::Color(135, 135, 135));
		playerInfoNew.username = username;
		playerInfoNew.money = std::stoi(moneyStr);
		playerInfoNew.isSelectingPiece = (isSelectingStr == "true");
		playerInfoNew.isInGame = (isInGameStr == "true");
	//	playerInfoNew.image = imagePath;
		int indexPiece = std::stoi(indexPieceStr);
		playerGameNew.CashSprite.setTexture(TextureCash);
		playerGameNew.Home.setTexture(TextureHome);
		playerGameNew.Check.setTexture(CheckTexturesOff);
		playerGameNew.Check.setOrigin(50.0f, 46.5f);
	//	playerGameNew.textureAvatarPLayer.loadFromFile(playerInfoNew.image);
		playerGameNew.NamePlayer.setString(playerInfoNew.username);
		globalBounds = playerGameNew.NamePlayer.getGlobalBounds();
		playerGameNew.NamePlayer.setOrigin(globalBounds.width / 2.0f, globalBounds.height / 2.0f);
		playerGameNew.boxPlayer.setTexture(textureBoxPerfil);
		playerGameNew.boxPlayer.setOrigin(125, 40);
		playerGameNew.boxPlayer.setScale(0.9f, 0.9f);
		playerInfos.push_back(playerInfoNew);
		playersGame.push_back(playerGameNew);
		UsuariosActivos.push_back(index);

		if (indexPiece >= 0) {

			std::cout << "\n pieza:" << indexPiece << " CplayerIndex:" << CplayerIndex;
			playerInfos[index].indexPiece = indexPiece;
			int newPieceIndex = playerInfos[index].indexPiece;

			pieces[previousSelectionIndex[index]].setColor(sf::Color::White); // Color original
			pieces[newPieceIndex].setColor(sf::Color(248, 134, 255)); // Resaltar la nueva pieza
			std::cout << "\nplayersGame" << playersGame.size();
			// Actualizar el sprite del jugador con la nueva textura de la pieza seleccionada
			playersGame[index].PieceSelect.setTexture(piecesTextures[newPieceIndex], true);
			playersGame[index].PieceSelect.setScale(pieces[newPieceIndex].getScale());
			playersGame[index].PieceSelect.setOrigin(pieces[newPieceIndex].getOrigin());
			playersGame[index].PieceSelect.setColor(sf::Color::White); // Asegurar el color correcto
			previousSelectionIndex[index] = newPieceIndex;
			CplayerIndex = -1;


		}


	}
	else if (message.rfind("PLAYER_COUNT:", 0) == 0) {

		NumPlayers = std::stoi(message.substr(13));

	}
	else if (message.rfind("XCASA:", 0) == 0) {

		accionCompra = true;

	}
	else if (message.rfind("SMG", 0) == 0) {

		int num = message[3] - '0';
		std::string rest = message.substr(4);  //
		PlantillaMensajeR.SMSEnviado.setString(rest);
		PlantillaMensajeR.AvatarEnviado.setTexture(&playersGame[num].textureAvatarPLayer);
		int In = calcularNumeroDeLineas(PlantillaMensajeR.SMSEnviado) + 1;
		clientData->Nmsg = true;
		if (In == 1) {
			sf::FloatRect altura = PlantillaMensajeR.SMSEnviado.getGlobalBounds();

			PlantillaMensajeR.ContenidoEnviado.setSize(sf::Vector2f(altura.width + 20, 40));
			PlantillaMensajeR.ContenidoEnviado.setPosition(970, 600);
			PlantillaMensajeR.SMSEnviado.setPosition(970 + 10, 618);
			PlantillaMensajeR.AvatarEnviado.setPosition(920, 600);
			PlantillaMensajeR.NombreChat.setPosition(925, 618);
			PlantillaMensajeR.positionContenidoEnviado = PlantillaMensajeR.ContenidoEnviado.getPosition();;
			PlantillaMensajeR.positionSMSEnviado = PlantillaMensajeR.SMSEnviado.getPosition();
			PlantillaMensajeR.positionAvatarEnviado = PlantillaMensajeR.AvatarEnviado.getPosition();
			PlantillaMensajeR.positionNombreChat = PlantillaMensajeR.NombreChat.getPosition();

		}

		else if (In > 1) {

			sf::FloatRect altura = PlantillaMensajeR.SMSEnviado.getGlobalBounds();
			PlantillaMensajeR.AvatarEnviado.setPosition(920, 600);
			PlantillaMensajeR.ContenidoEnviado.setSize(sf::Vector2f(altura.width + 20, altura.height + 22));
			PlantillaMensajeR.ContenidoEnviado.setPosition(sf::Vector2f(970, 640 - PlantillaMensajeR.ContenidoEnviado.getGlobalBounds().height));
			PlantillaMensajeR.SMSEnviado.setPosition(sf::Vector2f(970 + 10, PlantillaMensajeR.ContenidoEnviado.getPosition().y + 18));
			PlantillaMensajeR.NombreChat.setPosition(sf::Vector2f(9525 + 10, PlantillaMensajeR.NombreChat.getPosition().y + 18));
			PlantillaMensajeR.positionContenidoEnviado = PlantillaMensajeR.ContenidoEnviado.getPosition();
			PlantillaMensajeR.positionSMSEnviado = PlantillaMensajeR.SMSEnviado.getPosition();
			PlantillaMensajeR.positionAvatarEnviado = PlantillaMensajeR.AvatarEnviado.getPosition();
			PlantillaMensajeR.positionNombreChat = PlantillaMensajeR.NombreChat.getPosition();
		}

		PlantillaMensajeR.positionContenidoEnviado = PlantillaMensajeR.ContenidoEnviado.getPosition();
		PlantillaMensajeR.positionSMSEnviado = PlantillaMensajeR.SMSEnviado.getPosition();

		Mensajes.push_back(PlantillaMensajeR);
		float aux = PlantillaMensajeR.ContenidoEnviado.getGlobalBounds().height;

		aux += 20;

		for (int i = 0; i < Mensajes.size() - 1; i++)
		{
			Mensajes[i].ContenidoEnviado.setPosition(Mensajes[i].ContenidoEnviado.getPosition().x, Mensajes[i].ContenidoEnviado.getPosition().y - aux);
			Mensajes[i].AvatarEnviado.setPosition(Mensajes[i].AvatarEnviado.getPosition().x, Mensajes[i].AvatarEnviado.getPosition().y - aux);
			Mensajes[i].SMSEnviado.setPosition(Mensajes[i].ContenidoEnviado.getPosition().x + 10, Mensajes[i].ContenidoEnviado.getPosition().y + 20);
			Mensajes[i].positionContenidoEnviado = Mensajes[i].ContenidoEnviado.getPosition();
			Mensajes[i].positionSMSEnviado = Mensajes[i].SMSEnviado.getPosition();
			Mensajes[i].positionAvatarEnviado = Mensajes[i].AvatarEnviado.getPosition();
			Mensajes[i].positionNombreChat = Mensajes[i].NombreChat.getPosition();



		}
	}
	else if (message.rfind("PLAYER_CHANGED_PIECE:", 0) == 0) {

		size_t firstColon = message.find(":", 20);
		size_t secondColon = message.find(":", firstColon + 1);

		int Index = std::stoi(message.substr(firstColon + 1, secondColon - firstColon - 1));
		playerInfos[Index].indexPiece = std::stoi(message.substr(secondColon + 1));
		CplayerIndex = Index;


	}
	else if (message.rfind("PLAYER_READY:", 0) == 0) {

		int indexPlayer = std::stoi(message.substr(13));

		playerInfos[indexPlayer].isSelectingPiece = true;

	}
	else if (message.rfind("START_GAME", 0) == 0) {

		size_t casasPos = message.find("Casas:");
		if (casasPos != std::string::npos) {

			std::string casasData = message.substr(casasPos + 6);

			std::istringstream iss(casasData);
			std::string palabra;
			std::vector<std::vector<int>> casasPorJugador;
			std::vector<int> indicesJugadores;

			while (iss >> palabra) {
				if (palabra == "Jugador") {

					int jugadorIndex;
					iss >> jugadorIndex;
					indicesJugadores.push_back(jugadorIndex);
					iss.ignore(256, ':');
					casasPorJugador.emplace_back();

				}
				else {
					try {
						int casa = std::stoi(palabra);
						casasPorJugador.back().push_back(casa);
					}
					catch (...) {

					}
				}

			}

			for (size_t i = 0; i < indicesJugadores.size(); ++i) {

				for (int j = 0; j < 17; ++j) {
					playerInfos[i].casasPorJugador[j] = casasPorJugador[i][j];
				}

			}

			{
				std::lock_guard<std::mutex> lock(clientData->casasMutex);
				clientData->casasCargadas = true;
			}
			clientData->cv.notify_one();

		}

	}
	else if (message.rfind("ROBARPLAYER:", 0) == 0) {
		std::string datos = message.substr(12);
		std::stringstream ss(datos);
		std::string token;

		while (true) {
			std::string indiceStr, dineroStr;

			if (!std::getline(ss, indiceStr, ':')) break;
			if (!std::getline(ss, dineroStr, ':')) break;

			try {
				int indice = std::stoi(indiceStr);
				int dinero = std::stoi(dineroStr);

				playerInfos[indice].money = dinero;
				playersGame[indice].Money.setString(std::to_string(dinero));
			}
			catch (const std::exception& e) {
				std::cerr << "Error al convertir valores: " << e.what() << std::endl;
			}
		}
	}
	else if (message.rfind("EVENTOCASA", 0) == 0) {
		userCasa = true;
	}
	else if (message.rfind("EVENTOIMPUEST", 0) == 0) {

		std::string data = message.substr(15);
		std::istringstream iss(data);
		std::string impuesto, indexStr, moneyStr;

		if (!(std::getline(iss, impuesto, ':') &&
			std::getline(iss, indexStr, ':') &&
			std::getline(iss, moneyStr, ':'))
			) {
			return;
		}
		int indext = std::stoi(indexStr);
		playerInfos[indext].money = std::stoi(moneyStr);
		playerInfos[indext].impuesto = std::stoi(impuesto);

		playersGame[indext].Money.setString(std::to_string(playerInfos[indext].money));
		{
			std::lock_guard<std::mutex> lock(clientData->impuestoMutex);
			if (IndexTurn != playerIndex) {
				userImpuesto = true;

			}
			clientData->impuestoMessageReceived = true;
		}

		clientData->impuestoCondVar.notify_one();

	}
	else if (message.rfind("EVENTORULETA", 0) == 0) {

		userRuleta = true;

	}
	else if (message.rfind("JUEGOTERMINADO", 0) == 0) {

		juegoTerminado = true;

	}
	else if (message.rfind("image0;", 0) == 0) {

		std::stringstream ss(message);
		std::vector<std::string> partes;
		std::string item;

		while (std::getline(ss, item, ';')) {
			partes.push_back(item);
		}

		// Validar que el mensaje tenga el formato esperado
		if (partes.size() >= 3) {
			std::string tipo = partes[0];   // "image0"
			int idUsuario = std::stoi(partes[1]); // Convertir ID a entero
			std::string ruta = partes[2];   // Ruta de la imagen

			playerInfos[idUsuario].image = ruta;
			playersGame[idUsuario].textureAvatarPLayer.loadFromFile(playerInfos[idUsuario].image);

		}
	}

	else if (message.rfind("image1;", 0) == 0) { // Verifica si comienza con "image;"
		// Buscar los delimitadores `;`
		size_t pos1 = message.find(";");
		size_t pos2 = message.find(";", pos1 + 1);

		if (pos1 == std::string::npos || pos2 == std::string::npos) {
			std::cerr << "Paquete mal formado\n";
			return;
		}

		// Extraer el identificador del jugador
		int jugadorID;
		try {
			jugadorID = std::stoi(message.substr(pos1 + 1, pos2 - pos1 - 1));
		}
		catch (...) {
			std::cerr << "Error al convertir el ID del jugador\n";
			return;
		}

		// Extraer los datos binarios de la imagen después del segundo ';'
		size_t datosInicio = pos2 + 1;
		if (datosInicio >= preprocces->dataLength) {
			std::cerr << "Paquete sin datos de imagen\n";
			return;
		}

		std::vector<uint8_t> datos(preprocces->data + datosInicio, preprocces->data + preprocces->dataLength);
		std::string filename = "avatar_" + std::to_string(jugadorID) + ".png";
		// Guardar la imagen con el identificador del jugador
		std::ofstream archivo(filename, std::ios::binary);
		if (!archivo) {
			std::cerr << "No se pudo guardar la imagen\n";
			return;
		}
		archivo.write(reinterpret_cast<const char*>(datos.data()), datos.size());
		archivo.close();
		// 2?? Cargar la imagen en SFML
		sf::Image imagen;
		if (!imagen.loadFromFile(filename)) {
			std::cerr << "Error al cargar la imagen en SFML\n";
			return;
		}

		// 3?? Cargar la imagen en una textura SFML

		playerInfos[jugadorID].image = filename;
		playersGame[jugadorID].textureAvatarPLayer.loadFromFile(playerInfos[jugadorID].image);


	

	}
	else if (message.rfind("PLAYER_DISCONNECTED", 0) == 0) {

		clientData->disconnecte = true;

		while (!clientData->disActiv) {
		}

		{
			std::lock_guard<std::mutex> lock(clientData->mtex);
			int index = std::stoi(message.substr(20));

			if (playerIndex == 0) {

				UsuariosActivos.erase(UsuariosActivos.begin() + index);
				for (int i = index; i < UsuariosActivos.size(); i++) {


					UsuariosActivos[i] -= 1;

				}
			}
			else if (playerIndex >= index) {

				UsuariosActivos.erase(UsuariosActivos.begin() + (index + 1));
				for (int i = index; i < UsuariosActivos.size(); i++) {


					UsuariosActivos[i] -= 1;

				}
				playerIndex -= 1;
			}
			else if (playerIndex < index) {
				UsuariosActivos.erase(UsuariosActivos.begin() + index);
				for (int i = index; i < UsuariosActivos.size(); i++) {


					UsuariosActivos[i] -= 1;

				}
			}

			playerInfos.erase(playerInfos.begin() + index);
			playersGame.erase(playersGame.begin() + index);



			for (int i = 0; i < UsuariosActivos.size(); i++) {


			}
			clientData->eventOccurred = true;
		}
		clientData->cvDis.notify_one(); // Notifica al hilo principal que puede continuar.





	}

}