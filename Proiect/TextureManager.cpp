#include "TextureManager.h"
#include <fstream>

TextureManager::TextureManager(GameObject* player, std::string folder) :
	objectTex(player->getTexturePointer()), state(player->getState()) {
	SDL_Renderer* ren = Game::getRenderer();
	// normal textures
	if (TextureManager::FileExists("assets/" + folder + "/idle.png"))
		idle = TextureManager::LoadTexture("assets/" + folder + "/idle.png");
	else 
		throw* (new GameObjectTexExc(folder, "idle")); // polimorfism

	if (TextureManager::FileExists("assets/" + folder + "/crouch.png"))
		crouch = TextureManager::LoadTexture("assets/" + folder + "/crouch.png");
	else
		throw* (new GameObjectTexExc(folder, "crouch"));

	if (TextureManager::FileExists("assets/" + folder + "/punch.png"))
		punch = TextureManager::LoadTexture("assets/" + folder + "/punch.png");
	else
		throw* (new GameObjectTexExc(folder, "punch"));

	if (TextureManager::FileExists("assets/" + folder + "/kick.png"))
		kick = TextureManager::LoadTexture("assets/" + folder + "/kick.png");
	else
		throw* (new GameObjectTexExc(folder, "kick"));
	// inverted textures
	if (TextureManager::FileExists("assets/" + folder + "/idleInverted.png"))
		idleInverted = TextureManager::LoadTexture("assets/" + folder + "/idleInverted.png");
	else
		throw* (new GameObjectTexExc(folder, "idleInverted"));

	if (TextureManager::FileExists("assets/" + folder + "/crouchInverted.png"))
		crouchInverted = TextureManager::LoadTexture("assets/" + folder + "/crouchInverted.png");
	else
		throw* (new GameObjectTexExc(folder, "crouchInverted"));

	if (TextureManager::FileExists("assets/" + folder + "/punchInverted.png"))
		punchInverted = TextureManager::LoadTexture("assets/" + folder + "/punchInverted.png");
	else
		throw* (new GameObjectTexExc(folder, "punchInverted"));

	if (TextureManager::FileExists("assets/" + folder + "/kickInverted.png"))
		kickInverted = TextureManager::LoadTexture("assets/" + folder + "/kickInverted.png");
	else
		throw* (new GameObjectTexExc(folder, "kickInverted"));
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