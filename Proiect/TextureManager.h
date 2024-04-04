#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "StateManager.h"
#include "GameObject.h"

class GameObject;

class TextureManager {
	SDL_Texture* idle;
	SDL_Texture* crouch;
	SDL_Texture** objectTex;
	StateManager* state;
public:
	TextureManager(GameObject* player, SDL_Renderer* renderer, std::string folder);
	~TextureManager();
	static SDL_Texture* LoadTexture(std::string fileName, SDL_Renderer* renderer);
	void update();
};