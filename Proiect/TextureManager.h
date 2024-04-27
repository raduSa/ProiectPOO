#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "StateManager.h"
#include "GameObject.h"
#include "textureException.h"

class GameObjectTexExc : public textureException {
	std::string message;

public:
	GameObjectTexExc(const std::string& folderName, const std::string& fileName) : 
		message("No texture found - folder: " + folderName + ", file: " + fileName) {};

	const char* what() const throw() {
		return message.c_str();
	}

	~GameObjectTexExc() {}
};

class GameObject;

class TextureManager {
	SDL_Texture* idle;
	SDL_Texture* crouch;
	SDL_Texture* punch;
	SDL_Texture* kick;
	SDL_Texture* idleInverted;
	SDL_Texture* crouchInverted;
	SDL_Texture* punchInverted;
	SDL_Texture* kickInverted;
	SDL_Texture** objectTex;
	StateManager* state;
public:
	TextureManager(GameObject* player, std::string folder);
	~TextureManager();
	static bool FileExists(std::string);
	static SDL_Texture* LoadTexture(std::string fileName);
	void update();
};