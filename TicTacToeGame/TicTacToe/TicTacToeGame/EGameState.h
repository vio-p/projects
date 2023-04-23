#pragma once

/**
 * @brief This enum represents the possible states of the Tic-Tac-Toe game.
 */

enum class EGameState
{
    None, /**< The game is in an undefined state. */
    Ongoing, /**< The game is still in progress. */
    Win, /**< The game has been won by the player. */
    Loss, /**< The game has been lost by the player. */
    Draw /**< The game has ended in a draw. */
};
