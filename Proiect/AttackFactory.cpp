#include "AttackFactory.h"

std::unique_ptr<Attack> PunchFactory::createAttack(GameObject* player, GameObject* enemy) const {
	std::unique_ptr<Attack> punch = std::make_unique<Punch>(player, enemy);
	return std::move(punch);
}

std::unique_ptr<Attack> KickFactory::createAttack(GameObject* player, GameObject* enemy) const {
	std::unique_ptr<Attack> kick = std::make_unique<Kick>(player, enemy);
	return std::move(kick);
}
