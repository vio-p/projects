#include "ButtonTicTacToe.h"

ButtonTicTacToe::ButtonTicTacToe(const std::pair<int, int>& position, QWidget* parent) :
	QPushButton(parent), m_Position(position)
{
}

void ButtonTicTacToe::mouseReleaseEvent(QMouseEvent* event)
{
	QPushButton::mouseReleaseEvent(event);
	emit(tttClicked(m_Position));
}
