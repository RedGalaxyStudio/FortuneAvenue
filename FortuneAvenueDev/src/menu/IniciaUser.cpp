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
#ifdef _WIN32
#include <windows.h>
#include <commdlg.h>
#endif
#include <gtk/gtk.h>
#include <filesystem>
#include "../ui/MensageBox.hpp"

using json = nlohmann::json;

sf::RectangleShape createCorner(sf::Color color) {
	sf::RectangleShape corner(sf::Vector2f(10, 10));
	corner.setFillColor(color);
	return corner;
}


std::string wideToString(const std::wstring& wideStr) {

	#ifdef _WIN32
    	int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    	std::string strTo(sizeNeeded, 0);
    	WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, &strTo[0], sizeNeeded, nullptr, nullptr);
    	return strTo;
	#else
    	// En sistemas no Windows, podemos usar std::wstring_convert o métodos alternativos
    	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    	return conv.to_bytes(wideStr);
	#endif
}

// Abre un cuadro de di�logo para seleccionar un archivo
std::string openFileDialog() {
	/*wchar_t filename[MAX_PATH] = L"";
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L"Im�genes\0*.png;*.jpg;*.jpeg;*.bmp;*.tga\0Todos los archivos\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

	if (GetOpenFileName(&ofn)) {
		return wideToString(filename);
	}
	return "";*/ //antigua interfas de dialogo

	    // Inicializar GTK
		gtk_init(NULL, NULL);

		// Crear un cuadro de diálogo de selección de archivo
		GtkWidget *dialog = gtk_file_chooser_dialog_new(
			"Abrir Archivo", NULL,
			GTK_FILE_CHOOSER_ACTION_OPEN,
			"_Cancelar", GTK_RESPONSE_CANCEL,
			"_Abrir", GTK_RESPONSE_ACCEPT,
			NULL
		);
	
		// Establecer el filtro para mostrar solo imágenes
		GtkFileFilter *filter = gtk_file_filter_new();
		gtk_file_filter_add_mime_type(filter, "image/png");
		gtk_file_filter_add_mime_type(filter, "image/jpeg");
		gtk_file_filter_add_mime_type(filter, "image/bmp");
		gtk_file_filter_add_mime_type(filter, "image/tga");
		gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);
	
		// Mostrar el diálogo y esperar la respuesta
		std::string result = "";
		if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
			// Obtener el archivo seleccionado
			char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
			result = std::string(filename);
			g_free(filename); // Liberar memoria
		}
	
		// Cerrar el diálogo
		gtk_widget_destroy(dialog);
	
		// Finalizar GTK
		gtk_main_quit();
	
		return result;
}
IniciaUser::IniciaUser(sf::RenderWindow& windowRef, std::string Grd)
	: window(&windowRef), currentIndex(0), TextGrd(Grd) {
	Resource();
	loadAvatars();
}
IniciaUser::IniciaUser(sf::RenderWindow& windowRef)
	: window(&windowRef), currentIndex(0), TextGrd("") {
	Resource();
	loadAvatars();
}
IniciaUser::~IniciaUser() {
}
void IniciaUser::Resource() {
	projectPath = std::filesystem::current_path().string(); // Guarda la ruta original

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
	selectedAvatar.reset(&selectedAvatarCopy);  // Usar reset() con el puntero crudo
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
	TextBox textBox(496, 50, "Ingresa tu nombre: ", TextGrd);
	textBox.setPosition(496, 50);
	const float totalContentHeight = 440.0f;
	const float scrollbarHeight = 340.0f;
	float proportion = visibleAreaHeight / totalContentHeight;
	float thumbHeight = scrollbarHeight * proportion;
	const float minThumbHeight = 14.0f;
	thumbHeight = std::max(thumbHeight, minThumbHeight);
	Scrollbar scrollbar(340, thumbHeight, 14);
	scrollbar.setPosition(1260, 360);
	selectedAvatarCopy.setPosition(400, 112);
	for (int i = 0; i < avatars.size(); i++) {
		sf::Vector2f pos = avatars[i].getPosition();

	}
	float avatarYOffset = 0.0f;
	bool salir = false;
	std::vector<sf::CircleShape> circles;
	std::vector<sf::Color> colors = {
		sf::Color(255, 182, 193), // Rosa pastel
		sf::Color(152, 251, 152), // Verde pastel
		sf::Color(173, 216, 230), // Azul pastel
		sf::Color(255, 255, 153), // Amarillo pastel
		sf::Color(221, 160, 221), // Magenta/Lila pastel
	sf::Color(175, 238, 238), // Cian pastel
	sf::Color(255, 218, 185), // Naranja pastel
	sf::Color(216, 191, 216), // P�rpura pastel
	sf::Color(205, 133, 63),  // Marr�n claro (Tono pastel)
	sf::Color(240, 128, 128)  // Rojo pastel
	};

	float windowWidth = 1280;  
	size_t numCircles = 10;    
	float circleRadius = 30;  

	float totalWidth = windowWidth - 4 * circleRadius; 
	float spacing = totalWidth / (numCircles - 1);    

	float firstCircleX = (windowWidth - totalWidth) / 2;  
	for (size_t i = 0; i < numCircles; ++i) {
		sf::CircleShape circle(circleRadius);
		circle.setFillColor(colors[i]);  // Colores de los c�rculos

		float posX = firstCircleX + i * spacing;

		circle.setOrigin(circleRadius, circleRadius);  
		circle.setPosition(posX, 300); 

		circles.push_back(circle);
	}



	sf::Color selectedBackgroundColor = sf::Color::White; 
	sf::Texture tempTexture;
	sf::Image croppedImage;
	bool hasTransparency = false;
	sf::Image imageWithBackground;

	colores.setRadius(selectedAvatarCopy.getRadius());
	colores.setFillColor(sf::Color::Transparent);
	colores.setOrigin(selectedAvatarCopy.getOrigin());
	colores.setPosition(selectedAvatarCopy.getPosition());

	sf::Sprite holi;




	sf::RectangleShape marcoFondo, BordeFondo;

	marcoFondo.setSize(sf::Vector2f(1280.f, 400.f));
	marcoFondo.setFillColor(sf::Color(0, 0, 0, 0));
	marcoFondo.setPosition(0, 310);
	BordeFondo.setSize(sf::Vector2f(1280.f, 370.f));
	BordeFondo.setFillColor(sf::Color(0, 0, 0, 0));
	//	BordeFondo.setOutlineColor(sf::Color(0, 0, 0,200));
		//BordeFondo.setOutlineThickness(-22);
	BordeFondo.setPosition(0 - 2, 358);





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
					deltaScroll = 1.0f; 
					scrollbar.update(deltaScroll);
					avatarYOffset = scrollbar.getScrollOffset();
				}
				else if (event.key.code == sf::Keyboard::Up) {
					deltaScroll = -1.0f; 
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
				for (int i = 0; i < circles.size(); i++) {
					if (circles[i].getGlobalBounds().contains(mousePosFloat)) {

						colores.setFillColor(circles[i].getFillColor());
					}
				}
				if (spriteCkeck.getGlobalBounds().contains(mousePosFloat) && (selectedAvatar != nullptr) && (input1 != "")) {
					playClickSound();
					saveSelectedAvatar();
					salir = true;
				}
				sf::CircleShape* newSelection = nullptr;

				for (int i = 0; i < avatars.size(); ++i) {

					if (avatars[i].getGlobalBounds().contains(mousePosFloat)) {
						if (i == 0) {

							imagePath = openFileDialog();
							std::filesystem::current_path(projectPath);

							if (!originalImage.loadFromFile(imagePath)) {
								std::cerr << "Error al cargar la imagen\n";

							}

							sf::Vector2u imgSize = originalImage.getSize();


							sf::RenderTexture renderTexturo;
							// Si la imagen es cuadrada, solo escalar
							if (imgSize.x == imgSize.y) {

								if (!renderTexturo.create(128, 128)) {
									std::cerr << " Error al crear RenderTexture\n";
								}

								tempTexture.loadFromImage(originalImage);
								sf::Sprite sprite(tempTexture);

								float scale = std::min(128.f / imgSize.x, 128.f / imgSize.y);
								sprite.setScale(scale, scale);
								sf::Vector2f newSize(imgSize.x * scale, imgSize.y * scale);
								sprite.setPosition((128 - newSize.x) / 2, (128 - newSize.y) / 2);

								renderTexturo.clear(sf::Color::Transparent);
								renderTexturo.draw(sprite);
								renderTexturo.display();


							}
							else {
								if (!renderTexturo.create(128, 128)) {
									std::cerr << " Error al crear RenderTexture\n";
									//	return;
								}


								tempTexture = fun();

								sf::Vector2u imgSize = tempTexture.getSize();

								sf::Sprite sprite(tempTexture);

								float scale = std::min(128.f / imgSize.x, 128.f / imgSize.y);
								sprite.setScale(scale, scale);

								sf::Vector2f newSize(imgSize.x * scale, imgSize.y * scale);
								sprite.setPosition((128 - newSize.x) / 2, (128 - newSize.y) / 2);

								renderTexturo.clear(sf::Color::Transparent);
								renderTexturo.draw(sprite);
								renderTexturo.display();
							}


							croppedImage = renderTexturo.getTexture().copyToImage();

							if (croppedImage.getSize().x == 0 || croppedImage.getSize().y == 0) {
								std::cerr << " Error: La imagen final est� vac�a.\n";
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

							std::filesystem::current_path(projectPath);
							std::string dirPath = projectPath + "/assets/image/Avatars/personal/temp_crop.png";
							croppedImage.saveToFile(dirPath);

							textselectedAvatarCopy.loadFromFile("assets/image/Avatars/personal/temp_crop.png");
							newSelection = new sf::CircleShape(64);
							newSelection->setTexture(&textselectedAvatarCopy);
							selectedIndex = 0;
						}

						else {
							selectedIndex = i;
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
					if (newSelection != selectedAvatar.get()) {
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
						selectedAvatar.reset(newSelection);  // Asume que 'selectedAvatarCopy' es un puntero crudo
					}
				}
			}

			input1 = textBox.handleInput(event, 11);
		}
		window->clear();
		window->draw(SpriteFondoMenu);
		window->draw(marcoFondo);

		for (int i = 0; i < avatars.size(); ++i) {

			sf::Vector2f pos = avatars[i].getPosition();

			window->draw(avatars[i]);
		}



		window->draw(SpriteFondoMenuAvar);
		window->draw(BordeFondo);


		if (selectedAvatar != nullptr) {
			window->draw(colores);
			window->draw(selectedAvatarCopy);
		}
		textBox.draw(*window);

		scrollbar.draw(*window);
		window->draw(recua);
		window->draw(spriteCkeck);
		window->draw(holi);
		for (const auto& circle : circles) {
			window->draw(circle);
		}

		window->display();
	}
}
void IniciaUser::saveSelectedAvatar() {
	std::filesystem::current_path(projectPath);

	if (selectedAvatar != nullptr) {

		if (selectedIndex != -1) {

			json avatarData;
			if (selectedIndex == 0) {

				sf::RenderTexture renderTexturo;

				if (!renderTexturo.create(128, 128)) {
					std::cerr << " Error al crear RenderTexture\n";
				}
				sf::RectangleShape spo;
				spo.setFillColor(colores.getFillColor());
				spo.setSize(sf::Vector2f(128.f, 128.f));
				sf::Texture tempTexture;
				tempTexture.loadFromFile("assets/image/Avatars/personal/temp_crop.png");
				sf::Sprite sprite(tempTexture);
				renderTexturo.clear(colores.getFillColor());
				renderTexturo.draw(spo);
				renderTexturo.draw(sprite);
				renderTexturo.display();

				sf::Image croppedImage = renderTexturo.getTexture().copyToImage();

				std::filesystem::current_path(projectPath);
				std::string dirPath = projectPath + "/assets/image/Avatars/personal/temp_crop.png";
				croppedImage.saveToFile(dirPath);
				textselectedAvatarCopy.loadFromFile("assets/image/Avatars/personal/temp_crop.png");
				sf::CircleShape* newSelection;
				newSelection = new sf::CircleShape(64);
				newSelection->setTexture(&textselectedAvatarCopy);
				textselectedAvatarCopy = *newSelection->getTexture();
				selectedAvatarCopy.setTexture(&textselectedAvatarCopy);
				avatarData["selected_avatar_path"] = "assets/image/Avatars/personal/temp_crop.png";
				TextureAvatarPath = "assets/image/Avatars/personal/temp_crop.png";
			}
			else {

				avatarData["selected_avatar_path"] = textureAvatarsFilePath[selectedIndex];
				TextureAvatarPath = textureAvatarsFilePath[selectedIndex];
			}

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

		if (!TextureAvatarSelec.loadFromFile(TextureAvatarPath)) std::cout << "error";

		selectedAvatarCopy.setTexture(&TextureAvatarSelec);
	}
}
void IniciaUser::loadAvatars() {

	int avatarCount = 21;
	avatars.resize(avatarCount);
	avatarTextures.resize(avatarCount);
	textureAvatarsFilePath.resize(avatarCount);

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
	if (!sharedTexture.loadFromFile("assets/image/Avatars/vacio.jpg")) return;


	if (selectedAvatarCopy.getTexture() == nullptr) {
		selectedAvatarCopy.setRadius(64);
		selectedAvatarCopy.setTexture(&sharedTexture);
		selectedAvatarCopy.setOrigin(64, 64);
	}


	Texrecua.loadFromFile("assets/image/Avatars/recua.png");
	recua.setTexture(Texrecua);
	recua.setOrigin(65, 65);
}
sf::Texture IniciaUser::fun() {


	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	// Calcular el tama�o de la ventana (2/3 del tama�o de la pantalla)
	unsigned int windowWidth = desktop.width * 2 / 3;
	unsigned int windowHeight = desktop.height * 2 / 3;

	// Crear la ventana con el tama�o calculado
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Selecciona el �rea");

	sf::Texture tempTexture;
	tempTexture.loadFromImage(originalImage);
	sf::Sprite sprite(tempTexture);

	// Aqu� puedes permitir que el usuario seleccione una regi�n
	sf::IntRect selectedRegion(0, 0, 128, 128);

	bool dragging = false;
	sf::Vector2f offset;

	// Obtener tama�o de la imagen
	sf::Vector2u imgSize = tempTexture.getSize();
	sf::RectangleShape selectionBox;

	selectionBox.setPosition(static_cast<float>(selectedRegion.left), static_cast<float>(selectedRegion.top));
	selectionBox.setFillColor(sf::Color(255, 255, 255, 50)); // Transparente
	selectionBox.setOutlineThickness(2);
	selectionBox.setOutlineColor(sf::Color::Red);

	// Calcular escalado manteniendo la proporci�n
	float scaleX = static_cast<float>(windowWidth) / imgSize.x;
	float scaleY = static_cast<float>(windowHeight) / imgSize.y;
	float scale = std::min(scaleX, scaleY);  // Escalar para que todo quepa en la ventana

	sprite.setScale(scale, scale);

	sf::Vector2u imgSizeSprite = sprite.getTexture()->getSize();
	sf::Vector2f scaleo = sprite.getScale(); // Escala aplicada al sprite

	sf::Vector2f spriteSize(imgSizeSprite.x * scaleo.x, imgSizeSprite.y * scaleo.y);

	if (spriteSize.x >= spriteSize.y) {


		selectionBox.setSize(sf::Vector2f(spriteSize.y, spriteSize.y));


	}
	else {
		selectionBox.setSize(sf::Vector2f(spriteSize.x, spriteSize.x));

	}
	// Centrar la imagen
	float offsetX = (windowWidth - imgSize.x * scale) / 2;
	float offsetY = (windowHeight - imgSize.y * scale) / 2;
	sprite.setPosition(offsetX, offsetY);
	// Posici�n inicial dentro del sprite
	selectionBox.setPosition(offsetX, offsetY);

	bool resizing = false;
	int resizingCorner = -1;
	float enA = selectionBox.getSize().x / 12;
	float enH = selectionBox.getSize().x / 30;
	sf::RectangleShape topLeftH(sf::Vector2f(enA, enH));  // Horizontal
	sf::RectangleShape topLeftV(sf::Vector2f(enH, enA));  // Vertical

	sf::RectangleShape topRightH(sf::Vector2f(enA, enH));
	sf::RectangleShape topRightV(sf::Vector2f(enH, enA));

	sf::RectangleShape bottomLeftH(sf::Vector2f(enA, enH));
	sf::RectangleShape bottomLeftV(sf::Vector2f(enH, enA));

	sf::RectangleShape bottomRightH(sf::Vector2f(enA, enH));
	sf::RectangleShape bottomRightV(sf::Vector2f(enH, enA));

	// Color de las l�neas
	sf::Color cornerColor = sf::Color::Red;
	topLeftH.setFillColor(cornerColor);
	topLeftV.setFillColor(cornerColor);
	topRightH.setFillColor(cornerColor);
	topRightV.setFillColor(cornerColor);
	bottomLeftH.setFillColor(cornerColor);
	bottomLeftV.setFillColor(cornerColor);
	bottomRightH.setFillColor(cornerColor);
	bottomRightV.setFillColor(cornerColor);

	std::vector<sf::RectangleShape*> corners = {
		&topLeftH, &topLeftV, &topRightH, &topRightV,
		&bottomLeftH, &bottomLeftV, &bottomRightH, &bottomRightV
	};


	sf::Vector2f pos = selectionBox.getPosition();
	sf::Vector2f size = selectionBox.getSize();

	// Top-left
	corners[0]->setPosition(pos.x, pos.y);
	corners[1]->setPosition(pos.x, pos.y);

	// Top-right
	corners[2]->setPosition(pos.x + size.x - enA, pos.y);
	corners[3]->setPosition(pos.x + size.x - enH, pos.y);

	// Bottom-left
	corners[4]->setPosition(pos.x, pos.y + size.y - enH);
	corners[5]->setPosition(pos.x, pos.y + size.y - enA);

	// Bottom-right
	corners[6]->setPosition(pos.x + size.x - enA, pos.y + size.y - enH);
	corners[7]->setPosition(pos.x + size.x - enH, pos.y + size.y - enA);



	sf::Sprite boton;
	sf::Texture bottt;
	bottt.loadFromFile("assets/image/Button/aceptar1.png");
	boton.setTexture(bottt);
	boton.setPosition(325, 365);


	while (window.isOpen()) {
		sf::Event event;
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {

					if (!resizing && !dragging && boton.getGlobalBounds().contains(mousePos)) {
						// Obtener la posici�n y tama�o del `selectionBox`
						sf::Vector2f selPos = selectionBox.getPosition();
						sf::Vector2f selSize = selectionBox.getSize();

						// Convertir la posici�n en coordenadas de textura (en caso de transformaciones)
						sf::Vector2f texCoords = selPos - sf::Vector2f(offsetX, offsetY);

						// Definir el rect�ngulo a recortar
						sf::IntRect textureRect(static_cast<int>(texCoords.x / scale), static_cast<int>(texCoords.y / scale),
							static_cast<int>(selSize.x / scale),  static_cast<int>(selSize.y / scale));

						// Crear una nueva textura y copiar la parte seleccionada
						sf::Texture newTexture;
						newTexture.loadFromImage(sprite.getTexture()->copyToImage(), textureRect);

						// Crear un nuevo sprite con la nueva textura
						return newTexture;

					}
			
					for (int i = 0; i < 8; ++i) {
						if (corners[i]->getGlobalBounds().contains(mousePos)) {
							resizing = true;
					
							resizingCorner = i;
							break;
						}
					}

					if (!resizing && selectionBox.getGlobalBounds().contains(mousePos)) {
						dragging = true;
				
						offset = mousePos - selectionBox.getPosition();
					}


				}
			}


			// Detectar movimiento del mouse mientras se arrastra
			if (event.type == sf::Event::MouseMoved) {
				if (dragging) {
	
					sf::Vector2f newPos = mousePos - offset;

					float minX = offsetX;
					float minY = offsetY;
					float maxX = offsetX + imgSize.x * scale - selectionBox.getSize().x;
					float maxY = offsetY + imgSize.y * scale - selectionBox.getSize().y;

					newPos.x = std::max(minX, std::min(newPos.x, maxX));
					newPos.y = std::max(minY, std::min(newPos.y, maxY));

					selectionBox.setPosition(newPos);
				}
				else if (resizing) {
					sf::Vector2f newSize = selectionBox.getSize();
					sf::Vector2f newPos = selectionBox.getPosition();

					float minSize = 50; // Tama�o m�nimo
					float maxSize = std::min(imgSize.x * scale, imgSize.y * scale); // Tama�o m�ximo

					float diff = 0;

					if (resizingCorner == 0 || resizingCorner == 1) {  // Esquina superior izquierda
						diff = selectionBox.getPosition().x - mousePos.x;
						newSize.x += diff;
						newSize.y += diff;
						newPos.x -= diff;
						newPos.y -= diff;
					}
					else if (resizingCorner == 2 || resizingCorner == 3) {  // Esquina superior derecha
						diff = mousePos.x - (selectionBox.getPosition().x + selectionBox.getSize().x);
						newSize.x += diff;
						newSize.y += diff;
						newPos.y -= diff; //  Ajustar posici�n en Y para que la reducci�n sea hacia abajo
					}
					else if (resizingCorner == 4 || resizingCorner == 5) {  // Esquina inferior izquierda
						diff = selectionBox.getPosition().x - mousePos.x;
						newSize.x += diff;
						newSize.y += diff;
						newPos.x -= diff;
					}
					else if (resizingCorner == 6 || resizingCorner == 7) {  // Esquina inferior derecha
						diff = mousePos.x - (selectionBox.getPosition().x + selectionBox.getSize().x);
						newSize.x += diff;
						newSize.y += diff;
					}

					newSize.x = std::max(minSize, std::min(newSize.x, maxSize));
					newSize.y = newSize.x;  // Mantener cuadrado

					newPos.x = std::max(offsetX, std::min(newPos.x, offsetX + imgSize.x * scale - newSize.x));
					newPos.y = std::max(offsetY, std::min(newPos.y, offsetY + imgSize.y * scale - newSize.y));

					selectionBox.setSize(newSize);
					selectionBox.setPosition(newPos);


				}
			}

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				dragging = false;
				resizing = false;
			}
		}


		sf::Vector2f pos = selectionBox.getPosition();
		sf::Vector2f size = selectionBox.getSize();

		// Top-left
		corners[0]->setPosition(pos.x, pos.y);
		corners[1]->setPosition(pos.x, pos.y);

		// Top-right
		corners[2]->setPosition(pos.x + size.x - enA, pos.y);
		corners[3]->setPosition(pos.x + size.x - enH, pos.y);

		// Bottom-left
		corners[4]->setPosition(pos.x, pos.y + size.y - enH);
		corners[5]->setPosition(pos.x, pos.y + size.y - enA);

		// Bottom-right
		corners[6]->setPosition(pos.x + size.x - enA, pos.y + size.y - enH);
		corners[7]->setPosition(pos.x + size.x - enH, pos.y + size.y - enA);


		window.clear();
		window.draw(sprite);


		window.draw(selectionBox);
		for (auto& corner : corners) {
			window.draw(*corner);
		}
		window.draw(boton);
		window.display();
	}
	sf::Texture tempTexturooo;
	return tempTexturooo;
}
