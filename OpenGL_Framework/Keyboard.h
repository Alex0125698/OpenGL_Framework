#pragma once
class Keyboard
{
private:
	static Keyboard m_keyboard;
public:
	static Keyboard* getKeyboard();
	bool keys[2048];
};

