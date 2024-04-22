#include "TextureManager.h"
#include <fstream>

TextureManager::TextureManager(GameObject* player, SDL_Renderer* renderer, std::string folder) :
	objectTex(player->getTexturePointer()), state(player->getState()) {
	if (TextureManager::FileExists("assets/" + folder + "/idle.png"))
		idle = TextureManager::LoadTexture("assets/" + folder + "/idle.png", renderer);
	else 
		throw* (new GameObjectTexExc(folder, "idle"));

	if (TextureManager::FileExists("assets/" + folder + "/crouch.png"))
		crouch = TextureManager::LoadTexture("assets/" + folder + "/crouch.png", renderer);
	else
		throw* (new GameObjectTexExc(folder, "crouch"));
}
TextureManager::~TextureManager() { SDL_DestroyTexture(idle); SDL_DestroyTexture(crouch); }

bool TextureManager::FileExists(std::string filePath) {
	std::ifstream file;
	file.open(filePath);
	if (file) {
		return true;
	}
	else return false;
}

SDL_Texture* TextureManager::LoadTexture(std::string fileName, SDL_Renderer* renderer) {
		SDL_Surface* tempSurface = IMG_Load(fileName.c_str());
		SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
		return tex;
}

void TextureManager::update() {
	if (state->IsCrouching()) {
		*objectTex = crouch;
	}
	else
		*objectTex = idle;
}