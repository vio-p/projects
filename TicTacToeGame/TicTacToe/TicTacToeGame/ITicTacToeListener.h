#pragma once

#include <stdexcept>
#include <vector>

#include "EGameState.h"

/**
 * @brief This interface defines the behaviour of a Tic-Tac-Toe game listener.
 */
class ITicTacToeListener
{
public:
    /**
     * @brief Default constructor.
     */
    ITicTacToeListener() = default;

    /**
     * @brief Default destructor.
     */
    virtual ~ITicTacToeListener() = default;

    /**
     * @brief This method is called when the board changes during the game.
     *
     * @param board The current state of the board.
     */
    virtual void OnBoardChanged(const std::vector<std::vector<char>>& boardState) = 0;

    /**
     * @brief This method is called when the game is over.
     *
     * @param gameState The state of the game (Win/Loss/Draw) when the method is called.
     */
    virtual void OnGameOver(EGameState gameState) = 0;

    /**
     * @brief This method is called when an exception is raised during the game.
     *
     * @param exception The exception that was raised.
     */
    virtual void OnExceptionRaised(const std::exception& exception) = 0;
};
