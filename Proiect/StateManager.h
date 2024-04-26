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
	bool isAirborne = false;
	bool isTurned;
	bool countDown(int& x);

public:
	StateManager(bool);
	~StateManager() {}
	void update();
	void jump() { isJumping = 20; }
	void crouch() { isCrouching = true; }
	void attack() { isAttacking = 50; }
	void punch() { isPunching = true; isAttacking = 10; }
	void kick() { isKicking = true; isAttacking = 20; }
	void getsHit();
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
	bool IsAirborne() const { return isAirborne; }
	bool IsHit() const { return isHit; }
	friend std::ostream& operator<< (std::ostream& out, const StateManager& state);
};
