#include "Mouse.h"

#include <iostream>

Mouse Mouse::m_mouse;

void Mouse::update()
{
	m_px = m_x;
	m_py = m_y;
	m_x = m_fast_x;
	m_y = m_fast_y;
}

Mouse* Mouse::getMouse()
{
	return &m_mouse;
}

double Mouse::x()
{
	return m_x;
}

double Mouse::y()
{
	return m_y;
}

double Mouse::dx()
{
	return m_x - m_px;
}

double Mouse::dy()
{
	return m_y - m_py;
}

double Mouse::scrollX()
{
	return m_scroll_x;
}

double Mouse::scrollY()
{
	return m_scroll_y;
}

void Mouse::update_pos(double x, double y)
{
	m_fast_x = x;
	m_fast_y = y;
}

void Mouse::update_scroll(double x, double y)
{
	m_scroll_x += x;
	m_scroll_y += y;

	if (m_scroll_y >= 100.0)
		m_scroll_y = 100.0;
	if (m_scroll_y <= -100.0)
		m_scroll_y = -100.0;
}
