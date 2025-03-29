#include "Collider.h"

Collider::Collider(GameObject* player) : destR(player->getDestRPointer()), position(player->getPosPointer()), 
	dimensions(player->getDimPointer()) {
	setPrevPos();
}

void Collider::setPrevPos() {
	prevState.x = destR->x;
	prevState.y = destR->y;
	prevState.w = destR->w;
	prevState.h = destR->h;
	prevPos = position;
	prevDim = dimensions;
}

void Collider::getPrevPos() const { 
	*destR = prevState; 
	*position = prevPos; 
	*dimensions = prevDim;
}