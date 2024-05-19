#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GameObject.h"
#include "Vector2D.h"

class GameObject;

class Collider {
	SDL_Rect collider;
	SDL_Rect* destR;
	SDL_Rect prevState;
	Vector2D* position;
	Vector2D prevPos;
public:
 	Collider(GameObject* player);
	~Collider() { delete position; delete destR; }
	static bool collision(const SDL_Rect& recA, const SDL_Rect& recB);
	void setPrevPos();
	void getPrevPos() const;
	SDL_Rect getRect() const { return *destR; }
	friend std::ostream& operator<<(std::ostream& out, const Collider& col);
};