#include "MediumCompPlayerStrategy.h"
#include <random>

std::shared_ptr<ICompPlayerStrategy> ICompPlayerStrategy::Produce(EStrategyType strategyType)
{
	switch (strategyType)
	{
	case EStrategyType::Easy:
		return std::make_shared<EasyCompPlayerStrategy>();
	case EStrategyType::Medium:
		return std::make_shared<MediumCompPlayerStrategy>();
	case EStrategyType::Hard:
		return std::make_shared<HardCompPlayerStrategy>();
	default:
		break;
	}
}

MediumCompPlayerStrategy::MediumCompPlayerStrategy() :
	m_EasyCompPlayer(std::make_shared<EasyCompPlayerStrategy>()),
	m_HardCompPlayer(std::make_shared<HardCompPlayerStrategy>())
{}

std::pair<int, int> MediumCompPlayerStrategy::PickPosition(const std::vector<std::vector<char>>& boardState)
{
	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, 1);

	if (dist(rd) == 0)
	{
		return m_EasyCompPlayer->PickPosition(boardState);
	}
	else
	{
		return m_HardCompPlayer->PickPosition(boardState);
	}
}
