#include "StateManager.h"

bool StateManager::countDown(int& x) {
	if (!x)
		return false;
	x--;
	if (x == 0)
		return true;
	return false;
}

StateManager::StateManager(bool isTurned) : isJumping(0), isAttacking(0), isHit(0) {
	states["isCrouching"] = false;
	states["isKicking"] = false;
	states["isPunching"] = false;
	states["isBlocking"] = false;
	states["canAct"] = true;
	states["isAirborne"] = false;
	states["isTurned"] = isTurned;
	states["canTakeDamage"] = true;
	states["wantsToStand"] = false;
	states["isSquashed"] = false;
}

void StateManager::update() {
	states["isAirborne"] = false;
	countDown(isJumping);
	if (countDown(isAttacking)) {
		states["isPunching"] = false;
		states["isKicking"] = false;
		flipCanAct();
	}
	if (countDown(isHit)) {
		flipCanTakeDamage();
		flipCanAct();
	}
	if (states["wantsToStand"] && !states["isSquashed"] && states["canAct"]) {
		states["isCrouching"] = false;
		states["wantsToStand"] = false;
	}
}

void StateManager::getsHit() {
	isHit = 5;
	states["canAct"] = false;
	isAttacking = 0;
}

void StateManager::jump() { isJumping = 20; }
void StateManager::crouch() { states["isCrouching"] = true; }
void StateManager::attack() { isAttacking = 50; }
void StateManager::punch() { states["isPunching"] = true; isAttacking = 10; }
void StateManager::kick() { states["isKicking"] = true; isAttacking = 20; }
void StateManager::block() { states["isBlocking"] = true; }
void StateManager::airborne() { states["isAirborne"] = true; }
void StateManager::noCrouch() { states["isCrouching"] = false; }
void StateManager::noBlock() { states["isBlocking"] = false; }
void StateManager::flipCanAct() { states["canAct"] ^= 1; }
void StateManager::flipCanTakeDamage() { states["canTakeDamage"] ^= 1; }
void StateManager::turn() { states["isTurned"] ^= 1; }
void StateManager::WantsToStand() { states["wantsToStand"] = true; }
void StateManager::DoesntWantToStand() { states["wantsToStand"] = false; }
void StateManager::IsSquashed() { states["isSquashed"] = true; }
void StateManager::IsNotSquashed() { states["isSquashed"] = false; }
bool StateManager::CanAct() const { return states.at("canAct"); }
bool StateManager::IsJumping() const { return bool(isJumping); }
bool StateManager::IsCrouching() const { return states.at("isCrouching"); }
bool StateManager::IsAttacking() const { return isAttacking; }
bool StateManager::IsPunching() const { return states.at("isPunching"); }
bool StateManager::IsKicking() const { return states.at("isKicking"); }
bool StateManager::IsBlocking() const { return states.at("isBlocking"); }
bool StateManager::IsTurned() const { return states.at("isTurned"); }
bool StateManager::IsAirborne() const { return states.at("isAirborne"); }
bool StateManager::IsHit() const { return isHit; }
bool StateManager::CanTakeDamage() const { return states.at("canTakeDamage"); }

std::ostream& operator<< (std::ostream& out, const StateManager& state) {
	out << "Jumping: " << state.isJumping << " ";
	out << "Airborne: " << state.states.at("isAirborne") << " ";
	out << "Crouching: " << state.states.at("isCrouching") << "\n";
	out << "Attacking: " << state.isAttacking << " ";
	out << "Turned around: " << state.states.at("isTurned") << "\n";
	out << "Blocking: " << state.states.at("isBlocking") << "\n";
	return out;
}