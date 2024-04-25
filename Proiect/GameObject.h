#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Collider.h"
#include "Vector2D.h"
#include "StateManager.h"
#include "TextureManager.h"
#include "Game.h"
#include <string>

class TextureManager;
class StateManager;
class Collider;
class Attack;

class GameObject {
	Vector2D position;
	Vector2D velocity;
	Vector2D dimensions;// width/height
	static float speed;
	bool aDown, dDown, atckDown;
	SDL_KeyCode Up, Down, Left, Right, Atck;
	TextureManager* texture;
	Collider* collider;
	StateManager* state;
	SDL_Texture* objectTex;
	SDL_Rect destR;
	int windowW, windowH;
	void updateDestR();
	static void calculatePos(GameObject* player) { player->position += player->velocity * speed; }

public:
	GameObject(std::string folder, int x, int y, int w, int h, bool isTurned, 
		const SDL_KeyCode& up, const SDL_KeyCode& down, const SDL_KeyCode& left, const SDL_KeyCode& right, const SDL_KeyCode& attack);
	~GameObject() { delete texture; delete state; delete collider; }
	void Update();
	void MoveX();
	void MoveY();
	void handleInput(const SDL_Event& event);
	void Render();
	void revertPos();

	Vector2D getPos() const { return position; }
	Vector2D* getPosPointer() { return &position; }
	Vector2D getDim() const { return dimensions; }
	SDL_Rect* getDestRPointer() { return &destR; }
	Collider* getCollider() const { return collider; }
	SDL_Texture** getTexturePointer() { return &objectTex; }
	StateManager* getState() const { return state; }
	friend std::istream& operator>>(std::istream& in, GameObject player);
};
