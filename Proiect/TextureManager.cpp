#include "TextureManager.h"

TextureManager::TextureManager(GameObject* player, SDL_Renderer* renderer, std::string folder) :
	objectTex(player->getTexturePointer()), state(player->getState()) {
	idle = TextureManager::LoadTexture("assets/" + folder + "/idle.png", renderer);
	crouch = TextureManager::LoadTexture("assets/" + folder + "/crouch.png", renderer);
}
TextureManager::~TextureManager() { SDL_DestroyTexture(idle); SDL_DestroyTexture(crouch); }

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