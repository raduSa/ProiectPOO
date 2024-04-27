#include "StateManager.h"

bool StateManager::countDown(int& x) {
	if (!x)
		return false;
	x--;
	if (x == 0)
		return true;
	return false;
}

StateManager::StateManager(bool isTurned) : isJumping(0), isCrouching(false), isAttacking(0), isHit(0),
isTurned(isTurned), isKicking(false), isPunching(false) {}

void StateManager::update() {
	isAirborne = false;
	countDown(isJumping);
	if (countDown(isAttacking)) {
		isPunching = false;
		isKicking = false;
		flipCanAct();
	}
	if (countDown(isHit)) {
		flipCanTakeDamage();
		flipCanAct();
	}
}

void StateManager::getsHit() {
	isHit = 5;
	canAct = false;
	isAttacking = 0;
}

std::ostream& operator<< (std::ostream& out, const StateManager& state) {
	out << "Jumping: " << state.isJumping << " ";
	out << "Airborne: " << state.isAirborne << " ";
	out << "Crouching: " << state.isCrouching << "\n";
	out << "Attacking: " << state.isAttacking << " ";
	out << "Turned around: " << state.isTurned << "\n";
	return out;
}