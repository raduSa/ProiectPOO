#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include "Game.h"

int main(int argc, char* argv[]) {
	std::ifstream input("input.txt");
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	Game* game = Game::instantiate();
	input >> game;
	try {
		game->init("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);
	}
	catch (const textureException& e) { // upcasting
		std::cout << "\nInitialisation Failed: " << e.what() << std::endl;
		return 0;
	}

	while (game->running()) {
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart;
		// Delay if too many frames
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	game->clean();
	return 0;
}