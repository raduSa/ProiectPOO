#pragma once
#include "GameObject.h"

class Attack
{
	GameObject* attacker;
	GameObject* attacked;
	SDL_Renderer* renderer;
public:
	Attack() {};
	virtual ~Attack() {};

	virtual void drawHitbox() {
		SDL_Rect hitbox;
		SDL_RenderCopy(renderer, NULL, NULL, &hitbox);
	}
};

