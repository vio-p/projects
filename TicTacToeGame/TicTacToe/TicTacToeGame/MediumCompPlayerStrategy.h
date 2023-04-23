#pragma once
#include <memory>

#include "EasyCompPlayerStrategy.h"
#include "HardCompPlayerStrategy.h"

class MediumCompPlayerStrategy: public ICompPlayerStrategy
{
public:
	std::shared_ptr<EasyCompPlayerStrategy> m_EasyCompPlayer;
	std::shared_ptr<HardCompPlayerStrategy> m_HardCompPlayer;

	MediumCompPlayerStrategy();
	~MediumCompPlayerStrategy() override = default;

	std::pair<int, int> PickPosition(const std::vector<std::vector<char>>& boardState) override;
};

