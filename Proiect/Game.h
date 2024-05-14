#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <exception>
#include "GameObject.h"
#include "textureException.h"
#include "HPBar.h"

class BackgroundTexExc : public textureException {
public:
	const char* what() const throw() {
		return "No texture found - background";
	}
	~BackgroundTexExc() {}
};

class HPBar;

class Game {
	int cnt = 0;
	bool isRunning;
	SDL_Window* window;
	static SDL_Renderer* renderer;
	SDL_Texture* backgroundTex;
	GameObject* player;
	GameObject* enemy;
	int width, height;
	HPBar* playerHP;
	HPBar* enemyHP;
	void turnPlayers();
	void checkHP();
public:
	Game() { width = 0; height = 0; }
	void init(const char* title, int xpos, int ypos, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() const { return isRunning; }
	void stopGame() { isRunning = false; }
	static SDL_Renderer* getRenderer() { return renderer; }
	friend std::istream& operator>>(std::istream& in, Game* game);
};