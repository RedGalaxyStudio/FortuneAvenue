#include <SFML/Graphics.hpp>
#include "IniciaUser.hpp"
#include "../ui/TextBox.hpp"
#include <SFML/Audio.hpp>
#include "../ui/Scrollbar.hpp"
#include <string>
#include "../core/ResourceGlobal.hpp"
#include "../core/ObjetosGlobal.hpp"
#include <fstream>
#include "../../libs/nlohmann/json.hpp"
#include <windows.h>
#include <commdlg.h>
using json = nlohmann::json;


std::string wideToString(const std::wstring& wideStr) {
	int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	if (sizeNeeded <= 0) return "";

	std::string str(sizeNeeded - 1, 0);
	WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, &str[0], sizeNeeded, nullptr, nullptr);
	return str;
}

// Abre un cuadro de diálogo para seleccionar un archivo
std::string openFileDialog() {
	wchar_t filename[MAX_PATH] = L"";
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L"Imágenes\0*.png;*.jpg;*.jpeg;*.bmp;*.tga\0Todos los archivos\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

	if (GetOpenFileName(&ofn)) {
		return wideToString(filename);
	}
	return "";
}




IniciaUser::IniciaUser(sf::RenderWindow& windowRef)
	: window(&windowRef), currentIndex(0) {
	Resource();
	loadAvatars();
}
IniciaUser::~IniciaUser() {
}
void IniciaUser::Resource() {
	SpriteFondoMenu.setTexture(TextureFondoMenu);
}
void IniciaUser::Update() {

	if (!std::filesystem::exists("perfil.json")) {
		if (!ckeck.loadFromFile("assets/image/Avatars/cheeke2.png")) return;
		spriteCkeck.setTexture(ckeck);
		if (!TextureFondoMenuAvar.loadFromFile("assets/image/Fondos/fondomenuAvar.png")) return;
		SpriteFondoMenuAvar.setTexture(TextureFondoMenuAvar);
		loadAvatars();
		IniciAcion();
	}
	else {
		loadSelectedAvatar();
	}

}

void IniciaUser::UpdateEdit() {


	if (!ckeck.loadFromFile("assets/image/Avatars/cheeke2.png")) return;
	spriteCkeck.setTexture(ckeck);
	if (!TextureFondoMenuAvar.loadFromFile("assets/image/Fondos/fondomenuAvar.png")) return;
	SpriteFondoMenuAvar.setTexture(TextureFondoMenuAvar);
	loadAvatars();

	selectedAvatar = &selectedAvatarCopy;
	// selectedAvatar = nullptr;
	IniciAcion();



}
void IniciaUser::IniciAcion() {
	spriteCkeck.setPosition(850, 70);


	float baseXPos = 92.0f;
	float baseYPos = 472.0f;



	float deltaScroll = 0.0f;
	float scrollStep = 10.0f; // Para el desplazamiento con las teclas
	const float avatarWidth = 128.0f;
	const float avatarHeight = 128.0f;
	const float avatarSeparation = 28.0f;
	const float visibleAreaHeight = 248.0f;
	const float maxScrollOffset = 156.0f;

	float widthSeparation = avatarWidth + avatarSeparation;
	float heightSeparation = avatarHeight + avatarSeparation;

	recua.setPosition(400, 112);
	TextBox textBox(496, 50, "Ingresa tu nombre: ");
	textBox.setPosition(496, 50);

	const float totalContentHeight = 440.0f;
	const float scrollbarHeight = 340.0f;


	float proportion = visibleAreaHeight / totalContentHeight;
	float thumbHeight = scrollbarHeight * proportion;


	const float minThumbHeight = 14.0f;
	thumbHeight = std::max(thumbHeight, minThumbHeight);


	Scrollbar scrollbar(340, thumbHeight, 14);

	scrollbar.setPosition(1260, 340);



	selectedAvatarCopy.setPosition(400, 112);
	for (int i = 0; i < avatars.size(); i++) {
		sf::Vector2f pos = avatars[i].getPosition();

	}
	float avatarYOffset = 0.0f;
	bool salir = false;



	std::vector<sf::CircleShape> circles;
	std::vector<sf::Color> colors = {
		sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow,
		sf::Color::Magenta, sf::Color::Cyan, sf::Color(255, 165, 0), // Naranja
		sf::Color(128, 0, 128), // Púrpura
		sf::Color(139, 69, 19), // Marrón
		sf::Color(255, 192, 203) // Rosa
	};

	for (size_t i = 0; i < 10; ++i) {
		sf::CircleShape circle(30);
		circle.setFillColor(colors[i]);
		circle.setPosition(20 + i * 120, 300); // Distribuidos horizontalmente
		circles.push_back(circle);
	}

	sf::Color selectedBackgroundColor = sf::Color::White; // Color por defecto

	sf::Texture tempTexture;

	sf::Image croppedImage;
	bool hasTransparency = false;

	sf::Image imageWithBackground;
	sf::CircleShape colores=selectedAvatarCopy;
	colores.setFillColor(sf::Color::Transparent);

	while (window->isOpen() && !salir) {
		mousePosition = sf::Mouse::getPosition(*window);
		mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

		sf::Event event;
		while (window->pollEvent(event)) {

			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				renderTexture.clear(sf::Color::Transparent);
				renderTexture.draw(SpriteFondoMenu);
				for (int i = 0; i < avatars.size(); ++i) {
					renderTexture.draw(avatars[i]);
				}
				renderTexture.draw(SpriteFondoMenuAvar);
				if (selectedAvatar != nullptr) {
					renderTexture.draw(selectedAvatarCopy);
				}
				textBox.Prinf();

				scrollbar.Prinft();
				renderTexture.draw(recua);
				renderTexture.draw(spriteCkeck);
				renderTexture.draw(overlay);
				renderTexture.display();
				Menup.MenuSalir(nullptr);
			}

			scrollbar.handleEvent(event, *window);
			avatarYOffset = scrollbar.getScrollOffset();
			// scrollbar.evento(event);
			if (event.type == sf::Event::MouseWheelScrolled) {

				scrollbar.update(event.mouseWheelScroll.delta);
				avatarYOffset = scrollbar.getScrollOffset();

			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Down) {
					deltaScroll = 1.0f; // Desplazamiento hacia abajo
					scrollbar.update(deltaScroll);
					avatarYOffset = scrollbar.getScrollOffset();
				}
				else if (event.key.code == sf::Keyboard::Up) {
					deltaScroll = -1.0f; // Desplazamiento hacia arriba
					scrollbar.update(deltaScroll);
					avatarYOffset = scrollbar.getScrollOffset();
				}
			}


			if (avatarYOffset > maxScrollOffset) {
				avatarYOffset = maxScrollOffset;
			}
			else if (avatarYOffset < 0) {
				avatarYOffset = 0;
			}

			if (avatarYOffset != 0) {
				std::vector<sf::FloatRect> avatarBounds(avatars.size());
				for (int i = 0; i < avatars.size(); ++i) {
					int column = i % 8;
					int row = i / 8;

					float xPos = baseXPos + column * widthSeparation;

					float yPos = (baseYPos + row * heightSeparation) - avatarYOffset;

					avatarBounds[i] = sf::FloatRect(xPos, yPos, avatars[i].getGlobalBounds().width, avatars[i].getGlobalBounds().height);

					avatars[i].setPosition(xPos, yPos);

				}
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

				if (spriteCkeck.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					saveSelectedAvatar();
					salir = true;
				}
				sf::CircleShape* newSelection = nullptr;

				// Verificar si se selecciona un color
				for (int i = 0; i < circles.size(); ++i) {
					if (circles[i].getGlobalBounds().contains(mousePosFloat)) {
						selectedBackgroundColor = colors[i];
						colores.setFillColor(selectedBackgroundColor);

						/*if (hasTransparency) {


							sf::RenderTexture renderTexturo;

							if (!renderTexturo.create(128, 128)) {
								std::cerr << " Error al crear RenderTexture\n";
								return;
							}
							
							sf::Sprite sprite(tempTexture);

							// Dibujar la imagen escalada en el RenderTexture
							renderTexturo.clear(selectedBackgroundColor);
							renderTexturo.draw(sprite);
							renderTexturo.display();


							croppedImage = renderTexturo.getTexture().copyToImage();

							croppedImage.saveToFile("temp_crop_filled.png");
							std::cout << "HOLa";
							textselectedAvatarCopy.loadFromFile("temp_crop_filled.png");
							// Guardar y cargar la textura recortada

							// Crear el CircleShape con la textura
							newSelection = new sf::CircleShape(64);
							newSelection->setTexture(&textselectedAvatarCopy);

						}
						selectedAvatarCopy.setTexture(&textselectedAvatarCopy);*/
					}
				}

				for (int i = 0; i < avatars.size(); ++i) {

					if (avatars[i].getGlobalBounds().contains(mousePosFloat)) {
						if (i == 0) {

							std::string imagePath = openFileDialog();
							if (imagePath.empty()) {
								std::cout << "No se seleccionó ninguna imagen.\n";
								return;
							}

							sf::Image originalImage;
							if (!originalImage.loadFromFile(imagePath)) {
								std::cerr << "Error al cargar la imagen\n";
								return;
							}






							sf::Vector2u imgSize = originalImage.getSize();
							
							
							sf::RenderTexture renderTexturo;
							// Si la imagen es cuadrada, solo escalar
							if (imgSize.x == imgSize.y) {
								
								if (!renderTexturo.create(128, 128)) {
									std::cerr << " Error al crear RenderTexture\n";
									return;
								}
								
								tempTexture.loadFromImage(originalImage);
								sf::Sprite sprite(tempTexture);
								
								// Escalar la imagen para que encaje en 128x128 sin deformarse
								float scale = std::min(128.f / imgSize.x, 128.f / imgSize.y);
								sprite.setScale(scale, scale);

								// Centrar la imagen en caso de que sea más pequeña que 128x128
								sf::Vector2f newSize(imgSize.x * scale, imgSize.y * scale);
								sprite.setPosition((128 - newSize.x) / 2, (128 - newSize.y) / 2);

								// Dibujar la imagen escalada en el RenderTexture
								renderTexturo.clear(sf::Color::Transparent);
								renderTexturo.draw(sprite);
								renderTexturo.display();


							}
							else {
								// Si no es cuadrada, permitir al usuario elegir una región
								sf::RenderWindow window(sf::VideoMode(400, 400), "Selecciona el área");

								sf::Texture tempTexture;
								tempTexture.loadFromImage(originalImage);
								sf::Sprite sprite(tempTexture);

								// Aquí puedes permitir que el usuario seleccione una región
								sf::IntRect selectedRegion(0, 0, 128, 128);

								while (window.isOpen()) {
									sf::Event event;
									while (window.pollEvent(event)) {
										if (event.type == sf::Event::Closed) {
											window.close();
										}
										// Aquí podrías agregar lógica para permitir al usuario mover la selección
									}

									window.clear();
									window.draw(sprite);
									// Dibujar la selección con un rectángulo de 128x128
									sf::RectangleShape selectionBox(sf::Vector2f(128, 128));
									selectionBox.setPosition(selectedRegion.left, selectedRegion.top);
									selectionBox.setFillColor(sf::Color(255, 255, 255, 50)); // Transparente
									selectionBox.setOutlineThickness(2);
									selectionBox.setOutlineColor(sf::Color::Red);
									window.draw(selectionBox);

									window.display();
								}

								// Recortar la imagen
							
								croppedImage.create(128, 128);
								croppedImage.copy(originalImage, 0, 0, selectedRegion);

								// Guardar y cargar la textura recortada
								croppedImage.saveToFile("temp_crop.png");
								textselectedAvatarCopy.loadFromFile("temp_crop.png");

								newSelection = new sf::CircleShape(64);
								newSelection->setTexture(&textselectedAvatarCopy);
							}


							croppedImage = renderTexturo.getTexture().copyToImage();

							if (croppedImage.getSize().x == 0 || croppedImage.getSize().y == 0) {
								std::cerr << " Error: La imagen final está vacía.\n";
								return;
							}


							sf::Image imageWithBackground = croppedImage;

							for (unsigned int y = 0; y < imageWithBackground.getSize().y; y++) {
								for (unsigned int x = 0; x < imageWithBackground.getSize().x; x++) {
									sf::Color pixelColor = imageWithBackground.getPixel(x, y);
									if (pixelColor.a == 0) {  // Si es transparente
										hasTransparency = true;
									}
								}
							}
							
							croppedImage.saveToFile("temp_crop.png");
							std::cout << "HOLa";
							textselectedAvatarCopy.loadFromFile("temp_crop.png");
							// Guardar y cargar la textura recortada

							// Crear el CircleShape con la textura
							newSelection = new sf::CircleShape(64);
							newSelection->setTexture(&textselectedAvatarCopy);
						}
						else {
							newSelection = &avatars[i];
							break;

						}
					}
				}


				if (spriteX.getGlobalBounds().contains(mousePosFloat)) {
					playClickSound();
					Menup.MenuPrincipal();
				}
				if (newSelection != nullptr) {
					if (newSelection != selectedAvatar) {
						if (selectedAvatar) {
							selectedAvatar->setOutlineColor(sf::Color::Transparent);
							selectedAvatar->setOutlineThickness(0);
						}
						if (newSelection) {
							newSelection->setOutlineColor(sf::Color::Black);
							newSelection->setOutlineThickness(4);
							textselectedAvatarCopy = *newSelection->getTexture();
							selectedAvatarCopy.setTexture(&textselectedAvatarCopy);
						}
						selectedAvatar = newSelection;
					}
				}
			}

			input1 = textBox.handleInput(event, 11);
		}
		window->clear();
		window->draw(SpriteFondoMenu);

		for (int i = 0; i < avatars.size(); ++i) {

			sf::Vector2f pos = avatars[i].getPosition();

			window->draw(avatars[i]);
		}



		window->draw(SpriteFondoMenuAvar);
		

		if (selectedAvatar != nullptr) {
			window->draw(colores);
			window->draw(selectedAvatarCopy);
		}
		textBox.draw(*window);

		scrollbar.draw(*window);
		window->draw(recua);
		window->draw(spriteCkeck);
		for (const auto& circle : circles) {
			window->draw(circle);
		}

		window->display();
	}
}
void IniciaUser::saveSelectedAvatar() {
	if (selectedAvatar != nullptr) {

		int selectedIndex = -1;
		for (int i = 0; i < avatars.size(); ++i) {
			if (&avatars[i] == selectedAvatar) {
				selectedIndex = i;
				break;
			}
		}


		if (selectedIndex != -1) {

			json avatarData;
			avatarData["selected_avatar_path"] = textureAvatarsFilePath[selectedIndex];

			//std::cout << "\ninput1:" << input1;
			avatarData["username"] = input1;


			std::ofstream outFile("perfil.json");


			if (outFile.is_open()) {
				outFile << avatarData.dump(4);
				outFile.close();
			}
		}
	}
}
void IniciaUser::loadSelectedAvatar() {


	std::ifstream inFile("perfil.json");
	if (inFile.is_open()) {
		json avatarData;
		inFile >> avatarData;
		inFile.close();

		TextureAvatarPath = avatarData["selected_avatar_path"];
		input1 = avatarData["username"];


		if (!TextureAvatarSelec.loadFromFile(TextureAvatarPath)) loadAvatars();

		selectedAvatarCopy.setTexture(&TextureAvatarSelec);
	}
}

void IniciaUser::loadAvatars() {

	int avatarCount = 21;
	avatars.resize(avatarCount);
	avatarTextures.resize(avatarCount);
	textureAvatarsFilePath.resize(avatarCount);

	printMemoryUsage();

	for (int i = 0; i < avatarCount; i++) {

		textureAvatarsFilePath[i] = "assets/image/Avatars/avatar" + std::to_string(i) + ".png";

		if (!avatarTextures[i].loadFromFile(textureAvatarsFilePath[i]))
			return;

		float radio = avatarTextures[i].getSize().x / 2.0f;
		avatars[i].setRadius(radio);
		avatars[i].setTexture(&avatarTextures[i]);
		avatars[i].setOrigin(radio, radio);


	}

	for (int i = 0; i < avatars.size(); i++) {
		int row = i / 8;
		int col = i % 8;

		float x = 92.0f + col * 156.0f;
		float y = 472.0f + row * 156.0f;

		avatars[i].setPosition(x, y);
	}
	if (!sharedTexture.loadFromFile("assets/image/Avatars/Vacio.jpg")) return;


	if (selectedAvatarCopy.getTexture() == nullptr) {
		selectedAvatarCopy.setRadius(64);
		selectedAvatarCopy.setTexture(&sharedTexture);
		selectedAvatarCopy.setOrigin(64, 64);
	}


	Texrecua.loadFromFile("assets/image/Avatars/recua.png");
	recua.setTexture(Texrecua);
	recua.setOrigin(65, 65);
}