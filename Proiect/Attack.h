#pragma once
#include "GameObject.h"

class Attack
{
	GameObject* attacker;
	SDL_Texture* tex;
public:
	Attack(GameObject* player);
	~Attack() { std::cout << "Deleted attack!\n"; }

	void drawHitbox();
};

