#pragma once
#include "GameObject.h"
#include "Game.h"
#include <vector>
#include <algorithm>

class Attack
{
protected:
	GameObject* attacker;
	GameObject* attacked;
	static SDL_Texture* tex;
	SDL_Rect hitbox;
	virtual void getBoxDimensions() = 0;
	virtual void dealDMG() = 0;
public:
	Attack(GameObject*, GameObject*);
	virtual ~Attack();
	static void setAttackTexture(std::vector<int> rgbValues = {0, 0, 0});
	
	void drawHitbox();
	bool checkHit() const;
};

class Punch : public Attack {
private:
	void getBoxDimensions();
	void dealDMG();
public:
	Punch(GameObject* attacker, GameObject* attacked) : Attack(attacker, attacked) {}
	~Punch() {}
};

class Kick : public Attack {
private:
	void getBoxDimensions();
	void dealDMG();
public:
	Kick(GameObject* attacker, GameObject* attacked) : Attack(attacker, attacked) {}
	~Kick() {}
};