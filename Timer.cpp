#include "Timer.h"
#include "iostream"

using namespace std;

Timer::Timer(int tiempoJuego, float x,float y){ //reciBe como parametros el TIEMPO INICIAL y su POSICION EN PANTALLA
	tiempo_inicial = tiempoJuego;
	clock_timer = new Clock();
	time_timer = new Time();
	*time_timer = clock_timer->getElapsedTime();

	font_timer.loadFromFile("assets/Square.ttf");
	text_timer.setFont(font_timer);
	string_timer = " " + to_string(tiempo_inicial - static_cast<int>(time_timer->asSeconds()));
	text_timer.setString(string_timer);
	text_timer.setPosition(x,y);
	text_timer.setFillColor(Color::Black);

	
}
void Timer::actualizar_temp() {           //ACTUALIZA EL TIEMPO DEL TEMPORIZADOR EN SEGUNDOS
	*time_timer = clock_timer->getElapsedTime();
	string_timer = "Tiempo: " + to_string(tiempo_inicial - static_cast<int>(time_timer->asSeconds()));
	text_timer.setString(string_timer);
}
void Timer::penalizacion_time(bool descuento) {//DESCUENTA LOS SEGUNDOS CUANDO ES NECESARIO
	if (descuento == true)tiempo_inicial = tiempo_inicial - 10;
}

Text Timer::get_text() { //OBTIENE EL TEXTO PARA PODER DIBUJARLO
	return text_timer;
}
float Timer::get_time() {//DEVUELVE EL TIEMPO EN FLOAT CON LOS DESCUENTOS POR PENALIZACION HECHOS.
	return tiempo_inicial - time_timer->asSeconds();
}