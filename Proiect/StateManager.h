#pragma once
#include <iostream>
class StateManager {
	int isJumping;
	bool isCrouching;
	//int isHit;
	//int isAttacking;
public:
	StateManager() : isJumping(0), isCrouching(false) {}
	~StateManager() {}
	void update();
	void jump() { isJumping = 20; }
	void crouch() { isCrouching = true; }
	void noCrouch() { isCrouching = false; }
	bool IsJumping() const { return bool(isJumping); }
	bool IsCrouching() const { return isCrouching; }
	friend std::ostream& operator<< (std::ostream& out, const StateManager& state);
};
