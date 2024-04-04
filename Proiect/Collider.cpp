#include "Collider.h"

Collider::Collider(GameObject* player) : destR(player->getDestRPointer()), position(player->getPosPointer()) {
	setPrevPos();
}

bool Collider::collision(const SDL_Rect& recA, const SDL_Rect& recB) {
	if (recA.x + recA.w > recB.x &&
		recB.x + recB.w > recA.x &&
		recA.y + recA.h > recB.y &&
		recB.y + recB.h > recA.y)
		return true;
	return false;
}

void Collider::setPrevPos() {
	prevState.x = destR->x;
	prevState.y = destR->y;
	prevState.w = destR->w;
	prevState.h = destR->h;
	prevPos = position;
}

void Collider::getPrevPos() const { 
	*destR = prevState; 
	*position = Vector2D(prevPos.getX(), prevPos.getY()); 
}

std::ostream& operator<<(std::ostream& out, const Collider& col) {
	out << col.collider.x << " ";
	out << col.collider.y << " ";
	out << col.collider.w << " ";
	out << col.collider.h << "\n";
	return out;
}