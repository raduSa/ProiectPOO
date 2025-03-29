#include "Attack.h"

SDL_Texture* Attack::tex = nullptr;

Attack::~Attack() { std::cout << "Deleted attack!\n"; }

Attack::Attack(GameObject* player, GameObject* enemy) : attacker(player), attacked(enemy) { std::cout << "Attack created!\n"; }

void Attack::setAttackTexture(std::vector<int> rgbValues) {
	if (!std::all_of(rgbValues.begin(), rgbValues.end(), [](int i) { return i == 0; })) {
		SDL_Surface* surface = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);
		SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, rgbValues[0], rgbValues[1], rgbValues[2])); // color
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::getRenderer(), surface);
		tex = texture;
		return;
	}
	tex = nullptr;
}

bool Attack::checkHit() const {
	if (Game::collision(hitbox, *(attacked->getDestRPointer()))) {
		std::cout << "HIT!\n";
		attacked->getState()->getsHit();
		return true;
	}
	return false;
}

void Punch::getBoxDimensions() {
	std::cout << "Punch\n";
	SDL_Rect* destR = attacker->getDestRPointer();
	hitbox.y = destR->y;
	hitbox.h = (int)(destR->h * 0.4);
	hitbox.w = (int)(destR->w * 0.6);
	if (attacker->getState()->IsTurned()) {
		hitbox.x = destR->x - hitbox.w;
	}
	else
		hitbox.x = destR->x + destR->w;
}

void Kick::getBoxDimensions() {
	std::cout << "Kick\n";
	SDL_Rect* destR = attacker->getDestRPointer();
	hitbox.y = destR->y;
	hitbox.h = (int)(destR->h * 0.4);
	hitbox.w = (int)(destR->w * 1);
	if (attacker->getState()->IsCrouching())
		hitbox.y = destR->y + (int)(destR->h * 0.6);
	if (attacker->getState()->IsTurned()) {
		hitbox.x = destR->x - hitbox.w;
	}
	else
		hitbox.x = destR->x + destR->w;
}

void Attack::drawHitbox() {
	getBoxDimensions(); // polimorfism
	if (checkHit() && attacked->getState()->CanTakeDamage())
		dealDMG();
	SDL_RenderCopy(Game::getRenderer(), tex, NULL, &hitbox);
}

void Punch::dealDMG() {
	int damage = 10;
	if (attacked->getState()->IsBlocking())
		damage /= 5;
	attacked->drainHP(damage);
	attacked->getState()->flipCanTakeDamage();
}

void Kick::dealDMG() {
	int damage = 20;
	if (attacked->getState()->IsBlocking())
		damage /= 5;
	attacked->drainHP(damage);
	attacked->getState()->flipCanTakeDamage();
}