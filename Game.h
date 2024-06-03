#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bloque.h"
#include "iostream"

using namespace sf;

class Game
{
	RenderWindow* w;
	Event* e;
	Clock* clock;
	Time* t;
	//Clock* clock_temporizador;
	//Time* time_temporizador;

	Player* player;

	Sprite* sp_fondo;   
	Texture* tx_fondo;
	int fps = 60;   

	Font font_temporizador;
	Text text_temporizador;
	String temporizador_string;

	Bloque* bloque1;
	Bloque* bloque2;
	Bloque* bloque3;
	Bloque* bloque4;
	Bloque* bloque5;
	Bloque* bloque6;
	Bloque* bloque7;
	Bloque* bloque8;
	Bloque* bloque9;
	Bloque* bloque10;
	Bloque* bloque[10];// = {bloque1,bloque2,bloque3,bloque4,bloque5,bloque6,bloque7,bloque8,bloque9,bloque10};*/;

public:
	Game();
	Game(int, int, String);
	void gameloop();   
	void dibujar();
	
};

