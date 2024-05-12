#include "Attack.h"

SDL_Texture* Attack::tex = nullptr;

Attack::Attack(GameObject* player, GameObject* enemy) : attacker(player), attacked(enemy) { std::cout << "Attack created!\n"; }

void Attack::setAttackTexture() {
	SDL_Surface* surface = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 255, 0, 0)); // color
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::getRenderer(), surface);
	tex = texture;
}

bool Attack::checkHit() const {
	if (Collider::collision(hitbox, *(attacked->getDestRPointer()))) {
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
	hitbox.h = destR->h * 0.3;
	hitbox.w = destR->w * 0.4;
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
	hitbox.h = destR->h * 0.4;
	hitbox.w = destR->w * 0.7;
	if (attacker->getState()->IsCrouching())
		hitbox.y = destR->y + destR->h * 0.6;
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
	delete this;
}

void Punch::dealDMG() {
	attacked->drainHP(10);
	attacked->getState()->flipCanTakeDamage();
}

void Kick::dealDMG() {
	attacked->drainHP(20);
	attacked->getState()->flipCanTakeDamage();
}