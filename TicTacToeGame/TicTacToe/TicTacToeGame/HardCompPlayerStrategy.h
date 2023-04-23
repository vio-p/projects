#pragma once
#include "ICompPlayerStrategy.h"
#include "Board.h"

class HardCompPlayerStrategy: public ICompPlayerStrategy
{
public:
	HardCompPlayerStrategy() = default;
	~HardCompPlayerStrategy() override = default;
	std::pair<int, int> PickPosition(const std::vector<std::vector<char>>& boardState) override;

private:
	std::pair<std::pair<int,int>, int> Minimax(const Board& board, int level) const;
};
