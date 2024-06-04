#include "Timer.h"
#include "iostream"

using namespace std;

Timer::Timer(float x,float y){
	clock_timer = new Clock();
	time_timer = new Time();
	*time_timer = clock_timer->getElapsedTime();

	font_timer.loadFromFile("assets/Square.ttf");
	text_timer.setFont(font_timer);
	string_timer = " " + to_string(time_timer->asSeconds());
	text_timer.setString(string_timer);
	text_timer.setPosition(x,y);
	text_timer.setFillColor(Color::Black);

	
}