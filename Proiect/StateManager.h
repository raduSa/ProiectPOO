#pragma once
#include <iostream>
class StateManager {
	int isJumping;
	bool isCrouching;
	int isHit;
	int isAttacking;
	bool isPunching;
	bool isKicking;
	bool canAct = true;
	bool countDown(int& x);
	bool isAirborne;
	bool isTurned;
public:
	StateManager(bool);
	~StateManager() {}
	void update();
	void jump() { isJumping = 20; }
	void crouch() { isCrouching = true; }
	void attack() { isAttacking = 50; }
	void punch() { isPunching = true; isAttacking = 50; }
	void kick() { isKicking = true; isAttacking = 100; }
	void getsHit() { isHit = 10; }
	void airborne() { isAirborne = true; }
	void noCrouch() { isCrouching = false; }
	void flipCanAct() { canAct ^= 1; }
	void turn() { isTurned ^= 1; }
	bool CanAct() const { return canAct; }
	bool IsJumping() const { return bool(isJumping); }
	bool IsCrouching() const { return isCrouching; }
	bool IsAttacking() const { return isAttacking; }
	bool IsPunching() const { return isPunching; }
	bool IsKicking() const { return isKicking; }
	bool IsTurned() const { return isTurned; }
	friend std::ostream& operator<< (std::ostream& out, const StateManager& state);
};
