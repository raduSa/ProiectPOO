#pragma once
#include "GameObject.h"
#include "Game.h"

class Attack
{
protected:
	GameObject* attacker;
	GameObject* attacked;
	static SDL_Texture* tex;
	SDL_Rect hitbox;
public:
	Attack(GameObject*, GameObject*);
	virtual ~Attack() { std::cout << "Deleted attack!\n"; }
	static void setAttackTexture();
	
	void drawHitbox();
	virtual void getBoxDimensions() = 0;
	void checkHit() const;
};

class Punch : public Attack {
public:
	Punch(GameObject* attacker, GameObject* attacked) : Attack(attacker, attacked) {}
	~Punch() {}
	void getBoxDimensions();
};

class Kick : public Attack {
public:
	Kick(GameObject* attacker, GameObject* attacked) : Attack(attacker, attacked) {}
	~Kick() {}
	void getBoxDimensions();
};