#include "StateManager.h"

bool StateManager::countDown(int& x) {
	if (!x)
		return false;
	x--;
	if (x == 0)
		return true;
	return false;
}

StateManager::StateManager(bool isTurned) : isJumping(0), isCrouching(false), isAttacking(0), isHit(0), isTurned(isTurned) {}

void StateManager::update() {
	countDown(isJumping);
	countDown(isHit);
	if (countDown(isAttacking)) {
		flipCanAct();
	}
}

std::ostream& operator<< (std::ostream& out, const StateManager& state) {
	out << "Jumping: " << state.isJumping << " ";
	out << "Crouching: " << state.isCrouching << "\n";
	out << "Attacking: " << state.isAttacking << " ";
	out << "Turned around: " << state.isTurned << "\n";
	return out;
}