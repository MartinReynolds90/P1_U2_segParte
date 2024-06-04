#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Timer
{
private:
	Clock* clock_timer;
	Time* time_timer;
	Font font_timer;
	Text text_timer;
	String string_timer;
public:
	Timer();
	Timer(float,float);
};

