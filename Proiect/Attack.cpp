#include "Attack.h"

Attack::Attack(GameObject* player) : attacker(player)
{
	SDL_SetTextureColorMod(tex, 255, 0, 0); drawHitbox();
};

void Attack::drawHitbox() {
	SDL_Rect* destR = attacker->getDestRPointer();
	// get a red texture
	SDL_Surface* surface = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 255, 0, 0));
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::getRenderer(), surface);
	SDL_Rect hitbox;
	hitbox.y = destR->y;
	hitbox.h = destR->h * 0.3;
	hitbox.w = destR->w * 0.4;
	if (attacker->getState()->IsTurned()) {
		hitbox.x = destR->x - hitbox.w;
	}
	else 
		hitbox.x = destR->x + destR->w;
	
	SDL_RenderCopy(Game::getRenderer(), texture, NULL, &hitbox);
	delete this;
}