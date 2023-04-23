#pragma once

#include "ICompPlayerStrategy.h"

class EasyCompPlayerStrategy: public ICompPlayerStrategy
{
public:
	EasyCompPlayerStrategy() = default;
	~EasyCompPlayerStrategy() override  = default;

	std::pair<int, int> PickPosition(const std::vector<std::vector<char>>& boardState) override;
};
