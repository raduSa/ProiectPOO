#include "TextureManager.h"
#include <fstream>
#include <vector>
#include <utility>

TextureManager::TextureManager(GameObject* player, std::string folder) :
	objectTex(player->getTexturePointer()), state(player->getState()) {
	SDL_Renderer* ren = Game::getRenderer();
	std::vector<std::pair<SDL_Texture**, std::string>> textures =
	{ {&idle, "idle"}, {&idleInverted, "idleInverted"}, {&crouch, "crouch"}, {&crouchInverted, "crouchInverted"},
	{&punch, "punch"}, {&punchInverted, "punchInverted"}, {&kick, "kick"}, {&kickInverted, "kickInverted"},
	{&crouchPunch, "crouchPunch"}, {&crouchPunchInverted, "crouchPunchInverted"},
	{&crouchKick, "crouchKick"}, {&crouchKickInverted, "crouchKickInverted"} };

	for (auto& pair : textures)
		if (TextureManager::FileExists("assets/" + folder + "/" + pair.second + ".png"))
			*pair.first = TextureManager::LoadTexture("assets/" + folder + "/" + pair.second + ".png");
		else
			throw* (new GameObjectTexExc(folder, pair.second)); // polimorfism
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

SDL_Texture* TextureManager::LoadTexture(std::string fileName) {
		SDL_Surface* tempSurface = IMG_Load(fileName.c_str());
		SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::getRenderer(), tempSurface);
		SDL_FreeSurface(tempSurface);
		return tex;
}

void TextureManager::update() {
	if (state->IsTurned()) {
		if (state->IsCrouching()) {
			if (state->IsAttacking()) {
				if (state->IsPunching())
					*objectTex = crouchPunchInverted;
				else
					*objectTex = crouchKickInverted;
			}
			else
				*objectTex = crouchInverted;
		}
		else if (state->IsAttacking())
			if (state->IsPunching())
				*objectTex = punchInverted;
			else
				*objectTex = kickInverted;
		else
			*objectTex = idleInverted;
	}
	else {
		if (state->IsCrouching()) {
			if (state->IsAttacking()) {
				if (state->IsPunching())
					*objectTex = crouchPunch;
				else
					*objectTex = crouchKick;
			}
			else
				*objectTex = crouch;
		}
		else if (state->IsAttacking())
			if (state->IsPunching())
				*objectTex = punch;
			else
				*objectTex = kick;
		else
			*objectTex = idle;
	}
}