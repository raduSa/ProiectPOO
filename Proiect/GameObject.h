#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Collider.h"
#include "Vector2D.h"
#include "StateManager.h"
#include "TextureManager.h"
#include <string>

class TextureManager;
class StateManager;
class Collider;

class GameObject {
	Vector2D position;
	Vector2D velocity;
	Vector2D dimensions;// width/height
	static float speed;
	bool aDown, dDown;
	SDL_KeyCode Up, Down, Left, Right;
	TextureManager* texture;
	Collider* collider;
	StateManager* state;
	SDL_Texture* objectTex;
	SDL_Rect destR;
	SDL_Renderer* renderer;
	int windowW, windowH;
	void updateDestR();
	static void calculatePos(GameObject* player) { player->position += player->velocity * speed; }

public:
	GameObject(std::string folder, SDL_Renderer* ren, int x, int y, int w, int h, const SDL_KeyCode& up, const SDL_KeyCode& down, const SDL_KeyCode& left, const SDL_KeyCode& right);
	~GameObject() { delete texture; delete state; delete collider; }
	void Update();
	void MoveX();
	void MoveY();
	void handleInput(const SDL_Event& event);
	void Render() {
		SDL_RenderCopy(renderer, objectTex, NULL, &destR);
	}
	void revertPos();

	Vector2D getPos() const { return position; }
	Vector2D* getPosPointer() { return &position; }
	SDL_Rect* getDestRPointer() { return &destR; }
	Collider* getCollider() const { return collider; }
	SDL_Texture** getTexturePointer() { return &objectTex; }
	StateManager* getState() const { return state; }
	friend std::istream& operator>>(std::istream& in, GameObject player);
};
