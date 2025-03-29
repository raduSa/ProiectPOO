#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Collider.h"
#include "Vector2D.h"
#include "StateManager.h"
#include "TextureManager.h"
#include "Game.h"
#include "Attack.h"
#include "AttackFactory.h"
#include <string>

class TextureManager;
class StateManager;
class Collider;
class Attack;
class AttackFactory;

class GameObject {
	Vector2D<float> position;
	Vector2D<float> velocity;
	Vector2D<int> dimensions;// width/height
	static float speed;
	bool aDown, dDown, punchDown, kickDown;
	SDL_KeyCode Up, Down, Left, Right, PUNCH, KICK, BLOCK;
	TextureManager* texture;
	Collider* collider;
	StateManager* state;
	SDL_Texture* objectTex;
	SDL_Rect destR;
	int windowW, windowH;
	GameObject* other;
	std::shared_ptr<AttackFactory> punchFactory;
	std::shared_ptr<AttackFactory> kickFactory;
	int HP = 100;
	void updateDestR();
	static void calculatePos(GameObject* player);

public:
	GameObject(std::string folder, int x, int y, int w, int h, bool isTurned, 
		const SDL_KeyCode& up, const SDL_KeyCode& down, const SDL_KeyCode& left, const SDL_KeyCode& right, const SDL_KeyCode& punch, const SDL_KeyCode& kick, const SDL_KeyCode& block);
	~GameObject() { delete texture; delete state; delete collider; }
	void Update();
	void MoveX();
	void MoveY();
	void handleInput(const SDL_Event& event);
	void Render();
	void revertPos();
	void drainHP(const int&);

	Vector2D<float> getPos() const { return position; }
	Vector2D<float>* getPosPointer() { return &position; }
	Vector2D<int> getDim() const { return dimensions; }
	Vector2D<int>* getDimPointer() { return &dimensions; }
	SDL_Rect* getDestRPointer() { return &destR; }
	Collider* getCollider() const { return collider; }
	SDL_Texture** getTexturePointer() { return &objectTex; }
	StateManager* getState() const { return state; }
	int getHP() const { return HP; }
	void setOtherPlayer(GameObject* oth) { other = oth; }
	void setPunchFactory(std::shared_ptr<AttackFactory>);
	void setKickFactory(std::shared_ptr<AttackFactory>);
	friend std::istream& operator>>(std::istream& in, GameObject player);
};
