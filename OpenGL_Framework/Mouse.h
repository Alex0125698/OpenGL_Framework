#pragma once

class Mouse
{
public:
	double m_fast_x = 0.0, m_fast_y = 0.0;
	double m_x = 0.0, m_y = 0.0;
	double m_px = 0.0, m_py = 0.0;
	double m_scroll_x = 0.0, m_scroll_y = 0.0;
	bool m_pressed_left = false, m_pressed_right = false;

public:
	void update();
	static Mouse* getMouse();
	double x();
	double y();
	double dx();
	double dy();
	double scrollX();
	double scrollY();

private:
	Mouse() = default;
	static Mouse m_mouse;
	friend class MainWindow;
	void update_pos(double x, double y);
	void update_scroll(double x, double y);
};

