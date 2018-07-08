#include "Keyboard.h"

Keyboard Keyboard::m_keyboard;

Keyboard* Keyboard::getKeyboard()
{
	return &m_keyboard;
}
