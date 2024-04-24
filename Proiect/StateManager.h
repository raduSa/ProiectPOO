#pragma once
#include <iostream>
class StateManager {
	int isJumping;
	bool isCrouching;
	int isHit;
	int isAttacking;
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
	void getsHit() { isHit = 10; }
	void airborne() { isAirborne = true; }
	void noCrouch() { isCrouching = false; }
	void flipCanAct() { canAct ^= 1; }
	void turn() { isTurned ^= 1; }
	bool CanAct() const { return canAct; }
	bool IsJumping() const { return bool(isJumping); }
	bool IsCrouching() const { return isCrouching; }
	bool IsAttacking() const { return isAttacking; }
	bool IsTurned() const { return isTurned; }
	friend std::ostream& operator<< (std::ostream& out, const StateManager& state);
};
