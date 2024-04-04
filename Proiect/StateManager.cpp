#include "StateManager.h"

void StateManager::update() {
	if (isJumping)
		isJumping--;
}

std::ostream& operator<< (std::ostream& out, const StateManager& state) {
	out << state.isJumping << " ";
	out << state.isCrouching << "\n";
	return out;
}