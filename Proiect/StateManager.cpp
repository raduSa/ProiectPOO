#include "StateManager.h"

StateManager::StateManager() : isJumping(0), isCrouching(false), isAttacking(0), isHit(0) {}

void StateManager::update() {
	if (isJumping)
		isJumping--;
	if (isAttacking) {
		isAttacking--;
	}
	if (isHit) {
		isHit--;
	}
}

std::ostream& operator<< (std::ostream& out, const StateManager& state) {
	out << "Jumping: " << state.isJumping << " ";
	out << "Crouching: " << state.isCrouching << "\n";
	out << "Attacking: " << state.isAttacking << "\n";
	return out;
}