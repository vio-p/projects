#pragma once

#include <vector>
#include <memory>

#include "EStrategyType.h"

/**
 * @brief This is the interface that defines the strategy used by the computer player when picking a position.
 */
class ICompPlayerStrategy
{
public:
    /**
     * @brief Default constructor.
     */
    ICompPlayerStrategy() = default;

    /**
     * @brief Default destructor.
     */
    virtual ~ICompPlayerStrategy() = default;

    /**
     * @brief This method produces a shared pointer to an instance of ICompPlayerStrategy based on the EStrategyType parameter.
     *
     * @param strategyType The predefined strategy.
     * @return A shared pointer to the new instance.
     */
    static std::shared_ptr<ICompPlayerStrategy> Produce(EStrategyType strategyType);

    /**
     * @brief This method returns the position picked by the computer player based on the current state of the board.
     *
     * @param board The current state of the board.
     * @return A pair representing the row and column indices of the picked position.
     */
    virtual std::pair<int, int> PickPosition(const std::vector<std::vector<char>>& boardState) = 0;
};
