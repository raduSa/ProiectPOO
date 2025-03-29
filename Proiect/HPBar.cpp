#include "HPBar.h"

SDL_Texture* HPBar::tex = nullptr;
SDL_Texture* HPBar::background = nullptr;

HPBar::HPBar(GameObject* player, const int& width) : player(player), windowW(width) {
	bar.w = 600; bar.y = 65; bar.h = 50;
	back.w = 700; back.y = 30; back.h = 120;
}

PlayerHPBar::PlayerHPBar(GameObject* player, const int& w) : HPBar(player, w) {}

EnemyHPBar::EnemyHPBar(GameObject* player, const int& w) : HPBar(player, w) {}

void HPBar::setBarTextures() {
	SDL_Surface* surface = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 255, 0, 0)); // color
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::getRenderer(), surface);
	tex = texture;
	if (TextureManager::FileExists("assets/hpback.png"))
		background = TextureManager::LoadTexture("assets/hpback.png");
	else {
		std::cout << "\nHpbar - ";
		throw* (new BackgroundTexExc());
	}
		
}

void HPBar::drawBar() {
	updateBar();
	SDL_RenderCopy(Game::getRenderer(), background, NULL, &back);
	SDL_RenderCopy(Game::getRenderer(), tex, NULL, &bar);
}

void HPBar::updateBar() {
	if (player->getHP() < bar.w / 6) {
		bar.w -= 2;
	}
}

void PlayerHPBar::getBarLocation() {
	bar.x = 80;
	back.x = 30;
}

void EnemyHPBar::getBarLocation() {
	bar.x = windowW - bar.w - 80;
	back.x = windowW - back.w - 30;
}