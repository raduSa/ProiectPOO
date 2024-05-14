#pragma once
#include "GameObject.h"

class HPBar {
protected:
	GameObject* player;
	SDL_Rect bar;
	SDL_Rect back;
	int windowW;
	static SDL_Texture* tex;
	static SDL_Texture* background;
public:
	HPBar(GameObject* player, const int& width);
	virtual ~HPBar() {}
	void updateBar();
	virtual void getBarLocation() {}
	void drawBar();
	static void setBarTextures();
};

class PlayerHPBar : public HPBar {
public:
	PlayerHPBar(GameObject* player, const int& w) : HPBar(player, w) {}
	~PlayerHPBar() {}
	void getBarLocation();
};

class EnemyHPBar : public HPBar {
public:
	EnemyHPBar(GameObject* player, const int& w) : HPBar(player, w) {}
	~EnemyHPBar() {}
	void getBarLocation();
};

