#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GameObject.h"
#include "Vector2D.h"

class GameObject;

class Collider {
	SDL_Rect* destR;
	SDL_Rect prevState;
	Vector2D<float>* position;
	Vector2D<float> prevPos;
	Vector2D<int>* dimensions;
	Vector2D<int> prevDim;
public:
 	Collider(GameObject* player);
	~Collider() { delete position; delete destR; }
	Collider* makeMemento(GameObject*);
	void setPrevPos();
	void getPrevPos() const;
	SDL_Rect getRect() const { return *destR; }
};