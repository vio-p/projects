#pragma once

#include <memory>
#include "ITicTacToeListener.h"
#include "ICompPlayerStrategy.h"

/**
 * @brief A shared pointer to an instance of ITicTacToeGame.
 */
using ITicTacToeGamePtr = std::shared_ptr<class ITicTacToeGame>;

/**
 * @brief This interface defines the behaviour of a basic Tic-Tac-Toe game.
 */
class ITicTacToeGame
{
public:
    /**
     * @brief Default constructor.
     */
    ITicTacToeGame() = default;

    /**
     * @brief Default destructor.
     */
    virtual ~ITicTacToeGame() = default;

    /**
     * @brief This method produces a shared pointer to an instance of ITicTacToeGame.
     * @return A shared pointer to the new instance.
     */
    static ITicTacToeGamePtr Produce();

    /**
     * @brief Adds a listener to the game.
     * @param listener A pointer to ITicTacToeListener, the listener added to the game.
     */
    virtual void AddListener(ITicTacToeListener* listener) = 0;

    /**
     * @brief Removes a listener from the game.
     * @param listener A pointer to ITicTacToeListener, the listener removed from the game.
     */
    virtual void RemoveListener(ITicTacToeListener* listener) = 0;

    /**
     * @brief Sets the computer player strategy.
     * @param compPlayerStrategy A shared pointer to an instance of ICompPlayerStrategy.
     */
    virtual void SetCompPlayerStrategy(const std::shared_ptr<ICompPlayerStrategy>& compPlayerStrategy) = 0;

    /**
     * @brief Resets the game.
     */
    virtual void Reset() = 0;

    /**
     * @brief Makes a move in the game.
     * @param x The x-coordinate of the position picked by the player.
     * @param y The y-coordinate of the position picked by the player.
     */
    virtual void MakeMove(int x, int y) = 0;
};
