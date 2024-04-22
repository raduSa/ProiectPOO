#pragma once
#include <iostream>
class StateManager {
	int isJumping;
	bool isCrouching;
	int isHit;
	int isAttacking;
	bool canAttack = true;
public:
	StateManager();
	~StateManager() {}
	void update();
	void jump() { isJumping = 20; }
	void crouch() { isCrouching = true; }
	void attack() { isAttacking = 10; }
	void getsHit() { isHit = 10; }
	void noCrouch() { isCrouching = false; }
	void flipCanAttack() { canAttack ^= 1; }
	bool CanAttack() const { return canAttack; }
	bool IsJumping() const { return bool(isJumping); }
	bool IsCrouching() const { return isCrouching; }
	bool IsAttacking() const { return isAttacking; }
	friend std::ostream& operator<< (std::ostream& out, const StateManager& state);
};
