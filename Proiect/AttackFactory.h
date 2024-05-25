#pragma once
#include "Attack.h"
#include <memory>

class Attack;

class AttackFactory {
public:
	virtual std::unique_ptr<Attack> createAttack(GameObject*, GameObject*) const = 0;
	virtual ~AttackFactory() = default;
};

class PunchFactory : public AttackFactory {
public:
	std::unique_ptr<Attack> createAttack(GameObject*, GameObject*) const;
	~PunchFactory() = default;
};

class KickFactory : public AttackFactory {
public:
	std::unique_ptr<Attack> createAttack(GameObject*, GameObject*) const;
	~KickFactory() = default;
};
