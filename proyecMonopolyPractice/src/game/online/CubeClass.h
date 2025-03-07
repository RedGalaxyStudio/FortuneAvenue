#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#define M_PI 3.14159265358979323846

class Cube {
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
	Cube(float _size)
	{
		CDis      = _size / 2;
		C3D       = new Vector3D[8];
		distances = new float[9];

		textures[0].loadFromFile("assets/image/Dice/number1.png");
		textures[2].loadFromFile("assets/image/Dice/number3.png");
		textures[1].loadFromFile("assets/image/Dice/number4.png");
		textures[3].loadFromFile("assets/image/Dice/number2.png");
		textures[4].loadFromFile("assets/image/Dice/number6.png");
		textures[5].loadFromFile("assets/image/Dice/number5.png");

		move();

	}

	void draw(float x, float y, float z)
	{   
		
		show.clear();
		updateDistances(Vector3D(x, y, z));
		for (int face = 0; face < 6; face++)
		{
			int index = 0;
			for (int corner = 0; corner < 4; corner++)
				index += static_cast<int>(faces[face][corner] - (distances[faces[face][corner]] - 1));
			if (index == 0)show.push_back(faces[face]);
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
		center = Vector3D(640, 360, -100);

		CDis = 50.0f;

		vertex[0] = Vector3D(-1, -1, 1);
		vertex[1] = Vector3D(1, -1, 1);
		vertex[2] = Vector3D(1, -1, -1);
		vertex[3] = Vector3D(-1, -1, -1);
		vertex[4] = Vector3D(-1, 1, 1);
		vertex[5] = Vector3D(1, 1, 1);
		vertex[6] = Vector3D(1, 1, -1);
		vertex[7] = Vector3D(-1, 1, -1);


		switch (dadoIndex) {
		case 1: 
			rotate(0.0f, 0.0f, 0.0f); 
			break;
		case 2: 
			rotate(0.0f,static_cast<float>(90.0 * (M_PI / 180.0)), 0.0f);  
			break;
		case 3: 
			rotate(0.0f, static_cast<float>( 180.0 * (M_PI / 180.0)), 0.0f); 
			break;
		case 4: 
			rotate(0, static_cast<float>(270 * (M_PI / 180.0f)), 0.0f); 
			break;
		case 5: 
			rotate(static_cast<float>(90.0f * (M_PI / 180.0f)), 0.0f, 0.0f); 
			break;
		case 6: 
			rotate(static_cast<float>(- 90.0f * (M_PI / 180.0f)), 0.0f, 0.0f); 
			break;
		default:
			break;
		}
		
		move();


	}

	float getWidth() const {
		return CDis * 2; 
	}

	float getHeight() const {
		return CDis * 2;
	}

	Vector3D getPosition() const {
		return center; 
	}

};

