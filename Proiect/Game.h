#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "GameObject.h"

class Game {
	int cnt = 0;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* backgroundTex;
	GameObject* player;
	GameObject* enemy;
	int width, height;

public:
	Game() { width = 0; height = 0; }
	void init(const char* title, int xpos, int ypos, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }
	friend std::istream& operator>>(std::istream& in, Game* game);
};