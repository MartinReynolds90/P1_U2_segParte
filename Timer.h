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
	int cuenta_regresiva;
public:
	Timer();
	Timer(int, float, float);
	void actualizar_temp(); // toma el tiempo (de esta clase),lo transforma en string y se lo pasa al texto
	Text get_text();
	void penalizacion_time(bool);

};

