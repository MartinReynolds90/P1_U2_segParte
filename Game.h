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
	float inicial_y;
	float inicial_x;
	Player* player;
	Bloque* bloque[10];
	Sprite* sp_fondo;
	Texture* tx_fondo;
	int fps = 60;
public:
	Game();
	Game(int, int, String);
	void gameloop();
	void dibujar();
};

