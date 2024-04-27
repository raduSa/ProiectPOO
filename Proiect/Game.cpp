#include "Game.h"
#include "Attack.h"

SDL_Renderer* Game::renderer = nullptr;

void Game::turnPlayers() {
	if (((player->getPos().getX() + player->getDim().getX() / 2) * (-(player->getState()->IsTurned() * 2 - 1)) -
		(enemy->getPos().getX() + enemy->getDim().getX() / 2) * (enemy->getState()->IsTurned() * 2 - 1)) > 0) {
		player->getState()->turn();
		enemy->getState()->turn();
	}
}

void Game::init(const char* title, int xpos, int ypos, bool fullscreen) {
	int flags = 0;
	std::cout << width << " " << height;
	if (fullscreen) { flags = SDL_WINDOW_FULLSCREEN; }
	std::ifstream file;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (TextureManager::FileExists("assets/background.png"))
			backgroundTex = TextureManager::LoadTexture("assets/background.png");
		else
			throw *(new BackgroundTexExc()); // polimorfism
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		isRunning = true;
	}
	else { isRunning = false; }
	Attack::setAttackTexture();
	player = new GameObject("player", 0, height - 256, 200, 450, false, SDLK_w, SDLK_s, SDLK_a, SDLK_d, SDLK_e, SDLK_r);
	enemy = new GameObject("enemy", width - 128, height - 256, 200, 450, true, SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT, SDLK_KP_1, SDLK_KP_2);
	player->setOtherPlayer(enemy);
	enemy->setOtherPlayer(player);
	HPBar::setBarTextures();
	playerHP = new PlayerHPBar(player, width);
	playerHP->getBarLocation();
	enemyHP = new EnemyHPBar(enemy, width);
	enemyHP->getBarLocation();
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		isRunning = false;
		return;
	}
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
		isRunning = false;
		return;
	}
	player->handleInput(event);
	enemy->handleInput(event);
}

void Game::update() {
	// update player related proprieties
	std::cout << "Player:\n";
	player->Update();
	// move player along X axis,in case of collision go back
	player->MoveX();
	if (Collider::collision(player->getCollider()->getRect(), enemy->getCollider()->getRect()))
		player->revertPos();
	// move player along Y axis, in case of collision go back
	player->MoveY();
	if (Collider::collision(player->getCollider()->getRect(), enemy->getCollider()->getRect()))
		player->revertPos();
	// same with enemy
	std::cout << "Enemy:\n";
	enemy->Update();

	enemy->MoveX();
	if (Collider::collision(enemy->getCollider()->getRect(), player->getCollider()->getRect()))
		enemy->revertPos();

	enemy->MoveY();
	if (Collider::collision(enemy->getCollider()->getRect(), player->getCollider()->getRect()))
		enemy->revertPos();
	// check if players should turn around
	turnPlayers();
}

void Game::render() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgroundTex, NULL, NULL);
	player->Render();
	enemy->Render();
	playerHP->drawBar();
	enemyHP->drawBar();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(backgroundTex);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned\n";
}

std::istream& operator>>(std::istream& in, Game* game) {
	in >> game->width;
	in >> game->height;
	return in;
}