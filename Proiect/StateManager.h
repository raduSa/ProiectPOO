#pragma once
#include <iostream>
#include <unordered_map>

class StateManager {
	std::unordered_map<std::string, bool> states;
	int isJumping;
	int isHit;
	int isAttacking;
	bool countDown(int&);

public:
	StateManager(bool);
	~StateManager() {}
	void update();
	void jump();
	void crouch();
	void attack();
	void punch();
	void kick();
	void block();
	void getsHit();
	void airborne();
	void noCrouch();
	void noBlock();
	void flipCanAct();
	void flipCanTakeDamage();
	void turn();
	void WantsToStand();
	void DoesntWantToStand();
	void IsSquashed();
	void IsNotSquashed();
	bool CanAct() const;
	bool IsJumping() const;
	bool IsCrouching() const;
	bool IsAttacking() const;
	bool IsPunching() const;
	bool IsKicking() const;
	bool IsBlocking() const;
	bool IsTurned() const;
	bool IsAirborne() const;
	bool IsHit() const;
	bool CanTakeDamage() const;
	friend std::ostream& operator<< (std::ostream& out, const StateManager& state);
};
