#include "Game.h"

void Game::init(const char* title, int xpos, int ypos, bool fullscreen) {
	int flags = 0;
	std::cout << width << " " << height;
	if (fullscreen) { flags = SDL_WINDOW_FULLSCREEN; }

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		backgroundTex = TextureManager::LoadTexture("assets/background.png", renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		isRunning = true;
	}
	else { isRunning = false; }
	player = new GameObject("player", renderer, 0, height - 256, 200, 450, SDLK_w, SDLK_s, SDLK_a, SDLK_d);
	enemy = new GameObject("enemy", renderer, width - 128, height - 256, 200, 450, SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT);

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
	player->Update();
	player->MoveX();
	if (Collider::collision(player->getCollider()->getRect(), enemy->getCollider()->getRect()))
		player->revertPos();
	player->MoveY();
	if (Collider::collision(player->getCollider()->getRect(), enemy->getCollider()->getRect()))
		player->revertPos();
	enemy->Update();
	enemy->MoveX();
	if (Collider::collision(enemy->getCollider()->getRect(), player->getCollider()->getRect()))
		enemy->revertPos();
	enemy->MoveY();
	if (Collider::collision(enemy->getCollider()->getRect(), player->getCollider()->getRect()))
		enemy->revertPos();
}

void Game::render() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgroundTex, NULL, NULL);
	player->Render();
	enemy->Render();
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