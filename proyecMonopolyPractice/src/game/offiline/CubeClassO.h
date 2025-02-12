#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#define M_PI 3.14159265358979323846

class CubeO {
	float CDis = 0;

	
	struct Vector3D {
		float x, y, z;
		Vector3D(){
			x = 0, y = 0, z = 0;
		}
		Vector3D(float X, float Y, float Z){
			x = X; y = Y; z = Z;

		}
		Vector3D operator +(Vector3D vec) { return Vector3D(vec.x+x,vec.y+y,vec.z+z); }
		Vector3D operator *(float a) { return Vector3D(x * a, y * a, z * a); }

	};

	Vector3D vertex[8] ={
		Vector3D(-1, -1,  1),
		Vector3D(1, -1,  1),
		Vector3D(1, -1, -1),
		Vector3D(-1, -1, -1),
		Vector3D(-1,  1,  1),
		Vector3D(1,  1,  1),
		Vector3D(1,  1, -1),
		Vector3D(-1,  1, -1)
	};

	Vector3D center = Vector3D(0, 0, 0);

	void move(){
		for (int i = 0; i < 8; i++){
			C3D[i] = center + vertex[i] * CDis ;
		}
	}

	float calcDistance(Vector3D view, Vector3D obj){
		float xcb = (view.x - obj.x) * (view.x - obj.x);
		float ycb = (view.y - obj.y) * (view.y - obj.y);
		float zcb = (view.z - obj.z) * (view.z - obj.z);
		return sqrtf(xcb + ycb + zcb);

	}
	
	void updateDistances(Vector3D view){
		distances[8] = distances[0] = calcDistance(view, C3D[0]);
		
		for (int i = 1; i < 8; i++){
			distances[i] = calcDistance(view, C3D[i]);
			Dist[i] = distances[i];
			if (distances[i] > distances[8])distances[8] = distances[i];
		}
		for (int i = 0; i < 8; i++){
			if (distances[i] == distances[8])distances[i] = 0;
			else distances[i] = static_cast<float>(i + 1);

		}
	}

	void rotateX(float angle)
	{
		float sinF = sin(angle);
		float cosF = cos(angle);
		for (int i = 0; i < 8; i++)
		{
			float y = vertex[i].y;
			float z = vertex[i].z;

			vertex[i].y = y * cosF - z * sinF;
			vertex[i].z = z * cosF + y * sinF;
		}

	}

	void rotateY(float angle)
	{
		float sinF = sin(angle);
		float cosF = cos(angle);
		for (int i = 0; i < 8; i++)
		{
			float x = vertex[i].x;
			float z = vertex[i].z;

			vertex[i].x = x * cosF + z * sinF;
			vertex[i].z = z * cosF - x * sinF;
		}
		move();

	}
	void rotateZ(float angle)
	{
		float sinF = sin(angle);
		float cosF = cos(angle);
		for (int i = 0; i < 8; i++)
		{
			float x = vertex[i].x;
			float y = vertex[i].y;

			vertex[i].x = x * cosF - y * sinF;
			vertex[i].y = y * cosF + x * sinF;

		}
		move();

	}
	

	float* distances=nullptr;

public :
    sf::Texture textures[6];

	std::vector<std::vector<int>> faces = {
		{0,1,5,4},
		{1,2,6,5},
		{2,3,7,6},
		{3,0,4,7},
		{0,1,2,3},
		{4,5,6,7}
	};


    Vector3D*                     C3D;
    float                         Dist[8];
	std::vector<std::vector<int>> show;
	CubeO(float _size)
	{
		CDis      = _size / 2;
		C3D       = new Vector3D[8];
		distances = new float[9];

		// Cargar texturas
		textures[0].loadFromFile("number1.png");//lista
		textures[2].loadFromFile("number3.png");
		textures[1].loadFromFile("number4.png");
		textures[3].loadFromFile("number2.png");
		textures[4].loadFromFile("number6.png");//lista
		textures[5].loadFromFile("number5.png");//lista

		move();

	}

	void draw(float x, float y, float z)
	{   
		
		show.clear();
		updateDistances(Vector3D(x, y, z));
		for (int face = 0; face < 6; face++)
		{
			int indexFuncion = 0;
			for (int corner = 0; corner < 4; corner++)
				indexFuncion += static_cast<int>(faces[face][corner] - (distances[faces[face][corner]] - 1));
			if (indexFuncion == 0)show.push_back(faces[face]);
		}

	}

	float distanceTo(float x, float y, float z)
	{
		return calcDistance(center, Vector3D(x, y, z));
	}

	void rotate(float alfaX, float alfaY, float alfaZ)
	{
		rotateX(alfaX);
		rotateY(alfaY);
		rotateZ(alfaZ);
	}

	void move(float x, float y, float z){
		center = Vector3D(x, y, z);
		move();
	}

	void resetPosition(int dadoIndex) {
		// Restablecer la posición del centro a su posición inicial
		center = Vector3D(640, 360, -100);

		// Restablecer el tamaño del cubo (distancia entre centro y vértices)
		CDis = 50.0f;  // Asegúrate de que CDis tenga un valor adecuado, o el cubo puede colapsar en un punto

		// Restablecer las posiciones originales de los vértices
		vertex[0] = Vector3D(-1, -1, 1);
		vertex[1] = Vector3D(1, -1, 1);
		vertex[2] = Vector3D(1, -1, -1);
		vertex[3] = Vector3D(-1, -1, -1);
		vertex[4] = Vector3D(-1, 1, 1);
		vertex[5] = Vector3D(1, 1, 1);
		vertex[6] = Vector3D(1, 1, -1);
		vertex[7] = Vector3D(-1, 1, -1);


		switch (dadoIndex) {
		case 1: // Mostrar cara 1
			rotate(0.0f, 0.0f, 0.0f); // No rotar
			break;
		case 2: // Mostrar cara 2
			rotate(0.0f,static_cast<float>(90.0 * (M_PI / 180.0)), 0.0f); // Rotar 90 grados en Y  
			break;
		case 3: // Mostrar cara 3
			rotate(0.0f, static_cast<float>( 180.0 * (M_PI / 180.0)), 0.0f); // Rotar 180 grados en Y
			break;
		case 4: // Mostrar cara 4
			rotate(0, static_cast<float>(270 * (M_PI / 180.0f)), 0.0f); // Rotar 270 grados en Y
			break;
		case 5: // Mostrar cara 5
			rotate(static_cast<float>(90.0f * (M_PI / 180.0f)), 0.0f, 0.0f); // Rotar 90 grados en X
			break;
		case 6: // Mostrar cara 6
			rotate(static_cast<float>(- 90.0f * (M_PI / 180.0f)), 0.0f, 0.0f); // Rotar -90 grados en X
			break;
		default:
			//std::cout << "Face must be between 1 and 6." << std::endl;
			break;
		}
		
		//quiero que aqui este un switch para elegir que cara va estar en el frente , osea quiero que el cubo gire y que la cara que quede en el frente sea la que yo digo de 1 al 6 

		// Llamar a move() para actualizar las posiciones de los vértices
		move();


	}

	float getWidth() const {
		return CDis * 2; // Ancho del cubo
	}

	// Método para obtener la altura del cubo
	float getHeight() const {
		return CDis * 2; // Altura del cubo
	}

	Vector3D getPosition() const {
		return center; // Devuelve la posición del centro del cubo
	}

};

